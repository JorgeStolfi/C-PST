#define PROG_NAME "fni_log_ratio"
#define PROG_DESC "compute the log of the ratio of two FNI images"
#define PROG_VERS "1.0"

#define fni_log_ratio_C_COPYRIGHT "Copyright © 2008 by the State University of Campinas (UNICAMP)"

/* Last edited on 2008-12-13 10:46:31 by stolfi */

/* !!! This program should be replaced by {fni_arith}. */

#define PROG_HELP \
  "  " PROG_NAME " \\\n" \
  "    {FNI_FILE_0} {FNI_FILE_2} \\\n" \
  "    > {FNI_OUT}"

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
  argparser_help_info_HELP_INFO "\n" \
  "\n" \
  "SEE ALSO\n" \
  "  fni_to_pnm(1), pnm_to_fni(1).\n" \
  "\n" \
  "AUTHOR" \
  "  Created 2008-12-13 by Jorge Stolfi, Unicamp.\n" \
  "\n" \
  "MODIFICATION HISTORY\n" \
  "\n" \
  "WARRANTY\n" \
  argparser_help_info_NO_WARRANTY "\n" \
  "\n" \
  "RIGHTS\n" \
  "  " fni_log_ratio_C_COPYRIGHT ".\n" \
  "\n" \
  argparser_help_info_STANDARD_RIGHTS
  
#define PROG_INFO_DESC \
  "  Reads two multichannel float-valued (\".fni\") image files," \
  " generates another file where each sample is the log of the ratio" \
  " of the corresponding samples of each file.\n" \
  "\n" \
  "  The channel count of the output image is the minimum of\n" \
  " the input channel counts.  Ditto for the column and row counts."
  
#define PROG_INFO_OPTS \
  "  None yet."

#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <values.h>
#include <stdint.h>
#include <math.h>

#include <bool.h>
#include <jsmath.h>
#include <jsfile.h>
#include <argparser.h>
#include <float_image.h>

/* INTERNAL PROTOTYPES */

float_image_t *compute_output_image(float_image_t *img0, float_image_t *img1);
  /* Computes the log-ratio image from images {img0,img1}. */

/* COMMAND-LINE OPTIONS */

typedef struct options_t
  { char* image0Name;   /* File name of first image. */
    char* image1Name;   /* File name of second image. */
  } options_t;

float_image_t *read_fni_file(char *fileName);
  /* Reads a FNI image from file "{fileName}" (which should include the extension ".fni").
    If {fileName} is "-", reads from standard input. */

void write_fni_file(float_image_t *I, char *fileName, int indent);
  /* Writes the float image {I} in a human-readable format, to a file
    called "{fileName}" (which should include the extension ".fni").
    If {fileName} is "-", writes the image to standard output.
    Diagnostic messages are indented by {indent}. */

options_t *parse_options(int argc, char **argv);
  /* Parses the command line arguments and packs them as an {options_t}. */

int main(int argc,char** argv);

/* IMPLEMENTATIONS */

int main(int argc, char** argv)
  {
    options_t *o = parse_options(argc, argv);
    
    float_image_t *image0 = read_fni_file(o->image0Name);
    float_image_t *image1 = read_fni_file(o->image1Name);
    
    float_image_t *imageOut = compute_output_image(image0, image1);

    write_fni_file(imageOut, "-", 0);
    return 0;
  }


float_image_t *compute_output_image(float_image_t *img0, float_image_t *img1)
  {
    int NC0 = img0->sz[0];
    int NX0 = img0->sz[1];
    int NY0 = img0->sz[2];
    
    int NC1 = img1->sz[0];
    int NX1 = img1->sz[1];
    int NY1 = img1->sz[2];
    
    demand((NC0 == NC1) || (NC0 == 1) || (NC1 == 1), "incompatible channel counts");
    
    int NC = imax(NC0, NC1);
    int NX = imin(NX0, NX1);
    int NY = imin(NY0, NY1);
    
    float_image_t *img2 = float_image_new(NC, NX, NY);
    
    int c, x, y;
    for (c = 0; c < NC; c++)
      { /* Get the proper channel indices {c0,c1} in the two images: */
        int c0 = (NC0 == 1 ? 0 : c);
        int c1 = (NC1 == 1 ? 0 : c);
        for (x = 0; x < NX; x++)
          { for (y = 0; y < NY; y++)
              { float v0 = float_image_get_sample(img0, c0, x, y);
                float v1 = float_image_get_sample(img1, c1, x, y);
                double r = log(v0/v1);
                float_image_set_sample(img2, c, x, y, r);
              }
          }
      }
      
    return img2;
  }

float_image_t *read_fni_file(char *fileName)
  { demand(fileName != NULL, "file name not given");
    FILE *rd = open_read(fileName, TRUE);
    float_image_t *I = float_image_read(rd);
    if (rd != stdin) { fclose(rd); }
    return I;
  }

void write_fni_file(float_image_t *I, char *fileName, int indent)
  { demand(fileName != NULL, "file name not given");
    FILE* wr = open_write(fileName, TRUE);
    float_image_write(wr, I);
    if (wr == stdout) { fflush(wr); } else { fclose(wr); }
  }

options_t *parse_options(int argc, char **argv)
  { argparser_t *pp = argparser_new(stderr, argc, argv);
    argparser_set_help(pp, PROG_NAME " version " PROG_VERS ", usage:\n" PROG_HELP);
    argparser_set_info(pp, PROG_INFO);
    argparser_process_help_info_options(pp);
    
    options_t *o = (options_t *)notnull(malloc(sizeof(options_t)), "no mem"); 

    argparser_skip_parsed(pp);
    
    o->image0Name = argparser_get_next_non_keyword(pp);
    o->image1Name = argparser_get_next_non_keyword(pp);

    argparser_finish(pp);
    
    return o;
  }
