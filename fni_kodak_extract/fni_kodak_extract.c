#define PROG_NAME "fni_kodak_extract"
#define PROG_DESC "Extract a Kodak Q-13 chart from an image"
#define PROG_VERS "1.0"

/* Last edited on 2015-10-18 02:58:28 by stolfilocal */

#define PROG_C_COPYRIGHT "Copyright © 2004 by the State University of Campinas (UNICAMP)."

#define PROG_HELP \
  "  " PROG_NAME "\\\n" \
  "    " fke_corners_HELP " \\\n" \
  "    [ -scale {CSCALE} ] \\\n" \
  "    [ -yFlip ] \\\n" \
  "    [ -grayScaleName {SCALE_FNI} ] \\\n" \
  "    [ -bodyStripName {BODY_STRIP_FNI} ] \\\n" \
  "    [ -frameStripName {FRAME_STRIP_FNI} ] \\\n" \
  "    < {INPUT_FNI} \\\n" \
  "    > {OUTPUT_FNI}"

#define fke_corners_HELP \
  "-corners tl {TLX} {TLY} tr {TRX} {TRY} bl {BLX} {BLY} br {BRX} {BRY}"

#define PROG_INFO \
  "NAME\n" \
  "  " PROG_NAME " - " PROG_DESC ".\n" \
  "\n" \
  "SYNOPSIS\n" \
  PROG_HELP "\n" \
  "\n" \
  "DESCRIPTION\n" \
  "  Reads from standard input a digital photograph that" \
  " includes the Kodak Q-13 grayscale chart in arbitrary perspective" \
  " (conical or cylindrical).  Extracts the sub-image consisting of the" \
  " Q-13, with some of the surrounding" \
  " background, and writes it to standard output as a separate" \
  " image, in orthogonal projection with true aspect ratio, correcting" \
  " for perspective distortion.\n" \
  "\n" \
  "  Optionally the program extracts also the gray-scale" \
  " proper (the row of gray patches with varying densities" \
  " along the Q-13's bottom edge) and/or two narrow reference strips paralell to the" \
  " gray-scale.  The /body/ strip is taken from the Q-13's body, in the gray area" \
  " just above the scale.  The /frame/ strip is taken from" \
  " the background, just below the gray-scale.  These elements are" \
  " written to separate files named on the command line.\n" \
  "\n" \
  "  Parts of the gray-scale and/or the requested reference strips may lie" \
  " outside the input image.  The corresponding parts of the output images" \
  " are filled with an arbitrary gray value.\n" \
  "\n" \
  "  All input and output image files are in the FNI format. See" \
  " {float_image.h} for details.\n" \
  "\n" \
  "GENERAL OPTIONS\n" \
  "  " fke_corners_HELP " \n" \
  "    This mandatory argument specifies the coordinates of the corners of the Q-13 chart" \
  " on the input image.  The \"-corners\"keyword must be followed" \
  " by the four tags \"tl\" (top left), \"tr\" (top right)," \
  " \"bl\" (bottom left), and \"br\" (bottom right),  in any" \
  " order, each followed by the X and Y coordinates of the corresponding" \
  " corner of the chart.  The bottom edge of the Q-13 is, by" \
  " definition, the long side adjacent to the gray scale; and" \
  " the left edge is the short side adjacent to the chart's" \
  " `white' patch.  The coordinates may be fractional; they are" \
  " measured in pixels, in the input image coordinate system" \
  " (see the \"-yAxis\" option).\n" \
  "\n" \
  "  -scale {CSCALE}\n" \
  "    This optional argument specifies that the corner coordinates are" \
  " to be scaled by {CSCALE}.  Typically this option is used when the" \
  " coordinates have been measured on a full-size image and the input" \
  " is a reduced copy of the same.\n" \
  "\n" \
  "  -yFlip\n" \
  "    This optional keyword specifies that the Y coordinates" \
  " of the corners shoudl be complemented relative to the input" \
  " image's Y size.  It is useful when the coordinates have been" \
  " measured on a PNM or PNG image which was then converted" \
  " to FNI.\n" \
  "\n" \
  "  -grayScaleName {SCALE_FNI}\n" \
  "    Specifies the name of the file where the gray patch scale image" \
  " is to be written.\n" \
  "\n" \
  "  -bodyStripName {BODY_STRIP_FNI}\n" \
  "    Specifies the name of the file where the narrow reference strip" \
  " taken from the Q-13 body, just above the gray patch scale, is to be written.\n" \
  "\n" \
  "  -frameStripName {FRAME_STRIP_FNI}\n" \
  "    Specifies the name of the file where the narrow reference strip" \
  " taken from the background around the Q-13 body, just below the gray" \
  " patch scale, is to be written.\n" \
  "DOCUMENTATION OPTIONS\n" \
  argparser_help_info_HELP_INFO "\n" \
  "\n" \
  "SEE ALSO\n" \
  "  pnm_to_fni(1), fni_to_pnm(1).\n" \
  "\n" \
  "AUTHOR\n" \
  "  Created on 08/may/2006 by Jorge Stolfi, IC-UNICAMP, as part of {fni-kodak-adjust.c}.\n" \
  "\n" \
  "MODIFICATION HISTORY\n" \
  "  nov/2006 Rewritten to use sane PNM, argparser, etc. by J. Stolfi, IC-UNICAMP.\n" \
  "  jun/2007 Added \"-points\" option.  J. Stolfi, IC-UNICAMP.\n" \
  "  jul/2007 Added \"-yAxis\" option.  J. Stolfi, IC-UNICAMP.\n" \
  "  aug/2007 Rearranged the points in \"-points\".  J. Stolfi, IC-UNICAMP.\n" \
  "  dec/2008 Split off from {fni-kodak-adjust.c}.  J. Stolfi, IC-UNICAMP.\n" \
  "\n" \
  "WARRANTY\n" \
  argparser_help_info_NO_WARRANTY "\n" \
  "\n" \
  "RIGHTS\n" \
  "  " PROG_C_COPYRIGHT ".\n" \
  "\n" \
  argparser_help_info_STANDARD_RIGHTS

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
#include <r2.h> 
#include <r3x3.h> 
#include <vec.h>
#include <affirm.h>
#include <jsfile.h>
#include <argparser.h>

#include <pst_basic.h>
#include <pst_argparser.h>
#include <pst_Kodak_Q13.h>

/* GENERAL DEFINITIONS */

#define fke_chart_image_width 609
  /* Number of columns in chart cut-out image. */

typedef struct options_t
  { /* Q-13 chart geometry in input image (pixels, FNI system with Y axis up): */
    r2_t tl;  /* Top left corner of chart in input image. */
    r2_t tr;  /* Top right corner of chart in input image. */
    r2_t bl;  /* Bottom left corner of chart in input image. */
    r2_t br;  /* Bottom right corner of chart in input image. */
    double scale;  /* Scale factor for input coordinates. */
    bool_t yFlip;  /* If TRUE, complement the Y coordinates given. */
    /* Output options: */
    char *grayScaleName;   /* Filename for gray-scale image, or NULL. */
    char *bodyStripName;   /* Filename for body strip image, or NULL. */
    char *frameStripName;  /* Filename for frame strip image, or NULL. */
  } options_t;

/* INTERNAL PROTOTYPES */

float_image_t *fke_read_float_image(char *name);
  /* Reads a float image, in the format of {float_image_write}, from
    the named file (or {stdin} if {name} is "-"). */
    
void fke_write_float_image(char *name, float_image_t *img);
  /* Writes the image {img}, in the format of {float_image_write}, to
    the named file (or to {stdout} if {name} is "-"). */

options_t *fke_parse_options(int argc, char **argv);
  /* Parses the command line options, returns them in an {options_t}. */

void fke_parse_point(argparser_t *pp, r2_t *a);
  /* Parses the next two arguments on the command line as the (fractional) coordinates
    of a point, and stores them into {a}.  Requires that {a} be initialized with 
    {(+INF,+INF)}. */

void fke_check_point(argparser_t *pp, r2_t *a);
  /* Fails if {a} is {(+INF,+INF)}. */

int main (int argc,char** argv);
  /* Main program. */

/* IMPLEMENTATIONS */

int main (int argc,char** argv)
  { 
    /* Parse options from the command line: */
    options_t *o = fke_parse_options(argc, argv);

    /* Read actual photo: */
    float_image_t *img = fke_read_float_image("-");
    int NC, NX, NY;
    float_image_get_size(img, &NC, &NX, &NY);
      
    /* Get projective matrix from physical chart coords to {img} coords. */ 
    r3x3_t P; 
    pst_Kodak_Q13_get_matrix(&o->tl, &o->tr, &o->bl, &o->br, &P);
    if (o->scale != 1.0)
      { /* Compose {P} with a uniform scaling: */
        int a;
        for (a = 0; a < 2; a++) { P.c[a][1] *= o->scale; P.c[a][2] *= o->scale; }
      }
    if (o->yFlip)
      { /* Compose {P} with a Y-flipping matrix: */
        r3x3_t F; 
        r3x3_ident(&F);
        F.c[0][2] = NY;
        F.c[2][2] = -1;
        r3x3_mul(&P, &F, &P);
      }
    
    double pixelSize = 0.25; /* Pixel size in output chart/strip images (mm). */
    
    float_image_t *chartImg = pst_Kodak_Q13_extract_chart(img, &P, pixelSize);
    fke_write_float_image("-", chartImg);
    float_image_free(chartImg);
    
    if (o->grayScaleName != NULL)
      { float_image_t *grayScaleImg = pst_Kodak_Q13_extract_gray_scale(img, &P, pixelSize);
        fke_write_float_image(o->grayScaleName, grayScaleImg);
        float_image_free(grayScaleImg);
      }
    
    if (o->bodyStripName != NULL)
      { float_image_t *bodyStripImg = pst_Kodak_Q13_extract_body_strip(img, &P, pixelSize);
        fke_write_float_image(o->bodyStripName, bodyStripImg);
        float_image_free(bodyStripImg);
      }
    
    if (o->frameStripName != NULL)
      { float_image_t *frameStripImg = pst_Kodak_Q13_extract_frame_strip(img, &P, pixelSize);
        fke_write_float_image(o->frameStripName, frameStripImg);
        float_image_free(frameStripImg);
      }

    return 0;
  }

float_image_t *fke_read_float_image(char *name)
  { FILE *rd = open_read(name, TRUE);
    float_image_t *img = float_image_read(rd);
    if (rd != stdin) { fclose(rd); }
    return img;
  }

void fke_write_float_image(char *name, float_image_t *img)
  { FILE *wr = open_write(name, TRUE);
    float_image_write(wr, img);
    if (wr == stdout) { fflush(wr); } else { fclose(wr); }
  }

options_t *fke_parse_options(int argc, char **argv)
  { 
    argparser_t *pp = argparser_new(stderr, argc, argv);
    argparser_set_help(pp, PROG_NAME " version " PROG_VERS ", usage:\n" PROG_HELP);
    argparser_set_info(pp, PROG_INFO);
    argparser_process_help_info_options(pp);
    
    options_t *o = (options_t *)malloc(sizeof(options_t)); 
    
    o->tl = (r2_t){{ +INF, +INF }};
    o->tr = (r2_t){{ +INF, +INF }};
    o->bl = (r2_t){{ +INF, +INF }};
    o->br = (r2_t){{ +INF, +INF }};
    argparser_get_keyword(pp, "-corners");
    while (TRUE)
      { if (argparser_keyword_present_next(pp, "tl"))
          { fke_parse_point(pp, &(o->tl)); }
        else if (argparser_keyword_present_next(pp, "tr"))
          { fke_parse_point(pp, &(o->tr)); }
        else if (argparser_keyword_present_next(pp, "bl"))
          { fke_parse_point(pp, &(o->bl)); }
        else if (argparser_keyword_present_next(pp, "br"))
          { fke_parse_point(pp, &(o->br)); }
        else
          { /* That must be the end of "-corners" spec: */
            break;
          }
      }
    /* Check for missing corners: */
    fke_check_point(pp, &(o->tl));      
    fke_check_point(pp, &(o->tr));
    fke_check_point(pp, &(o->bl));
    fke_check_point(pp, &(o->br));
      
    if (argparser_keyword_present(pp, "-scale"))
      { o->scale = argparser_get_next_double(pp, 1.0e-10, 1.0e+10); }
    else
      { o->scale = 1.0; }
    
    o->yFlip = argparser_keyword_present(pp, "-yFlip");
    
    if (argparser_keyword_present(pp, "-grayScaleName"))
      { o->grayScaleName = argparser_get_next(pp); }
    else
      { o->grayScaleName = NULL; }
    
    if (argparser_keyword_present(pp, "-bodyStripName"))
      { o->bodyStripName = argparser_get_next(pp); }
    else
      { o->bodyStripName = NULL; }
    
    if (argparser_keyword_present(pp, "-frameStripName"))
      { o->frameStripName = argparser_get_next(pp); }
    else
      { o->frameStripName = NULL; }
    
    argparser_finish(pp);
    
    return o;
  }

void fke_parse_point(argparser_t *pp, r2_t *a)
  { if ((fabs(a->c[0]) != INF) || (fabs(a->c[1]) != INF))
      { argparser_error(pp, "the same corner was specified twice"); }
    a->c[0] = argparser_get_next_double(pp, -1000000.0, +1000000.0);
    a->c[1] = argparser_get_next_double(pp, -1000000.0, +1000000.0);
  }

void fke_check_point(argparser_t *pp, r2_t *a)
  { if ((fabs(a->c[0]) == INF) || (fabs(a->c[1]) == INF))
      { argparser_error(pp, "not all corners were specified"); }
  }
