#define PROG_NAME "make_test_slope_maps"
#define PROG_DESC "generate gradient maps for tests of slope_to_height"
#define PROG_VERS "1.0"

/* Copyright © 2005 by the State University of Campinas (UNICAMP). */
/* See the copyright, authorship, and warranty notice at end of file. */
/* Last edited on 2025-01-08 16:49:08 by stolfi */

#define PROG_HELP \
  "  " PROG_NAME " \\\n" \
  "    -function {ZFUNC} \\\n" \
  "    -size {NX} {NY} \\\n" \
  "    [ -smoothZ {LZ} {NZ} ] \\\n" \
  "    [ -smoothG {LG} {NG} ] \\\n" \
  "    [ -numGrad ] \\\n" \
  "    -noiseG {SIGMA_G} \\\n" \
  "    -noiseW {SIGMA_W} \\\n" \
  "    -maxGDiff {MAXGDIFF} \\\n" \
  "    -outPrefix {OUT_PREFIX}" " \\\n" \
  "    " argparser_help_info_HELP
  
#define PROG_INFO \
  "NAME\n" \
  "  " PROG_NAME " - " PROG_DESC "\n" \
  "\n" \
  "SYNOPSIS\n" \
  PROG_HELP "\n" \
  "\n" \
  "DESCRIPTION\n" \
  "  Generates a height map {Z(X,Y)}, its gradient (slope) map {G(X,Y)}, and" \
  " a corresponding weight map, in the format required" \
  " by {slope_to_height}.  The height map is written to the" \
  " single-channel float image file \"{OUT_PREFIX}-Z.fni\"." \
  " The gradient is written as" \
  " channels 0 (X derivative) and channel 1 (Y derivative) of the two-channel float image" \
  " file \"{OUT_PREFIX}-G.fni\".  The weight" \
  " map is written to \"{OUT_PREFIX}-W.fni\"." \
  " The normal map is written as the three-channel float image" \
  " file \"{OUT_PREFIX}-N.fni\".\n" \
  "\n" \
  "  The height map is defined by the {ZFUNC} parameter, an integer" \
  " that selects one of the program's built-in functions" \
  " ({function_00}, {function_01}, ...). See {pst_proc_map.h} for" \
  " the list of available functions.  The parameters" \
  " {NX} and {NY} are the width and height of the slope" \
  " map, in pixels.\n" \
  "\n" \
  "  The height function is nominally evaluated" \
  " at the corners of a rectangular grid with" \
  " {NX} by {NY} square cells. Note that the height map" \
  " has {NX+1} columns and {NY+1} rows.  If \"-smoothZ\" is not" \
  " specified, the height is sampled at that point only, otherwise it" \
  " is an average of {NZ} by {NZ} samples in a" \
  " window {LZ} by {LZ} pixels centered at that point.\n" \
  "\n" \
  "  The slope maps are nominally evaluated at the center of each pixel" \
  " of the grid, so it has {NX} columns and {NY} rows.   If \"-numGrad\" is" \
  " specified, the average gradient in each cell is computed by finite" \
  " differences from the height values at the four corners of the" \
  " cell.  If \"-numGrad\" is not specified, the gradient is computed" \
  " by sampling the analytic gradient of the function.  In any case," \
  " if \"-smoothG\" is not specified, the analytic gradient is sampled" \
  " at the center of the pixel, otherwise it is an average of {NG} by" \
  " {NG} samples in a window {LG} by {LG} pixels centered at that" \
  " point around that point.  Note that the analytic gradient may be" \
  " widely inconsistent with the height field, especially if the function" \
  " is discontinuous or highly random inside the pixel.\n" \
  "\n" \
  "  The allowed values for {LZ} and {LG} are 0, 1, and 2.  If {NZ} is 1, a" \
  " single sample is taken at the nominal position; this is the default" \
  " behavior.  One of the samples will fall at the nominal position if" \
  " and only if {NZ} is odd.  If {LZ} is zero, then {NZ} must be 1. \n" \
  "\n" \
  "  In any case, the reliability weight of each pixel is set ot 1.0 if the" \
  " \"-numGrad\" option is given. If \"-numGrad\" is not given, the weight" \
  " is 1 if the average analytic gradient coincides with the numeric gradient, and" \
  " decreases to zero as the Euclidean norm of the difference between the two" \
  " gradients increases to or beyond {MAXGDIFF}.\n" \
  "\n" \
  "  If {SIGMA_G} is positive, the program also randomly perturbs each" \
  " component of the gradient value, to simulate noisy data.  The" \
  " perturbation consists in adding a random number {E} with" \
  " Gaussian distribution, zero mean, and standard" \
  " deviation {SIGMA_G}.  The perturbation affects only" \
  " the gradient map, not the height map.\n" \
  "\n" \
  "  Similarly, if {SIGMA_W} is positive, each weight gets mutiplied" \
  " by {exp(E)} where {E} is a random number with Gaussian distribution,"\
  " zero mean, and standard deviation {SIGMA_W}.\n" \
  "\n" \
  "  The normal map is computed from the (perturbed) gradient map.  The Z"\
  " component is always positive.\n" \
  "\n" \
  "SEE ALSO\n" \
  "  fni_to_pnm(1), pnm_to_fni(1), slope_to_height(1)\n" \
  "\n" \
  "AUTHOR\n" \
  "  Created 2005-08-15 by Jorge Stolfi, UNICAMP.\n" \
  "MODIFICATION HISTORY\n" \
  "  2010-05-04 by J. Stolfi, IC-UNICAMP:\n" \
  "    * Weight is always 1 with \"-numGrad\"."

#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <values.h>

#include <float_image.h>
#include <argparser.h>
#include <jsfile.h>
#include <jsprintf.h>
#include <jsrandom.h>
#include <jsmath.h>
#include <r2.h>
#include <r3.h>

#include <pst_proc_map.h>
#include <pst_normal_map.h>

typedef struct sampling_opts_t
  { int N;     /* Number of sampling points per axis. */
    int L;     /* Width of window in pixels. */
  } sampling_opts_t;
  /* A sampling specification. The window width must be an integer
    to ensure the partition-of-unit property. */

typedef struct options_t
  { int function;            /* Integer code of height map. */
    int NX, NY;              /* Image size. */
    sampling_opts_t smoothZ; /* Sampling options for the heights. */
    sampling_opts_t smoothG; /* Sampling options for the analytic gradient. */
    bool_t numGrad;          /* Output numeric gradient instead of analytic one. */
    double maxGDiff;         /* Max discrepancy between analyic and numeric gradient. */
    double noiseG;           /* Deviation of gaussian gradient noise. */
    double noiseW;           /* Deviation of log-gaussian weight noise. */
    char* outPrefix;         /* Output name prefix. */
  } options_t;

/* INTERNAL PROTOTYPES */

void write_test_image
  ( char *pref,
    char *tag,
    float_image_t *I
  );
  /* Writes the image {I} to file named "{pref}-{tag}.fni",
    in FNI format (see float_image.h}). */

void normalize(double v[]);
  /* Normalizes the three-vector {v[0..2]} to unit Euclidean length. */

void write_fni_image(char *fileName, float_image_t *I);
  /* Writes the image {I} to file "{fileName}" as a FNI image, with
    {float_image_write}. */

options_t *parse_options(int argc, char **argv);
  /* Parses the command line arguments and packs them as an {options_t}. */

sampling_opts_t parse_sampling_options(argparser_t *pp, char *key);
  /* Parses an optional smoothing option consisting of the keyword {key} followed
    by the window width {L} and the number of samples per axis {N}. */

int main(int argc, char** argv);

/* IMPLEMENTATIONS */

int main(int argc, char** argv)
  {
    options_t *o = parse_options(argc, argv);
    
    float_image_t *IZ = float_image_new(1, o->NX+1, o->NY+1);
    float_image_t *IG = float_image_new(2, o->NX, o->NY);
    float_image_t *IW = float_image_new(1, o->NX, o->NY);
    float_image_t *IN = float_image_new(3, o->NX, o->NY);
    
    pst_proc_map_zfunc_t *func = pst_proc_map_function_generic(o->function);

    /* Compute the sample displacements and weights: */
    pst_proc_map_sampling_t smpZ = pst_proc_map_make_sampling_tables(o->smoothZ.L, o->smoothZ.N);
    pst_proc_map_sampling_t smpG = pst_proc_map_make_sampling_tables(o->smoothG.L, o->smoothG.N);

    /* Compute height and gradient maps: */
    pst_proc_map_make_images
      ( func, o->NX, o->NY, smpZ, smpG, 
        o->numGrad, o->maxGDiff, 
        o->noiseG, o->noiseW, 
        IZ, IG, IW, IN
      );
    
    /* Write images: */
    write_test_image(o->outPrefix, "Z", IZ);
    write_test_image(o->outPrefix, "G", IG);
    write_test_image(o->outPrefix, "W", IW);
    write_test_image(o->outPrefix, "N", IN);
    
    return 0;
  }

void write_test_image(char *pref, char *tag, float_image_t *I)
  { char *fileName = jsprintf("%s-%s.fni", pref, tag);
    write_fni_image(fileName, I);
    free(fileName);
  }

void normalize(double v[])
  { int c;
    double m2 = 0;
    for (c = 0; c < 3; c++) { double vax = v[c]; m2 += vax*vax; }
    double m = sqrt(m2);
    for (c = 0; c < 3; c++) 
      { if (m > 0)
          { /* Normalize vector to unit length: */
            v[c] /= m;
          }
        else
          { /* Messy spot, give +Z as the normal: */
            v[c] = (c == 2);
          }
      }
  }

void write_fni_image(char *fileName, float_image_t *I)
  { FILE *wr = open_write(fileName, TRUE);
    float_image_write(wr, I);
    fclose(wr);
  }

options_t *parse_options(int argc, char **argv)
  {
    argparser_t *pp = argparser_new(stderr, argc, argv);
    argparser_set_help(pp, PROG_NAME " version " PROG_VERS ", usage:\n" PROG_HELP);
    argparser_set_info(pp, PROG_INFO);
    argparser_process_help_info_options(pp);
   
    options_t *o = (options_t *)malloc(sizeof(options_t));
    
    argparser_skip_parsed(pp);

    argparser_get_keyword(pp, "-function"); 
    o->function = (int)argparser_get_next_int(pp, pst_proc_map_MIN_ZFUNC, pst_proc_map_MAX_ZFUNC);
    
    argparser_get_keyword(pp, "-size"); 
    o->NX = (int)argparser_get_next_int(pp, 1, 4095);
    o->NY = (int)argparser_get_next_int(pp, 1, 4095);
    
    o->smoothZ = parse_sampling_options(pp, "-smoothZ");
      
    o->smoothG = parse_sampling_options(pp, "-smoothG");
    
    o->numGrad = argparser_keyword_present(pp, "-numGrad");
    
    argparser_get_keyword(pp, "-maxGDiff"); 
    o->maxGDiff = argparser_get_next_double(pp, 0.0, +DBL_MAX);
    
    argparser_get_keyword(pp, "-noiseG"); 
    o->noiseG = argparser_get_next_double(pp, 0.0, +DBL_MAX);
    
    argparser_get_keyword(pp, "-noiseW"); 
    o->noiseW = argparser_get_next_double(pp, 0.0, +DBL_MAX);
    
    argparser_get_keyword(pp, "-outPrefix"); 
    o->outPrefix = argparser_get_next(pp);

    argparser_finish(pp);
    
    return o;
  }

sampling_opts_t parse_sampling_options(argparser_t *pp, char *key)
  {
    sampling_opts_t smooth;
    if (argparser_keyword_present(pp, key)) 
      { smooth.L = (int)argparser_get_next_int(pp, 0, 2);
        smooth.N = (int)argparser_get_next_int(pp, 1, (smooth.L == 0 ? 1 : 65));
      }
    else
      { smooth.L = 0;
        smooth.N = 1;
      }
    return smooth;
  }

/* COPYRIGHT, AUTHORSHIP, AND WARRANTY NOTICE:
** 
**   Copyright © 2005 by the State University of Campinas (UNICAMP).
**
** Created on 2005-08-15 by Jorge Stolfi, IC-UNICAMP.       
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
