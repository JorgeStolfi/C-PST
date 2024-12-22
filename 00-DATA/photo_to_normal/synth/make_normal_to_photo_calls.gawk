#! /usr/bin/gawk -f
# Last edited on 2006-04-28 23:40:36 by stolfi

BEGIN \
  {
    PROG_NAME = "make-normal_to_photo-calls";
    PROG_DESC = "create a list of calls to normal_to_photo(1)";
    PROG_HELP = \
      PROG_NAME " \\\n" \
      "    -v NF={NUMBER} \\\n" \
      "    -v NS={NUMBER} \\\n" \
      "    -v NC={NUMBER} \\\n" \
      "    -v IN={NAME} \\\n" \
      "    -v OT={NAME} \\\n" \
      "    > NORMALS.fni" ;
    PROG_INFO = \
      "NAME\n" \
      "  " PROG_NAME " - " PROG_DESC ".\n" \
      "\n" \
      "SYNOPSIS\n" \
      "  " PROG_HELP "\n" \
      "\n" \
      "DESCRIPTION\n" \
      "  Writes to {stdout} a set of calls to normal_to_photo(1)\n" \
      " that generate a set of {NF} synthetic photos of a scene from a\n" \
      " normal map of the same.  Each photo assumes a distinct simulated\n" \
      " light field.  Each field has {NS} lamps in\n" \
      " varied positions.  The photos have {NC} channels.\n" \
      "\n" \
      "  The input normal map is read from file \"{IN}-nrm.fni\". The\n" \
      " output files are called \"{OT}-0.fni\", .. \"{OT}-{NF}.fni\".\n" \
      "\n" \
      "  The input and output files is in the FNI format. See\n" \
      " {float_image.h} for details.\n" \
      "\n" \
      "AUTHOR\n" \
      "  Created 2006-04-07 by Jorge Stolfi, Unicamp" ;

    abort = -1;
    if (NF == "") { arg_error(("must define \"NF\"")); }
    if (NC == "") { arg_error(("must define \"NC\"")); }
    if (NS == "") { arg_error(("must define \"NS\"")); }
    if (IN == "") { arg_error(("must define \"IN\"")); }
    if (OT == "") { arg_error(("must define \"OT\"")); }

    NF += 0;
    if ((NF < 3) || (NF > 9)) { arg_error(("invalid \"NF\" = " NF "")); }

    NS += 0;
    if ((NS < 1) || (NS > 3)) { arg_error(("invalid \"NS\" = " NS "")); }

    NC += 0;
    if ((NC < 1) || (NC > 6)) { arg_error(("invalid \"NC\" = " NC "")); }

    # Squaring the circle:
    PI = 3.1415926;
    
    # Total number of lamps: 
    NT = NS*NF;

    # Number of lamp rings {NR} and number of main lamps per ring {KR}:
    NR = (NF <= 4 ? 1 : 2);
    KR = int((NF + NR - 1)/NR);
    for (i = 0; i < NF; i++)
      { # Write command:
        printf "normal_to_photo \\\n";
        # Compute index {r} of lamp ring and index {p} in ring of main lamp:
        r = int(i/KR);
        p = i % KR;
        # Compute number {nr} of main lamps in this lamp ring:
        nr = (r == NR-1 ? NF - r*KR : KR);
        # Compute azimuth {az} and elevation {el} of main lamp (degrees):
        az = p*360/nr
        el = 20 + (80-20)*(r + 0.5)/NR;
        for (s = 0; s < NS; s++)
          { # Write azimuth {azs} and elevation {els} of lamp {s}:
            if (s == 0) 
              { azs = az; els = el; }
            else if (s == 1)
              { azs = az + 60; els = (el + 80)/2; }
            else
              { azs = az - 45; els = (el + 20)/2; }
            printf "  -v lamp%d='%.1f,%.1f", s+1, azs, els;
            # Compute overall intensity {pws} of lamp {s}: 
            pws = ipow(2,NS-1-s)/(ipow(2,NS) - 1);
            # Compute index of this lamp among all lamps:
            t = i*NS + s;
            for (c = 0; c < NC; c++)
              { # Write intensity {pwsc} of lamp {s} in channel {c}: 
                pwsc = pws*(1.0 + cos(c*t*PI/NT))/2;
                printf ",%5.3f", pwsc;
              }
            printf "' \\\n"
          }
        # Write input and output file names:
        printf "  < %s-nrm.fni \\\n", IN;
        printf "  > %s-%d.fni\n", OT, i;
        # Write command that converts to PPM:
        printf "fni_to_pnm \\\n";
        if (NC == 1)
          { printf "  -channel 0 \\\n";
            printf "  < %s-%d.fni \\\n", OT, i;
            printf "  > %s-%d.pgm\n", OT, i;
          }
        else
          { printf "  -channels 0 1 %d \\\n", (NC == 2 ? 0 : 2);
            printf "  < %s-%d.fni \\\n", OT, i;
            printf "  > %s-%d.ppm\n", OT, i;
          }
      }
  }

function ipow(b,e,  p,i)
  { p = 1;
    for (i = 0; i < e; i++) { p *= b; }
    return p;
  }

(abort >= 0) { exit abort; }

function arg_error(msg)
  { printf "%s: ** %s\n", PROG_NAME, msg > "/dev/stderr";
    printf "usage: %s\n", PROG_HELP > "/dev/stderr"
    abort = 1; exit abort; 
  }

function data_error(msg)
  { printf "%s:%d: %s: ** %s\n", FILENAME, FNR, PROG_NAME, msg > "/dev/stderr";
    abort = 1; exit abort; 
  }
