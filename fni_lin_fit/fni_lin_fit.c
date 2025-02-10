#define PROG_NAME "fni_lin_fit"
#define PROG_DESC "fit a linear model to a sequence of images"
#define PROG_VERS "1.0"

#define fni_lin_fit_C_COPYRIGHT "Copyright © 2010 by the State University of Campinas (UNICAMP)"

/* Last edited on 2025-01-18 13:02:44 by stolfi */

#define PROG_HELP \
  PROG_NAME  " \\\n" \
  "  { -image {Z[k]} [ / {DEN[k]} ] {INPUT_FNI_FILE[k]} }... \\\n" \
  "  -gain {GAIN_FNI_FILE} \\\n" \
  "  [ -offset {OFFSET_FNI_FILE} ]\\\n" \
  "  [ -origin {ORIGIN_FNI_FILE} ]\\\n" \
  "  [ -scale {SCALE} ]\\\n" \
  "  [ -verbose ]"

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
  "  Genius is not seeing what no one has seen, but thinking what no one has thought.\n" \
  "\n" \
  "AUTHOR\n" \
  "  Created in jun/2010 by Jorge Stolfi, IC-UNICAMP.\n" \
  "\n" \
  "MODIFICATION HISTORY\n" \
  "  Option bla bla added by J. Stolfi, IC-UNICAMP.\n" \
  "\n" \
  "WARRANTY\n" \
  argparser_help_info_NO_WARRANTY "\n" \
  "\n" \
  "RIGHTS\n" \
  "  " fni_lin_fit_C_COPYRIGHT ".\n" \
  "\n" \
  argparser_help_info_STANDARD_RIGHTS
  
#define PROG_INFO_DESC \
  "  The program reads two or more FNI images {IMG[k]} and associated values {Z[k]} of" \
  " some parameter {Z}.  It finds a sample-by-sample linear model {OFFSET + GAIN*Z[k]} that" \
  " best approximates all the images {IMG[k]} in the least-squares sense; where {OFFSET}" \
  " and {GAIN} are two images.\n" \
  "\n" \
  "  Optionally, the program also computes an {ORIGIN} image" \
  " defined as {-OFFSET/GAIN}, which allows the model" \
  " to be written in the alternative form {GAIN*(Z[k] - ORIGIN)}.\n" \
  "\n" \
  "  In particular, if there is only one image, or if \"-offset\" is not" \
  " specified, the {OFFSET} image is set to all-zeros.\n" \
  "\n" \
  "  All input images must have the same number of channels,columns, and" \
  " rows.  The output images will have the same dimensions."
  
#define PROG_INFO_OPTS \
  "  -image {Z[k]} [ / {DEN[k]} ] {INPUT_FNI_FILE[k]}\n" \
  "    This parameter specifies one of the input images {IMG[k]} and" \
  " the associated parameter value {Z[k]}.  If the slash \"/\" is present," \
  " the parameter is {Z[k]} divided by the number {DEN[k]}. The image is read from" \
  " the file {INPUT_FNI_FILE[k]} in the FNI image format.  If the" \
  " name is \"-\", the image is read from the standard input; if more" \
  " than one input name is \"-\", the images are read in the order given.  This" \
  " parameter must be specified at least once.  \n" \
  "\n" \
  "  -gain {GAIN_FNI_FILE}\n" \
  "  -offset {OFFSET_FNI_FILE}\n" \
  "  -origin {ORIGIN_FNI_FILE}\n" \
  "    These parameters specify the names of the image" \
  " files where the fitted {GAIN}, {OFFSET}, and {ORIGIN} images are to be written out.  The files" \
  " will be in the FNI image format.  If the name is \"-\", the corresponding image" \
  " is written to the standard output (if two or more are \"-\", they" \
  " are written out in the above order).  The \"-gain\" is" \
  " mandatory.  The \"-offset\" and \"-origin\" are optional; if both are missing the offset is assumed" \
  " to be all-zeros and only the {GAIN} is adjusted to fit the data.\n" \
  "\n" \
  "  -scale {SCALE}\n" \
  "    This optional parameter specifies that the {OFFSET} and {GAIN} should" \
  " be multiplied by the given {SCALE} factor before being written out.  The" \
  " default is \"-scale 1.0\" (no scaling).\n" \
  "\n" \
  "  -verbose\n" \
  "    Produces diagnostic output."

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <bool.h>
#include <frgb_ops.h>
#include <affirm.h>
#include <argparser.h>
#include <vec.h>
#include <jsfile.h>
#include <float_image.h>

/* PROTOTYPES */

typedef struct options_t
  { /* Files: */
    double_vec_t image_param;    /* Parameters associated to the input images. */
    string_vec_t image_filename; /* Input image filenames. */
    char *gain_filename;         /* Filename of output gain image. */
    char *offset_filename;       /* Filename of output offset image, or {NULL}. */
    char *origin_filename;       /* Filename of output Z origin image, or {NULL}. */
    double scale;                /* Output scaling factor, or 1 if none. */
    /* Diagnostics: */
    bool_t verbose;
  } options_t;
  /* Command line arguments. */

int main(int argc, char* argv[]);

float_image_t *read_image(char *filename, bool_t verbose);
  /* Reads an image from file {filename} in FNI format. If {filename} is "-"
    reads from standard input. */
   
void write_image(char *filename, float_image_t *img, bool_t verbose);
  /* Writes an image to file {filename} in FNI format. If {filename} is "-"
    writes standard output. */

options_t *fni_lin_fit_parse_options(int argc, char **argv);
  /* Parses the command line arguments. */

/* REAL CODE */

int main(int argc, char** argv)
  {
    /* Parse command line arguments. */
    options_t *o = fni_lin_fit_parse_options(argc, argv);

    /* Get the input image count {NI} and decide whether to include an offset term: */
    int NI = o->image_filename.ne;
    assert(NI >= 1);
    assert(NI == o->image_param.ne);
    bool_t has_offset = (NI > 1) && ((o->offset_filename != NULL) || (o->origin_filename != NULL));
    
    /* Get input images and accumulate the scalar product images: */
    /* !!! Should accumulate in {double}. !!! */
    /* !!! But {float} is probably OK for a few images converted from PNM. !!! */
    float_image_t *szz = NULL; /* Scalar prod of {Z} and {Z}. */
    float_image_t *szv = NULL; /* Scalar prod of {Z} and {V}. */
    float_image_t *s1z = NULL; /* Scalar prod of {Z} and {1} (if {has_offset}). */
    float_image_t *s11 = NULL; /* Scalar prod of {1} and {1} (if {has_offset}). */
    float_image_t *s1v = NULL; /* Scalar prod of {1} and {V} (if {has_offset}). */
    int NC, NX, NY; /* Image dimensions. */
    int k;
    int c, x, y;
    for (k = 0; k < NI; k++)
      { /* Get parameter value {zk} and image {imgk}: */
        double zk = o->image_param.e[k];
        float_image_t *img = read_image(o->image_filename.e[k], o->verbose);
        if (k == 0)
          { /* First image: allocate and clear the accumulator images. */
            NC = img->sz[0];
            NX = img->sz[1];
            NY = img->sz[2];
            szz = float_image_new(NC, NX, NY); float_image_fill(szz, 0);
            szv = float_image_new(NC, NX, NY); float_image_fill(szv, 0);
            if (has_offset)
              { s1z = float_image_new(NC, NX, NY); float_image_fill(s1z, 0);
                s11 = float_image_new(NC, NX, NY); float_image_fill(s11, 0);
                s1v = float_image_new(NC, NX, NY); float_image_fill(s1v, 0);
              }
          }
        else
          { /* Second and later images: check s1zes. */
            float_image_check_size(img, NC, NX, NY, "mismatched input images");
          }
          
        /* All images: accumulate the least-squares scalar products. */
        for (c = 0; c < NC; c++)
          { for (x = 0; x < NX; x++)
              { for (y = 0; y < NY; y++) 
                  { float vk = float_image_get_sample(img, c, x, y);
                    float *pzz = float_image_get_sample_address(szz, c, x, y); (*pzz) += zk*zk;
                    float *pzv = float_image_get_sample_address(szv, c, x, y); (*pzv) += zk*vk;
                    if (has_offset)
                      { float *p1z = float_image_get_sample_address(s1z, c, x, y); (*p1z) += zk;
                        float *p11 = float_image_get_sample_address(s11, c, x, y); (*p11) += 1;
                        float *p1v = float_image_get_sample_address(s1v, c, x, y); (*p1v) += vk;
                      }
                  }
              }
          }
          
        /* Release image: */
        float_image_free(img);
      }
                        
    /* Allocate and fill the output gain and offset images {gmg,omg}: */
    float_image_t *gmg = float_image_new(NC, NX, NY);
    float_image_t *omg = float_image_new(NC, NX, NY);
    for (c = 0; c < NC; c++)
      { for (x = 0; x < NX; x++)
          { for (y = 0; y < NY; y++) 
              { double pzz = float_image_get_sample(szz, c, x, y);
                double pzv = float_image_get_sample(szv, c, x, y);
                if (has_offset)
                  { double p1z = float_image_get_sample(s1z, c, x, y);
                    double p11 = float_image_get_sample(s11, c, x, y);
                    double p1v = float_image_get_sample(s1v, c, x, y);
                    double det = pzz*p11 - p1z*p1z;
                    double gv = (pzv*p11 - p1v*p1z)/det;
                    double ov = (pzz*p1v - p1z*pzv)/det;
                    float_image_set_sample(gmg, c, x, y, gv * o->scale);
                    float_image_set_sample(omg, c, x, y, ov * o->scale);
                  }
                else
                  { double gv = pzv/pzz;
                    float_image_set_sample(gmg, c, x, y, gv * o->scale);
                    float_image_set_sample(omg, c, x, y, 0.0);
                  }
              }
          }
      }
    
    /* Free the work images: */
    float_image_free(szz);
    float_image_free(szv);
    if (has_offset)
      { float_image_free(s1z);
        float_image_free(s11);
        float_image_free(s1v);
      }
      
    /* Write output images: */
    write_image(o->gain_filename, gmg, o->verbose);
    if (o->offset_filename != NULL)
      { assert(omg != NULL);
        write_image(o->offset_filename, omg, o->verbose);
      }
    if (o->origin_filename != NULL)
      { assert(omg != NULL);
        /* Convert {omg} from value offset to Z origin: */
        for (c = 0; c < NC; c++)
          { for (x = 0; x < NX; x++)
              { for (y = 0; y < NY; y++) 
                  { double gv = float_image_get_sample(gmg, c, x, y);
                    double ov = float_image_get_sample(omg, c, x, y);
                    /* Compute the Z offset.  Note that the scale factor is canceled. */
                    double fv = -ov/gv;
                    float_image_set_sample(omg, c, x, y, fv * o->scale);
                  }
              }
          }
        write_image(o->origin_filename, omg, o->verbose);
      }
    
    /* All done: */
    if (o->verbose) { fprintf(stderr, "done.\n"); }
    exit(0);
  }
  
float_image_t *read_image(char *filename, bool_t verbose)
  { FILE *rd = open_read(filename, verbose);
    float_image_t *img = float_image_read(rd);
    if (rd != stdin) { fclose(rd); }
    return img;
  }
  
void write_image(char *filename, float_image_t *img, bool_t verbose)
  { FILE *wr = open_write(filename, verbose);
    float_image_write(wr, img);
    if ((wr != stdout) || (wr != stderr)) { fclose(wr); }
  }

options_t *fni_lin_fit_parse_options(int argc, char **argv)
  {
    options_t *o = (options_t *)notnull(malloc(sizeof(options_t)), "no mem");
    
    argparser_t *pp = argparser_new(stderr, argc, argv);
    argparser_set_help(pp, PROG_NAME " version " PROG_VERS ", usage:\n" PROG_HELP);
    argparser_set_info(pp, PROG_INFO);
    argparser_process_help_info_options(pp);

    o->image_filename = string_vec_new(10);
    o->image_param = double_vec_new(10);
    int nimg = 0; /* Number of input images. */
    while (argparser_keyword_present(pp, "-image"))
      { /* Get the parameter value: */
        double_vec_expand(&(o->image_param), nimg);
        string_vec_expand(&(o->image_filename), nimg);
        o->image_param.e[nimg] = argparser_get_next_double(pp, -1.0e-300, 1.0e+300);
        if (argparser_keyword_present_next(pp, "/"))
          { /* Parse the denominator and divide into the parameter: */
            double den = argparser_get_next_double(pp, 1.0e-300, 1.0e+300);
            o->image_param.e[nimg] /= den;
          }
        /* Get the file name: */
        o->image_filename.e[nimg] = argparser_get_next_non_keyword(pp);
        nimg++;
      }
    if (nimg < 1) { argparser_error(pp, "must specify at least one input image"); }
    double_vec_trim(&(o->image_param), nimg);
    string_vec_trim(&(o->image_filename), nimg);
    
    if (argparser_keyword_present(pp, "-offset"))
      { o->offset_filename = argparser_get_next_non_keyword(pp); }
    else
      { o->offset_filename = NULL; }
    
    if (argparser_keyword_present(pp, "-origin"))
      { o->origin_filename = argparser_get_next_non_keyword(pp); }
    else
      { o->origin_filename = NULL; }
    
    argparser_get_keyword(pp, "-gain");
    o->gain_filename = argparser_get_next_non_keyword(pp);
    
    if (argparser_keyword_present(pp, "-scale"))
      { o->scale = argparser_get_next_double(pp, 1.0e-300, 1.0e+300); }
    else
      { o->scale = 1.0; }
    
    o->verbose = argparser_keyword_present(pp, "-verbose");
    
    /* Get optional input file name: */
    argparser_skip_parsed(pp);

    /* Check for extraneous arguments: */
    argparser_finish(pp);
    
    return o;
  }
