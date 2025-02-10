#define PROG_NAME "fit_sphere_to_photo"
#define PROG_DESC "fit an ideal sphere to one or more photos"
#define PROG_VERS "1.0"

/* Copyright © 2006 by the State University of Campinas (UNICAMP).*/
/* See the copyright, authorship, and warranty notice at end of file.*/
/* Last edited on 2025-01-21 19:53:54 by stolfi*/

#define PROG_HELP \
  PROG_NAME " \\\n" \
  "    -images {PHOTO_FNI}.. \\\n" \
  "    -sphere \\\n" \
  "      " pst_geom_sphere_radius_HELP " \\\n" \
  "      [ " pst_geom_sphere_center_HELP " ] \\\n" \
  "      [ " pst_geom_sphere_stretch_HELP " ] \\\n" \
  "    -adjust \\\n" \
  "      [ " pst_geom_sphere_radius_adjust_HELP " ] \\\n" \
  "      [ " pst_geom_sphere_center_adjust_HELP " ] \\\n" \
  "      [ " pst_geom_sphere_stretch_adjust_HELP " ] \\\n" \
  "      [ " fsp_adjust_step_HELP " ] \\\n" \
  "    " pst_geom_aperture_HELP " \\\n" \
  "    " pst_light_spec_HELP " \\\n" \
  "    [ -adjustDir {INDEX} {DIRSTEP} ] \\\n" \
  "    [ " pst_fit_light_parse_weightBias_HELP " ] \\\n" \
  "    [ " pst_fit_light_parse_minNormalZ_HELP " ] \\\n" \
  "    [ " pst_fit_light_parse_iterations_HELP " ] \\\n" \
  "    [ " pst_fit_light_parse_tolerance_HELP " ] \\\n" \
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
  "  Reads a list of {NF} monochromatic photographs" \
  " of the same spherical object, taken with the same" \
  " camera position and settings, but under different light" \
  " conditions.  Computes the geometric parameters" \
  " (center, radius, and perspective stretching) of the" \
  " sphere's projection on the images, and, for each" \
  " image, a simple lighting model that best fits" \
  " the appearance of the object in the" \
  " photo.  Writes the geometric parameters to file" \
  " \"{PREFIX}-sphere.parms\", and the light field parameters" \
  " to \"{PREFIX}-{K}-light.parms\", for {K=0,1,...,NF-1}.\n" \
  "\n" \
  "  The program also writes a normal map for the fitted sphere" \
  " to file \"{PREFIX}-nrm.fni\", and simulated photos of the same," \
  " under the fitted light field, to \"{PREFIX}-{K}-fit.fni\"," \
  " for {K=0,1,...,NF-1}.  It also writes to file" \
  " \"{PREFIX}-{K}-dif.fni\" the difference between" \
  " the actual and fitted images, and to file \"{PREFIX}-{K}-msk.fni\"" \
  " the weight mask used for light fitting.\n" \
  "\n" \
  "  The spherical object should have uniform color and mostly matte" \
  " (Lambertian) finish. The user must specify the approximate" \
  " geometric parameters of its projection, and the amont by which" \
  " each may be adjusted.\n" \
  "\n" \
  "  IMPORTANT: The procedure assumes that the input image is a complete photo," \
  " not a cropped version thereof. In particular, it assumes that the" \
  " optical center of the camera is the center of the image, and that" \
  " the camera's field of view (measured by {APERTURE}) spans the" \
  " width of if the image.\n" \
  "\n" \
  "  See {fit_light_to_photo}(1)" \
  " for details on light field modeling and fitting, and" \
  " {make_sphere_normal_map}(1) for details on the geometric" \
  " parameters.\n" \
  "\n" \
  "  All input and output files are in the FNI format. See" \
  " {float_image.h} for details.\n" \
  "\n" \
  "LIGHT FIELD MODEL\n" \
  "  " pst_light_model_INFO "\n" \
  "\n" \
  "  " pst_fit_light_model_INFO "\n" \
  "\n" \
  "  " pst_fit_light_model_uniform_INFO "\n" \
  "\n" \
  "LIGHT SOURCE MODEL\n" \
  "  " pst_lamp_model_INFO \
  "\n" \
  "INTENSITY FITTING ALGORITHM\n" \
  "  " pst_fit_light_multi_INFO "\n" \
  "\n" \
  "DIRECTION FITTING ALGORITHM\n" \
  "  If the user requests adjustment of the direction of some" \
  " light source, the program uses a special method to estimate" \
  " the lamp's direction.\n" \
  "  " pst_fit_light_single_iterative_INFO "\n" \
  "\n" \
  "  " pst_fit_light_single_iterative_dark_weight_INFO "\n" \
  "\n" \
  "GENERAL OPTIONS\n" \
  "  -images {PHOTO_FNI}.. \n" \
  "    Specifies the names of one or more files containing" \
  " the photos of the spherical object.  All images must" \
  " be in the FNI format, must be monochromatic, and must" \
  " have the same dimensions.  This parameter is mandatory," \
  " and at least one image must be given.\n" \
  "\n" \
  "  " pst_geom_aperture_HELP "\n" \
  "    " pst_geom_aperture_HELP_INFO "  This parameter is used to compute" \
  " the stretch from the center's position.  The default" \
  " is \"-aperture 0\" meaning that the camera is very far" \
  " away so that the projection is practically cylindrical.\n" \
  "\n" \
  "  -sphere {SPHERE_PARAMETERS}\n" \
  "    This keyword should be followed by the sphere geometry" \
  " parameters (see below).  This keyword is mandatory.\n" \
  "\n" \
  "  -adjust {SPHERE_ADJUSTMENTS}\n" \
  "    This keyword should be followed by the sphere geometry" \
  " adjustment parameters (see below).  If this this keyword" \
  " is absent, all geometry adjustment amounts default to zero.\n" \
  "\n" \
  "LIGHT FIELD OPTIONS\n" \
  pst_light_spec_HELP_INFO "\n" \
  "\n" \
  "  The program will estimate a separate light field for each" \
  " photo.  The number of lamps and their angular radii are the" \
  " same in all fields, but the program will adjust the" \
  " intensity (and direction, if so requested) of each lamp" \
  " independently in each field.  Except for the angular" \
  " radius, any lamp parameters that are specified in the" \
  " command line are used only as starting guesses for" \
  " iterative fitting, or just ignored. n" \
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
  " " stringify(fsp_default_iterations) " .\n" \
  "\n" \
  pst_fit_light_parse_tolerance_HELP_INFO "  The" \
  " default is " stringify(fsp_default_tolerance) ".\n" \
  "\n" \
  "  -outPrefix {PREFIX} \n" \
  "    Specifies the common prefix for names of all output" \
  " files.  This parameter is mandatory.\n" \
  "\n" \
  "SPHERE PARAMETERS\n" \
  pst_geom_sphere_center_HELP_INFO "  The default is the center of the photos.\n" \
  "\n" \
  pst_geom_sphere_radius_HELP_INFO "  The default is the largest radius" \
  " that will fit in the photo, minus 1 pixel.\n" \
  "\n" \
  pst_geom_sphere_stretch_HELP_INFO "  If this parameter is not given, the" \
  " initial amount of stretching is computed from the center position and the camera" \
  " aperture." \
  "\n" \
  "SPHERE GEOMETRY AJUSTMENT PARAMETERS\n" \
  pst_geom_sphere_center_adjust_HELP_INFO "  The default is \"center 0\", meaning" \
  " that the given or defaulted center position should be used without" \
  " any adjustment. \n" \
  "\n" \
  pst_geom_sphere_radius_adjust_HELP_INFO "  The default is \"radius 0\", meaning" \
  " that the given or defaulted radius should be used without any adjustment. \n" \
  "\n" \
  pst_geom_sphere_stretch_adjust_HELP_INFO "  The default is \"center 0\", meaning" \
  " that the given or defaulted stretch vector should be used" \
  " without any adjustment. \n" \
  "\n" \
  fsp_adjust_step_HELP_INFO "  The default is " \
  stringify(fsp_default_adjStep) " pixel.\n" \
  "\n" \
  "DOCUMENTATION OPTIONS\n" \
  argparser_help_info_HELP_INFO "\n" \
  "\n" \
  "SEE ALSO\n" \
  "  make_sphere_normal_map(1), photo_to_normal(1)," \
  " normal_to_slope(1), slope_to_height(1)," \
  " slope_to_normal(1), pnm_to_fni(1), fni_to_pnm(1).\n" \
  "\n" \
  "AUTHOR\n" \
  "  Created in apr/2006 by Jorge Stolfi, IC-UNICAMP.\n" \
  "  Based on jul/2005 work by Rafael Saracchini, IC-UFF."

#define fsp_adjust_step_HELP \
  "step {ADJ_STEP}"

#define fsp_adjust_step_INFO \
  "This option may be specified once, after all adjustment amounts for" \
  " \"center\", \"radius\", and/or \"stretch\".  It specifies the" \
  " ideal granularity by which all parameters may be adjusted by" \
  " the program.  The actual step used for each parameter may" \
  " be somewhat different, depending on the adjustment inerval, the" \
  " adjustment algorithm used, imposed time limits, etc.."

#define fsp_adjust_step_HELP_INFO \
  "      " fsp_adjust_step_HELP "\n" \
  "        " fsp_adjust_step_INFO
 
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
#include <vec.h>
#include <r3x3.h> 
#include <ellipse_crs.h> 
#include <affirm.h>
#include <jsfile.h>
#include <argparser.h>

#include <pst_basic.h>
#include <pst_argparser.h>
#include <pst_lamp.h>
#include <pst_light.h>
#include <pst_normal_map.h>
#include <pst_shading.h>
#include <pst_fit_light.h>
#include <pst_geom.h>
#include <pst_fit_sphere.h>

typedef struct options_t
  { string_vec_t images;   /* Names of the FNI files with the sphere's photos. */
    char *outPrefix;     /* Prefix for output file names. */
    /* Parameters for sphere geometry and adjustment: */
    double aperture;     /* Horizontal aperture of the camera, or 0.0. */
    ellipse_crs_t E;     /* Geometry of the sphere's projection given by user. */
    double ctrAdj;       /* Max adjustment allowed in each center coordinate. */
    double radAdj;       /* Max adjustment allowed in radius. */
    double strAdj;       /* Max adjustment allowed in stretch vector coords. */
    double adjStep;      /* Adjustment step size. */
    /* Light field model: */
    pst_light_t lht;     /* Light model spec (fixed parms and initial guesses). */
    /* Parameters for light field modeling and fitting: */
    int adjustDir;       /* Index of lamp whose direction is to be adjusted, or -1. */
    double dirStep;      /* Maximum direction change allowed in each iteration. */
    double weightBias;   /* Bias for dark-weighted fitting, or {+INF} for normal fitting. */
    double minNormalZ;   /* Min Z coordinate of normal for light fitting. */
    int iterations;      /* Maximum number of light-fitting iterations. */
    double tolerance;    /* Stopping criterion for light-fitting iteration. */
  } options_t;

#define fsp_default_iterations  2
  /* Default max number of iterations for light fitting. */
  
#define fsp_default_tolerance   1.0e-6
  /* Default iteration tolerance for light fitting. */

#define fsp_default_adjStep   0.25
  /* Default geometry adjustment step (in pixels). */

image_vec_t fsp_read_float_image_list(string_vec_t *name, int *NCP, int *NXP, int *NYP);
  /* Reads a list of {NF} images, where {NF=name.ne}, from the files
    called {name[0..NF-1]}. If any name is "-", reads the image from
    {stdin}. 
    
    All images must have the same number of channels {*NCP}, columns
    {*NXP}, and rows {*NYP}. If any of {*NCP,*NXP,*NYP} is -1, the
    procedure sets that variable to the corresponding attribute of the
    first image read, and checks it against the rest. */

float_image_t *fsp_read_float_image(char *name, int *NCP, int *NXP, int *NYP);
  /* Reads a float image, in the format of {float_image_write}, from
    the named file (or {stdin} if {name} is "-").
    
    If any of {*NCP,*NXP,*NYP} is -1, stores into it the number of
    channels, columns, and rows of the image, respectively; otherwise
    checks whether the variable's value matches the corresponding
    image attribute. */

float_image_t *fsp_compute_mask_image
  ( options_t *o, 
    float_image_t *IMG, 
    float_image_t *NRM, 
    pst_light_t *lht
  );
  /* Computes a monochromatic image {MSK} whose values are the final
    pixel weights used in the least-squares fitting of the light
    model. Of {o->adjustDir} is some non-negative value {IX}, the
    weights take into acount the direction of lamp {lht->lampv[IX]};
    otherwise the weights are independent of {lht}. */

void fsp_write_sphere_geometry(char *prefix, ellipse_crs_t *E);
  /* Writes the geometric parameters {E} of a sphere to a file named
    "{prefix}-sphere.parms", in a format compatible with
    {pst_sphere_options_parse}. */

void fsp_write_light_field_parameters(char *prefix, int i, pst_light_t *lht);
  /* Writes the light field description {lht} to a file named
    "{prefix}-{i}-light.parms", in a format compatible with
    {pst_light_spec_parse}. */

void fsp_write_sphere_normal_map(char *prefix, float_image_t *NRM);
  /* Writes the normal map {NRM} to a file named "{prefix}-nrm.fni",
    in the FNI format. */

void fsp_write_synthetic_image(char *prefix, int i, float_image_t *IMG);
  /* Writes the image {IMG} to a file named "{prefix}-{i}-fit.fni",
    in the FNI format. */

void fsp_write_mask_image(char *prefix, int i, float_image_t *MSK);
  /* Writes the mask image {MSK} to a file named "{prefix}-{i}-msk.fni",
    in the FNI format. */

void fsp_write_difference_image
  ( char *prefix, 
    float_image_t *NRM, 
    int i, 
    float_image_t *AIMG, 
    float_image_t *BIMG
  );
  /* Writes the difference image {AIMG-BIMG} to a file named "{prefix}-{i}-dif.fni",
    in the FNI format.  The difference is set to zero where the 
    normal map {NRM} is zero. */

void fsp_write_float_image(char *name, float_image_t *IMG);
  /* Writes the image {IMG} to a file named "{name}", in the FNI format. */

options_t *fsp_parse_options(int argc, char **argv);
  /* Parses the command line options, returns them in an {options_t}. */

int main (int argc,char** argv);
  /* Main program. */

int main (int argc,char** argv)
  { 
    /* Parse options from the command line: */
    options_t *o = fsp_parse_options(argc, argv);
    int NF = o->images.ne;
    int i;

    fprintf(stderr, "adjusting sphere geometry to %d photos\n", NF);

    /* Read input sphere images: */
    int NC = 1;           /* Number of channels - must be 1. */
    int NX = -1, NY = -1; /* Image dimensions - must be all the same. */
    image_vec_t IMGV = fsp_read_float_image_list(&(o->images), &NC, &NX, &NY);
    fprintf(stderr, "image size = %d × %d\n", NX, NY);

    /* Provide defaults for image center and stretch: */
    if (isnan(o->E.ctr.c[0]) || isnan(o->E.ctr.c[1]))
      { o->E.ctr = (r2_t) {{ 0.5*NX, 0.5*NY }}; }
    if (isnan(o->E.rad))
      { double xrad = fmin(o->E.ctr.c[0], NX - o->E.ctr.c[0]) - 1;
        double yrad = fmin(o->E.ctr.c[1], NY - o->E.ctr.c[1]) - 1;
        o->E.rad = fmin(xrad, yrad);
        demand(o->E.rad > 0, "no space for sphere at this position");
      }
    if (isnan(o->E.str.c[0]) || isnan(o->E.str.c[1]))
      { /* Estimate the stretch from center, radius, and aperture: */
        double ap = o->aperture;
        o->E.str = pst_geom_sphere_est_stretch(&(o->E.ctr), o->E.rad, NX, NY, ap);
      }
    
    /* Allocate output sphere normal map: */
    float_image_t *NRM = float_image_new(3, NX, NY);

    /* Allocate synthetic sphere images: */
    image_vec_t SYNV = image_vec_new(NF);
    for(i = 0; i < NF; i++) { SYNV.e[i] = float_image_new(NC, NX, NY); }

    /* Regularize model light field: */
    pst_light_regularize_channels(&(o->lht), NC);
    
    /* Create a separate light field for each photo: */
    pst_light_vec_t lhtv = pst_light_vec_new(NF);
    for(i = 0; i < NF; i++)  
      { /* Make a copy {lhtv.e[i]} of the lightfield {o->lht}: */
        pst_light_t *lht = &(lhtv.e[i]);
        (*lht) = pst_light_copy(&(o->lht));
      }

    /* Initialize the geometry parameters from the command line: */
    ellipse_crs_t E = (o->E);
    
    /* Provide the default center: */
    if ((E.ctr.c[0] == +INF) || (E.ctr.c[1] == +INF))
      { E.ctr = (r2_t){{ 0.5*(double)NX, 0.5*(double)NY }};  }

    /* Do the fitting: */
    fprintf(stderr, "initial geometry:\n");
    fprintf(stderr, "  radius  = %8.5f ± %8.5f\n", E.rad, o->radAdj);
    fprintf(stderr, "  center  = ( %8.4f , %8.5f ) ± %8.5f\n", E.ctr.c[0], E.ctr.c[1], o->ctrAdj);
    fprintf(stderr, "  stretch = ( %+8.5f , %+8.5f ) ± %8.5f\n", E.str.c[0], E.str.c[1], o->strAdj);
    fprintf(stderr, "  nominal adjustment step = %8.5f\n", o->adjStep);

    pst_fit_sphere_and_lights
      ( &IMGV, 
        &E, o->ctrAdj, o->radAdj, o->strAdj, o->adjStep,
        &lhtv, o->adjustDir, o->dirStep,
        o->weightBias, FALSE, o->minNormalZ, o->iterations, o->tolerance,
        NRM, &SYNV
      );

    /* Print results: */
    fprintf(stderr, "best-fit geometry:\n");
    fprintf(stderr, "  radius  = %8.5f\n", E.rad);
    fprintf(stderr, "  center  = ( %8.5f , %8.5f )\n", E.ctr.c[0], E.ctr.c[1]);
    fprintf(stderr, "  stretch = ( %+8.5f , %+8.5f )\n", E.str.c[0], E.str.c[1]);

    /* Write sphere parameters and normal map: */
    fsp_write_sphere_geometry(o->outPrefix, &E);
    fsp_write_sphere_normal_map(o->outPrefix, NRM);

    /* Write lamp parameters and virtual sphere images: */
    for (i = 0; i < NF; i++)
      { fsp_write_light_field_parameters(o->outPrefix, i, &(lhtv.e[i]));
        fsp_write_synthetic_image(o->outPrefix, i, SYNV.e[i]);
        
        /* Compute and write the least squares weight mask image: */
        float_image_t *MSK = fsp_compute_mask_image(o, IMGV.e[i], NRM, &(lhtv.e[i]));
        fsp_write_mask_image(o->outPrefix, i, MSK);
        float_image_free(MSK);

        fsp_write_difference_image(o->outPrefix, NRM, i, IMGV.e[i], SYNV.e[i]);
      }
    return 0;
  }

float_image_t *fsp_compute_mask_image
  ( options_t *o, 
    float_image_t *IMG, 
    float_image_t *NRM, 
    pst_light_t *lht
  )
  { 
    /* Get/check image dimensions: */
    int NC = IMG->sz[0];
    int NX = IMG->sz[1];
    int NY = IMG->sz[2];
    demand(NRM->sz[0] == 3, "mismatch: channels");
    demand(NRM->sz[1] == NX, "mismatch: columns");
    demand(NRM->sz[2] == NY, "mismatch: rows");
    demand(NC == 1, "image is not monochromatic");
    /* Identify the relevant lamp {src} in {lht} (NULL if none): */
    pst_lamp_t *src = (o->adjustDir < 0 ? NULL : lht->lmpv.e[o->adjustDir]);
    /* Get the lamp's direction {dirP} (or NULL if none) and its {minCos}: */
    r3_t *dirP = (src == NULL ? NULL : &(src->dir)); 
    double minCos = (src == NULL ? -1.0 : cos(M_PI/2 - acos(src->crad)));
    /* Allocate mask image: */
    float_image_t *MSK = float_image_new(3, NX, NY);
    /* Compute lsq weights of all pixels and save them in {MSK}: */
    int wch = 1; /* Index of weight channel in {MSK} (green). */
    int x, y;
    double maxw = 0; /* Maximum weight seen. */
    for (y = 0; y < NY; y++)
      { for (x = 0; x < NX; x++)
          { double img = float_image_get_sample(IMG, 0, x, y);
            r3_t nrm = pst_normal_map_get_pixel(NRM, x, y);
            double w = 
              pst_fit_light_lsq_pixel_weight
                ( img, &nrm, o->minNormalZ, dirP, minCos, o->weightBias );
            assert(w >= 0.0);
            /* Set channel {wch} to {w}, others to {img}: */
            int c;
            for (c = 0; c < 3; c++)
              { float_image_set_sample(MSK, c, x, y, (c == wch ? w : img)); }
            /* Update maximum weight: */
            if (w > maxw) { maxw = w; }
          }
      }
    if ((maxw != 0.0) && (maxw != 1.0))
      { /* Normalize the weight channel to the range [0_1]: */
        int x, y;
        for (y = 0; y < NY; y++)
          { for (x = 0; x < NX; x++)
              { double w = float_image_get_sample(MSK, wch, x, y);
                float_image_set_sample(MSK, wch, x, y, w/maxw);
              }
          }
      }
    return MSK;
  }

void fsp_write_sphere_geometry(char *prefix, ellipse_crs_t *E)
  { char *name = NULL;
    char *name = jsprintf("%s-sphere.parms", prefix);
    FILE *wr = open_write(name, TRUE);
    pst_geom_sphere_args_write(wr, E);
    fclose(wr);
    free(name);
  }

void fsp_write_light_field_parameters(char *prefix, int i, pst_light_t *lht)
  { char *name = NULL;
    char *name = jsprintf("%s-%d-light.parms", prefix, i);
    FILE *wr = open_write(name, TRUE);
    pst_light_spec_write(wr, lht);
    fclose(wr);
    free(name);
  }

image_vec_t fsp_read_float_image_list(string_vec_t *name, int *NCP, int *NXP, int *NYP)
  { image_vec_t IMVEC = image_vec_new(name->ne);
    int i;
    for (i = 0; i < name->ne; i++)
      { IMVEC.e[i] = fsp_read_float_image(name->e[i], NCP, NXP, NYP); }
    return IMVEC;
  }

float_image_t *fsp_read_float_image(char *name, int *NCP, int *NXP, int *NYP)
  { FILE *rd = open_read(name, TRUE);
    float_image_t *IMG = float_image_read(rd);
    int NC = IMG->sz[0];
    int NX = IMG->sz[1];
    int NY = IMG->sz[2];
    if ((*NCP) < 0) { (*NCP) = NC; } else { demand((*NCP) == NC, "mismatch: channels"); }
    if ((*NXP) < 0) { (*NXP) = NX; } else { demand((*NXP) == NX, "mismatch: columns"); }
    if ((*NYP) < 0) { (*NYP) = NY; } else { demand((*NYP) == NY, "mismatch: rows"); }
    if (rd != stdin) { fclose(rd); }
    return IMG;
  }

void fsp_write_sphere_normal_map(char *prefix, float_image_t *NRM)
  { char *name = NULL;
    char *name = jsprintf("%s-nrm.fni", prefix);
    fsp_write_float_image(name, NRM);
    free(name);
  }

void fsp_write_synthetic_image(char *prefix, int i, float_image_t *IMG)
  { char *name = NULL;
    char *name = jsprintf("%s-%d-fit.fni", prefix, i);
    fsp_write_float_image(name, IMG);
    free(name);
  }

void fsp_write_mask_image(char *prefix, int i, float_image_t *MSK)
  { char *name = NULL;
    char *name = jsprintf("%s-%d-msk.fni", prefix, i);
    fsp_write_float_image(name, MSK);
    free(name);
  }

void fsp_write_difference_image
  ( char *prefix, 
    float_image_t *NRM, 
    int i, 
    float_image_t *AIMG, 
    float_image_t *BIMG
  )
  { float_image_t *DIF = pst_shading_difference_image(NRM, AIMG, BIMG); 
    char *name = jsprintf("%s-%d-dif.fni", prefix, i);
    fsp_write_float_image(name, DIF);
    free(name);
    float_image_free(DIF);
  }

void fsp_write_float_image(char *name, float_image_t *IMG)
  { FILE *wr = open_write(name, TRUE);
    float_image_write(wr, IMG);
    if (wr == stdout) { fflush(wr); } else { fclose(wr); }
  }

options_t *fsp_parse_options(int argc, char **argv)
  {
    argparser_t *pp = argparser_new(stderr, argc, argv);
    argparser_set_help(pp, PROG_NAME " version " PROG_VERS ", usage:\n" PROG_HELP);
    argparser_set_info(pp, PROG_INFO);
    argparser_process_help_info_options(pp);
    
    options_t *o = (options_t *)malloc(sizeof(options_t)); 
    
    argparser_get_keyword(pp, "-images");
    int NF = -1; /* Number of light fields. */
    o->images = argparser_get_next_file_name_list(pp, &NF);
    if (NF == 0) { argparser_error(pp, "must specify at least one image file"); }

    argparser_get_keyword(pp, "-sphere");
    o->E = pst_geom_sphere_args_parse(pp);
      
    if (argparser_keyword_present(pp, "-adjust"))
      { pst_geom_sphere_adjust_args_parse(pp, &o->ctrAdj, &o->radAdj, &o->strAdj);
        /* Parse the "step" modifier to the sphere adjustment args: */
        if (argparser_keyword_present_next(pp, "step"))
          { o->adjStep = argparser_get_next_double(pp, 0.0, 100.0); }
        else
          { o->adjStep = fsp_default_adjStep; }
      }
    else
      { o->ctrAdj = o->radAdj = o->strAdj = 0.0;
        o->adjStep = fsp_default_adjStep;
      }

    int NC = 1;
    o->lht = pst_light_spec_parse(pp, FALSE, &NC);
    
    if (argparser_keyword_present(pp, "-aperture"))
      { o->aperture = argparser_get_next_double(pp, 1.0e-10, 1.0e+10); }
    else
      { o->aperture = 0.0; }

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

    o->iterations = fsp_default_iterations;
    pst_fit_light_parse_iterations(pp, &(o->iterations));

    o->tolerance = fsp_default_tolerance;
    pst_fit_light_parse_tolerance(pp, &(o->tolerance));

    /* Parse th eoutput filename prefix: */
    argparser_get_keyword(pp, "-outPrefix");
    o->outPrefix = argparser_get_next(pp);

    argparser_finish(pp);
    return o;
  }

/* COPYRIGHT, AUTHORSHIP, AND WARRANTY NOTICE:
**
**   Copyright © 2006 by the State University of Campinas (UNICAMP).
**
** Created apr/2006 by Jorge Stolfi, IC-UNICAMP.
** Based on work by Rafael Saracchini, IC-UFF.
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
