#define PROG_NAME "fni_nodak_extract"
#define PROG_DESC "Extract a circular 25-spot gray chart from an image"
#define PROG_VERS "1.0"

/* Copyright  2009 by the State University of Campinas (UNICAMP).*/
/* See the copyright, authorship, and warranty notice at end of file.*/
/* Last edited on 2023-02-12 07:49:49 by stolfi */

#define PROG_HELP \
  "  " PROG_NAME "\\\n" \
  "    -geomFile {GEOMFILE_TXT} \\\n" \
  "    [ -chartBorder {BWD} ] \\\n" \
  "    { -spot {NUM} {CTRX} {CTRY} }.. \n" \
  "    [ -yFlip ] \\\n" \
  "    -outChartSize {OSZ} \\\n" \
  "    [ -outScale {SCALE_NAME} {PNX} {PNY} ] \\\n" \
  "    [ -spotMargin {SPOT_MARGIN} ] \\\n" \
  "    < {INPUT_FNI} \\\n" \
  "    > {OUTPUT_FNI}"

#define PROG_INFO \
  "NAME\n" \
  "  " PROG_NAME " - " PROG_DESC ".\n" \
  "\n" \
  "SYNOPSIS\n" \
  PROG_HELP "\n" \
  "\n" \
  "DESCRIPTION\n" \
  "  Reads from standard input a digital photograph that" \
  " includes the N-spot circular grayscale chart" \
  " (see {make_light_chart}) in arbitrary perspective," \
  " conical or cylindrical.  Extracts the sub-image consisting of the" \
  " chart, and writes it to standard output as a separate" \
  " image, in orthogonal projection with true aspect ratio, correcting" \
  " for perspective distortion.\n" \
  "\n" \
  "  Optionally the program outputs also a strip-like gray-scale image," \
  " consisting of all the spots of the chart, converted to rectangles" \
  " and concatenated left-to-right, in spot index order; And a text file \n" \
  " with the number, centers, radii and reflectances of the spots extracted from image \n" \
  "\n" \
  "  It is OK if some or all gray-scale spots lie" \
  " outside the input image.  The corresponding parts of the output images" \
  " are filled with an arbitrary gray value.\n" \
  "\n" \
  "  All input and output image files are in the FNI format. See" \
  " {float_image.h} for details.\n" \
  "\n" \
  "OPTIONS\n" \
  "  -geomFile {GEOMFILE_TXT} \n" \
  "    This option specifies the name of the file that contains the geometry" \
  " of circular chart. The first line of the file has the format\n" \
  "    nspots = {NSPOTS}\n" \
  " The second line had the form\n" \
  "    radius = {CHART_RADIUS}\n" \
  " The third line had the brightness of the chart's backgound\n" \
  "    bg_lum = {BG_LUM}\n" \
  " Each subsequent line of the file describes one spot and has" \
  " the format\n" \
  "    {NUM} {CTRX} {CTRY} {RADIUS} {LIGHTNESS}\n" \
  "\n" \
  "  -chartBorder {BWD} \n" \
  "    This optional argument specifies that the extracted" \
  " chart image should include a border of {BWD} millimeters" \
  " beyond the chart radius specified in the geometry file.\n" \
  "\n" \
  "  -spot {NUM} {CTRX} {CTRY} \n" \
  "    This mandatory argument specifies the image coordinates" \
  " of the center of one of the spots of the N-spot chart" \
  " on the input image.  The \"-spot\" keyword must be followed" \
  " by the index {NUM} of the spot, and the" \
  " coordinates {CTRX} and {CTRY} of the center of the spot" \
  " in the input image. The coordinates may be fractional; they are" \
  " measured in pixels, in the input image coordinate system" \
  " (see the \"-yFlip\" option).  At least four \"-spot\" arguments" \
  " must be given, in any order.\n" \
  "\n" \
  "  -scale {SCALE} \n" \
  "    This optional argument specifies that the image" \
  " coordinates {CTRX,CTRY} given in the \"-spot\" arguments should" \
  " be scaled by {CSCALE}.  Typically this option is used when the" \
  " coordinates have been measured on a full-size image and the input" \
  " is a reduced copy of the same.\n" \
  "\n" \
  "  -yFlip\n" \
  "    This optional keyword specifies that the Y image coordinates" \
  " given in the \"-spot\" arguments should be complemented relative to the input" \
  " image's Y size.  It is useful when the coordinates have been" \
  " measured on a PNM or PNG image which was then converted" \
  " to FNI with Y-axis flipping.\n" \
  "\n" \
  "  -outChartSize {OSZ} \n" \
  "    This mandatory argument specifies that the output chart image" \
  " should have {OSZ} rows and {OSZ} columns.\n" \
  "\n" \
  "  -outScale {SCALE_NAME} {PNX} {PNY}\n" \
  "    This optional argument specifies the name (without extension) of the output files that" \
  " will contain the strip-like gray scale image," \
  " and the width and height {PNX,PNY} of each step" \
  " of that scale, in pixels.\n" \
  "\n" \
  "  -spotMargin {SPOT_MARGIN}  \n" \
  "    Safety margin (in pixels) to omit when computing the spot average for strip-like gray scale" \
  "\n" \
  "DOCUMENTATION OPTIONS\n" \
  argparser_help_info_HELP_INFO "\n" \
  "\n" \
  "SEE ALSO\n" \
  "  pnm_to_fni(1), fni_to_pnm(1).\n" \
  "\n" \
  "AUTHOR\n" \
  "  Created on 12/jul/2009 by Jorge Stolfi/Rafael Saracchini, IC-UNICAMP, from {fni_kodak_extract.c}.\n" \
  "\n" \
  "MODIFICATION HISTORY\n" \
  "  jul/2009 Adapted from {fni-kodak-extract.c}.  J. Stolfi, IC-UNICAMP.\n" \
  "\n" \
  "WARRANTY\n" \
  argparser_help_info_NO_WARRANTY "\n" \
  "\n" \
  "RIGHTS\n" \
  "  Copyright  2009 by the State University of Campinas (UNICAMP).\n" \
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

#include <fget.h>
#include <nget.h>
#include <fget_geo.h>
#include <pst_basic.h>
#include <pst_argparser.h>
#include <pst_nodak.h>

/* GENERAL DEFINITIONS */

#define fne_MAX_SPOTS 30


typedef struct chart_t 
  {
    double radius;         /* Radius of background-colored area. */
    double bg_lum;         /* Reflectivity of background area. */
    int nspots;            /* Number of spots in chart. */
    r2_vec_t spot_ctr;     /* Spot centers. */
    double_vec_t spot_rad; /* Spot radii. */
    double_vec_t spot_lum; /* Spot reflectivities. */
  } chart_t;

typedef struct options_t
  { /* Q-13 chart geometry in input image (pixels, FNI system with Y axis up): */
    char *geomFile;	  /* Name of the chart geometry file. */
    double chartBorder;	  /* Width of extra border to be extracted around the chart (mm). */
    r2_vec_t ctr;	  /* Centers of the reference spots in the image (px). */
    int_vec_t num;	  /* Numbers of the reference spots. */
    double scale;	  /* Scale factor for input coordinates. */
    bool_t yFlip;	  /* If TRUE, complement the Y coordinates given. */
    double spotMargin;   /* Safety margin to omit when computing strip-like scale*/
    /* Output options: */
    int outChartSize;     /* Output chart image size, in pixels. */
    char *outScaleName;   /* Filename for strip-like gray-scale image, or NULL. */
    int outScaleNX;       /* Width of steps in strip-like gray-scale image, in pixels. */
    int outScaleNY;       /* Height of strip-like gray-scale image, in pixels. */
  } options_t;

/* INTERNAL PROTOTYPES */

float_image_t *fne_read_float_image(char *name);
  /* Reads a float image, in the format of {float_image_write}, from
    the named file (or {stdin} if {name} is "-"). */
    
void fne_write_float_image(char *name, float_image_t *img);
  /* Writes the image {img}, in the format of {float_image_write}, to
    the named file (or to {stdout} if {name} is "-"). */

options_t *fne_parse_options(int argc, char **argv);
  /* Parses the command line options, returns them in an {options_t}. */

r2_t fne_parse_point(argparser_t *pp);
  /* Returns the next two arguments on the command line as the (fractional) coordinates
    of a point */

chart_t* fne_read_chart_geom(char* fileName); 
/* Reads a chart geometry file from {fileName}
  */

int main (int argc,char** argv);
  /* Main program. */

/* IMPLEMENTATIONS */

int main (int argc,char** argv)
  { 
    /* Parse options from the command line: */
    options_t *o = fne_parse_options(argc, argv);

    /* Read actual photo: */
    float_image_t *img = fne_read_float_image("-");
    int NC, NX, NY;
    float_image_get_size(img, &NC, &NX, &NY);
      
    chart_t *g = fne_read_chart_geom(o->geomFile);

    /* Get the projective matrix {P} that maps physical chart coords to {img} coords. */ 
    r3x3_t P; 
    P = pst_nodak_get_matrix(&g->spot_ctr, g->radius, &o->num, &o->ctr);

    /* Apply the "-scale" and "-yFlip" options */
    r3x3_t F; 
    r3x3_ident(&F);
    if (o->scale != 1.0)
      { /* Compose {F} with a uniform scaling: */
        int a;
        for (a = 1; a < 3; a++) { F.c[a][1] *= o->scale; F.c[a][2] *= o->scale; }
      }
    if (o->yFlip)
      { /* Compose {P} with a Y-flipping matrix: */
        F.c[0][2] = NY;
        F.c[2][2] *= -1;
      }
    r3x3_mul(&P, &F, &P);
    
    float_image_t *chartImg = pst_nodak_extract_chart(img,g->radius+o->chartBorder,&P,o->outChartSize);
    fne_write_float_image("-", chartImg);
    float_image_free(chartImg);
    
    double safetyMargin = o->spotMargin;
    if (o->outScaleName != NULL)
      { float_image_t *outScaleImg = pst_nodak_extract_gray_scale(img, &(g->spot_ctr),&(g->spot_rad), &P,safetyMargin,o->outScaleNX, o->outScaleNY );
	char* outScaleImageName = NULL;
	char *outScaleImageName = jsprintf("%s.fni",o->outScaleName);
        fne_write_float_image(outScaleImageName, outScaleImg);
        
	free(outScaleImageName);
	char* outScaleTextName = NULL;
	char *outScaleTextName = jsprintf("%s.txt",o->outScaleName);
	FILE* wr=  open_write(outScaleTextName,TRUE);
	int i;
	fprintf(wr,"nspots = %d\n",g->nspots);
	fprintf(wr,"radius = %f\n",g->radius);
	fprintf(wr,"bg_lum = %6.4f\n",g->bg_lum);
	for(i = 0; i < g->nspots; i++){
		r2_t ctr = g->spot_ctr.e[i];
		double rad = g->spot_rad.e[i];
		float val[NC];
		double lum = 0;
		int c;
		for( c = 0; c < NC; c++){
			val[c] = float_image_get_sample(outScaleImg,c, i*o->outScaleNX, 0);
		}
		if(NC == 1){
			lum = val[0];
		}else{
			assert(NC == 3);
			lum = +0.298911*val[0] +0.586611*val[1] +0.114478*val[2];
		}
		
		fprintf(wr, "%2d %+9.4f %+9.4f %8.4f  %6.4f", i, ctr.c[0], ctr.c[1], rad, lum);
		for( c = 0; c < NC; c++){
			fprintf(wr," %6.4f",val[c]);
		}
		fprintf(wr,"\n");
	}
	fclose(wr);
	float_image_free(outScaleImg);
	free(outScaleTextName);
      }

    return 0;
  }

float_image_t *fne_read_float_image(char *name)
  { FILE *rd = open_read(name, TRUE);
    float_image_t *img = float_image_read(rd);
    if (rd != stdin) { fclose(rd); }
    return img;
  }

void fne_write_float_image(char *name, float_image_t *img)
  { FILE *wr = open_write(name, TRUE);
    float_image_write(wr, img);
    if (wr == stdout) { fflush(wr); } else { fclose(wr); }
  }

options_t *fne_parse_options(int argc, char **argv)
  { 
    argparser_t *pp = argparser_new(stderr, argc, argv);
    argparser_set_help(pp, PROG_NAME " version " PROG_VERS ", usage:\n" PROG_HELP);
    argparser_set_info(pp, PROG_INFO);
    argparser_process_help_info_options(pp);
    
    options_t *o = (options_t *)malloc(sizeof(options_t)); 

    argparser_get_keyword(pp, "-geomFile");
    o->geomFile = argparser_get_next(pp);
    
    if (argparser_keyword_present(pp, "-chartBorder"))
      { o->chartBorder = argparser_get_next_double(pp, 0.0, 1000.0); }
    else
      { o->chartBorder = 0.0; }
 

    argparser_get_keyword(pp, "-outChartSize");
    o->outChartSize = argparser_get_next_int(pp,1,100000);

    o->num = int_vec_new(25);
    o->ctr = r2_vec_new(25);
    int nspots = 0;
    while (argparser_keyword_present(pp, "-spot")) 
      { int_vec_expand(&o->num, nspots);
        r2_vec_expand(&o->ctr, nspots);
        o->num.e[nspots] = argparser_get_next_int(pp, 0, fne_MAX_SPOTS);
        o->ctr.e[nspots] = fne_parse_point(pp); 
        nspots++;
      }
    int_vec_trim(&o->num, nspots);
    r2_vec_trim(&o->ctr, nspots);
      
    if (argparser_keyword_present(pp, "-scale"))
      { o->scale = argparser_get_next_double(pp, 1.0e-10, 1.0e+10); }
    else
      { o->scale = 1.0; }
    
    o->yFlip = argparser_keyword_present(pp, "-yFlip");
   
    
    if (argparser_keyword_present(pp, "-outScale"))
      { o->outScaleName = argparser_get_next(pp);
        o->outScaleNX = argparser_get_next_int(pp, 1, 1000);
        o->outScaleNY = argparser_get_next_int(pp, 1, 1000);
      }
    else
      { o->outScaleName = NULL;
        o->outScaleNX = 0;
        o->outScaleNY = 0;
      }
   
    if( argparser_keyword_present(pp, "-spotMargin") ){
	o->spotMargin = argparser_get_next_double(pp,-1000.0,1000.0);
    }else{
	o->spotMargin = 4.0;
    }
    argparser_finish(pp);
    
    return o;
  }

r2_t fne_parse_point(argparser_t *pp)
  { 
    r2_t p;
    p.c[0] = argparser_get_next_double(pp, -1000000.0, +1000000.0);
    p.c[1] = argparser_get_next_double(pp, -1000000.0, +1000000.0);
    return p;
  }


chart_t* fne_read_chart_geom(char* fileName){
	FILE* rd = open_read(fileName,TRUE);
	chart_t * g = (chart_t*)notnull(malloc(sizeof(chart_t)),"NOMEN");
	int nspots = nget_int32(rd,"nspots"); fget_eol(rd);
	g->radius = nget_double(rd,"radius"); fget_eol(rd);
        g->nspots = nspots;
        g->bg_lum = nget_double(rd,"bg_lum"); fget_eol(rd);
	g->spot_ctr = r2_vec_new(nspots);
	g->spot_rad = double_vec_new(nspots);
	g->spot_lum = double_vec_new(nspots);
	int i;
	for(i = 0; i < nspots; i++){
		int j = fget_int32(rd);
		demand(i == j,"Sequence error");
		g->spot_ctr.e[i] = fget_r2(rd);
		g->spot_rad.e[i] = fget_double(rd);
		g->spot_lum.e[i] = fget_double(rd);
		fget_eol(rd);
	}
	fclose(rd);
	return g;
}

/* COPYRIGHT, AUTHORSHIP, AND WARRANTY NOTICE:
**
**   Copyright  2006 by the Fluminense Federal University (UFF).
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
