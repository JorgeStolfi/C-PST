#define PROG_NAME "make_sphere_normal_map"
#define PROG_DESC "create the normal map of a sphere"
#define PROG_VERS "1.0"

/* Copyright © 2006 by the State University of Campinas (UNICAMP). */
/* See the copyright, authorship, and warranty notice at end of file. */
/* Last edited on 2009-03-01 00:52:31 by stolfi */ 

#define PROG_HELP \
  PROG_NAME " \\\n" \
  "    -size {NX} {NY} \\\n" \
  "    -sphere \\\n" \
  "      " ellipse_crs_args_radius_HELP " \\\n" \
  "      [ " ellipse_crs_args_center_HELP " ] \\\n" \
  "      [ " ellipse_crs_args_stretch_HELP " ] \\\n" \
  "    ] \\\n" \
  "    [ -camera \\\n" \
  "      [ " pst_camera_args_axis_HELP " ] \\\n" \
  "      [ " pst_camera_args_resolution_HELP " ] \\\n" \
  "    ] \\\n" \
  "    [ -subsample {NSAMP} ] \\\n" \
  "    [ -noise {AMOUNT} ] \\\n" \
  "    " argparser_help_info_HELP " \\\n" \
  "    > {NORMALMAP}.fni"

#define PROG_INFO \
  "NAME\n" \
  "  " PROG_NAME " - " PROG_DESC ".\n" \
  "\n" \
  "SYNOPSIS\n" \
  "  " PROG_HELP "\n" \
  "\n" \
  "DESCRIPTION\n" \
  "  Writes to {stdout} the /normal map/ of a sphere --- that is, a" \
  " three-channel float-valued image of a sphere, with {NX} columns" \
  " and {NY} rows, where the value of each pixel is the outwards-pointing" \
  " unit vector normal to the sphere's surface in that pixel." \
  "\n" \
  "  The sphere is assumed to be viewed in cylindrical oblique projection," \
  " so that its image is an ellipse.  The center of the ellipse is at" \
  " {(CTRX,CTRY)}.  The ellipse has minor radius {RAD} and major radius" \
  " {RAD+LEN}, where {LEN} is the length of the stretch vector" \
  " {(STRX,STRY)}.  The major radius is parallel to that vector.\n" \
  "\n" \
  "  The normal vector for each pixel is obtained by averaging the" \
  " slopes {dZ/dX} and {dZ/dY} at a grid of {NSAMP*NSAMP} points" \
  " with each pixel, and then converting the average slopes to a" \
  " normal vector.\n" \
  "\n" \
  "  Although digital photographs use conical projection, the cylindrical" \
  " oblique model is a first-order approximation that should be fairly" \
  " accurate for a small sphere taken at typical camera geometries.\n" \
  "\n" \
  "  All dimensions and coordinates are in pixels. The origin is" \
  " assumed to be at the lower left corner of the image, with the" \
  " Y axis pointing up.  Note that row 0 in a FNI image file is the" \
  " BOTTOM row of the image.\n" \
  "\n" \
  "  The output file is in the FNI format. See" \
  " {float_image.h} for details.\n" \
  "\n" \
  "OPTIONS\n" \
  "  -size {NX} {NY}\n" \
  "    Specifies the number of columns and the number of rows" \
  " of the output image.  Required.\n" \
  ellipse_crs_args_center_INFO "  Defaults to the image's center.\n" \
  "\n" \
  ellipse_crs_args_radius_INFO "  This parameter is mandatory.\n" \
  "\n" \
  ellipse_crs_args_stretch_INFO "  The default is \"stretch 0 0\", meaning" \
  " a circular image of radius {RAD} (as in orthogonal projection).\n" \
  "\n" \
  "  -subsample {NSAMP}\n" \
  "    Specifies a grid of {NSAMP*NSAMP} sampling points with each" \
  " pixel for slope averaging.  Defaults to \"-subsample 3\".\n" \
  "\n" \
  "  -noise {AMOUNT}\n" \
  "    Randomly perturbs the direction of the normal vectors.  In" \
  " particular, {AMOUNT=0} means no perturbation, while {AMOUNT=1}" \
  " means that the result is uniformly distributed on the unit sphere" \
  " and independent of the true norm.  For small values of {AMOUNT}," \
  " the perturbation is (to first order) a tangential vector with" \
  " zero mean and root-mean-square length {AMOUNT}.  Defaults to" \
  " no perturbation.\n" \
  "\n" \
  argparser_help_info_HELP_INFO "\n" \
  "\n" \
  "SEE ALSO\n" \
  "  virtual-gauge(1), normal_to_slope(1), slope_to_height(1)," \
  " slope-to-norma(1), pnm_to_fni(1), fni_to_pnm(1).\n" \
  "\n" \
  "AUTHOR\n" \
  "  Created 2006-04-07 by Jorge Stolfi, Unicamp."

#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <values.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <float_image.h>
#include <argparser.h>
#include <r2.h>
#include <r3.h> 
#include <r3x3.h> 
#include <ellipse_crs.h> 
#include <ellipse_crs_args.h> 

#include <pst_normal_map.h>
#include <pst_geom.h>
#include <pst_camera.h>

typedef struct options_t
  { /* Output image dimensions: */
    int NX;            /* Number of columns in output image. */
    int NY;            /* Number of rows in output image. */
    int subsample;     /* Order of subsampling grid within each pixel. */
    double noise;      /* Root mean square length of perturbation vector. */
    pst_camera_t C;    /* Camera parameters. */
    ellipse_crs_t E;   /* Geometry of sphere's image (dimensions in pixels): */
  } options_t;

options_t *msn_parse_options(int argc, char **argv);
  /* Parses the command line options, returns them as an {options_t} record. */

#define X c[0]
#define Y c[1]
#define Z c[2]
  /* Coordinates of an {r2_t} or {r2_t}. */

/* IMPLEMENTATIONS */

void msn_fix_sphere_and_camera_options(pst_camera_t *CP, ellipse_crs_t *EP);
  /* Compatibilizes the camera options {CP} and ellipse options {EP}. */

int main(int argc, char** argv);

int main(int argc, char** argv)
  { 
    pst_normal_map_proc_t *nrmf = &pst_geom_sphere_compute_normal;
  
    /* Parse options from the command line: */
    options_t *o = msn_parse_options(argc, argv);
    msn_fix_sphere_and_camera_options(&(o->C), &(o->E));
    float_image_t *NRM = float_image_new(3, o->NX, o->NY);
    r3x3_t xym_to_uvm, uvw_to_xyz;
    pst_geom_sphere_view_matrices(&(o->E), &xym_to_uvm, &uvw_to_xyz);
    pst_normal_map_from_proc(*nrmf, o->subsample, &xym_to_uvm, &uvw_to_xyz, NRM);
    float_image_write(stdout, NRM);
    return 0;
  }
  
void msn_fix_sphere_and_camera_options(pst_camera_t *CP, ellipse_crs_t *EP)
  {
    bool_t fix_sphere = TRUE; /* TRUE fixes the sphere, FALSE the camera. */
    /* Print the given data: */
    fprintf(stderr, "given sphere outline parameters:\n");
    ellipse_crs_args_print(stderr, EP, "%10.5f");
    fprintf(stderr, "given camera parameters:\n");
    pst_camera_args_print(stderr, CP, "%10.5f", "14.12f");
    fprintf(stderr, "\n");
    /* Compute the nominal parameters of the sphere from its projection: */
    r2_t tct;   /* Nominal center of sphere. */
    double trd; /* Nominal radius of sphere. */
    r2_t str;   /* Expected stretch vector of sphere's projection. */
    pst_geom_sphere_compute_nominal_params_and_stretch_from_apparent_params
      ( &(CP->axis), CP->zoom, &(EP->ctr), EP->rad, &tct, &trd, &str ); 
    fprintf(stderr, "nominal sphere parameters:\n");
    fprintf(stderr, "  center %10.5f %10.5f\n", tct.X, tct.Y);
    fprintf(stderr, "  radius %10.5f\n", trd);
    fprintf(stderr, "  expected stretch %10.5f %10.5f\n", str.X, str.Y);
    fprintf(stderr, "\n");
    if (fix_sphere)
      { /* Recompute the apparent params from the nominal ones, for debugging: */
        pst_geom_sphere_compute_apparent_params_from_nominal_params
          ( &(CP->axis), CP->zoom, &tct, trd, &(EP->ctr), &(EP->rad), &(EP->str) );
        /* Print the reconstructed params of the sphere's outline: */
        fprintf(stderr, "reconstructed sphere outline parameters:\n");
        ellipse_crs_args_print(stderr, EP, "%10.5f");
        fprintf(stderr, "\n");
      }
    else
      { /* Recompute the camera axis and zoom from the ellipse parameters: */
        demand(FALSE, "!!! not implemented yet !!!");
      }
  }

options_t *msn_parse_options(int argc, char **argv)
  {
    argparser_t *pp = argparser_new(stderr, argc, argv);
    argparser_set_help(pp, PROG_NAME " version " PROG_VERS ", usage:\n" PROG_HELP);
    argparser_set_info(pp, PROG_INFO);
    argparser_process_help_info_options(pp);
    
    options_t *o = (options_t *)notnull(malloc(sizeof(options_t)), "no mem"); 
    
    /* Parse the image size arguments: */
    argparser_get_keyword(pp, "-size");
    o->NX = argparser_get_next_int(pp, 1, float_image_max_size);
    o->NY = argparser_get_next_int(pp, 1, float_image_max_size);
    
    /* Parse the parameters of the sphere's outline and provide defaults: */
    argparser_get_keyword(pp, "-sphere");
    ellipse_crs_args_parse(pp, &(o->E), NULL, NULL, NULL);
    if (isnan(o->E.ctr.c[0]) || isnan(o->E.ctr.c[1]))
      { o->E.ctr = (r2_t){{ 0.5*(double)(o->NX), 0.5*(double)(o->NY) }}; }
    if (isnan(o->E.rad)) { argparser_error(pp, "the sphere \"radius\" must be given"); }
    /* Leave the stretch vector as {NAN,NAN} if not specified. */
    
    /* Parse the camera parameters and provide defaults: */
    if (argparser_keyword_present(pp, "-camera"))
      { pst_camera_args_parse(pp, &o->C, NULL, NULL); }
    else
      { o->C.axis = (r2_t) {{ NAN, NAN }}; o->C.zoom = NAN; }
    if (isnan(o->C.axis.c[0]) || isnan(o->C.axis.c[1]))
      { o->C.axis = (r2_t){{ 0.5*(double)(o->NX), 0.5*(double)(o->NY) }}; }
    if (isnan(o->C.zoom)) { o->C.zoom = +INF; }

    /* Parse the subssampling argument: */
    if (argparser_keyword_present(pp, "-subsample"))
      { o->subsample = argparser_get_next_int(pp, 1, 100); }
    else
      { o->subsample = 3; }
    
    /* Parse the perturbation amount: */
    if (argparser_keyword_present(pp, "-noise"))
      { o->noise = argparser_get_next_double(pp, 0.0, 1.0e+20); }
    else
      { o->noise = 0.0; }
    
    argparser_finish(pp);
    
    return o;
  }

/* COPYRIGHT, AUTHORSHIP, AND WARRANTY NOTICE:
**
**   Copyright © 2006 by the State University of Campinas (UNICAMP).
**
** Created on 08/apr/2006 by Jorge Stolfi, UNICAMP.
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
