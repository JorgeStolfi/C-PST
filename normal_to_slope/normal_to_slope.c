#define PROG_NAME "normal_to_slope"
#define PROG_DESC "convert a FNI normal map image to a FNI slope map image"
#define PROG_VERS "1.0"

/* Copyright © 2006 by the State University of Campinas (UNICAMP). */
/* See the copyright, authorship, and warranty notice at end of file. */
/* Last edited on 2015-10-18 02:58:46 by stolfilocal */

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
  "  The program reads a three-channel image where the" \
  " three samples in column {x} and row {y} are the X, Y, and Z" \
  " components of a normal vector.  The program writes a two-channel" \
  " image, with the same dimensions, where those normal vectors" \
  " have been converted to slopes {dZ/dX} and {dZ/dY}.\n" \
  "\n" \
  "  Input and output files are in the multichannel float-valued" \
  " image (FNI) format.  See {float_image.h} for details.\n" \
  "\n" \
  "  If the normal is close to horizontal or pointing downwards," \
  " the slopes are clipped so that the total slope is equal to a" \
  " fixed maximum value,  the Z component points up, and the" \
  " horizontal direction of the normal is preserved.\n" \
  "\n" \
  "OPTIONS\n" \
  "  -maxSlope {NUM}\n" \
  "    Limits the maximum slope in any direction to {NUM}" \
  " (default " stringify(default_maxSlope) ").\n" \
  "\n" \
  argparser_help_info_HELP_INFO "\n" \
  "\n" \
  "SEE ALSO\n" \
  "  fni_to_pnm(1), pnm_to_fni(1), fni_plot(1), slope_to_normal(1)," \
  " slope_to_height(1).\n" \
  "\n" \
  "AUTHOR\n" \
  "  Created 2005-11-27 by Jorge Stolfi, UNICAMP."

#define stringify(x) strngf(x)
#define strngf(x) #x

#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#include <argparser.h>
#include <float_image.h>

#include <pst_basic.h>
#include <pst_normal_map.h>

/* COMMAND-LINE OPTIONS */

typedef struct options_t
  { double maxSlope;   /* Maximum allowed slope in any direction. */
  } options_t;

#define default_maxSlope 100

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
    float_image_t *IN = float_image_read(stdin);
    float_image_t *IDZ = pst_normal_map_to_slope_map(IN, o->maxSlope);
    float_image_write(stdout, IDZ);
    fflush(stdout);
    return 0;
  }

options_t *parse_options(int argc, char **argv)
  {
    argparser_t *pp = argparser_new(stderr, argc, argv);
    argparser_set_help(pp, PROG_NAME " version " PROG_VERS ", usage:\n" PROG_HELP);
    argparser_set_info(pp, PROG_INFO);
    argparser_process_help_info_options(pp);
    
    options_t *o = (options_t *)malloc(sizeof(options_t)); 
      
    if (argparser_keyword_present(pp, "-maxSlope"))
      { o->maxSlope = argparser_get_next_double(pp, 1.0e-100, 1.0e+100); }
    else
      { o->maxSlope = default_maxSlope; }
    
    argparser_finish(pp);
    
    return o;
  }

/* COPYRIGHT, AUTHORSHIP, AND WARRANTY NOTICE:
** 
**   Copyright © 2005 by the State University of Campinas (UNICAMP).
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
