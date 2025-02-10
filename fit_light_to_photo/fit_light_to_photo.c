#define PROG_NAME "fit_light_to_photo"
#define PROG_DESC "determine light field parameters given a photo and a normal map"
#define PROG_VERS "1.0"

/* Copyright © 2004 by the Fluminense Federal University (UFF).*/
/* See the copyright, authorship, and warranty notice at end of file.*/
/* Last edited on 2025-01-18 13:03:31 by stolfi */

#define PROG_HELP \
  PROG_NAME "\\\n" \
  "    -image {ACTUAL_FNI} \\\n" \
  "    -normal {NORMALS_FNI} \\\n" \
  "    " pst_light_spec_HELP " \\\n" \
  "    [ -adjustDir {INDEX} {DIRSTEP} ] \\\n" \
  "    [ " pst_fit_light_parse_weightBias_HELP " ] \\\n" \
  "    [ " pst_fit_light_parse_minNormalZ_HELP " ] \\\n" \
  "    [ " pst_fit_light_parse_iterations_HELP " ] \\\n" \
  "    [ " pst_fit_light_parse_tolerance_HELP " ] \\\n" \
  "    [ -showLights ] \\\n" \
  "    -outPrefix {PREFIX} \\\n" \
  "    " argparser_help_info_HELP

#define PROG_INFO \
  "NAME\n" \
  "  " PROG_NAME " - " PROG_DESC ".\n" \
  "\n" \
  "SYNOPSIS\n" \
  "  " PROG_HELP "\n" \
  "\n" \
  "DESCRIPTION\n" \
  "  Reads from file \"{ACTUAL_FNI}\" a monochromatic photograph" \
  " of some object, and from \"{NORMALS_FNI}\" the normal" \
  " map (actual or modeled) of the same object.  Estimates" \
  " a light field that best fits the appearance of the" \
  " object in the photo." \
  "\n" \
  "  The program writes to the text file \"{PREFIX}-light.parms\"" \
  " a description of the fitted light light field," \
  " and to file \"{PREFIX}-fit.fni\"" \
  " a synthetic photo of the object derived from the normal map and" \
  " that light field.  It also writes to file" \
  " \"{PREFIX}-dif.fni\" the difference between" \
  " the actual and fitted images, and to file \"{PREFIX}-msk.fni\"" \
  " the weight mask used for light fitting.\n" \
  "\n" \
  "  The actual object is assumed to have a mostly uniform color and" \
  " mostly matte (Lambertian) finish.  The" \
  " synthetic photo assumes perfectly uniform color" \
  " and perfectly Lambertian finish.\n" \
  "\n" \
  "  This program is useful for smoothing photographs of" \
  " imperfect light field gauges (marred by dents, scratches, stains," \
  " etc.).  For that purpose, the input normal map should be that" \
  " of a smooth ideal gauge.  The resulting /virtual gauge/ photo" \
  " is likely to produce better results than the actual photo" \
  " when used with {photo_to_normal}.\n" \
  "\n" \
  "  All input and output files are in the FNI format. See" \
  " {float_image.h} for details.\n" \
  "\n" \
  "LIGHT FIELD MODEL\n" \
  "  " pst_light_model_INFO "\n" \
  "  " pst_fit_light_model_INFO "\n" \
  "  " pst_fit_light_model_uniform_INFO "\n" \
  "\n" \
  "LIGHT SOURCE MODEL\n" \
  "  " pst_lamp_model_INFO "\n" \
  "\n" \
  "SCENE SURFACE MODEL\n" \
  "  " pst_shading_Lambertian_INFO "\n" \
  "  The diffusion"\
  " coefficient is assumed to be 1. If that is not the case,"\
  " the fitted lamp intensities will be multiplied by"\
  " the scene's actual diffusion coefficient.\n" \
  "\n" \
  "INTENSITY FITTING ALGORITHM\n" \
  "  " pst_fit_light_multi_INFO "\n" \
  "\n" \
  "DIRECTION FITTING ALGORITHM\n" \
  "  If the user requests adjustment of the direction of some" \
  " light source, the program uses a special method to estimate" \
  " the lamp's direction.\n" \
  pst_fit_light_single_iterative_INFO "\n" \
  pst_fit_light_single_iterative_dark_weight_INFO "\n" \
  "\n" \
  "FITTING REGION\n" \
  "  " pst_fit_light_valid_pixels_INFO "\n" \
  "  " pst_fit_light_steep_parts_INFO"\n" \
  "\n" \
  "GENERAL OPTIONS\n" \
  "  -image {ACTUAL_FNI} \n" \
  "    Specifies the name of the files containing" \
  " the actual photo of the scene. If the argument is \"-\", the" \
  " normal map is read from {stdin}.  The image must be monochromatic" \
  " and in the FNI format.  This parameter is mandatory.\n" \
  "\n" \
  "  -normal {NORMAL_FNI} \n" \
  "    Specifies the name of the image file containing the" \
  " normal map of the gauge. If the argument is \"-\", the" \
  " normal map is read from {stdin}, after the actual" \
  " photo.  This parameter is mandatory.\n" \
  "\n" \
  "  -showLights \n" \
  "    If present, this parameter causes the light model" \
  " to be printed to standard error output at various" \
  " moments during the fitting.\n" \
  "\n" \
  "LIGHT FIELD OPTIONS\n" \
  pst_light_spec_HELP_INFO "\n" \
  "\n" \
  "OPTIONS FOR THE LIGHT FITTING PROCEDURE\n" \
  "  -adjustDir {INDEX} {DIRSTEP}\n" \
  "    Specifies that the program should try to optimize the" \
  " direction of lamp number {INDEX} (counting from 0), using" \
  " the iterative procedure described above.  At each" \
  " iteration, the lamp's direction will be allowed to" \
  " change by {DIRSTEP} radians at most.  The default" \
  " is not to do any adjustment of the lamp directions.\n" \
  "\n" \
  pst_fit_light_parse_weightBias_HELP_INFO "  The default is to" \
  " use the same weight (1.0) for all valid pixels.\n" \
  "\n" \
  pst_fit_light_parse_minNormalZ_HELP_INFO "  The default is" \
  " \"-1.0\", that is, no pixels are excluded by this criterion.\n" \
  "\n" \
  pst_fit_light_parse_iterations_HELP_INFO "  The default is" \
  " " stringify(flp_default_iterations) " .\n" \
  "\n" \
  pst_fit_light_parse_tolerance_HELP_INFO "  The" \
  " default is " stringify(flp_default_tolerance) ".\n" \
  "\n" \
  "  -outPrefix {PREFIX}\n" \
  "    Specifies the common prefix for all output file" \
  " names. This parameter is mandatory.\n" \
  "\n" \
  "DOCUMENTATION OPTIONS\n" \
  argparser_help_info_HELP_INFO "\n" \
  "\n" \
  "SEE ALSO\n" \
  "  make_sphere_normal_map(1), photo_to_normal(1)," \
  " normal_to_slope(1), slope_to_height(1)," \
  " slope-to-norma(1), pnm_to_fni(1), fni_to_pnm(1).\n" \
  "\n" \
  "AUTHOR\n" \
  "  Created on jul/2005 by Rafael Saracchini, IC-UFF.\n" \
  "  Modified by Jorge Stolfi, mar/2006:\n" \
  "    * Moved computation of the ideal normal map to a" \
  "      separate program {make_sphere_normal_map(1)}.\n" \
  "    * Added iterative mask computation."

#define stringify(x) strngf(x)
#define strngf(x) #x

#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <values.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <float_image.h>
#include <r3.h> 
#include <r4.h> 
#include <vec.h>
#include <affirm.h>
#include <jsfile.h>
#include <argparser.h>

#include <pst_basic.h>
#include <pst_lamp.h>
#include <pst_light.h>
#include <pst_normal_map.h>
#include <pst_shading.h>
#include <pst_fit_light.h>

typedef struct options_t
  { char *image;       /* Name of the FNI file with the gauge's actual photo. */
    char *outPrefix;   /* Prefix for output name files. */
    char *normal;      /* Name of the FNI file with the gauge's normal map. */
    bool_t showLights; /* TRUE prints the light model at seeral stages. */
    /* Light field model: */
    pst_light_t lht;   /* Light model spec (fixed parms and initial guesses). */
    /* Parameters for light field modeling and fitting: */
    int adjustDir;     /* Index of lamp whose direction is to be adjusted, or -1. */
    double dirStep;    /* Maximum direction change allowed in each iteration. */
    double weightBias; /* Bias for dark-weighted fitting, or {+INF} for normal fitting. */
    double minNormalZ; /* Min Z coordinate of normal for light fitting. */
    int iterations;    /* Maximum number of iterations in mask finding. */
    double tolerance;  /* Stopping criterion for mask finding iteration. */
  } options_t;

#define flp_default_iterations  2
  /* Default max number of iterations for direction fitting. */
  
#define flp_default_tolerance   1.0e-6
  /* Default direction tolerance for stopping the direction fitting. */

float_image_t *flp_make_synthetic_photo(float_image_t *NRM, pst_light_t *lht);
  /* Creates an image of the object whose normal field is {NRM},
    assumed to be white and Lambertian, when illuminated by the 
    light field {lht}. */

float_image_t *flp_read_float_image(char *name);
  /* Reads a float image, in the format of {float_image_write}, from
    the named file (or {stdin} if {name} is "-"). */
    
void flp_write_synthetic_image(char *name, float_image_t *IMG);
  /* Writes the image {IMG} to a file named "{prefix}-fit.fni",
    in the FNI format. */

void flp_write_mask_image(char *prefix, float_image_t *MSK);
  /* Writes the mask image {MSK} to a file named "{prefix}-msk.fni",
    in the FNI format. */

void flp_write_difference_image
  ( char *prefix, 
    float_image_t *NRM, 
    float_image_t *AIMG, 
    float_image_t *BIMG
  );
  /* Writes the difference image {AIMG-BIMG} to a file named "{prefix}-dif.fni",
    in the FNI format.  The difference is set to zero where the 
    normal map {NRM} is zero. */

void flp_write_light_field_parameters(char *prefix, pst_light_t *lht);    
  /* Writes the parameters of light field {lht} to a
    file named "{prefix}-light.parms", in a format compatible with
    {pst_light_spec_parse}. */

void flp_write_float_image(char *name, float_image_t *IMG);
  /* Writes the image {IMG}, in the format of {float_image_write}, to
    the named file (or to {stdout} if {name} is "-"). */

void flp_show_light_field_parameters(char *title, pst_light_t *lht);
  /* Prints the light field model {lht} to {stderr}. */

options_t *flp_parse_options(int argc, char **argv);
  /* Parses the command line options, returns them in an {options_t}. */

int main (int argc,char** argv);
  /* Main program. */

int main (int argc,char** argv)
  { 
    /* Parse options from the command line: */
    options_t *o = flp_parse_options(argc, argv);
    if (o->showLights) { flp_show_light_field_parameters("specified lights", &(o->lht)); }

    /* Read actual photo: */
    float_image_t *IMG = flp_read_float_image(o->image);
    int NC, NX, NY;
    float_image_get_size(IMG, &NC, &NX, &NY);
    demand(NC == 1, "input image must be monochromatic");

    /* Read normal map: */
    float_image_t *NRM = flp_read_float_image(o->normal);
    float_image_check_size(NRM, 4, NX, NY, "bad normal map");
    
    /* Regularize light field: */
    fprintf(stderr, "regularizing lamp channels ...\n");
    pst_light_regularize_channels(&(o->lht), NC);
    if (o->showLights) { flp_show_light_field_parameters("regularized lights", &(o->lht)); }
    
    /* Optimize the light field parameters: */
    if (o->adjustDir >= 0)
      { fprintf(stderr, "optimizing direction of lamp %d ...\n", o->adjustDir);
        pst_lamp_t *src = o->lht.lmpv.e[o->adjustDir]; 
        pst_fit_light_single_iterative
          ( IMG, NRM, 
            &(o->lht),
            src, o->dirStep, TRUE, TRUE,
            o->weightBias, FALSE, o->minNormalZ,
            o->iterations, o->tolerance
          );
      }
    if (o->showLights) { flp_show_light_field_parameters("fitted lights", &(o->lht)); }
    
    /* Finish off with a global intensity optimization: */
    fprintf(stderr, "optimizing power levels of all lamps ...\n");
    pst_fit_light_multi(IMG, NRM, &(o->lht), o->weightBias, FALSE, o->minNormalZ);
    if (o->showLights) { flp_show_light_field_parameters("intensity-optimized lights", &(o->lht)); }

    /* Compute synthetic image from {NRM} and light field paramteres: */
    fprintf(stderr, "computing sythetic image ...\n");
    float_image_t *SYN = flp_make_synthetic_photo(NRM, &(o->lht));

    /* Write output files: */
    flp_write_light_field_parameters(o->outPrefix, &(o->lht));
    flp_write_synthetic_image(o->outPrefix, SYN);
    flp_write_difference_image(o->outPrefix, NRM, IMG, SYN);
    return 0;
  }

float_image_t *flp_make_synthetic_photo(float_image_t *NRM, pst_light_t *lht)
  { assert(NRM->sz[0] == 3);
    int NX = NRM->sz[1];
    int NY = NRM->sz[2];
    /* Create shaded image: */
    float_image_t *SYN = float_image_new(1, NX, NY);
    float_image_fill(SYN, 0.0);
    pst_shading_add_diffuse(NRM, NULL, lht, SYN);
    /* Reclaim temp storage: */
    return SYN;
  }

float_image_t *flp_read_float_image(char *name)
  { FILE *rd = open_read(name, TRUE);
    float_image_t *IMG = float_image_read(rd);
    if (rd != stdin) { fclose(rd); }
    return IMG;
  }

void flp_write_light_field_parameters(char *prefix, pst_light_t *lht)
  { char *name = NULL;
    char *name = jsprintf("%s-light.parms", prefix);
    FILE *wr = open_write(name, TRUE);
    pst_light_spec_write(wr, lht);
    fclose(wr);
    free(name);
  }

void flp_write_synthetic_image(char *prefix, float_image_t *IMG)
  { char *name = NULL;
    char *name = jsprintf("%s-fit.fni", prefix);
    flp_write_float_image(name, IMG);
    free(name);
  }

void flp_write_difference_image
  ( char *prefix, 
    float_image_t *NRM, 
    float_image_t *AIMG, 
    float_image_t *BIMG
  )
  { float_image_t *DIF = pst_shading_difference_image(NRM, AIMG, BIMG); 
    char *name = jsprintf("%s-dif.fni", prefix);
    flp_write_float_image(name, DIF);
    free(name);
    float_image_free(DIF);
  }

void flp_write_float_image(char *name, float_image_t *IMG)
  { FILE *wr = open_write(name, TRUE);
    float_image_write(wr, IMG);
    if (wr == stdout) { fflush(wr); } else { fclose(wr); }
  }
  
void flp_show_light_field_parameters(char *title, pst_light_t *lht)
  { fprintf(stderr, "%s\n", title);
    pst_light_spec_write(stderr, lht);
  }

options_t *flp_parse_options(int argc, char **argv)
  { 
    argparser_t *pp = argparser_new(stderr, argc, argv);
    argparser_set_help(pp, PROG_NAME " version " PROG_VERS ", usage:\n" PROG_HELP);
    argparser_set_info(pp, PROG_INFO);
    argparser_process_help_info_options(pp);
    
    options_t *o = (options_t *)malloc(sizeof(options_t)); 
    
    argparser_get_keyword(pp, "-image");
    o->image = argparser_get_next(pp);

    argparser_get_keyword(pp, "-normal");
    o->normal = argparser_get_next(pp);

    o->showLights = argparser_keyword_present(pp, "-showLights");
    
    int NC = 1;
    o->lht = pst_light_spec_parse(pp, FALSE, &NC);
    
    if (argparser_keyword_present(pp, "-adjustDir"))
      { o->adjustDir = argparser_get_next_int(pp, 0, MAXINT);
        o->dirStep = argparser_get_next_double(pp, 0, M_PI);
      }
    else
      { o->adjustDir = -1; o->dirStep = 0.0; }
    
    /* Parse light fitting parameters: */
    o->weightBias = +INF;
    pst_fit_light_parse_weightBias(pp, &(o->weightBias));

    o->minNormalZ = -1.0;
    pst_fit_light_parse_minNormalZ(pp, &(o->minNormalZ));

    o->iterations = flp_default_iterations;
    pst_fit_light_parse_iterations(pp, &(o->iterations));

    o->tolerance = flp_default_tolerance;
    pst_fit_light_parse_tolerance(pp, &(o->tolerance));

    /* Parse th eoutput filename prefix: */
    argparser_get_keyword(pp, "-outPrefix");
    o->outPrefix = argparser_get_next(pp);

    argparser_finish(pp);
    
    return o;
  }

/* COPYRIGHT, AUTHORSHIP, AND WARRANTY NOTICE:
**
**   Copyright © 2004 by the Fluminense Federal University (UFF).
**
** Created on jul/2005 by Rafael Saracchini, IC-UFF.
** Modified by Jorge Stolfi, mar/2006.
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
