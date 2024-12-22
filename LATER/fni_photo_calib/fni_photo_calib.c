#define PROG_NAME "fni_photo_calib"
#define PROG_DESC "computes a camera's light transfer table from a photo of a color scale"
#define PROG_VERS "1.0"

/* Copyright © 2004 by the State University of Campinas (UNICAMP).*/
/* See the copyright, authorship, and warranty notice at end of file.*/
/* Last edited on 2015-10-18 02:57:53 by stolfilocal */

!!! Generalize for color not just grayscale.

#define PROG_HELP \
  PROG_NAME "\\\n" \
  "    -steps {NS} \\\n" \
  "    { -scale {SCALE_FNI} \\\n" \
  "        { -KodakQ13 \\\n" \
  "        | { -position {OX} {OY} ] \\\n" \
  "            -stride {SX} {SY} \\\n" \
  "            -pixelSize {PIX_SIZE} \\\n" \
  "            { -albedos {ALB[1]} ... {ALB[NS]} \\\n" \
  "            | -colors {RED[1]} {GRN[1]} {BLU[1]} ... {RED[NS]} {GRN[NS]} {BLU[NS]} \\\n" \
  "            | -uniform \\\n" \
  "            } \\\n" \
  "          } \\\n" \
  "    }... \\\n" \
  "    [ -useSelf ] \\\n" \
  "    [ -basis {BTYPE} {NTERMS} ] [ -monotonic ] \\\n" \
  "    [ -outPrefix {OUT_PREFIX} ]"

#define PROG_INFO \
  "NAME\n" \
  "  " PROG_NAME " - " PROG_DESC ".\n" \
  "\n" \
  "SYNOPSIS\n" \
  "  " PROG_HELP "\n" \
  "\n" \
  "DESCRIPTION\n" \
  "  Reads digital photographs of one or more reflectance scales" \
  " (such as the gray scale provided by the Kodak Q-13chart), and" \
  " estimates from them the camera's /light transfer function/ (LTF), the" \
  " correspondence between the physical lightness (brightness) of a surface" \
  " to the sample values stored in a digital photo of the same.\n" \
  "\n" \
  "ASSUMPTIONS\n" \
  "  Each input scale image must be a photograph of a flat chart consisting" \
  " of two or more Lambertian (matte) patches, each with uniform intrinsic" \
  " color (per-channel reflectance).  The input photos must have been geometrically" \
  " rectified, so that the steps of the chart are rectangular sub-images, all" \
  " with the same width and height, concatenated left to right without any gaps.  The" \
  " images should have been edited as needed to eliminate all stains, borders, lettering," \
  " and patch-to-patch transition areas.\n" \
  "\n" \
  "  The patches of a scale may have all" \
  " the same intrinsic color, as long as all scales together span the desired" \
  " range of surface colors.)  Note that such uniform scales provide useful" \
  " information about the illumination, especially if they lie near other scales.\n" \
  "\n" \
  "  The patches of each scale must be equally spaced along a straight" \
  " line in the original chart.  The position of the first patch and the" \
  " displacement between consecutive patches must be informed through" \
  " the \"-position\" and \"-stride\" arguments.\n" \
  "\n" \
  "  The scene's illumination does not have to be uniform" \
  " over the whole gray-scale, as long as the photo is free from highlights" \
  " and cast shadows, and can be approximated by an affine function" \
  " (first-degree polynomial) over any patch of the scale.\n" \
  "\n" \
  "OUTPUTS\n" \
  "  The program writes the estimated LTF to the text file \"{ADJUST_TBL_FNI}\"" \
  " in a human- and machine-readable tabular format.  Each line of this file" \
  " contains an input value and a corresponding brightness, both fractional" \
  " numbers between 0 and 1.  The input value is the sample value as stored" \
  " in the image file, scaled so that 1.0 is the maximum possible sample" \
  " value.  The brightness is proportional to the physical radiance, scaled" \
  " so that 1.0 is the radiance of the brightest patch present in the" \
  " input images.  The table is valid only for sample values in the" \
  " range spanned by the sample values present in the input images.\n" \
  "\n" \
  "   The program may write to file \"{BASIS_FNI}\" the basis functions" \
  " used for fitting.  The table will assign brightness \n" \
  "\n" \
  "FILE FORMAT\n" \
  "  All input and output image files are in the FNI format. See" \
  " {float_image.h} for details.\n" \
  "\n" \
  "MONOTONIC FITTING\n" \
  "  The input-output map may be optionally constrained to be" \
  " monotonic increasing.  Input samples are assumed to lie in the" \
  " range [0 _ 1]. The scale for the output samples is chosen" \
  " so that an input sample value 1.0 is mapped to 1.0.\n" \
  "\n" \
  "GENERAL OPTIONS\n" \
  "  " fka_corners_HELP " \n" \
  "    Specifies the coordinates of the corners of the Q-13 chart" \
  " on the input image.  The \"-corners\"keyword must be followed" \
  " by the four tags \"tl\" (top left), \"tr\" (top right)," \
  " \"bl\" (bottom left), and \"br\" (bottom right),  in any" \
  " order, each followed by the X and Y coordinates of the corresponding" \
  " corner of the chart.  The bottom edge of the Q-13 is, by" \
  " definition, the long side adjacent to the gray scale; and" \
  " the left edge is the short side adjacent to the chart's" \
  " `white' patch.  The coordinates may be fractional; they are" \
  " measured in pixels, in the FNI coordinate system (whose" \
  " origin is the BOTTOM left corner of the image, with" \
  " the Y axis pointing UP).  These parameters are mandatory.\n" \
  "\n" \
  "  -basis {BTYPE} {NTERMS}\n" \
  "    Specifies the type and number of terms to use in the mathematical" \
  " model of the input-output value map. The basis type may be" \
  " either \"A\" (splines) or \"B\" (Gaussian sigmoids).  The" \
  " number of terms must be between" \
  " " stringify(fka_min_basis_size) " and " \
  " " stringify(fka_max_basis_size) ".  The default" \
  " is " stringify(fka_default_basis_size) ".  More terms" \
  " allow more precise correction, but they may result in numerical" \
  " instabilities and wildly wrong value tables.\n" \
  "\n" \
  "  -monotonic\n" \
  "    Forces the input-output map to be monotonically" \
  " increasing.  By default, allows a non-monotonic" \
  " mapping. (However, non-monotonicity is more likely" \
  " to be due to bad data, and when it occurs the output image" \
  " is probably garbage.)\n" \
  "\n" \
  "  -dontAdjust\n" \
  "    If this optional switch is present, the data fitting" \
  " is skipped, and the adjusted images are not written.\n" \
  "\n" \
  "  -useGray\n" \
  "    ???\n" \
  "\n" \
  "  -useWhite\n" \
  "    ???\n" \
  "\n" \
  "  -useSelf\n" \
  "    ???\n" \
  "\n" \
  "  -writeChart {RAW_CHART_FNI} {ADJ_CHART_FNI}\n" \
  "    Specifies the names of the files where the chart images" \
  " (before and after the photometric correction) are to be written.\n" \
  "\n" \
  "  -writeStrip {RAW_STRIP_FNI} {ADJ_STRIP_FNI}\n" \
  "    Specifies the names of the files where the narrow chart strips" \
  " (before and after the photometric correction) are to be written.\n" \
  "\n" \
  "  -writeTable {VAL_TABLE_FNI} {LOG_TABLE_FNI}\n" \
  "    Specifies the name of the files where the input-output map" \
  " is to be written.  The first file \"{VAL_TABLE_FNI}\" will" \
  " contain the mapping from image sample values {V} to the" \
  " photometrically corrected (linear-scale) intensity {H(V)}. The" \
  " second file \"{LOG_TABLE_FNI}\" will contain the internal" \
  " map {h(v) = log(H(V))}, where {v} is the logaritm of {V} normalized" \
  " to the interval {[0 _ 1]}).\n" \
  "\n" \
  "    Each mapping is formatted as FNI image file" \
  " with a single row of pixels and {NC+1} channels, where {NC}" \
  " is the number of channels in the input image. Channel" \
  " 0 has a linear ramp of image sample values {V} (resp. logscale" \
  " normalized values {v}).  Channel {C+1}" \
  " of the table has the values of {H(V)} (resp. {h(v)})  for image" \
  " channel {C}, for {C} from 0 to {NC-1}.  If this option" \
  " is not specified, the input-output map is not written.\n" \
  "\n" \
  "  -writeBasis {BASIS_FNI}\n" \
  "    Specifies the name of the file where the function basis" \
  " used for data fitting is to be written.  The file is" \
  " formatted as a FNI image file with a single row" \
  " of pixels and {NTERMS+1} channels. Channel" \
  " 0 has a linear ramp of equally spaced values, from 0.0" \
  " to 1.0.  Channel {I+1} has the corresponding values of" \
  " basis element {I}, for {I} from 0 to {NTERMS-1}.  If this" \
  " option is not specified, the file" \
  " is not written.\n" \
  "\n" \
  "DOCUMENTATION OPTIONS\n" \
  argparser_help_info_HELP_INFO "\n" \
  "\n" \
  "EXAMPLE\n" \
  "  " PROG_NAME " \\\n" \
  "    -steps 5 \\\n" \
  "    -scale GrayScale.fni \\\n" \
  "      -pixelSize 0.5 \\\n" \
  "      -position 2.5 1.5 -stride 10.0 0.0 \\\n" \
  "      -albedos  \\\n" \
  "\n" \
  "SEE ALSO\n" \
  "  pnm_to_fni(1), fni_kodak_extract(1), fni_to_pnm(1), fni_hist(1), pnmnorm(1).\n" \
  "\n" \
  "AUTHOR\n" \
  "  Created on 08/may/2006 by Jorge Stolfi, IC-UNICAMP.\n" \
  "  Based on earlier Q-13 analysis programs by ??? and ???, IC-UFF."

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
#include <pst_kodak.h>

/* GENERAL DEFINITIONS */

typedef pst_kodak_basis_t fka_basis_t; /* A shorter name. */

#define fka_default_basis_type pst_kodak_btype_A
  /* Default type of function basis for I/O map fitting. */

#define fka_default_basis_size 10
  /* Default number of functions in I/O map basis (incl. unit). */
  
#define fka_min_basis_size 3
  /* Maximum number of functions in I/O map basis (incl. unit). */

#define fka_max_basis_size 20
  /* Maximum number of functions in I/O map basis (incl. unit). */

#define fka_num_bas_table_lines 1001
  /* Number of lines in function basis dump. */

#define fka_num_adj_table_lines 1001
  /* Number of lines in input-output table dump. */

#define fka_chart_image_width 609
  /* Number of columns in chart cut-out image. */

typedef struct options_t
  { /* Chart geometry in input image (pixels, FNI system with Y axis up): */
    r2_t tl;  /* Top left corner of chart in input image. */
    r2_t tr;  /* Top right corner of chart in input image. */
    r2_t bl;  /* Bottom left corner of chart in input image. */
    r2_t br;  /* Bottom right corner of chart in input image. */
    /* Function fitting options: */
    bool_t dontAdjust;    /* TRUE skips the adjustment computations. */
    bool_t useGray;       /* TRUE uses the gray background strip as reference. */
    bool_t useWhite;      /* TRUE uses the white frame strip as reference. */
    bool_t useSelf;       /* TRUE uses the previous patch as reference. */
    fka_basis_t basis;    /* Type and size of function basis to use for fitting. */
    bool_t monotonic;     /* Restrict the basis coefficients to be monotonic. */
    /* Output options: */
    char *writeChartRaw;  /* Filename for raw chart image, or NULL. */
    char *writeChartAdj;  /* Filename for adjusted chart image, or NULL. */
    char *writeStripRaw;  /* Filename for raw chart strips, or NULL. */
    char *writeStripAdj;  /* Filename for adjusted chart strips, or NULL. */
    char *writeValTable;  /* Filename for the plain adjustment table, or NULL. */
    char *writeLogTable;  /* Filename for the logscale adjustment table, or NULL. */
    char *writeBasis;     /* Filename for function basis, or NULL. */
  } options_t;

/* INTERNAL PROTOTYPES */

float_image_t *fka_read_float_image(char *name);
  /* Reads a float image, in the format of {float_image_write}, from
    the named file (or {stdin} if {name} is "-"). */
    
void fka_write_float_image(char *name, float_image_t *IMG);
  /* Writes the image {IMG}, in the format of {float_image_write}, to
    the named file (or to {stdout} if {name} is "-"). */

void fka_write_chart_and_strip
  ( float_image_t *IMG, /* Scene image. */
    char *chartName,    /* Filename for chart image, or NULL. */
    char *stripName,    /* Filename for chart strips, or NULL. */
    bool_t useGray,
    bool_t useWhite,
    r3x3_t *P,          /* Chart-to-{IMG} projective map. */
    double step         /* Output pixel size (mm). */
  );
  /* If {chartName} is not NULL, extracts from {IMG} the sub-image of
    the Q-13 chart, rectifies it to orthogonal projection view, and
    writes it to file {chartName}.
    
    Similarly, if {stripName} is not NULL, extracts the relevant
    strips from the chart, stacks them vertically, and and writes them
    to file {stripName}. If {useGray} is TRUE, extracts the gray
    background strip just above the scale. If {useWhite} is TRUE,
    extracts a strip from the (presumed) white frame below the scale.
    In any case, extracts the strip of patches from the gray scale.
    
    In both cases the files will be in FNI format. The {step}
    parameter is the actual size of the output image pixels in {mm}.
    Needs the homogeneous projective map matrix {P} that maps points
    on the chart (in mm from the chart's bottom left corner) to point
    on the image {IMG} (in pixels from {IMG}'s bottom left corner). */

void fka_write_val_table
  ( char *name, 
    int NP, 
    int NC, 
    double noise,
    double logVlo[],
    double logVhi[],
    fka_basis_t B, 
    double_vec_t coef[]
  );
  /* Writes the photometric correction table to a FNI file called
    "{name}". The table consists of {NP} tuples {(V[i], H[0](V[i]),...
    H[NC-1](V[i])}, where the sample values {V[0..NP-1]} are uniformly
    spaced in {[0_1]}; and {H[c]} is the photometric correction map
    defined by the parameters {noise}, {logVlo[c]}, and {logVhi[c]},
    the basis {B}, and the coefficient vector {coef[c]}, for {c} in
    {0..NC-1}. */

void fka_write_log_table
  ( char *name, 
    int NP, 
    int NC, 
    fka_basis_t B, 
    double_vec_t coef[]
  );
  /* Writes the logscale versions of the correcton table to a FNI file
    called "{name}". The table consists of {NP} tuples
    {(v[i],h[0](v[i]),...h[NC-1](v[i])}, where the logscale normalized
    values {v[0..NP-1]} are uniformly spaced in a slight superset of
    the interval {[0_1]}; and {h[c]} is the logscale photometric
    correction map defined by the basis {B} and the coefficient vector
    {coef[c]}, for {c} in {0..NC-1}. */

void fka_write_basis(char *name, int NP, fka_basis_t B);
  /* Writes {NP} data pairs of the each element of function
    basis {B} to file "{name}". */

options_t *fka_parse_options(int argc, char **argv);
  /* Parses the command line options, returns them in an {options_t}. */

void fka_parse_point(argparser_t *pp, r2_t *a);
  /* Parses the next two arguments on the command line as the (fractional) coordinates
    of a point, and stores them into {a}.  Requires that {a} be initialized with 
    {(+INF,+INF)}. */

void fka_check_point(argparser_t *pp, r2_t *a);
  /* Fails if {a} is {(+INF,+INF)}. */

int main (int argc,char** argv);
  /* Main program. */

/* IMPLEMENTATIONS */

int main (int argc,char** argv)
  { 
    /* Parse options from the command line: */
    options_t *o = fka_parse_options(argc, argv);

    /* Read actual photo: */
    float_image_t *IMG = fka_read_float_image("-");
    int NC, NX, NY;
    float_image_get_size(IMG, &NC, &NX, &NY);
      
    /* Get projective matrix from physical chart coords to {IMG} coords. */ 
    r3x3_t P; 
    pst_kodak_get_matrix(&o->tl, &o->tr, &o->bl, &o->br, &P);

    /* Extract and write the raw chart images, if so requested: */
    double chartStep = 0.25; /* Pixel size in chart/strip images (mm). */
    fka_write_chart_and_strip
      (IMG, o->writeChartRaw, o->writeStripRaw, o->useGray, o->useWhite, &P, chartStep);
      
    if (o->dontAdjust) { return 0; }

    /* Compute input-output map and adjust image, channel by channel: */
    double noise = 1.0/256.0; /* Guess. */
    double_vec_t coef[NC];
    double logVlo[NC], logVhi[NC];
    int c;
    for (c = 0; c < NC; c++)
      { coef[c] = double_vec_new(o->basis.N);
        pst_kodak_compute_light_map
          ( IMG, c, noise, o->useGray, o->useWhite, o->useSelf, &P, 
            o->basis, o->monotonic,
            coef[c].e, &(logVlo[c]), &(logVhi[c])
          );
        pst_kodak_apply_map(IMG, c, noise, logVlo[c], logVhi[c], o->basis, coef[c].e);
      }
      
    /* Extract and write the raw chart images, if so requested: */
    fka_write_chart_and_strip
      (IMG, o->writeChartAdj, o->writeStripAdj, o->useGray, o->useWhite, &P, chartStep);

    /* Write the adjusted image: */
    fka_write_float_image("-", IMG);
    
    /* Write the adjustment table, if so requested: */
    if (o->writeValTable != NULL)
      { int NP = fka_num_adj_table_lines;
        fka_write_val_table(o->writeValTable, NP, NC, noise, logVlo, logVhi, o->basis, coef);
      }
    
    /* Write the adjustment table, if so requested: */
    if (o->writeLogTable != NULL)
      { int NP = fka_num_adj_table_lines;
        fka_write_log_table(o->writeLogTable, NP, NC, o->basis, coef);
      }
    
    /* Write the function basis, if so requested: */
    if (o->writeBasis != NULL)
      { int NP = fka_num_bas_table_lines;
        fka_write_basis(o->writeBasis, NP, o->basis); }

    return 0;
  }

void fka_write_chart_and_strip
  ( float_image_t *IMG, /* Scene image. */
    char *chartName,    /* Filename for chart image, or NULL. */
    char *stripName,    /* Filename for chart strips, or NULL. */
    bool_t useGray,
    bool_t useWhite,
    r3x3_t *P,          /* Chart-to-{IMG} projective map. */
    double step         /* Output pixel size (mm). */
  )
  {
    /* Extract and write the chart image, if so requested: */
    if (chartName != NULL)
      { float_image_t *QIMG = pst_kodak_extract_chart(IMG, P, step); 
        fka_write_float_image(chartName, QIMG);
        float_image_free(QIMG);
      }

    /* Extract and write the chart strip image, if so requested: */
    if (stripName != NULL)
      { float_image_t *SIMG = 
          pst_kodak_extract_chart_strips(IMG, P, useGray, useWhite, step); 
        fka_write_float_image(stripName, SIMG);
        float_image_free(SIMG);
      }
  }

float_image_t *fka_read_float_image(char *name)
  { FILE *rd = open_read(name, TRUE);
    float_image_t *IMG = float_image_read(rd);
    if (rd != stdin) { fclose(rd); }
    return IMG;
  }

void fka_write_float_image(char *name, float_image_t *IMG)
  { FILE *wr = open_write(name, TRUE);
    float_image_write(wr, IMG);
    if (wr == stdout) { fflush(wr); } else { fclose(wr); }
  }

void fka_write_val_table
  ( char *name, 
    int NP, 
    int NC, 
    double noise,
    double logVlo[],
    double logVhi[],
    fka_basis_t B, 
    double_vec_t coef[]
  )
  { float_image_t *TIMG = float_image_new(NC+1, NP, 1);
    int i;
    for (i = 0; i < NP; i++)
      { double V = i/((double)NP-1);
        float_image_set_sample(TIMG, 0, i, 0, V);
        int c;
        for (c = 0; c < NC; c++)
          { double Vc = pst_kodak_eval_map(V, noise, logVlo[c], logVhi[c], B, coef[c].e);
            float_image_set_sample(TIMG, c+1, i, 0, Vc);
          }
      }
    fka_write_float_image(name, TIMG);
    float_image_free(TIMG);
  }

void fka_write_log_table
  ( char *name, 
    int NP, 
    int NC, 
    fka_basis_t B, 
    double_vec_t coef[]
  )
  { int K = NP/20; /* Points outside the {[0_1]} range, at each end. */
    float_image_t *TIMG = float_image_new(NC+1, NP, 1);
    int i;
    for (i = 0; i < NP; i++)
      { double v = (i - K)/((double)NP-2*K-1);
        float_image_set_sample(TIMG, 0, i, 0, v);
        int c;
        for (c = 0; c < NC; c++)
          { double vc = pst_kodak_eval_raw_map(v, B, coef[c].e);
            float_image_set_sample(TIMG, c+1, i, 0, vc);
          }
      }
    fka_write_float_image(name, TIMG);
    float_image_free(TIMG);
  }

void fka_write_basis(char *name, int NP, fka_basis_t B)
  { 
    int NB = B.N;
    float_image_t *BIMG = float_image_new(NB+1, NP, 1);
    int KP = (NP/(B.N-2))/2;
    int i;
    for (i = 0; i < NP; i++)
      { double v = (i-KP)/((double)NP-2*KP-1);
        float_image_set_sample(BIMG, 0, i, 0, v);
        int p;
        for (p = 0; p < NB; p++)
          { double zp = pst_kodak_eval_basis(v, p, B);
            float_image_set_sample(BIMG, p+1, i, 0, zp);
          }
      }
    fka_write_float_image(name, BIMG);
    float_image_free(BIMG);
  }

options_t *fka_parse_options(int argc, char **argv)
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
          { fka_parse_point(pp, &(o->tl)); }
        else if (argparser_keyword_present_next(pp, "tr"))
          { fka_parse_point(pp, &(o->tr)); }
        else if (argparser_keyword_present_next(pp, "bl"))
          { fka_parse_point(pp, &(o->bl)); }
        else if (argparser_keyword_present_next(pp, "br"))
          { fka_parse_point(pp, &(o->br)); }
        else
          { /* That must be the end of "-corners" spec: */
            break;
          }
      }
    /* Check for missing corners: */
    fka_check_point(pp, &(o->tl));      
    fka_check_point(pp, &(o->tr));
    fka_check_point(pp, &(o->bl));
    fka_check_point(pp, &(o->br));
      
    o->dontAdjust = argparser_keyword_present(pp, "-dontAdjust");
    
    if (argparser_keyword_present(pp, "-basis"))
      { if (argparser_keyword_present_next(pp, "A"))
          { o->basis.bt = pst_kodak_btype_A; }
        else if (argparser_keyword_present_next(pp, "B"))
          { o->basis.bt = pst_kodak_btype_B; }
        else 
          { argparser_error(pp, "invalid basis type"); }
        o->basis.N = argparser_get_next_int
          ( pp, fka_min_basis_size, fka_max_basis_size );
      }
    else
      { o->basis.bt = fka_default_basis_type;
        o->basis.N = fka_default_basis_size;
      }
    
    o->monotonic = argparser_keyword_present(pp, "-monotonic");

    o->useGray = argparser_keyword_present(pp, "-useGray");
    o->useWhite = argparser_keyword_present(pp, "-useWhite");
    o->useSelf = argparser_keyword_present(pp, "-useSelf");
    if ((!o->useGray) && (!o->useWhite) && (!o->useSelf))
      { argparser_error(pp, "must give \"-useGray\", \"-useWhite\", or \"-useSelf\""); }

    if (argparser_keyword_present(pp, "-writeChart"))
      { o->writeChartRaw = argparser_get_next(pp);
        o->writeChartAdj = argparser_get_next(pp);
      }
    else
      { o->writeChartRaw = o->writeChartAdj = NULL; }
    
    if (argparser_keyword_present(pp, "-writeStrip"))
      { o->writeStripRaw = argparser_get_next(pp);
        o->writeStripAdj = argparser_get_next(pp);
      }
    else
      { o->writeStripRaw = o->writeStripAdj = NULL; }
    
    if (argparser_keyword_present(pp, "-writeTable"))
      { o->writeValTable = argparser_get_next(pp);
        o->writeLogTable = argparser_get_next(pp);
      }
    else
      { o->writeValTable = NULL;
        o->writeLogTable = NULL;
      }

    if (argparser_keyword_present(pp, "-writeBasis"))
      { o->writeBasis = argparser_get_next(pp); }
    else
      { o->writeBasis = NULL; }

    argparser_finish(pp);
    
    return o;
  }

void fka_parse_point(argparser_t *pp, r2_t *a)
  { if ((fabs(a->c[0]) != INF) || (fabs(a->c[1]) != INF))
      { argparser_error(pp, "the same corner was specified twice"); }
    a->c[0] = argparser_get_next_double(pp, -1000000.0, +1000000.0);
    a->c[1] = argparser_get_next_double(pp, -1000000.0, +1000000.0);
  }

void fka_check_point(argparser_t *pp, r2_t *a)
  { if ((fabs(a->c[0]) == INF) || (fabs(a->c[1]) == INF))
      { argparser_error(pp, "not all corners were specified"); }
  }

/* COPYRIGHT, AUTHORSHIP, AND WARRANTY NOTICE:
**
**   Copyright © 2006 by the Fluminense Federal University (UFF).
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
