#define PROG_NAME "fni_high_dyn"
#define PROG_DESC "Combine two or more PGM files into a high dynamic range image"
#define PROG_VERS "1.0"

/* !!! Finish !!! */

#define fni_high_dyn_C_COPYRIGHT "Copyright © 2008 by the State University of Campinas (UNICAMP)"
/* Last edited on 2024-12-20 17:02:19 by stolfi */

#define PROG_HELP \
  PROG_NAME " \\\n" \
  "  { -image {FILE} \\\n" \
  "      [ gamma {GAMMA} ] \\\n" \
  "      [ vmin {VMIN}... [ / {DEN} ] ] \\\n" \
  "      [ vmax {VMAX}... [ / {DEN} ] ] \\\n" \
  "  }... \\\n" \
  "  [ -plot {PREFIX} ] \\\n" \
  "  [ -verbose ]"

#define PROG_INFO_DESC \
  "  The program reads one or more PNM or FNI files containing photos of the same scene, taken" \
  " with the same camera from the same viewpoint but with different" \
  " image transfer functions, and combines them into a single image" \
  " {OFILE} with more accurate values and without overexposed/underexposed values.  For" \
  " PNM files, the input samples are mapped linearly with 0 becoming 0 and {maxval}" \
  " becoming 1.0; and then are gamma-corrected. \n" \
  "\n" \
  "FITTING MODEL\n" \
  "  The program assumes that, after gamma compensation, each" \
  " input image has a straight encoding, except for noise, overexposure," \
  " and zero-offsetting.  Namely, the value stored in each" \
  " pixel of an image is assumed to be related to the true" \
  " brightness {Y} of that sample as follows:\n." \
  " pixel of an image is assumed to be related to the true" \
  "    {VMIN} for {Y <= YMIN}\n" \
  "    {VMIN + A*(Y - YMIN)} for {YMIN < Y < YMAX}\n" \
  "    {VMAX} for {Y > YMAX}\n" \
  " where {A = (VMAX - VMIN)/(YMAX - YMIN)}.  The parameters" \
  " {YMIN,YMAX,VMIN,VMAX} are assumed to be different for each" \
  " color channel and each image, and are adjusted by the program.  For each" \
  " pixel, at least one image must not be overexposed.\n" \
  "\n" \
  "  The current version assumes {YMIN = 0.0} for all images.\n" \
  "\n" \
  "OUTPUT\n" \
  "  The program writes to standard output an FNI image" \
  " that combines the given images. Each output pixel is" \
  " computed from the true Y values of all" \
  " corresponding input pixels, in a scale from 0 to 1.  If a" \
  " pixel is overexposed or underexposed in all images, it" \
  " is set to 0.0 or 1.0, respectively"

#define PROG_INFO_OPTS \
  "  -image {FILE}\n" \
  "    This keyword specifies one additional input image.  The" \
  " argument \"{FILE}\" should be the image file name" \
  " (in \".fni\", \".ppm\" or \".pgm\" format).  If the" \
  " {FILE} is \"-\", the corresponding" \
  " input image is read from {stdin}.\n" \
  "\n" \
  "  vmin {VMIN}... [ / {DEN} ]\n" \
  "  vmax {VMAX}... [ / {DEN} ]\n" \
  "    These optional modifiers following an \"-image\" argument" \
  " specify the minimum and maximum sample values for each channel.  Samples" \
  " near or below {VMIN} are assumed to be underexposed; samples volve {VMAX} are" \
  " assumed to be overeexposed.  For PNM images, a value of 1.0 means the file's" \
  " {maxval}.  If the \"/\" is present, the given values are divided" \
  " by the common denominator {DEN}.  For PNM files, these values refer" \
  " to the raw image sample values, *before* gamma correction.  The defaults" \
  " are {VMIN = 0.0}, {VMAX = 1.0}.\n" \
  "\n" \
  "  gamma {GAMMA}\n" \
  "    This optional modifier following an \"-image\" argument" \
  " specifies the power law exponent {GAMMA} used in the file" \
  " encoding.  It is only relevant for \".ppm\" or \".pgm\" images" \
  " and is ignored for \".fni\" images.  It also applies implicitly to" \
  " the {VMIN} and {VMAX} values.\n" \
  "\n" \
  "  -plot {PREFIX}\n" \
  "    If this optional keyword is present, the program writes for each channel {c}" \
  " a file called \"{PREFIX}-c{CC}.dat\" where {CC} is a two-digit" \
  " channel index {c}.  The file contains the samples from" \
  " channel {c} of the output image and each of the input images, in a" \
  " format suitable for {gnuplot}.  Each row of the file corresponds" \
  " to one pixel, in the format \"{X} {Y} {YVAL} {VAL0} {VAL1}...\", where" \
  " {X} and {Y} are the pixel indices, {YVAL} is the sample of the" \
  " output image, and {VAL0,VAL1,...} are the samples from the input images.\n" \
  "\n" \
  "  -verbose\n" \
  "    If this optional keyword is present, the program prints" \
  " various diagnostic messages."

#define PROG_INFO \
  "NAME\n" \
  "  " PROG_NAME " - " PROG_DESC "\n" \
  "\n" \
  "SYNOPSIS\n" \
  PROG_HELP "\n" \
  "\n" \
  "DESCRIPTION\n" \
  PROG_INFO_DESC "\n" \
  "\n" \
  "OPTIONS\n" \
  PROG_INFO_OPTS "\n" \
  "\n" \
  "DOCUMENTATION OPTIONS\n" \
  argparser_help_info_HELP_INFO "\n" \
  "\n" \
  "SEE ALSO\n" \
  "  pnmscale(1).\n" \
  "\n" \
  "AUTHOR\n" \
  "  Started nov/2008 by Jorge Stolfi, IC-UNICAMP.\n" \
  "  Resumed mar/2010 by Jorge Stolfi as.\n" \
  "\n" \
  "MODIFICATION HISTORY\n" \
  "  nov/2008 Created as pgmhdyn.c, unfinished.\n" \
  "  mar/2010 Renamed fni_high_dyn.c, retargeted.\n" \
  "\n" \
  "WARRANTY\n" \
  argparser_help_info_NO_WARRANTY "\n" \
  "\n" \
  "RIGHTS\n" \
  "  " fni_high_dyn_C_COPYRIGHT ".\n" \
  "\n" \
  argparser_help_info_STANDARD_RIGHTS

/* We need to set these in order to get {isnan}. What a crock... */
#undef __STRICT_ANSI__
#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <jsfile.h>
#include <vec.h>
#include <float_image.h>
#include <float_image_hdyn.h>
#include <sample_conv.h>
#include <float_image_io_pnm.h>
#include <argparser.h>

#define MAX_NC 5
  /* Max number of channels allowed in an input image. */

typedef struct options_t 
  { /* Input image arguments: */
    string_vec_t fname;           /* Input file names. */
    double_vec_t gamma;           /* Power law exponents for PNM images. */
    double_vec_t vmin[MAX_NC];    /* Underexposed value per channel and image. */
    double_vec_t vmax[MAX_NC];    /* Overexposed value per channel and image. */
    char *plot;                   /* Prefix for plot files, or NULL. */
    /* Debugging options: */
    bool_t verbose;      /* TRUE to print global statistics. */
  } options_t;

/* INTERNAL PROTOTYPES */

int main(int argc, char **argv);

bool_t is_uint16_image(char *filename);
  /* TRUE iff the extension is ".ppm" or ".pgm" or ".pbm" or ".pnm". */

bool_t is_fni_image(char *filename);
  /* TRUE iff the extension is ".fni". */

float_image_t *read_input_image(char *filename, double gamma, bool_t verbose);
  /* Reads a PBM/PGM/FNI image file with the given {filename}.
    If {verbose} is true, prints image statistics to {stderr}. */

void plot_values(char *prefix, int c, int NI, float_image_t *img[], float_image_t *omg, bool_t verbose);
  /* Writes the plot file for channel {c} of the output image {omg} and the input
    images {img[0..NI-1]}. */

void cleanup_image_values(float_image_t *img, int c, bool_t verbose);
  /* Scales all valid samples so that the largest valid value is a bit
    less than 1.0, and the smallest valid value is a bit above 0.0
    Replaces {-INF} samples by 0, {+INF} values by 1.0, and {NAN}
    values by 0.5. */

options_t *parse_options(int argc, char **argv);
  /* Parses the arguments from the command line and returns them as an
    {options_t} record {o}. */

void parse_values(argparser_t *pp, int NC, int i, double_vec_t val[]);
  /* Parses between 1 and {NC} values from the command line, stores them into 
    {val[0..NC-1].e[i]}.  If less than {NC} values are given, replicates
    the last one. */

/* IMPLEMENTATIONS */

int main(int argc, char **argv)
  {
    /* Parse command line options: */
    options_t *o = parse_options(argc, argv);
    int NI = o->fname.ne; /* Number of input images. */
    assert(o->gamma.ne == NI);

    /* Read input images, get/check dimensions: */
    float_image_t *img[NI];
    int NC, NX, NY;
    int k, c;
    for (k = 0; k < NI; k++)
      { img[k] = read_input_image(o->fname.e[k], o->gamma.e[k], o->verbose);
        /* Set/check {NX,NY}: */
        if (k == 0)
          { NC = img[k]->sz[0];
            NX = img[k]->sz[1];
            NY = img[k]->sz[2];
          }
        else
          { demand(img[k]->sz[0] == NC, "inconsistent image channels");
            demand(img[k]->sz[1] == NX, "inconsistent image width");
            demand(img[k]->sz[2] == NY, "inconsistent image height");
          }
        demand(NC <= MAX_NC, "too many channels");
        
        if (is_uint16_image(o->fname.e[k]))
          { /* Apply gamma correction to {o->vmin, o->vmax}: */
            for (c = 0; c < NC; c++)
              { o->vmin[c].e[k] = sample_conv_gamma(o->vmin[c].e[k], o->gamma.e[k], 0.0); 
                o->vmax[c].e[k] = sample_conv_gamma(o->vmax[c].e[k], o->gamma.e[k], 0.0); 
              }
          }
        
      }
    
    /* Adjust parameters and compute values for each channel: */
    double gain[NI];
    double offset[NI];
    double sigma[NI];
    float_image_t *omg = float_image_new(NC, NX, NY);
    for (c = 0; c < NC; c++)
      { double *vmin = o->vmin[c].e;
        double *vmax = o->vmax[c].e;
        float_image_hdyn_estimate_gains_offsets_sigmas_values
          ( c, NI, img, vmin, vmax, o->verbose, gain, offset, sigma, omg );
        cleanup_image_values(omg, c, o->verbose);

        if (o->plot != NULL)
          { plot_values(o->plot, c, NI, img, omg, o->verbose); }
      }

    /* Write the filtered image, scaled and quantized: */
    float_image_write(stdout, omg);

    if (o->verbose) { fprintf(stderr, "done."); }
    return 0;
  }

void plot_values(char *prefix, int c, int NI, float_image_t *img[], float_image_t *omg, bool_t verbose)
  {
    /* Open output file: */
    char *filename = jsprintf("%s-c%02d.dat", prefix, c);
    FILE *wr = open_write(filename, TRUE);

    /* Get image dimensions: */
    int NX = omg->sz[1];
    int NY = omg->sz[2];
    
    /* Write pixel data: */
    int x, y;
    for (y = 0; y < NY; y++)
      { for (x = 0; x < NX; x++)
          { fprintf(wr, "%5d %5d", x, y);
            fprintf(wr, " %12.8f", float_image_get_sample(omg, c, x, y));
            int i;
            for (i = 0; i < NI; i++)
              { fprintf(wr, " %9.6f", float_image_get_sample(img[i], c, x, y)); }
            fprintf(wr, "\n");
          }
      }
    
    fclose(wr);
    free(filename);
  }

void cleanup_image_values(float_image_t *img, int c, bool_t verbose)
  {
    /* Get image dimensions: */
    int NX = img->sz[1];
    int NY = img->sz[2];
    
    /* Find range of luminosities ignoring {INF}s and {NAN}s: */
    float Vmin = +INF;
    float Vmax = -INF;
    float_image_update_sample_range(img, c, &Vmin, &Vmax);
    if (verbose)
      { fprintf(stderr, "raw Y range = [ %+12.8f _ %+12.8f ]\n", Vmin, Vmax); }
    if (Vmin < 0)
      { fprintf(stderr, "warning: negative Vmin\n"); }
    if (Vmax <= 0)
      { fprintf(stderr, "warning: non-positive Vmax\n");
        Vmax = 0;
      }
      
    /* Do not change the zero luninosity level: */
    Vmin = 0;

    /* Choose new min and max values: */
    float Yeps = 1.0e-5;
    float Ymin = 0.0 + Yeps;
    float Ymax = 1.0 - Yeps;
    double scale = (Vmax <= Vmin ? 0.0 : (Ymax - Ymin)/(Vmax - Vmin));
    if (verbose)
      { fprintf(stderr, "adjusted Y range = [ %12.8f _ %12.8f ]\n", Ymin, Ymax); }
 
    /* Scan pixels: */
    int nva = 0; /* Counts valid pixels. */
    int nlo = 0; /* Counts underexposed pixels. */
    int nhi = 0; /* Counts overexposed pixels. */
    int nun = 0; /* Counts indeterminate pixels. */
    int x, y;
    for (y = 0; y < NY; y++)
      { for (x = 0; x < NX; x++)
          { /* Get value: */
            float V = float_image_get_sample(img, c, x, y);
            float Y;
            if (isnan(V))
              { Y = 0.5; nun++; }
            else if (V == -INF)
              { Y = 0.0; nlo++; }
            else if (V == +INF)
              { Y = 1.0; nhi++; }
            else if (Vmax <= Vmin)
              { Y = 0.5; nun++; }
            else if (V <= Vmin)
              { Y = Ymin; nva++; }
            else if (V >= Vmax)
              { Y = Ymax; nva++; }
            else 
              { Y = Ymin + scale * (V - Vmin); nva++; }
            float_image_set_sample(img, c, x, y, Y);
          }
      }
    if (verbose)
      { fprintf(stderr, "%9d valid pixels\n", nva);
        fprintf(stderr, "%9d underexposed pixels\n", nlo);
        fprintf(stderr, "%9d overexposed pixels\n", nhi);
        fprintf(stderr, "%9d indeterminate pixels\n", nun);
      }
  }

float_image_t *read_input_image(char *filename, double gamma, bool_t verbose)
  { float_image_t *img;
    if (is_uint16_image(filename))
      { /* Read PNM image: */
        uint16_image_t *pim = uint16_image_read_pnm_named(filename, TRUE);
        /* Get image dimensions: */
        int NC = pim->chns; /* Num of channels. */
        int NX = pim->cols;
        int NY = pim->rows;
        uint16_t maxval = pim->maxval;
        img = float_image_new(NC, NX, NY);
        int c, x, y;
        /* Convert pixels to floats with {0->0}, {maxval->1}: */
        for(y = 0; y < NY; y++)
          { int pgmy = NY - 1 - y;
            uint16_t *prow = pim->smp[pgmy];
            for(x = 0; x < NX; x++)
              { for (c = 0; c < NC; c++)
                  { /* Convert int sample {*prow} to float {v}, store, keep stats: */
                    uint16_t ismp = (*prow);
                    float fsmp = ((double)ismp)/((double)maxval);
                    float_image_set_sample(img, c, x, y, fsmp);
                    prow++;
                  }
              }
          }
        if (gamma != 1)
          { for (c = 0; c < NC; c++)
              { float_image_apply_gamma(img, c, gamma, 0.0); }
          }
        uint16_image_free(pim);
      }
    else if (is_fni_image(filename))
      { FILE *rd = open_read(filename, TRUE);
        img = float_image_read(rd);
        if (rd != stdin) { fclose(rd); }
      }
    else
     { demand(FALSE, "unknown image name extension"); }
    return img;
  }

bool_t is_uint16_image(char *filename)
  { char *ext = strrchr(filename, '.');
    demand(ext != NULL, "input file name must have an extension");
    return 
      (strcmp(ext, ".ppm") == 0) || 
      (strcmp(ext, ".pgm") == 0) || 
      (strcmp(ext, ".pbm") == 0) || 
      (strcmp(ext, ".pnm") == 0);
  }

bool_t is_fni_image(char *filename)
  { char *ext = strrchr(filename, '.');
    demand(ext != NULL, "input file name must have an extension");
    return (strcmp(ext, ".fni") == 0);
  }

#define BIG  (1.0e+100)
  /* A very large value, but still far from overflow. */

#define MAX_SIZE (32*1024)
  /* A limit on image size, to avoid humongous mallocs. */

options_t *parse_options(int argc, char **argv)
  {
    argparser_t *pp = argparser_new(stderr, argc, argv);
    
    argparser_set_help(pp, PROG_NAME " version " PROG_VERS ", usage:\n" PROG_HELP);
    argparser_set_info(pp, PROG_INFO);
    argparser_process_help_info_options(pp);
     
    options_t *o = (options_t *)notnull(malloc(sizeof(options_t)), "no mem");
    
    o->fname = string_vec_new(10);
    o->gamma = double_vec_new(10);
    
    int ni = 0;
    int c;
    while (argparser_keyword_present(pp, "-image"))
      { 
        string_vec_expand(&(o->fname), ni);
        double_vec_expand(&(o->gamma), ni);
        o->gamma.e[ni] = 1.0;
        for (c = 0; c < MAX_NC; c++)
          { double_vec_expand(&(o->vmin[c]), ni);
            o->vmin[c].e[ni] = 0.0;
            double_vec_expand(&(o->vmax[c]), ni);
            o->vmax[c].e[ni] = 1.0;
          }
          
        o->fname.e[ni] = argparser_get_next(pp);
        while (TRUE)
          { /* Try to parse an image modifier: */
            if (argparser_keyword_present_next(pp, "gamma"))
              { o->gamma.e[ni] = argparser_get_next_double(pp, 0.1, 10.0); }
            else if (argparser_keyword_present_next(pp, "vmin"))
              { parse_values(pp, MAX_NC, ni, o->vmin); }
            else if (argparser_keyword_present_next(pp, "vmax"))
              { parse_values(pp, MAX_NC, ni, o->vmax); }
            else
              { break; }
          }
        for (c = 0; c < MAX_NC; c++)
          { if (o->vmin[c].e[ni] >= o->vmax[c].e[ni])
              { argparser_error(pp, "invalid value range"); }
          }
        ni++;
     }
    string_vec_trim(&(o->fname), ni);
    double_vec_trim(&(o->gamma), ni);
    for (c = 0; c < MAX_NC; c++)
      { double_vec_trim(&(o->vmin[c]), ni);
        double_vec_trim(&(o->vmax[c]), ni);
      }
    
    if (argparser_keyword_present(pp, "-plot"))
      { o->plot = argparser_get_next(pp); }
    else
      { o->plot = NULL; }
    
    o->verbose = argparser_keyword_present(pp, "-verbose");

    /* Check for spurious args: */
    argparser_finish(pp);

    return o;
  }

void parse_values(argparser_t *pp, int NC, int i, double_vec_t val[])
  { 
    int c;
    for (c = 0; c < NC; c++)
      { if (argparser_next_is_number(pp))
          { val[c].e[i] = argparser_get_next_double(pp, -1.0e6, +1.0e6); }
        else if (c == 0)
          { argparser_error(pp, "expecting a sample value"); }
        else
          { val[c].e[i] = val[c-1].e[i]; }
      }
    if (argparser_keyword_present_next(pp, "/"))
      { double den = argparser_get_next_double(pp, 1.0e-6, 1.0e+6);
        for (c = 0; c < NC; c++) { val[c].e[i] /= den; }
      }
  }
    
