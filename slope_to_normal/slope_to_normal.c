#define PROG_NAME "slope_to_normal"
#define PROG_DESC "convert a FNI slope map image to a FNI normal map image"
#define PROG_VERS "1.0"

/* Copyright © 2006 by the State University of Campinas (UNICAMP). */
/* See the copyright, authorship, and warranty notice at end of file. */
/* Last edited on 2015-10-18 02:59:16 by stolfilocal */

#define PROG_HELP \
  "  " PROG_NAME " \\\n" \
  "    [ -maxSlope {NUM} ] \\\n" \
  "    " argparser_help_info_HELP " \\\n" \
  "    < {INFILE} \\\n" \
  "    > {OUTFILE}"

#define PROG_INFO \
  "NAME\n" \
  "  " PROG_NAME " - " PROG_DESC "\n" \
  "\n" \
  "SYNOPSIS\n" \
  PROG_HELP "\n" \
  "\n" \
  "DESCRIPTION\n" \
  "  The program reads a two-channel image where the two samples" \
  " in column {x} and row {y} are the slopes {dZ/dX} and {dZ/dY}" \
  " of some height field {Z(X,Y)}.  The program writes a three-channel" \
  " image, with the same dimensions, where those slopes have been" \
  " converted to the X, Y, and Z components of the corresponding" \
  " outwards-pointing unit normal vector.\n" \
  "\n" \
  "  Input and output files are in the multichannel float-valued" \
  " image (FNI) format.  See {float_image.h} for details.\n" \
  "\n" \
  "OPTIONS\n" \
  "  None so far.\n" \
  "\n" \
  argparser_help_info_HELP_INFO "\n" \
  "\n" \
  "SEE ALSO\n" \
  "  fni_to_pnm(1), pnm_to_fni(1), fni_plot(1), normal_to_slope(1)," \
  " slope_to_height(1).\n" \
  "\n" \
  "AUTHOR\n" \
  "  Created 2006-04-07 by Jorge Stolfi, UNICAMP."

#define stringify(x) strngf(x)
#define strngf(x) #x

#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#include <argparser.h>
#include <float_image.h>

#include <pst_normal_map.h>

/* COMMAND-LINE OPTIONS */

typedef struct options_t
  { 
  } options_t;

/* 
  INTERNAL PROTOTYPES
  
  Keep in mind that row 0 of a {float_image_t} is the BOTTOM 
  scanline of the image. */

options_t *parse_options(int argc, char **argv);
  /* Parses the command line arguments and packs them as an {options_t}. */

int main(int argc,char** argv);

/* IMPLEMENTATIONS */

int main(int argc, char** argv)
  { options_t *o = parse_options(argc, argv);
    float_image_t *IDZ = float_image_read(stdin);
    float_image_t *IN = pst_normal_map_from_slope_map(IDZ);
    float_image_write(stdout, IN);
    fflush(stdout);
    free(o);
    return 0;
  }

options_t *parse_options(int argc, char **argv)
  {
    argparser_t *pp = argparser_new(stderr, argc, argv);
    argparser_set_help(pp, PROG_NAME " version " PROG_VERS ", usage:\n" PROG_HELP);
    argparser_set_info(pp, PROG_INFO);
    argparser_process_help_info_options(pp);
    
    options_t *o = (options_t *)malloc(sizeof(options_t)); 
      
    argparser_finish(pp);
    
    return o;
  }

/* COPYRIGHT, AUTHORSHIP, AND WARRANTY NOTICE:
** 
**   Copyright © 2006 by the State University of Campinas (UNICAMP).
**
** Permission to use, copy, modify, and redistribute this software and
** its documentation for any purpose and without fee is hereby
** granted, provided that: (1) the copyright notice at the top of this
** file and this copyright, authorship, and warranty notice is retained
** in all derived source files and documentation; (2) no executable
** code derived from this file is published or distributed without the
** corresponding source code; and (3) these same rights are granted to
** any recipient of such code, under the same conditions.
** This software is provided "as is", WITHOUT ANY EXPLICIT OR IMPLICIT
** WARRANTIES, not even the implied warranties of merchantibility and
** fitness for a particular purpose. END OF NOTICE.
*/
