#define PROG_NAME "fni_arith"
#define PROG_DESC "perform pixel-wise arithmetic on float-valued multichannel image files"
#define PROG_VERS "2.0"

/* Copyright © 2006 State University of Campinas (UNICAMP) */
/* See end of file for full copyright and (no)warranty notice */
/* Last edited on 2007-04-06 17:12:29 by stolfi */

#define PROG_HELP \
  "  " PROG_NAME " \\\n" \
  "    { -image {ID} {INPUT_FNI} \\\n" \
  "    | { -output | -set {ID} {EXPRESSION} \\\n" \
  "    }.. \\\n" \
  "    " argparser_help_info_HELP " \\\n" \
  "    > {OUTPUT_FNI}"

#define PROG_INFO \
  "NAME\n" \
  "  " PROG_NAME " - " PROG_DESC "\n" \
  "\n" \
  "SYNOPSIS\n" \
  PROG_HELP "\n" \
  "\n" \
  "DESCRIPTION\n" \
  "  Reads one or more image files, and combines them into one" \
  " or more new images by evaluating some user-given formula.  Some" \
  " of the computed images (introduced with \"-set {ID}\") are just" \
  " saved internally for use in later computations.  One of" \
  " them (introduced with \"-output\") is written out to standard output." \
  "\n" \
  "IMAGE MODEL\n" \
  "  An /image/ is mathematically modeled as a function {A} from the real" \
  " plane to some finite-dimensional real vector space of /image values/.  The" \
  " dimension of this space (which may be zero) is called" \
  " the /depth/ of the image, and is denoted by {nc(A)}.  In" \
  " other words, the value {A(x,y)} of an image {A} at any point" \
  " {(x,y)} is a tuple of {nc(A)} real numbers.\n" \
  "  An image with depth 1 is called a /scalar image/.  An arbitrary" \
  " image {A} can be seen as a stack of {nc(A)} scalar images; these" \
  " layers are the /channels of {A}/, and are identified by indices, from 0 to" \
  " {nc(A)}-1.  In particular, many programs that deal with RGB color" \
  " images assume that channels 0, 1, and 2 are the Red, Green," \
  " and Blue components, respectively.\n" \
  "\n" \
  "PIXMAPS\n" \
  "  An important kind of image is the /pixmap/, which is defined by" \
  " a finite two-dimensional rectangular array of image values, whose" \
  " elements are called /pixels/." \
  "  Each pixel is identified by a pair of integer /pixel indices/.  We write {A[x,y]}" \
  " (with square brackets) to mean the pixel in column {x}" \
  " and row {y} of the array.  It is convenient to visualize that pixel" \
  " as a square of unit side, with opposite corners at the points" \
  " {(x,y)} and {(x+1,y+1)} of the real plane.\n" \
  "  The set of indices of all pixels in the array of a pixmap {A} is a" \
  " rectangular subset of the integer grid, which is called the" \
  " pixmap's /domain/ and denoted by {dom(A)}. The" \
  " lowest X index in {dom(A)} is denoted by {lox(A)}, the number of columns" \
  " by {nx(A)}, and {hix(A)} is defined as {lox(A)+nx(A)}. The" \
  " corresponding parameters for the Y axis are {loy(A)}, {ny(A)}, and" \
  " {hiy(A)}.  Therefore {dom(A)} is the set of integers" \
  " {[lox(A)..hix(A)-1] × [loy(A)..hiy(A)-1]}, and can" \
  " be visualized as the rectangle with corners {(lox(A),loy(A))}" \
  " and {(hix(A),hiy(A))}, divided into unit squares (the pixels).\n" \
  "  An image {A} that was read from an FNI file with {NX} and {NY} rows will have" \
  " {dom(A) = [0..NX-1] × [0..NY-1]}.  For computed pixmaps, the domain is defined by the" \
  " corresponding formula.  Typically, if one or more of the arguments of an" \
  " operation is a pixmap, the resulting image {R} will be a pixmap; and the" \
  " domain of {R} will contain the union of the domains of the operands.\n" \
  "\n" \
  "PIXMAP INTERPOLATION AND EXTRAPOLATION\n" \
  "  Every pixmap {A} has an /interpolation method/ and" \
  " an /extrapolation method/, that together turn the" \
  " pixel array into a proper image --- that is, a function" \
  " defined over the whole real plane." \
  "  The interpolation method defines the value of {A} at arbitrary" \
  " points of the plane in terms of its values at integer points.  The" \
  " simplest interpolation method is \"flat\", which" \
  " gives {A(x,y) = A[floor(x),floor(y)]}. That" \
  " is, for any point {(x,y)} within any pixel {[ix,iy]}, the" \
  " function {A(x,y)} is constant and equal to {A[ix,iy]}, the pixel" \
  " value stored in the array.\n" \
  "  The extrapolation method defines the value of {A} at integer points" \
  " that lie outside the array's domain.  Available extrapolation methods include" \
  " tiling the plane with the pixel" \
  " array by translation or mirroring, replicating the pixels along" \
  " the edges of the pixmap, and so on.  The simplest extrapolation" \
  " method is \"pad\", which yields a fixed pixel value {pad(A)} for any pixel" \
  " outside the image's domain.\n" \
  "  The interpolation and extrapolation methods are an attribute of each pixmap, and are" \
  " determined by the operations that created it.  Pixmaps read from FNI files have" \
  " interpolation method \"flat\", and extrapolation method \"pad\" with {pad(A)=0}.\n" \
  "\n  Images read from files are pixmaps," \
  " and the expression of a \"-set\" or \"-output\" command must yield" \
  " a pixmap.\n" \
  " with the same domain and same" \
  " inerpolation method as {A}" \
  "COMMAND EXECUTION\n" \
  "  The options \"-input\", \"-set\", and \"-output\" are interpreted" \
  " as commands, executed in the order they appear in the command" \
  " line.  Each \"-output\" comand writes the image described by its" \
  " expression to standard output.  Each \"-set\" and \"-input\" command" \
  " creates a new image, and assigns it to the corresponding" \
  " identifier {ID}; the previous meaning of {ID}, if any is discarded.  At" \
  " the end of the processing, all images created with \"-set\" and" \
  " \"-input\" are discarded.\n" \
  "\n" \
  "EXPRESSION EVALUATION\n" \
  "  Each /top-level formula/ (the {EXPRESSION} argument of a  \"-set\" or \"-output\" command) is first analyzed to determine the depth, domain, and methods of the pixmap {R} where the result" \
  " will be stored.  Then the expression is repeatedly evaluated, each time" \
  " for a specific point {(x,y)} of the plane, and a" \
  " specific channel index {c}, so as to fill the pixel array of {R}." \
  "  The points of evaluation for the who;e include the centers of all pixels in the" \
  " pixmap, that is, {(x+1/2,y+1/2)} for all integer pairs {(x,y)} in" \
  " {dom(R)}.  (If the result's extrapolaton method is \"pad\", the" \
  " formula is evaluated also for one pixel outside {D}, to obtain" \
  " the padding value.)  For each of these points, the expression is" \
  " evaluated for channels 0 through {nc(R)-1}.\n" \
  "  Although the whole {EXPRESSION} of a \"-set\" or \"-output\" command" \
  " must yield a pixmap, its sub-expressions may be non-pixmap (/NP/)" \
  " images.  Moreover, each sub-expression may be evaluated at a" \
  " different set of points and channel indices than the enclosing" \
  " sub-expression.  In particular, when evaluating a scalar image," \
  " the current channel index {c} is ignored, and channel 0 is ." \
  "  Some image operators have specific requirements about the depths" \
  " of their operands, and specific rules to determine the depth of" \
  " the result.  However, operations and functions that are defined" \
  " to take scalar images and return a scalar result, such as \"+\" or" \
  " \"log\", can be applied to operands of arbitrary depth.  In that" \
  " case, all operands that are not scalar must have the same depth" \
  " {NC}, which will be the depth of the result; and any" \
  " operand which is a scalar image is implicitly turned into" \
  " an image of depth {NC}, by replicating its" \
  " single channel {NC} times.  Thus, for example," \
  " adding a greyscale (single-channel) photo {A} to an RGB" \
  " (three-channel) photo {B} will add {A} to each channel of {B}.\n" \
  "  For visualization purposes, this document assume the mathematical" \
  " convention for coordinate axes, namely with {y} increasing from" \
  " *bottom to top*, and {x} increasing from left to right.\n" \
  "\n" \
  "EXPRESSION SYNTAX AND EVALUATION\n" \
  "  The expression syntax is similar to that of C language.  In the following description, {FLOAT} means any floating-point" \
  " value; {ID} is an identifier previously defined with" \
  " \"-input\" or \"-set\", or the name of a built-in image;" \
  " {FUNC} is the name of a built-in function; {OP} is a" \
  " built-in binary operator; {EXPR} is the expression itself;" \
  " and {EXPR1},{EXPR2},... are sub-expressions of the same.  The notation {EVAL(EXPR,x,y,c)} means the result of evaluating {EXPR} with current point {(x,y)} and current channe\n" \
  "\n" \
  "   {SCALAR}\n" \
  "     where {SCALAR} is any floating-point numeric constant. The" \
  " result is a non-pixmap scalar image, all of whose pixels are equal to" \
  " {SCALAR}, with flat interpolation." \
  "\n" \
  "   {ID}\n" \
  "     without indices or arguments.  Means the image with name {ID}.  Eval" \
  "\n" \
  "   {ID}[{EXPR1}]\n" \
  "     where {EXPR1} is a formula that yields a scalar" \
  " image. The result is a scalar image with same domain as {EXPR1}.  Evaluation of {EXPR} at  all of whose pixels are equal to {SCALAR}, with flat interpolation." \
  " as defined by the \"-image\" or \"-set\" option.  Without indices, an indentifier" \
  " like \"A\" means the pixel from that image that comes from the" \
  " same pixel and channel as the sample that is being" \
  " computed.  An identifier with a single index, as in" \
  " \"A[2]\", selects a specific color channel (numbered" \
  " from 0) of of the current pixel in the named image.  If" \
  " three indices are used, as in \"A[2,5,7]\", they are" \
  " interepreted as channel, column, and row indices, in" \
  " that order." \
  "\n" \
  "  Arithmetic operations are denoted" \
  " by \"+\", \"-\", \"*\", \"/\".  Also available" \
  " are some functions:\n" \
  "\n" \
  "     \"col()\" = current column index.\n" \
  "     \"row()\" = current row index.\n" \
  "     \"chn()\" = current channel index.\n" \
  "     \"chn()\" = current channel index.\n" \
  "     \"abs(x)\" = absolute value of x.\n" \
  "     \"sqr(x)\" = square of x.\n" \
  "     \"min(x,y)\" = min of x and y.\n" \
  "     \"max(x,y)\" = max of x and y.\n" \
  "     \"reldiff(x,y)\" = (x-y)/hypot(x,y).\n" \
  "     \"inter(s,x,y)\" = (1-s)*x + s*y.\n" \
  " .  Another popular interpolation method is \"bilinear\", which gives {A(x,y)=A[x,y]} when {x} and {y} are integers, and otherwise interpolates linearly between the pixel values {A[r(x),s(y)]}, where {r} and {s} are either {floor} or {ceil}. " \
  "\n" \
  "OPTIONS\n" \
  "  -image {ID} {INPUT_FNI}\n" \
  "    Specifies that the image called {ID} in the" \
  " expression(s) should be read from the file named" \
  " \"{INPUT_FNI}\".\n" \
  "\n" \
  "  -formula {EXPRESSION}\n" \
  "    Specifies the {EXPRESSION} to be used to compute" \
  " all samples of the output image.  Either this keyword" \
  " or \"-channel\" must be specified (but not both).\n" \
  "\n" \
  "  -channel {NUM} {EXPRESSION}\n" \
  "    Specifies the {EXPRESSION} to be used to compute" \
  " all samples of channel {NUM} of the output image.  If" \
  " this option is used, it should be used for each channel" \
  " of the output image.   Either this keyword" \
  " or \"-formula\" must be specified (but not both).\n" \
  "\n" \
  argparser_help_info_INFO "\n" \
  "\n" \
  "SEE ALSO" \
  "  pnmxarith(1)" \
  "AUTHOR" \
  "  Created on 2006-04-14 by Jorge Stolfi, IC-UNICAMP.\n" \
  " Inspired on pnmarith(1) by Jef Poskanzer." \

#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#include <argparser.h>

/* COMMAND-LINE OPTIONS */

typedef struct options_t
  { bool_t op1;     /* A boolean argument. */
    char* op2;      /* A string-valued argument. */
  } options_t;

/* INTERNAL PROTOTYPES */

options_t *parse_options(int argc, char **argv);
  /* Parses the command line arguments and packs them as an {options_t}. */

int main(int argc,char** argv);

/* IMPLEMENTATIONS */

int main(int argc, char** argv)
  {
    options_t *o = parse_options(argc, argv);
    
    return 0;
  }

options_t *parse_options(int argc, char **argv)
  {
    argparser_t *pp = argparser_new(stderr, argc, argv);
    argparser_set_help(pp, PROG_NAME " version " PROG_VERS ", usage:\n" PROG_HELP);
    argparser_set_info(pp, PROG_INFO);
    argparser_process_help_info_options(pp);
    
    options_t *o = (options_t *)malloc(sizeof(options_t)); 
    

    function = ' ';
    offset = 0.0;
    scale = 1.0;

    /* Check for flags. */
    argn = 1;
    while ((argn < argc) && (argv[argn][0] == '-') && (argv[argn][1] != '\0'))
      {
        if (argparser_keyword_present("-add"))
            function = '+';
        else if (argparser_keyword_present("-subtract"))
            function = '-';
        else if (argparser_keyword_present("-multiply"))
            function = '*';
        else if (argparser_keyword_present("-divide"))
            function = '/';
        else if (argparser_keyword_present("-difference"))
            function = 'D';
        else if (argparser_keyword_present("-ratio"))
            function = 'R';
        else if (argparser_keyword_present("-maximum"))
            function = 'X';
        else if (argparser_keyword_present("-minimum"))
            function = 'N';
        else if (argparser_keyword_present("-mix"))
          { function = 'M';
            if (argn+2 < argc)
              { 
                char *rest;
                alpha = argparser_get_next_double(pp, ???, ???); ++argn;
                if (*rest != '\0') { pm_usage(usage); } 
                beta = argparser_get_next_double(pp, ???, ???); ++argn;
                if (*rest != '\0') { pm_usage(usage); } 
              }
            else
              pm_usage(usage);
          }
        else if (argparser_keyword_present("-scale"))
          { if (argn+1 < argc)
              { 
                char *rest;
                scale = argparser_get_next_double(pp, ???, ???); ++argn;
                if (*rest != '\0') { pm_usage(usage); } 
              }
            else
              pm_usage(usage);
          }
        else if (argparser_keyword_present("-offset"))
          { if (argn+1 < argc)
              { 
                char *rest;
                offset = argparser_get_next_double(pp, ???, ???); ++argn;
                if (*rest != '\0') { pm_usage(usage); } 
              }
            else
              pm_usage(usage);
          }
        else
            pm_usage(usage);
        ++argn;
      }

    if (function == ' ') { pm_usage(usage); }

    if (argn == argc) { pm_usage(usage); }
    ifp1 = pm_openr(argv[argn]);
    ++argn;

    if (argn == argc) { pm_usage(usage); }
    ifp2 = pm_openr(argv[argn]);
    ++argn;

    if (argn != argc) { pm_usage(usage); }


    o->images = string_vec_new(0);
    NI = 0;
    while (argparser_keyword_present(pp, "-image"))
      { string_vec_expand(&(o->images), NI);
        o->images.el[NI] = argparser_get_next(pp); 
      }
    string_vec_trim(&(o->images), NI);
    
    if (argparser_keyword_present(pp, "-op2"))
      { o->op2 = argparser_get_next(pp); }
    else
      { o->op2 = "NONE"; }

    argparser_finish(pp);
        
    return o;
  }

/* COPYRIGHT, AUTHORSHIP, AND WARRANTY NOTICE:
** 
**   Copyright © ???? by the State University of Campinas (UNICAMP).
**
** Created on ???? by Jorge Stolfi, IC-UNICAMP.       
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

/* This program is similar to "pnmarith", with added operations. */

#include <jspnm.h>

/* Compute "a/b" scaled by "maxv". */
#define XELDIV(a,b,maxv) \
  ((xelval)((((double)(a))/((double)(b)))*(maxv) + 0.5))

extern double strtod(const char *, char **);

int
main(argc, argv)
  int argc;
  char* argv[];
{
  FILE* ifp1;
  FILE* ifp2;
  register xel* xelrow1;
  register xel* xelrow2;
  register xel* x1P;
  register xel* x2P;
  xelval maxval1, maxval2, maxval3;
  int hugeval;
  double scale, offset;
  double alpha = 0.5, beta = 0.5;
  int argn, rows1, cols1, format1, rows2, cols2, format2, format3, row, col;
  char function;

  options_t *o = get_options(argc, argv);

  pnm_readpnminit(ifp1, &cols1, &rows1, &maxval1, &format1);
  xelrow1 = pnm_allocrow(cols1);
  pnm_readpnminit(ifp2, &cols2, &rows2, &maxval2, &format2);
  if (cols2 != cols1 || rows2 != rows1)
    { pm_error("the two anymaps must be the same width and height"); }
  xelrow2 = pnm_allocrow(cols1);

  maxval3 = max(maxval1, maxval2);
  format3 = max(PNM_FORMAT_TYPE(format1), PNM_FORMAT_TYPE(format2));
  if (PNM_FORMAT_TYPE(format1) != format3 ||
       PNM_FORMAT_TYPE(format2) != format3)
    {
      switch (PNM_FORMAT_TYPE(format3))
        {
          case PPM_TYPE:
            if (PNM_FORMAT_TYPE(format1) != format3)
              { pm_message("promoting first file to PPM"); }
            if (PNM_FORMAT_TYPE(format2) != format3)
              { pm_message("promoting second file to PPM"); }
          break;
          case PGM_TYPE:
            if (PNM_FORMAT_TYPE(format1) != format3)
              { pm_message("promoting first file to PGM"); }
            if (PNM_FORMAT_TYPE(format2) != format3)
              { pm_message("promoting second file to PGM"); }
          break;
        }
    }
  hugeval = (int)(((unsigned int)(-1)) >> 1);
  /* fprintf(stderr, "hugeval = %d", hugeval); */
  if ((hugeval/maxval3 < maxval3) && ((function == '*') || (function == '/')))
    { pm_message("warning: maxval too large, overflow may occur"); }

  pnm_writepnminit(stdout, cols1, rows1, maxval3, format3, 0);
  for (row = 0; row < rows1; ++row)
    {
      pnm_readpnmrow(ifp1, xelrow1, cols1, maxval1, format1);
      if (maxval1 != maxval3 || PNM_FORMAT_TYPE(format1) != format3)
        { pnm_promoteformatrow(xelrow1, cols1, maxval1, format1, maxval3, format3); }

      pnm_readpnmrow(ifp2, xelrow2, cols1, maxval2, format2);
      if (maxval2 != maxval3 || PNM_FORMAT_TYPE(format2) != format3)
        { pnm_promoteformatrow(xelrow2, cols1, maxval2, format2, maxval3, format3); }

      for ( col = 0, x1P = xelrow1, x2P = xelrow2;
            col < cols1;
            ++col, ++x1P, ++x2P
          )
        {
          switch (PNM_FORMAT_TYPE(format3))
            {
              case PPM_TYPE:
                {
                  int r1, g1, b1, r2, g2, b2;

                  r1 = PPM_GETR(*x1P);
                  g1 = PPM_GETG(*x1P);
                  b1 = PPM_GETB(*x1P);
                  r2 = PPM_GETR(*x2P);
                  g2 = PPM_GETG(*x2P);
                  b2 = PPM_GETB(*x2P);
                  switch (function)
                    {
                      case '+':
                        r1 += r2;
                        g1 += g2;
                        b1 += b2;
                      break;

                      case '-':
                        r1 -= r2;
                        g1 -= g2;
                        b1 -= b2;
                      break;

                      case 'M':  /* alpha-beta mix */
                        r1 = (int)(alpha*(double)r1 + beta*(double)r2);
                        g1 = (int)(alpha*(double)g1 + beta*(double)g2);
                        b1 = (int)(alpha*(double)b1 + beta*(double)b2);
                      break;

                      case '*':
                        r1 = r1 * r2 / maxval3;
                        g1 = g1 * g2 / maxval3;
                        b1 = b1 * b2 / maxval3;
                      break;

                      case '/':
                        r1 = (r2 == 0 ? hugeval : XELDIV(r1, r2, maxval3));
                        g1 = (g2 == 0 ? hugeval : XELDIV(g1, g2, maxval3));
                        b1 = (b2 == 0 ? hugeval : XELDIV(b1, b2, maxval3));
                      break;

                      case 'D':
                        r1 = (r1>r2)?(r1-r2):(r2-r1);
                        g1 = (g1>g2)?(g1-g2):(g2-g1);
                        b1 = (b1>b2)?(b1-b2):(b2-b1);
                      break;

                      case 'R':
                        r1 = (r1+r2 == 0 ? maxval3/2 : XELDIV(r1, r1+r2, maxval3));
                        g1 = (g1+g2 == 0 ? maxval3/2 : XELDIV(g1, g1+g2, maxval3));
                        b1 = (b1+b2 == 0 ? maxval3/2 : XELDIV(b1, b1+b2, maxval3));
                      break;

                      case 'X':
                        r1 = (r1>r2)?r1:r2;
                        g1 = (g1>g2)?g1:g2;
                        b1 = (b1>b2)?b1:b2;
                      break;

                      case 'N':
                        r1 = (r1>r2)?r2:r1;
                        g1 = (g1>g2)?g2:g1;
                        b1 = (b1>b2)?b2:b1;
                      break;

                      default:
                        pm_error("can't happen");
                      break;
                    }
                  if ((offset != 0.0) || (scale != 1.0))
                    { r1 = (int)(scale * r1 + offset);
                      g1 = (int)(scale * g1 + offset);
                      b1 = (int)(scale * b1 + offset);
                    }
                  if (r1 < 0) r1 = 0; else if (r1 > maxval3) r1 = maxval3;
                  if (g1 < 0) g1 = 0; else if (g1 > maxval3) g1 = maxval3;
                  if (b1 < 0) b1 = 0; else if (b1 > maxval3) b1 = maxval3;
                  PPM_ASSIGN(*x1P, r1, g1, b1);
                }
              break;

              default:
                {
                  int g1, g2;

                  g1 = PNM_GET1(*x1P);
                  g2 = PNM_GET1(*x2P);
                  switch (function)
                    {
                      case '+':
                        g1 += g2;
                      break;

                      case '-':
                        g1 -= g2;
                      break;

                      case 'M':  /* alpha-beta mix */
                        g1 = (int)(alpha*(double)g1 + beta*(double)g2);
                      break;

                      case '*':
                        g1 = g1 * g2 / maxval3;
                      break;

                      case '/':
                        g1 = (g2 == 0 ? hugeval : XELDIV(g1, g2, maxval3));
                      break;

                      case 'D':
                        g1 = (g1>g2)?(g1-g2):(g2-g1);
                      break;

                      case 'R':
                        g1 = (g1+g2 == 0 ? maxval3/2 : XELDIV(g1, g1+g2, maxval3));
                      break;

                      case 'X':
                        g1 = (g1>g2)?g1:g2;
                      break;

                      case 'N':
                        g1 = (g1>g2)?g2:g1;
                      break;

                      default:
                        pm_error("can't happen");
                      break;
                    }
                  if ((offset != 0.0) || (scale != 1.0))
                    { g1 = (int)(scale * g1 + offset); }
                  if (g1 < 0) g1 = 0; else if (g1 > maxval3) g1 = maxval3;
                  PNM_ASSIGN1(*x1P, g1);
                }
              break;
            }
        }
      pnm_writepnmrow(stdout, xelrow1, cols1, maxval3, format3, 0);
    }

  pm_close(ifp1);
  pm_close(ifp2);

  exit(0);
}

/* Modification history:
** 
**   nov/2001: options_t "-ratio", "-mix" added by Jorge Stolfi.
**   ???/????: options_t "-div", "-max", "-min", "-scale", "-offset"
**     added by Jorge Stolfi.
**   ???/????: Slightly modified by Marcel Wijkstra <wijkstra@fwi.uva.nl>.
**   1989-1991: Original "pnmarith" by Jef Poskanzer.
*/

/* Copyright © 1989, 1991 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <jspnm.h>

#define wR  0.299
#define wG 0.597
#define wB 0.104

long int menor(long int a, long int b){
	if(a > b){
		return b;
	}
	return a;
}

float media_ponderada(float R, float G, float B){
	float temp;
	temp = wR*R;
	temp = temp + (wG*G);
	temp = temp + (wB*B);
	//temp = fabs(temp);// fabs - funcao do math.h que retorna o valor absoluto de um  float
	return temp;
}

void  calcular_diferenca(Imagem* im1,Imagem* im2, Imagem*  saida){
	long int i,j;
	for(i = 0 ; i< get_widht(saida);i++){
		for(j = 0;j< get_height(saida);j++){
			pixel A ;
			pixel B ;
			A =  get_Pixel(im1,i,j);
			B =  get_Pixel(im2,i,j);
			//printf("%d %d %d \n",A.canal[0],A.canal[1],A.canal[2]);
			float corA  = media_ponderada(A.canal[0],A.canal[1],A.canal[2])/255.0;
			float corB  = media_ponderada(B.canal[0],B.canal[1],B.canal[2])/255.0;
			float  diferenca;
			diferenca  = sqrt((corB - corA)*(corB - corA));
			//printf("A:%f B:%f \n",corA,corB);
			//printf("R:%d G:%d B:%d \n",A.canal[0],A.canal[1],A.canal[2]);
			set_pixel(saida,i,j,0, diferenca * 255);
			set_pixel(saida,i,j,1, diferenca * 255);
			set_pixel(saida,i,j,2, diferenca * 255);
		}
	}
}

void  calcular_diferenca_pixel_a_pixel(Imagem* im1,Imagem* im2, Imagem*  saida){
	long int i,j;
	for(i = 0 ; i< get_widht(saida);i++){
		for(j = 0;j< get_height(saida);j++){
			pixel A ;
			pixel B ;
			pixel C;
			int k;
			A =  get_Pixel(im1,i,j);
			B =  get_Pixel(im2,i,j);
			for(k=0;k<3;k++){
				C.canal[k] = (B.canal[k] - A.canal[k])*(B.canal[k] - A.canal[k]);
				printf("%d\n",C.canal[k]);
				set_pixel(saida,i,j,k, C.canal[k]);
			}
					//printf("%f\n",diferenca);
			
		}
	}
}

int main(int argc, char** argv){
	if(argc != 4 ){
		puts("USO DO PROGRAMA");
		puts("programa <imagem 1> <imagem 2> <imagem-saida>");
		
		return 0;
	}
	long int h,w;
	Imagem* im1;
	Imagem* im2;
	Imagem* saida;
	abre_arquivo(&im1,argv[1]);
	abre_arquivo(&im2,argv[2]);
	h = menor(get_height(im1),get_height(im2));
	w = menor(get_widht(im1),get_widht(im2));
	if((get_height(im1) != get_height(im2)) || (get_widht(im1) != get_widht(im2))){
		char resp;
		puts("Atencao:O tamanho das imagens difere.");
		puts("As dimensÃ•es da imagem de saida serÃ£o as menores entre as 2 imagens.");
		printf("Deseja continuar (S/N)?");
		scanf(" %c",&resp);
		if(resp != 'S'){
			return 0;
		}
		
	}
	saida = cria_imagem(w,h);
	calcular_diferenca(im1,im2,saida);
	salva_arquivo(argv[3],saida);
	//salva_arquivo("lixo.pnm",im1);
	puts("Imagem de diferenca gerada com sucesso!");
	return 0;
}

