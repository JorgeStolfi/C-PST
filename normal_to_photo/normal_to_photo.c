#define PROG_NAME "normal_to_photo"
#define PROG_DESC "make a synthetic photo from a normal map and light field"
#define PROG_VERS "1.0"

/* Copyright © 2006 by the State University of Campinas (UNICAMP). */
/* See the copyright, authorship, and warranty notice at end of file. */
/* Last edited on 2006-05-02 15:17:16 by stolfi */

#define PROG_HELP \
  "  " PROG_NAME " \\\n" \
  "    [ -channels {NC} ] \\\n" \
  "    " pst_light_spec_HELP " \\\n" \
  "    " argparser_help_info_HELP " \\\n" \
  "    < NORMALS.fni\\\n" \
  "    > PHOTO.fni "

#define PROG_INFO \
  "NAME\n" \
  "  " PROG_NAME " - " PROG_DESC "\n" \
  "\n" \
  "SYNOPSIS\n" \
  PROG_HELP "\n" \
  "\n" \
  "DESCRIPTION\n" \
  "  Reads from {stdin} the normal map of some scene. Writes" \
  " to {stdout} a simulated photograph of that scene under a" \
  " set of distant round lamps with specified positions," \
  " angular radii, and colors (including ambient" \
  " light and diffuse light from bright floors or walls).\n" \
  "\n" \
  "  The program assumes a white Lambertian surface.  The color" \
  " of a lamp is defined as the apparent color it produces on" \
  " such a surface, when the lamp's direction coincides with the" \
  " surface normal.  The output image will have as many channels" \
  " as the lamps.\n" \
  "\n" \
  "  The program does not compute projected shadows, only proper" \
  " shadows.\n" \
  "\n" \
  "LIGHT FIELD MODEL\n" \
  pst_light_model_INFO "\n" \
  "\n" \
  "  The input and output files is in the FNI format. See" \
  " {float_image.h} for details.\n" \
  "\n" \
  "OPTIONS\n" \
  "  -channels {NC}\n" \
  "    Specifies the number {NC} of color channels in the output" \
  " image.  The number must be positive. Defaults to 1.\n" \
  "\n" \
  "LIGHT FIELD OPTIONS\n" \
  pst_light_spec_HELP_INFO "\n" \
  "\n" \
  "DOCUMENTATION OPTIONS\n" \
  argparser_help_info_HELP_INFO "\n" \
  "\n" \
  "SEE ALSO\n" \
  "  fni_to_pnm(1), pnm_to_fni(1), slope_to_height(1)\n" \
  "\n" \
  "AUTHOR\n" \
  "  Created 2006-04-07 by Jorge Stolfi, UNICAMP."

#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>

#include <argparser.h>

#include <pst_basic.h>
#include <pst_lamp.h>
#include <pst_shading.h>

/* COMMAND-LINE OPTIONS */

typedef struct options_t
  { int NC;            /* Number of color channels. */
    pst_light_t lht;   /* Light field description. */
  } options_t;

/* INTERNAL PROTOTYPES */

options_t *parse_options(int argc, char **argv);
  /* Parses the command line arguments and packs them as an {options_t}. */

int main(int argc,char** argv);

/* IMPLEMENTATIONS */

int main(int argc, char** argv)
  {
    options_t *o = parse_options(argc, argv);

    /* Read normals image: */
    float_image_t *NRM = float_image_read(stdin);
    
    demand(NRM->sz[0] == 3, "normal map must have 3 channels"); 
    
    int NC = o->NC;      /* Number of channels. */
    int NX = NRM->sz[1]; /* Number of columns. */
    int NY = NRM->sz[2]; /* Number of rows. */
    
    /* Create output image: */
    float_image_t *IMG = float_image_new(NC, NX, NY);
    float_image_fill(IMG, 0.0);
    pst_shading_add_diffuse(NRM, NULL, &(o->lht), IMG);
    float_image_write(stdout, IMG);
    return 0;
  }

options_t *parse_options(int argc, char **argv)
  {
    argparser_t *pp = argparser_new(stderr, argc, argv);
    argparser_set_help(pp, PROG_NAME " version " PROG_VERS ", usage:\n" PROG_HELP);
    argparser_set_info(pp, PROG_INFO);
    argparser_process_help_info_options(pp);
    
    options_t *o = (options_t *)malloc(sizeof(options_t)); 
    
    if (argparser_keyword_present(pp, "-channels"))
      { o->NC = argparser_get_next_int(pp, 1, float_image_max_size); }
    else
      { o->NC = -1; }

    o->lht = pst_light_spec_parse(pp, FALSE, &(o->NC));
    
    /* If the user did not set the number of channels, set it to 1: */
    if (o->NC < 0) { o->NC = 1; }

    /* Make sure all lamps have {o->NC} channels: */
    pst_light_regularize_channels(&(o->lht), o->NC);

    /* Check for leftover arguments: */
    argparser_finish(pp);
    
    return o;
  }

/* COPYRIGHT, AUTHORSHIP, AND WARRANTY NOTICE:
** 
**   Copyright © 2006 by the State University of Campinas (UNICAMP).
**
** Created on 2006-04-07 by Jorge Stolfi, IC-UNICAMP.       
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
