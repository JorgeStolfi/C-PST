#define PROG_NAME "fit_ellipse_to_photo"
#define PROG_DESC "fits the outline of an ellipse to a photo"
#define PROG_VERS "1.0"

#define fit_ellipse_to_photo_C_COPYRIGHT \
  "Copyright © 2009 by the State University of Campinas (UNICAMP)"

/* Last edited on 2025-01-21 19:50:23 by stolfi*/

/* !!! See how it is best to generate the normal map. !!! */
/* !!! Add radial distortion {kappa} to the parameters. !!! */
/* !!! Use the true perspective projection instead of affine. !!! */

#define PROG_HELP \
  PROG_NAME " \\\n" \
  "    -image {PNM_PHOTO_FILE} \\\n" \
  "    { -ellipse | -sphere | -circle } \\\n" \
  "      [ " ellipse_crs_args_radius_adjust_HELP " ] \\\n" \
  "      [ " ellipse_crs_args_center_adjust_HELP " ] \\\n" \
  "      [ " ellipse_crs_args_stretch_adjust_HELP " ] \\\n" \
  "    ] \\\n" \
  "    [ -camera \\\n" \
  "      [ " pst_camera_args_viewpoint_HELP " ] \\\n" \
  "      [ " pst_camera_args_center_HELP " ] \\\n" \
  "      [ " pst_camera_args_spread_adjust_HELP " ] \\\n" \
  "    ] \\\n" \
  "    [ -noise {NOISE} ] \\\n" \
  "    [ -minRadius {MIN_RADIUS} ] \\\n" \
  "    [ -debug ] \\\n" \
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
  "  Looks for an elliptical shape in a digital image.  Depending" \
  " on the options, the program can search" \
  " for an arbitrary ellipse, or an ellipse that is a" \
  " perspective view of a sphere, or a circle.\n" \
  "\n" \
  "  The elliptical shape in the photo must be smoothly" \
  " shaded and must have good contrast against the background, over" \
  " a substantial part of its boundary. The user must specify" \
  " the approximate geometric parameters that define the shape, and" \
  " the amount by which each parameter may be adjusted.\n" \
  "\n" \
  "  Most image files, input and output, are in the PBM/PGM/PPM format.  Some " \
  " diagnostic images are in the FNI format (see" \
  " {float_image_write} in {float_image.h}).  All input" \
  " and output coordinates are" \
  " in pixels, relative to the top left corner of the image.\n" \
  "\n" \
  "OUTPUT FILES\n" \
  "  The program writes the following output files:\n" \
  "\n" \
  "    \"{PREFIX}-igu.ppm\"\n" \
  "      An image showing the initial guess for the outline," \
  " in red, drawn on top of a copy of the input image.\n" \
  "\n" \
  "    \"{PREFIX}-fit.ppm\"\n" \
  "    \"{PREFIX}-fgr.ppm\"\n" \
  "      Two images showing the fitted outline, in red, drawn" \
  " on top of a copy of the input image, and of its relative" \
  " gradient squared, respectively.\n" \
  "\n" \
  "    \"{PREFIX}-msk.pgm\"\n" \
  "      A grayscale mask image, with the same size as the input" \
  " image, defining the fitted projection of the sphere (0 outside," \
  " 1 inside, with antialiased boundary).\n" \
  "\n" \
  "    \"{PREFIX}-clip-img.{EXT}\"\n" \
  "      A copy of the input image, clipped to contain" \
  " just the fitted ellipse plus a safety margin, a few" \
  " pixels wide, all around. The extension" \
  " is \"ppm\" or \"pgm\" depending on the input image type.\n" \
  "\n" \
  "    \"{PREFIX}-clip-msk.pgm\"\n" \
  "      The same mask image above, clipped to the same" \
  " rectangle as \"{PREFIX}-clip-img.ppm\".\n" \
  "\n" \
  "    \"{PREFIX}-full.epar\"\n" \
  "    \"{PREFIX}-clip.epar\"\n" \
  "      The geometric parameters of the adjusted sphere's outline" \
  " respectively for the full image and the clipped image.\n" \
  "\n" \
  "    \"{PREFIX}-full.cpar\"\n" \
  "    \"{PREFIX}-clip.cpar\"\n" \
  "      The adjusted camera parameters respectively for" \
  " the full image and the clipped image.  (These are intersting" \
  " mainly when doing a \"-sphere\" fit with camera spread adjustment.)\n" \
  "\n" \
  "GENERAL OPTIONS\n" \
  "  -image {PNM_PHOTO_FILE} \n" \
  "    Specifies the name of the file containing" \
  " the elliptical shape to be sought. The file must" \
  " be in PBM, PGM, or PPM format.  This parameter is mandatory.\n" \
  "\n" \
  "  -sphere {ELLIPSE_PARAMETERS}\n" \
  "  -ellipse {ELLIPSE_PARAMETERS}\n" \
  "  -circle {ELLIPSE_PARAMETERS}\n" \
  "    These keywords specify the approximate geometric" \
  " parameters of the target shape in the input" \
  " image.  See the ELLIPSE PARAMETERS section (below) for" \
  " details.  With \"-sphere\" and \"-circle\", the \"stretch\" parameter" \
  " (and its adjustment) must be zero or omitted.  Exactly one" \
  " of these options must be given.\n" \
  "\n" \
  "  -camera {CAMERA_PARAMETERS}\n" \
  "    This keyword should be followed by the geometric" \
  " parameters of the camera,  See the CAMERA PARAMETERS" \
  " section (below) for details.  This information" \
  " is needed only when looking for a sphere's outline" \
  " (with \"-sphere\" option), since the" \
  " the stretch of the sphere's outline depends on the" \
  " camera's spread ant on the position of its" \
  " optical axis in the image.\n" \
  "\n" \
  "  -noise {NOISE}\n" \
  "    This parameter is the standard deviation of the" \
  " noise in the darkest parts of the image.  It is used to" \
  " compute the relative gradient" \
  " image.  See {float_image_gradient_sqr_relative} for" \
  " details.  Its value should be chosen so as to bring out" \
  " the object's outline in the gradient" \
  " image, while nearby noise is supressed.  The default" \
  " is " stringify(fep_default_noise) ".\n" \
  "\n" \
  "  -minRadius {MIN_RADIUS}\n" \
  "    This optional parameter specifies the minimum" \
  " alowed radius in multiscale fitting.  Namely, the" \
  " program will use multiscale fitting only if the" \
  " guess radius is at least twice {MIN_RADIUS}.  If" \
  " multiscale fitting is not possible, the program" \
  " always uses single-scale fitting.  The default" \
  " is \"minRadius " stringify(fep_default_minRadius) "\".\n" \
  "\n" \
  "  -debug\n" \
  "    This optional keyword asks for extra diagnostic printouts" \
  " and images.  The latter include \"{PREFIX}-ctr.fni\", a plot" \
  " of the mismatch as the center position is varied around the given" \
  " position; and \"{PREFIX}-ctr.fni\", a plot of the mismatch" \
  " as the radius and stretch length are varied around" \
  " the given values.  These files are in the FNI format" \
  " (see {float_image.h}) and may be viewed with fni_plot(1).\n" \
  "\n" \
  "  -outPrefix {PREFIX} \n" \
  "    Specifies the common prefix for names of all output" \
  " files.  This parameter is mandatory.\n" \
  "\n" \
  "ELLIPSE PARAMETERS\n" \
  ellipse_crs_args_center_adjust_HELP_INFO "  The default" \
  " {CTRX,CTRY} is the center of the photo, and the default {CTR_ADJUST} is" \
  " zero.\n" \
  "\n" \
  ellipse_crs_args_radius_adjust_HELP_INFO "  The" \
  " default {RAD} is the largest radius" \
  " that will fit in the photo, minus 1 pixel; and the" \
  " default {RAD_ADJUST} is zero.\n" \
  "\n" \
  ellipse_crs_args_stretch_adjust_HELP_INFO "  For" \
  " \"-circle\" and \"-sphere\" search, the" \
  " stretch and adjstment should be zero or" \
  " omitted.  For \"-ellipse\" search, the" \
  " default for {STRX}, {STRY}, and {STR_ADJUST} is zero.\n" \
  "\n" \
  "CAMERA PARAMETERS\n" \
  pst_camera_args_viewpoint_HELP_INFO "  This information" \
  " is relevant only" \
  " for the \"-sphere\" option.  The default" \
  " is \"viewpoint 0 0 0 1\", a point at infinity on the Z axis.\n" \
  "\n" \
  pst_camera_args_center_HELP_INFO "  This information is relevant only" \
  " for the \"-sphere\" option.  The default is the center of the image.\n" \
  "\n" \
  pst_camera_args_spread_adjust_HELP_INFO "  The default" \
  " is " stringify(fep_default_camera_res) ", with zero adjustment.\n" \
  "\n" \
  "DOCUMENTATION OPTIONS\n" \
  argparser_help_info_HELP_INFO "\n" \
  "\n" \
  "SEE ALSO\n" \
  "  make_sphere_normal_map(1), photo_to_normal(1)," \
  " normal_to_slope(1), slope_to_height(1)," \
  " slope_to_normal(1), pnm(5), pnm_to_fni(1), fni_to_pnm(1).\n" \
  "\n" \
  "AUTHOR\n" \
  "  Created by Jorge Stolfi, IC-UNICAMP, on feb/2009.\n" \
  "  Based on work by Rafael Saracchini, IC-UFF, on jul/2005.\n" \
  "\n" \
  "MODIFICATION HISTORY\n" \
  "  2009-02-15 created from pieces of {fni_fit_sphere_to_photo} [J. Stolfi].\n" \
  "  2009-02-25 added the \"-sphere\" and \"-circle\" options [J. Stolfi].\n" \
  "  2012-01-25 modified to use {minn_plot.h} [J. Stolfi].\n" \
  "\n" \
  "WARRANTY\n" \
  argparser_help_info_NO_WARRANTY "\n" \
  "\n" \
  "RIGHTS\n" \
  "  " fit_ellipse_to_photo_C_COPYRIGHT ".\n" \
  "\n" \
  argparser_help_info_STANDARD_RIGHTS ""

#define stringify(x) strngf(x)
#define strngf(x) #x

#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <values.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <r3.h> 
#include <vec.h>
#include <r3x3.h> 
#include <ellipse_crs.h> 
#include <float_image.h>
#include <float_image_read_pnm.h>
#include <float_image_gradient.h>
#include <float_image_paint.h> 
#include <affirm.h>
#include <ellipse_crs.h>
#include <ellipse_crs_args.h>
#include <jsfile.h>
#include <argparser.h>
#include <argparser_extra.h>
#include <minn_plot.h>

#include <pst_basic.h>
#include <pst_camera.h>
#include <pst_geom.h>
#include <pst_fit_ellipse.h>
#include <pst_fit_sphere.h>

typedef enum 
  { fep_kind_ELLIPSE, /* Search for a general ellipse. */
    fep_kind_CIRCLE,  /* Search for a circle. */
    fep_kind_SPHERE   /* Search for projection of a sphere. */
  } fep_kind_t;
  /* A kind of search to perform. */
  
static char* fep_kind_name[3] = { "ellipse", "circle", "sphere" };
    
typedef struct options_t
  { char *image;            /* Name of the PNM file with the sphere's photo. */
    bool_t debug;           /* If TRUE, generates extra diagnostics. */
    char *outPrefix;        /* Prefix for output file names. */
    /* Geometric parameters and adjustment amounts: */
    pst_camera_t C;         /* Camera parameters. */
    ellipse_crs_t E;        /* Approximate shape and position of ellipse. */
    double ctrAdj;          /* Max adjustment allowed in {E.ctr} coords. */
    double radAdj;          /* Max adjustment allowed in {E.rad}. */
    double strAdj;          /* Max adjustment allowed in {E.str} coords. */
    double GAdj;          /* Max adjustment in spread of {C}. */
    /* Parameters for multiscale fitting: */
    fep_kind_t kind;        /* Kind of search: sphere, circle, etc. */
    double noise;           /* RMS noise level for gradient computation. */
    double minRadius;       /* Min acceptable radius in any recursive call. */
  } options_t;
  
float_image_t *fep_read_uint16_image(char *fname);
  /* Reads the file "{fname}" (or {stdin} if {fname} is "-"), 
    which must contain an image in PNM format, and 
    converts it to a float image with samples in 
    the range {[0_1]}. */

void fep_provide_defaults
  ( fep_kind_t kind,
    int NX,
    int NY,
    pst_camera_t *C,
    double *GAdj, 
    ellipse_crs_t *E,
    double *ctrAdj,
    double *radAdj,
    double *strAdj
  );
  /* Substitutes appropriate defaults for the NANs in the camera
    parameters {*C}, the ellipse parameters {*E}, and their adjustment
    amounts, depending on the search kind {kind}. */
    
void fep_fit_ellipse
  ( float_image_t *IMG, 
    options_t *o,
    pst_camera_t *C,
    ellipse_crs_t *E
  );
  /* Finds the best-fitting ellipse to the image {IMG},
     starting with the geometry {o->E}, adjusted as specified in {o}.
     Returns the fitted ellipse parameters in {*E}, and the fitted 
     camera parameters in {*C}. */
     
void fep_plot_goal_function
  ( char *prefix,
    char *tag,
    float_image_t *IGR,
    ellipse_crs_t *E,
    double ctrVar,
    double radVar, 
    double strVar
  );
  /* Writes a FNI image file "{prefix}-{tag}.fni" containing a 2D plot
    of {pst_fit_ellipse_eval} for various ellipses. 

    The X axis of the plot corresponds to variation in the X
    coordinate of the center (if {ctrVar} is nonzero) and/or the
    radius (if {radVar} is nonzero).
    
    The Y axis of the plot corresponds to variation in the Y
    coordinate of the center (if {ctrVar} is nonzero) and/or the
    stretch vector's length (if {strVar} and {E.str} are nonzero). */

float_image_t *fep_compute_fit_image
  ( ellipse_crs_t *E, 
    float_image_t *IMG, 
    bool_t grad,
    double noise
  );
  /* Computes a monochrome image {FIT} consisting of the outline of an
    ellipse whose parameters are described by {E} drawn over an
    effaced copy ot {IMG} (if {grad} is false) or of its relative
    squared gradient (if {grad} is true). The {noise} level is used
    when computing the relative squared gradient. */

float_image_t *fep_compute_msk_image(ellipse_crs_t *E, int NX, int NY);
  /* Computes a monochromatic image {MSK} with size {NX} by {NY} where
    the value of each pixel is the fraction of its area that is
    covered by the ellipse described in {E}. */

void fep_write_goal_plot_images(float_image_t *IMG, ellipse_crs_t *E, options_t *o);
  /* Writes diagnostic images, containing 2D plots of the goal
     function around the ellipse {E}. */

void fep_write_ellipse_params(char *prefix, char *tag, ellipse_crs_t *E);
  /* Writes the geometric parameters {E} of a sphere to the file
    "{prefix}-{tag}.epar", in a format compatible with
    {ellipse_crs_args_parse}. */

void fep_write_camera_params(char *prefix, char *tag, pst_camera_t *C);
  /* Writes the camera parameters {C} the file
    "{prefix}-{tag}.cpar", in a format compatible with
    {pst_camera_args_parse}. */

void fep_write_sub_image_as_pnm
  ( char *prefix, 
    char *tag, 
    float_image_t *A,
    bool_t isMask,
    int xLo,
    int xHi,
    int yLo, 
    int yHi
  );
  /* Writes to a PNM file named "{prefix}-{tag}.{ext}" the image {A},
    clipped to the rectangle {[xLo _ xHi] × [yLo _ yHi]}.
    The extension {ext} is either "ppm" or "pbm"
    dependng on the number of channels of {A}.
    The parameter {isMask} tells whether {A} is a mask or a photo;
    this affects how samples are rounded. */

void fep_write_image_as_fni(char *name, float_image_t *A);
  /* Writes image {IMG} to a FNI file called "{name}.fni",
    without any sample rescaling or encoding. */
    
void fep_write_image_as_pnm(char *name, float_image_t *A, bool_t isMask);
  /* Writes image {IMG} to a PGM file named "{name}.pgm" or to a PPM
    file named "{name}.ppm", depending on the number of channels,
    using {VIEW_GAMMA,VIEW_BIAS} gamma encoding. The parameter
    {isMask} tells whether {A} is a mask or a photo; this affects how
    samples are rounded. */

options_t *fep_parse_options(int argc, char **argv);
  /* Parses the command line options, returns them in an {options_t}. */

int main (int argc,char** argv);
  /* Main program. */

#define Pr fprintf
#define Er stderr

#define X c[0]
#define Y c[1]
#define Z c[2]
  /* Coordinates of {r2+t} or {r3_t}. */

#define fep_default_noise 0.01
  /* Default value for the {noise} option (RMS noise level in the
    darkest parts of image). */

#define fep_default_minRadius 5.0
  /* Default value of {minRadius}option (min radius in reduced-scale
    recursion), in pixels. */

#define fep_default_camera_zoom +INF
  /* Default value of {C.zoom} (focal length) option. */

/* IMPLEMENTATIONS */

int main (int argc,char** argv)
  { 
    /* Parse options from the command line: */
    options_t *o = fep_parse_options(argc, argv);

    /* Read input image and grab its dimensions: */
    float_image_t *IMG = fep_read_uint16_image(o->image);
    int NC = IMG->sz[0];  /* Image channels. */
    int NX = IMG->sz[1];  /* Image width (pixels). */
    int NY = IMG->sz[2];  /* Image height (pixels). */
    Pr(Er, "searching for %s\n", fep_kind_name[o->kind]);
    Pr(Er, "image channels = %d\n", NC);
    Pr(Er, "image size = %d × %d\n", NX, NY);

    /* Provide defaults for camera and ellipse parameters: */
    fep_provide_defaults
      ( o->kind, NX, NY,
        &(o->C), &(o->GAdj), 
        &(o->E), &(o->ctrAdj), &(o->radAdj), &(o->strAdj)
      );

    /* Compute and print the angular span of the image. */
    double G = pst_camera_spread(&(o->C.O));
    r2_t Q = pst_camera_center_cartesian(&(o->C.O));
    double xApt = (180/M_PI)*2*atan(0.5*NX*G);
    double yApt = (180/M_PI)*2*atan(0.5*NY*G);
    Pr(Er, "angular aperture of camera = %6.2f × %6.2f (degrees)\n", xApt, yApt);
    
    /* Compute and write the input image with the guessed ellipse on top: */
    float_image_t *IGU = fep_compute_fit_image(&(o->E), IMG, FALSE, 1.0);
    fep_write_sub_image_as_pnm(o->outPrefix, "igu", IGU, FALSE, 0, NX, 0, NY);
    
    /* Compute the best-fitting (hopefully) ellipse {E}: */
    pst_camera_t C;
    ellipse_crs_t E;
    fep_fit_ellipse(IMG, o, &C, &E);
    
    /* Write the ellipse and camera parameters relative to the full image: */
    fep_write_ellipse_params(o->outPrefix, "full", &E);
    fep_write_camera_params(o->outPrefix, "full", &C);
    
    /* Generate diagnostic images if requested: */
    if (o->debug) { fep_write_goal_plot_images(IMG, &E, o); }
    
    /* Compute and write the input image with the ellipse on top: */
    float_image_t *FIT = fep_compute_fit_image(&E, IMG, FALSE, 1.0);
    fep_write_sub_image_as_pnm(o->outPrefix, "fit", FIT, FALSE, 0, NX, 0, NY);
    
    /* Compute and write the gradient image with the ellipse on top: */
    float_image_t *FGR = fep_compute_fit_image(&E, IMG, TRUE, o->noise);
    fep_write_sub_image_as_pnm(o->outPrefix, "fgr", FGR, FALSE, 0, NX, 0, NY);
    
    /* Compute and write the full mask: */
    float_image_t *MSK = fep_compute_msk_image(&E, NX, NY);
    fep_write_sub_image_as_pnm(o->outPrefix, "msk", MSK, TRUE, 0, NX, 0, NY);
    
    /* Get a bounding box with some safety margin: */
    double mrg = 2.0;
    int xLo, xHi, yLo, yHi;
    ellipse_crs_int_bbox(&E, mrg, &xLo, &xHi, &yLo, &yHi);

    Pr(Er, "gauge cropping commands:\n"); 
    Pr(Er, "  convert {IN} -crop '%dx%d+%d+%d' {OUT}\n", xHi-xLo, yHi-yLo, xLo, NY-yHi);
    Pr(Er, "  pnmcut %d %d %d %d < {IN} > {OUT}\n", xLo, NY-yHi, xHi-xLo, yHi-yLo);
    
    /* Write the clipped versions of the image and mask: */
    fep_write_sub_image_as_pnm(o->outPrefix, "clip-img", IMG, FALSE, xLo, xHi, yLo, yHi);
    fep_write_sub_image_as_pnm(o->outPrefix, "clip-msk", MSK, TRUE,  xLo, xHi, yLo, yHi);
    
    /* Compute the ellipse parameters {EC} relative to the clipped images: */
    ellipse_crs_t EC = E; 
    r2_t shift = (r2_t){{ xLo, yLo }};
    r2_sub(&(E.ctr), &shift, &(EC.ctr));
    
    /* Compute the camera parameters {CC} for the clipped images: */
    r2_t QC; r2_sub(&Q, &shift, &QC);
    pst_camera_t CC;
    CC.O = pst_camera_viewpoint_from_center_spread(&QC, G);

    /* Write the ellipse and camera parameters relative to the clipped image: */
    fep_write_ellipse_params(o->outPrefix, "clip", &EC);
    fep_write_camera_params(o->outPrefix, "clip", &CC);
    
    float_image_free(MSK); MSK = NULL;
    float_image_free(FGR); FGR = NULL;
    float_image_free(FIT); FIT = NULL;
    float_image_free(IGU); IGU = NULL;
    float_image_free(IMG); IMG = NULL;

    return 0;
  }
  
void fep_provide_defaults
  ( fep_kind_t kind,
    int NX,
    int NY,
    pst_camera_t *C,
    double *GAdj, 
    ellipse_crs_t *E,
    double *ctrAdj,
    double *radAdj,
    double *strAdj
  )
  {
    if (kind == fep_kind_SPHERE)
      { /* Get or choose the camera's  spread: */
        double G = pst_camera_spread(&(C->O));
        if (isnan(G))
          { /* Camera at infinity: */ 
            G = 0;
          }

        /* Get or choose the camera's axis position: */
        r2_t Q = pst_camera_center_cartesian(&(C->O));
        if (isnan(Q.X) || isnan(Q.Y))
          { /* Optical center is center of image: */
            Q = (r2_t) {{ 0.5*NX, 0.5*NY }};
          }

        /* Reassmeble the camera {C} from updated center and spread: */
        C->O = pst_camera_viewpoint_from_center_spread(&Q, G);
        if (isnan(*GAdj)) { (*GAdj) = 0; }
      }
    else
      { /* Camera is irrelevant, but, just in case make it finite at very large distance: */
        C->O = (hr3_point_t) {{{ 1.0, 0.0, 0.0, 1.0e7 }}};
        if ((! isnan(*GAdj)) && ((*GAdj) != 0))
          { 
            fprintf(stderr, "%s:%d: ** Camera adjustment ignored\n", __FUNCTION__, __LINE__);
          }
        (*GAdj) = 0.0;
      }
      
    /* Ellipse center: */
    if (isnan(E->ctr.X) || isnan(E->ctr.Y))
      { E->ctr = (r2_t) {{ 0.5*NX, 0.5*NY }}; }
    if (isnan(*ctrAdj)) { (*ctrAdj) = 0; }
      
    /* Ellipse radius: */
    if (isnan(E->rad))
      { double xrad = fmin(E->ctr.X, NX - E->ctr.X) - 1;
        double yrad = fmin(E->ctr.Y, NY - E->ctr.Y) - 1;
        E->rad = fmin(xrad, yrad);
        demand(E->rad > 0, "no space for sphere at this position");
      }
    if (isnan(*radAdj)) { (*radAdj) = 0; }
    
    /* Stretch vector: */
    switch(kind)
      { 
        case fep_kind_ELLIPSE:
          if (isnan(E->str.X) || isnan(E->str.Y))
            { E->str = (r2_t) {{ 0, 0 }}; }
          if (isnan(*strAdj)) { (*strAdj) = 0; }
          break;
        
        case fep_kind_CIRCLE:
          /* Stretch of a circle is always zero: */
          if 
            ( ((! isnan(E->str.X)) && (E->str.X != 0)) ||
              ((! isnan(E->str.Y)) && (E->str.Y != 0)) ||
              ((! isnan(*strAdj)) && ((*strAdj) != 0))
            )
            { fprintf(stderr, "** stretch specs ignored for \"-circle\"\n"); }
          E->str = (r2_t) {{ 0, 0 }};
          (*strAdj) = 0;
          break;
        
        case fep_kind_SPHERE:
          demand(FALSE, "!!! Not implemented yet !!!");
          break;
      }
  }      

void fep_fit_ellipse
  ( float_image_t *IMG, 
    options_t *o,
    pst_camera_t *C,
    ellipse_crs_t *E
  )
  {
    Pr(Er, "finding the best-fit ellipse...\n");
    
    /* Get/check image dimensions: */
    int NX = IMG->sz[1];
    int NY = IMG->sz[2];

    /* Print the user's guess: */
    Pr(Er, "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    Pr(Er, "initial guess for ellipse and adjustment amounts:\n");
    ellipse_crs_args_adjust_print(Er, &(o->E), o->ctrAdj, o->radAdj, o->strAdj, "%8.2f");
    Pr(Er, "initial guess for camera and adjustment amounts:\n");
    pst_camera_args_adjust_print_center_spread(Er, &(o->C), 0.0, o->GAdj, "%8.2f", "%12.10f");
    Pr(Er, "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
    /* Check whether the initial guess is within the image bounds: */
    int xLo, xHi, yLo, yHi;
    double mrg = 0.0;
    ellipse_crs_int_bbox(&(o->E), mrg, &xLo, &xHi, &yLo, &yHi);
    Pr(Er, "initial bbox: [%d _ %d] × [%d _ %d]\n", xLo, xHi, yLo, yHi);
    demand((xLo >= 0) && (xHi <= NX), "guess extends outside valid X range");
    demand((yLo >= 0) && (yHi <= NY), "guess extends outside valid Y range");

    /* Do the fitting, according to {o->kind}: */
    ellipse_crs_t EFit = o->E; /* Fitted ellipse. */
    pst_camera_t  CFit = o->C; /* Fitted camera. */
    double H = +INF;                /* Mismatch of {E}. */
    int maxIts = 15; /* Max iterations of the minimizer at coarsest scale. */
    switch (o->kind)
      {
        case fep_kind_ELLIPSE:
        case fep_kind_CIRCLE:
          H = pst_fit_ellipse_multiscale
            ( IMG, o->noise, 
              &EFit, o->ctrAdj, o->radAdj, o->strAdj,
              o->minRadius, maxIts
            );
          break;
          
        case fep_kind_SPHERE:
          /* r2_t Q = ...; */
          /* double G = ...;  */
          /* r2_t K = ...; */
          /* double R = ...; */
          /* H = pst_fit_sphere_multiscale */
          /*   ( IMG, o->noise,  */
          /*     &Q, &G, &K, &R, o->GAdj, o->ctrAdj, o->radAdj, */
          /*     o->minRadius, maxIts */
          /*   ); */
          demand(FALSE, "!!! not implemented yet !!!");
          break;
      }
   
    /* Print the adjusted ellipse and camera: */
    Pr(Er, "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    Pr(Er, "adjusted ellipse:\n");
    ellipse_crs_args_adjust_print(Er, &EFit, 0.0, 0.0, 0.0, "%8.2f");
    Pr(Er, "mismatch H = %12.6f\n", H);  
    Pr(Er, "adjusted camera:\n");
    pst_camera_args_print(Er, &CFit, "%8.2f", "%12.10f");
    Pr(Er, "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
    /* Return the fitted camera and ellipse: */
    (*C) = CFit;
    (*E) = EFit;
  }

void fep_write_goal_plot_images(float_image_t *IMG, ellipse_crs_t *E, options_t *o)
  {
    float_image_t *IGR = float_image_gradient_sqr_relative(IMG, o->noise, TRUE);
    /* Adjustment values for plot: */
    double ctrVar = (o->ctrAdj > 0 ? o->ctrAdj : 0.1 * o->E.rad);
    double radVar = (o->ctrAdj > 0 ? o->ctrAdj : 0.1 * o->E.rad);
    double strVar = (o->strAdj > 0 ? o->strAdj : 0.1 * o->E.rad);
    fep_plot_goal_function(o->outPrefix, "ctr", IGR, E, ctrVar, 0, 0);
    fep_plot_goal_function(o->outPrefix, "rad", IGR, E, 0, radVar, strVar);
    float_image_free(IGR);
  }

void fep_plot_goal_function
  ( char *prefix,
    char *tag,
    float_image_t *IGR,
    ellipse_crs_t *E,
    double ctrVar,
    double radVar, 
    double strVar
  )
  {
    Pr(Er, "generating a goal function plot... \n");
    bool_t debug = FALSE;
    
    /* Paranoia: */
    demand(E->rad > 0, "invalid mean radius");
    demand(ctrVar >= 0, "invalid {ctrVar}");
    demand(radVar >= 0, "invalid {radVar}");
    demand(strVar >= 0, "invalid {strVar}");
    
    /* Compute the stretch length and direction: */
    r2_t strDir;
    double strLen = r2_dir(&(E->str), &strDir);
    
    /* For the plot we vary only the length of the stretch. So: */
    if (strLen == 0) { strVar = 0; }
    
    /* Report the mean ellipse: */
    Pr(Er, "mean ellipse: \n");
    ellipse_crs_args_print(Er, E, "%8.2f");
    
    /* Report the variation along the X axis: */
    Pr(Er, "X axis:\n");
    if (ctrVar == 0)
      { Pr(Er, "  center X is fixed at %6.3f\n", E->ctr.X); }
    else
      { double xctrLo = E->ctr.X - ctrVar;
        double xctrHi = E->ctr.X + ctrVar;
        Pr(Er, "  center X ranging in [ %6.3f _ %6.3f ]\n", xctrLo, xctrHi);
      }
    if (radVar == 0)
      { Pr(Er, "  radius is fixed at  %6.3f\n", E->rad); }
    else
      { double radHi = E->rad + radVar;
        double radLo = E->rad / (radHi/E->rad);
        Pr(Er, "  radius ranging in [ %6.3f _ %6.3f ]\n", radLo, radHi);
      }
      
    /* Report the variation along the Y axis: */
    Pr(Er, "Y axis:\n");
    if (ctrVar == 0)
      { Pr(Er, "  center Y is fixed at %6.3f\n", E->ctr.Y); }
    else
      { double yctrLo = E->ctr.Y - ctrVar;
        double yctrHi = E->ctr.Y + ctrVar;
        Pr(Er, "  center Y ranging in [ %6.3f _ %6.3f ]\n", yctrLo, yctrHi);
      }
    if (strVar == 0)
      { Pr(Er, "  stretch is fixed at ( %6.3f %6.3f )\n", E->str.X, E->str.Y); }
    else
      { Pr(Er, "  stretch direction is fixed at ( %6.3f %6.3f )\n", strDir.X, strDir.Y);
        double strHi = strLen + strVar;
        double strLo = strLen / (strHi/strLen);
        Pr(Er, "  stretch length ranges in [ %6.3f _ %6.3f ]\n", strLo, strHi);
      }

    int nx = 2;     /* Number of parameters to vary. */
    
    ellipse_crs_t EMin = *E; /* The best ellipse seen so far. */
    double HMin = +INF;      /* Its mismatch. */

    auto double goalf(int n, double x[]);
      /* Goal function for ellipse fitting. Also keeps track of {HMin,EMin}. */

    double goalf(int n, double x[])
      { 
        /* Evaluate the mismatch for the parameters {x[0..n-1]}: */
        double sa = x[0];
        double sb = x[1];
        ellipse_crs_t ETry = (*E);
        ETry.ctr.X = E->ctr.X + sa * ctrVar;
        ETry.ctr.Y = E->ctr.Y + sb * ctrVar;
        double radMag = pow((E->rad + radVar)/E->rad, sa);
        ETry.rad = E->rad * radMag;
        double strMag = (strLen == 0 ? 1 : pow((strLen + strVar)/strLen, sb));
        r2_scale(strMag, &(E->str), &(ETry.str));
        if (debug && ((radVar != 0) || (strVar != 0)))
          { Pr(Er, "    rad = %10.6f", ETry.rad); 
            Pr(Er, "    str = ( %10.6f %10.6f )\n", ETry.str.X, ETry.str.Y); 
          }
        /* Evaluate the ellipse: */
        double HTry = pst_fit_ellipse_eval(IGR, &ETry);

        /* Save the best one: */
        if (HTry < HMin) { HMin = HTry; EMin = ETry; }
        
        return HTry;
      }

    /* Allocate the plot image {PLT}: */
    int NS = 30; /* Number of steps on each side of {*E}. */

    /* Fill the plot image, remember the best ellipse {EMin,HMin}: */
    double xo[2] = { 0, 0 };
    double xa[2] = { 1, 0 };
    double xb[2] = { 0, 1 };

    /* Write plot as a FNI image file: */
    char *fname = jsprintf("%s-%s.fni", prefix, tag);
    FILE *wr = open_write(fname, TRUE);
    minn_plot_2D_float_image(wr, nx, goalf, xo, xa, xb, NS);
    fclose(wr);
    free(fname);

    /* Report the best ellipse seen: */
    Pr(Er, "best brute-force fit:\n");
    ellipse_crs_args_print(Er, &EMin, "%8.2f");
  }

float_image_t *fep_compute_fit_image
  ( ellipse_crs_t *E, 
    float_image_t *IMG, 
    bool_t grad,
    double noise
  )
  { 
    /* Get/check image dimensions: */
    int NX = IMG->sz[1];
    int NY = IMG->sz[2];
    
    int c;
    
    /* Choose the reference image {REF} and its max sample {vMax}: */
    float_image_t *REF = NULL;
    float vMax;
    if (grad)
      { /* Background is the gradient image: */
        REF = float_image_gradient_sqr_relative(IMG, noise, TRUE);
        /* Normalize its samples to {[0-1]} scale: */
        vMax = 1.0e-100; /* Just in case {REF} is all zeros. */
        float_image_update_sample_range(REF, 0, NULL, &vMax);
      }
    else
      { /* Background is the original image: */
        REF = IMG;
        vMax = 1.0;
      }
    
    /* Make a three-channel copy of {REF}, reduced in intensity: */
    int NCR = REF->sz[0];
    float_image_t *FMG = float_image_new(3, NX, NY);
    for (c = 0; c < 3; c++)
      { float_image_set_channel(FMG, c, REF, (NCR == 1 ? 0 : c));
        float_image_rescale_samples(FMG, c, 0.0, vMax, 0.0, 0.80);
      }
    
    /* Draw the outline in red: */
    double hwd = 0.5;
    (void)float_image_paint_ellipse_crs(FMG, 0, E, hwd, NAN, 1.0, 3);
    
    /* Clean up: */
    if (REF != IMG) { float_image_free(REF); REF = NULL; }
    
    return FMG;
  }

float_image_t *fep_compute_msk_image(ellipse_crs_t *E, int NX, int NY)
  { 
    /* Make an image with the same size as the original: */
    float_image_t *MSK = float_image_new(1, NX, NY);
    float_image_fill(MSK, 0.0);
    
    /* Paint the precise filled ellipse into it: */
    (void)float_image_paint_ellipse_crs(MSK, 0, E, 0.0, 1.0, NAN, 3 );
    
    return MSK;
  }

void fep_write_ellipse_params(char *prefix, char *tag, ellipse_crs_t *E)
    char *fname = jsprintf("%s-%s.epar", prefix, tag);
    FILE *wr = open_write(fname, TRUE);
    ellipse_crs_args_print(wr, E, "%8.2f");
    fclose(wr);
    free(fname);
  }

void fep_write_camera_params(char *prefix, char *tag, pst_camera_t *C)
    char *fname = jsprintf("%s-%s.cpar", prefix, tag);
    FILE *wr = open_write(fname, TRUE);
    pst_camera_args_print(wr, C, "%8.2f", "%18.16f");
    fclose(wr);
    free(fname);
  }

void fep_write_sub_image_as_pnm
  ( char *prefix, 
    char *tag, 
    float_image_t *A,
    bool_t isMask,
    int xLo,
    int xHi,
    int yLo, 
    int yHi
  )
  { /* Do we really need to crop? */
    int NC, NX, NY;
    float_image_get_size(A, &NC, &NX, &NY);
    bool_t crop = ((xLo != 0) || (xHi != NX) || (yLo != 0) || (yHi != NY));
    /* Get the (sub-)image {S} to write: */
    float_image_t *S = (crop ? float_image_crop(A, 0, NC, xLo, xHi, yLo, yHi, 0) : A);
    /* Write it: */
    char *name = jsprintf("%s-%s", prefix, tag);
    fep_write_image_as_pnm(name, S, isMask);
    if (S != A) { float_image_free(S); }
    free(name);
  }

float_image_t *fep_read_uint16_image(char *fname)
  { bool_t yup = FALSE; /* Use Y axis down, as in {pnmcut} and {convert}. */
    bool_t isMask = FALSE; /* Assume pixels have a smooth distribution. */
    float_image_t *IMG = float_image_read_pnm_named(fname, isMask, VIEW_GAMMA, VIEW_BIAS, yup, TRUE, FALSE);
    return IMG;
  }

void fep_write_image_as_pnm(char *name, float_image_t *A, bool_t isMask)
  { int NC = A->sz[0];
    char *ext = (NC == 1 ? "pgm" : "ppm");
    char *fname = jsprintf("%s.%s", name, ext);
    bool_t yup = FALSE; /* Use Y axis down, as in {pnmcut} and {convert}. */
    float_image_write_pnm_named(fname, A, isMask, VIEW_GAMMA, VIEW_BIAS, yup, TRUE, FALSE);
    free(fname);
  }

void fep_write_image_as_fni(char *name, float_image_t *A)
    char *fname = jsprintf("%s.fni", name);
    FILE *wr = open_write(fname, TRUE);
    float_image_write(wr, A);
    free(fname);
  }

options_t *fep_parse_options(int argc, char **argv)
  {
    argparser_t *pp = argparser_new(stderr, argc, argv);
    argparser_set_help(pp, PROG_NAME " version " PROG_VERS ", usage:\n" PROG_HELP);
    argparser_set_info(pp, PROG_INFO);
    argparser_process_help_info_options(pp);
    
    options_t *o = (options_t *)malloc(sizeof(options_t)); 
    
    argparser_get_keyword(pp, "-image");
    o->image = argparser_get_next_file_name(pp);

    /* Parse the initial ellipse params and adjstment amounts: */
    if (argparser_keyword_present(pp, "-sphere"))
      { o->kind = fep_kind_SPHERE; }
    else if (argparser_keyword_present(pp, "-circle"))
      { o->kind = fep_kind_CIRCLE; }
    else if (argparser_keyword_present(pp, "-ellipse"))
      { o->kind = fep_kind_ELLIPSE; }
    else
      { argparser_error(pp, "must specify \"-sphere\", \"-circle\", or \"-ellipse\""); }
    ellipse_crs_args_parse(pp, &(o->E), &o->ctrAdj, &o->radAdj, &o->strAdj);
    
    /* Check for inappropriate stretch specs given {o->kind}: */
    if ((o->kind == fep_kind_SPHERE) || (o->kind == fep_kind_CIRCLE))
      { /* The stretch must be zero or undefined: */
        if
          ( ((! isnan(o->E.str.X)) && (o->E.str.X != 0)) ||
            ((! isnan(o->E.str.Y)) && (o->E.str.Y != 0)) ||
            ((! isnan(o->strAdj)) && (o->strAdj != 0))
          )
          { argparser_error(pp, "\"stretch\" is not allowed in this mode"); }
      }
      
    /* Parse the camera parameters: */
    if (argparser_keyword_present(pp, "-camera"))
      { pst_camera_args_parse(pp, &o->C, NULL, NULL, &(o->GAdj)); }
    else
      { /* Set optical center to NAN, will be filled in later: */
        o->C.O = (hr3_point_t) {{{ NAN, NAN, NAN, NAN }}};
        /* Provide the default spread and adjustment: */
        o->GAdj = 0.0;
      }
      
    if (argparser_keyword_present(pp, "-minRadius"))
      { o->minRadius = argparser_get_next_double(pp, 0.0, 1.0e+10); }
    else
      { o->minRadius = fep_default_minRadius; }
      
    if (argparser_keyword_present(pp, "-noise"))
      { o->noise = argparser_get_next_double(pp, 0.0, 1.0); }
    else
      { o->noise = fep_default_noise; }
      
    o->debug = argparser_keyword_present(pp, "-debug");

    /* Parse the output filename prefix: */
    argparser_get_keyword(pp, "-outPrefix");
    o->outPrefix = argparser_get_next(pp);

    argparser_finish(pp);
    return o;
  }
