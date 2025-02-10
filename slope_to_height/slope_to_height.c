#define PROG_NAME "slope_to_height"
#define PROG_DESC "compute a heigth map from X and Y slope maps"
#define PROG_VERS "1.0"

#define slope_to_height_C_COPYRIGHT "Copyright © 2005 by the State University of Campinas (UNICAMP)"

/* Last edited on 2025-01-16 17:39:47 by stolfi */

#define PROG_HELP \
  "  " PROG_NAME " \\\n" \
  "    [ -maxIter {MAX_ITER} ] \\\n" \
  "    [ -convTol [CONV_TOL} ] \\\n" \
  "    [ -topoSort ] \\\n" \
  "    [ -compareZ {REF_Z_FNI_NAME} ] \\\n" \
  "    [ -verbose ] \\\n" \
  "    [ -debugG ] [ -debugZ ] [ -debugSys ] \\\n" \
  "    [ -debugIter {DBG_STEP} ] \\\n" \
  "    -slopes {IG_FNI_NAME} \\\n" \
  "    -weights {IW_FNI_NAME} \\\n" \
  "    -outPrefix {PREFIX} \\\n" \
  "    " argparser_help_info_HELP ""

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
  "OUTPUT FILES\n" \
  PROG_INFO_FILE "\n" \
  "\n" \
  "OPTIONS\n" \
  PROG_INFO_OPTS "\n" \
  "\n" \
  argparser_help_info_HELP_INFO "\n" \
  "\n" \
  "SEE ALSO\n" \
  "  fni_to_pnm(1), pnm_to_fni(1).\n" \
  "\n" \
  "AUTHOR\n" \
  "  Created 2005-08-15 by Jorge Stolfi, UNICAMP.\n" \
  "MODIFICATION HISTORY\n" \
  "  2008-11-08 by J. Stolfi, IC-UNICAMP: added the weight map option.\n" \
  "\n" \
  "  2008-11-09 by J. Stolfi, IC-UNICAMP: added the reference height map.\n" \
  "\n" \
  "  2010-04-26 by J. Stolfi, IC-UNICAMP: options \"-newStyle\", \"-avgWidth\".\n" \
  "\n" \
  "  2010-04-28 by J. Stolfi, IC-UNICAMP:\n" \
  "    * Computes a {Z} confidence map {OW} from the {G} confidence map {IW}.\n" \
  "    * \"-debugZ\"   implies output of Z and error maps at various levels and iterations.\n" \
  "    * \"-compareZ\" also writes one-line files with error summaries.\n" \
  "    * Explicit \"-slopes\" and \"-weights\" options.\n" \
  "    * Removed \"-debugPrefix\" added \"-outPrefix\".\n" \
  "    * The debug prefix is {PREFIX} plus \"-dbg\".\n" \
  "    * Output {OZ} goes to file, not to standard output.\n" \
  "\n" \
  "  2010-05-04 by J. Stolfi, IC-UNICAMP:" \
  "    * Excludes zero-weight pixels from system.\n" \
  "\n" \
  "  2010-05-04 by J. Stolfi, IC-UNICAMP:" \
  "    * Removed \"-newStyle\", \"-avgWidth\", \"-harmonicAvgW\".\n" \
  "    * Added \"-topoSort\".\n" \
  "\n" \
  "WARRANTY\n" \
  argparser_help_info_NO_WARRANTY "\n" \
  "\n" \
  "RIGHTS\n" \
  "  " slope_to_height_C_COPYRIGHT ".\n" \
  "\n" \
  argparser_help_info_STANDARD_RIGHTS
  
#define DEFAULT_MAX_ITER 100000
  /* Default max iterations per level. */
  
#define DEFAULT_CONV_TOL 0.0000005
  /* Default convergence threshold per level. */
  
#define DEFAULT_AVG_WIDTH 2
  /* Default kernel window size for map reduction. */
  
#define stringify(x) strngf(x)
#define strngf(x) #x

#define PROG_INFO_DESC \
  "  The program reads a /slope map/ {IG}, consisting of" \
  " the {X} and {Y} derivatives of some terrain surface {Z(X,Y)}; and" \
  " computes the corresponding /height map/ {OZ}.  Optionally, the" \
  " program may also compare the computed height map {OZ} with" \
  " a reference height map {RZ} provided by the user.\n" \
  "\n" \
  "  The input slope map is a two-channel float image {IG}.  Each" \
  " pixel {IG[X,Y]} of this image is" \
  " the gradient of the {Z} function, averaged" \
  " over the unit square cell (/pixel/) whose lower left corner" \
  " is the point {(X,Y)}.\n" \
  "\n" \
  "  The program may also read an optional /weight map/ {IW}, a" \
  " single-channel image that specifies the reliability" \
  " of the slope data.  Specifically, {IW[X,Y]} is the reliability" \
  " for the slope datum {IG[X,Y]}.  A zero weight means that the slope" \
  " datum should be ignored.\n" \
  "\n" \
  "  The output height map {OZ} is a single-channel" \
  " image containing the {Z} values of the terrain most" \
  " compatible with the given slopes.  It includes an arbitrary" \
  " global integration constant for each maximal part of the" \
  " domain which is connected by paths with non-zero weight.  This" \
  " image has one more column and one more row than the input slope maps.\n" \
  "\n" \
  "  If the \"-compareZ {REF_Z_NAME}\" option is given, the program" \
  " also outputs an error map {EZ}, defined as the difference between" \
  " the height map computed by the program and a reference map" \
  " read from the FNI-format file {REF_Z_NAME}.  The error map" \
  " is adjusted to have zero mean.  Any {Z} values that are" \
  " next to missing or unreliable slope data are excluded from the comparison.\n" \
  "\n" \
  "  If the \"-debugZ\" option is given, the program" \
  " also writes out the intermediate (reduced-scale)" \
  " solutions found, for debugging.  If \"-debugIter {DBG_STEP}\" is" \
  " given and {DBG_STEP} is nonzero, these diagnostics are written" \
  " every that many iterations.  The options" \
  " \"-debugG\" and \"-debugSys\" cause additional" \
  " debugging data to be written---namely, the reduced slope" \
  " maps and the linear systems solved at each scale," \
  " respectively."
  
#define PROG_INFO_FILE \
  "  {PREFIX}-Z.fni\n" \
  "    The computed height map {OZ}.\n" \
  "\n" \
  "  {PREFIX}-eZ.fni\n" \
  "    The error map {EZ} for the cmputed map {OZ}.\n" \
  "\n" \
  "  {PREFIX}-eZ.txt\n" \
  "    A one-line summary of the error, with the format\n" \
  "\n" \
  "     {level} {NX} {NY} {iter} {change} {sRZ} {sOZ} {sEZ} {sre}.\n" \
  "\n" \
  "    where {NX,NY} is the image size, {iter} is the number of" \
  " iterations performed at level 0, {change} is the change in" \
  " the last iteration, {sRZ} and {sOZ} are the deviations of" \
  " the {RZ} and {OZ} maps, {sEZ} is the RMS value of {EZ}, and" \
  " {sre} is the relative error.\n" \
  "\n" \
  "  The following files are produced for each level" \
  " of the recursion (except the topmost one in some" \
  " cases).  The {LEVEL} part is the recursion" \
  " level (0 = original scale), with 2 digits.  They are" \
  " requested by the \"-debugG\", \"-debugZ\", and \"-debugSys\" options," \
  " some of them in conjunction with \"-compareZ\".\n" \
  "\n" \
  "  {PREFIX}-dbg-{LEVEL}-dZ.fni\n" \
  "    The input slopes {IG}, reduced to level {LEVEL}.\n" \
  "\n" \
  "  {PREFIX}-dbg-{LEVEL}-W.fni\n" \
  "    The input slope weight mask {IW}, reduced to level {LEVEL}.\n" \
  "\n" \
  "  {PREFIX}-dbg-{LEVEL}-rZ.fni\n" \
  "    The reference height map {RZ}, reduced to level {LEVEL}.\n" \
  "\n" \
  "  {PREFIX}-dbg-{LEVEL}-Z.fni\n" \
  "    The computed height map {OZ} at level {LEVEL}.\n" \
  "\n" \
  "  {PREFIX}-dbg-{LEVEL}-U.fni\n" \
  "    The confidence mask {OW} for the heights at level {LEVEL}.\n" \
  "\n" \
  "  {PREFIX}-dbg-{LEVEL}-eZ.fni\n" \
  "    The height error map {EZ} for {OZ} and {RZ} at level {LEVEL}.\n" \
  "\n" \
  "  {PREFIX}-dbg-{LEVEL}-eZ.txt\n" \
  "    The error summary for level {LEVEL}.\n\n" \
  "\n" \
  "  {PREFIX}-dbg-{LEVEL}-S.sys\n" \
  "    The linear system solved at level {LEVEL}.\n" \
  "\n" \
  "  The following files may be produced at the beginning, during, and" \
  " after the end of the iteration.  The {ITER} part is" \
  " the number of iterations done, with 9 digits.  They are" \
  " requested by the \"-debugG\", \"-debugZ\", and \"-debugSys\" options," \
  " some of them with \"-compareZ\", together with a positive \"-debugIter\".\n" \
  "\n" \
  "  {PREFIX}-dbg-{LEVEL}-{ITER}-Z.fni\n" \
  "    The computed height map {OZ} at level {LEVEL} after {ITER} iterations.\n" \
  "\n" \
  "  {PREFIX}-dbg-{LEVEL}-{ITER}-eZ.fni\n" \
  "    The height error map {EZ} for {OZ} and {RZ} at level {LEVEL} after {ITER} iterations.\n" \
  "\n" \
  "  {PREFIX}-dbg-{LEVEL}-{ITER}-eZ.txt\n" \
  "    The height error summary for level {LEVEL} after {ITER} iterations."

#define PROG_INFO_OPTS \
  "  -slopes {IG_FNI_NAME}\n" \
  "    This mandatory argument specifies the file name" \
  " containing the input slope map {IG}, which must be a two-channel image in FNI format" \
  " (see float_image.h).  If {IG_FNI_NAME}" \
  " is \"-\", the slope map is read from standard input.\n" \
  "\n" \
  "  -weights {IW_FNI_NAME}\n" \
  "    This optional argument specifies the file containing the input" \
  " slope weight map {IW}.  It must be a single-channel image with non-negative" \
  " values, preferably between 0 and 1, and with the same size as {IG}.  Slope" \
  " samples with weight 0 are ignored.  If {IW_FNI_NAME}" \
  " is \"-\", the slope weight map is read from standard input.  If this argument is omitted, the" \
  " program assumes that all slope samples have weight 1.\n" \
  "\n" \
  "  -outPrefix {PREFIX}\n" \
  "    Specifies the common prefix for all output" \
  " file names.  Mandatory." \
  "\n" \
  "  -compareZ {REF_Z_FNI_NAME}\n" \
  "    If this argument is present, the program" \
  " also outputs an error map, defined as the difference between" \
  " the height map computed by the program and a reference map" \
  " read from the FNI-format file \"{REF_Z_NAME}\".  The reference" \
  " map must have either the same size as the input slope map, or one extra column and" \
  " one extra row.  In the first case, the computed height map" \
  " will be interpolated before the comparison.  The error map, with" \
  " the same size as the reference map, is written" \
  " to the file \"{ERR_Z_FNI_NAME}\".  If this option is" \
  " omitted, the reference map is not read and the error file" \
  " is not written.\n" \
  "\n" \
  "  -maxIter {MAX_ITER}\n" \
  "  -convTol {CONV_TOL}\n" \
  "    These optional parameters specify the stopping criterion for the" \
  " iteration.  The iteration will stop when the maximuum change in any" \
  " height field is less than {CONV_TOL}, or after {MAX_ITER} iterations, whichever" \
  " happens first. The defaults are {MAX_ITER = " stringify(DEFAULT_MAX_ITER) "}," \
  " {CONV_TOL = " stringify(DEFAULT_CONV_TOL) "}.\n" \
  "\n" \
  "  -topoSort\n" \
  "    This optional flag causes the program to solve the equations in order of" \
  " increasing equation weight.  If omitted, the equations are solved in row-by-row order.\n" \
  "\n" \
  "  -verbose\n" \
  "    Causes the program to write various diagnostics to stderr, in" \
  " particular one line per iteration of the Gauss-Seidel solver.\n" \
  "\n" \
  "  -debugG\n" \
  "    Causes the program to write the reduced versions" \
  " of the slope maps used at intermediate scales," \
  " in human-readable format.  The reduced weight maps are written too.\n" \
  "\n" \
  "  -debugZ\n" \
  "    Causes the program to write the solutions" \
  " (height maps) obtained at intermediate scales," \
  " in human-readable formats.  The height confidence maps {OW} are" \
  " also written.  If \"compareZ\" was" \
  " also given, the program also writes the error" \
  " map and error summaries for these reduced solutions.\n" \
  "\n" \
  "  -debugSys\n" \
  "    Causes the program to write the linear systems" \
  " used at intermediate scales.\n" \
  "\n" \
  "  -debugIter {DBG_STEP}\n" \
  "    If this optional argument is given and {DBG_STEP} is" \
  " not zero, the heights {OZ}, the error maps {EZ}, and the" \
  " error summaries are written out after every {DBG_STEP} iterations, as" \
  " well as at the beginning (0 iterations) and after the end of the" \
  " iterative solving.  If {DBG_STEP} is larger than {MAX_ITER} only" \
  " the initial and final states are written.  If {DBG_STEP} is zero (the default)," \
  " no \"...-{ITER}-...\" files are written."

#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <values.h>
#include <stdint.h>
#include <math.h>

#include <bool.h>
#include <jsstring.h>
#include <jsfile.h>
#include <argparser.h>
#include <float_image.h>
#include <float_image_mscale.h>

#include <pst_slope_map.h>
#include <pst_imgsys.h>
#include <pst_height_map.h>

/* COMMAND-LINE OPTIONS */

typedef struct options_t
  {
    char *slopeFileName;  /* File name of input slope file, or "-" for stdin. */
    char *weightFileName; /* File name of weight slope file, or "-" for stdin (NULL if none). */
    char *refZFileName;   /* File name of input reference height map (NULL if none). */
    char *outPrefix;      /* Output file name prefix. */
    int64_t maxIter;      /* Max iterations per level. */
    double convTol;       /* Convergence threshold. */
    bool_t topoSort;      /* TRUE solves the equations in order of increasing weight. */
    /* Debugging and analysis */
    bool_t verbose;       /* TRUE to print various diagnostics. */
    bool_t debugZ;        /* TRUE writes out the intermediate Z images. */
    bool_t debugG;        /* TRUE writes out the intermediate slope and weight arrays. */
    bool_t debugSys;      /* TRUE writes the linear system(s). */
    int32_t debugIter;        /* Frequency for debugging output during iteration, or 0 if none. */
  } options_t;

float_image_t *read_fni_file(char *fileName);
  /* Reads a FNI image from file "{fileName}" (which should include the extension ".fni").
    If {fileName} is "-", reads from standard input. */

void write_fni_file(float_image_t *I, char *fileName, int32_t indent);
  /* Writes the float image {I} in a human-readable format, to a file
    called "{fileName}" (which should include the extension ".fni").
    If {fileName} is "-", writes the image to standard output.
    Diagnostic messages are indented by {indent}. */

options_t *parse_options(int32_t argc, char **argv);
  /* Parses the command line arguments and packs them as an {options_t}. */

void compute_and_write_height_map(options_t *o, float_image_t *IG, float_image_t *IW, float_image_t *RZ);
  /* Computes the height map {OZ} from the gradient map {IG} and its
    reliability map {IW}. If {IW} is null, assumes all weights are 1.
    If {RZ} is not null, compares {OZ} with {RZ} and writes the error
    map {EZ=OZ-RZ} and the error sumary file. Depending on the options
    {o} also writes these outputs at each level of the multiscale
    recursion, and possibly also after certain iterations at each
    level. */

int32_t main(int32_t argc,char** argv);

/* IMPLEMENTATIONS */

int32_t main(int32_t argc, char** argv)
  {
    options_t *o = parse_options(argc, argv);
    
    fprintf(stderr, "Reading the slope map {IG}:\n");
    float_image_t *IG;  /* Input gradient map. */
    IG = read_fni_file(o->slopeFileName);
    
    float_image_t *IW; /* Input (gradient) reliability weight map. */
    if (o->weightFileName == NULL)
      { IW = NULL; }
    else
      { fprintf(stderr, "Reading the slope reliability weight map {IW}:\n");
        IW = read_fni_file(o->weightFileName);
      }
    
    float_image_t *RZ; /* Reference height map. */
    if (o->refZFileName == NULL)
      { RZ = NULL; }
    else
      { fprintf(stderr, "Reading the reference height map {RZ}:\n");
        RZ = read_fni_file(o->refZFileName);
      }
    
    fprintf(stderr, "Computing the height map {OZ}:\n");
    compute_and_write_height_map(o, IG, IW, RZ);
    
    float_image_free(IG); IG = NULL;
    float_image_free(IW); IW = NULL;
    float_image_free(RZ); RZ = NULL;

    fprintf(stderr, "Done!\n");
    return 0;
  }
  
#define MAX_LEVEL 20
  /* Max level expected in recursion; that is {log_2} of max image width or height. */
  
void compute_and_write_height_map(options_t *o, float_image_t *IG, float_image_t *IW, float_image_t *RZ)
  {
    demand(IG->sz[0] == 2, "gradient map must have two channels");
    int32_t NX_G = IG->sz[1];
    int32_t NY_G = IG->sz[2];
    
    /* Check the slope weight map {IW}: */
    if (IW != NULL)
      { demand(IW->sz[0] == 1, "weight map must have a single channel");
        demand(NX_G == IW->sz[1], "wrong IW width");
        demand(NY_G == IW->sz[2], "wrong IW height");
      }
    
    /* Check the reference height map {RZ}: */
    int32_t NX_RZ = 0;
    int32_t NY_RZ = 0;
    bool_t interpolate_OZ;  /* Tells whether {OZ} must be reduced by 1 before comparison. */
    if (RZ != NULL)
      { 
        demand(RZ->sz[0] == 1, "ref Z must have a single channel");
        NX_RZ = RZ->sz[1]; 
        NY_RZ = RZ->sz[2]; 
        if ((NX_RZ == NX_G+1) && (NY_RZ == NY_G+1))
          { interpolate_OZ = FALSE; }
        else if ((NX_RZ == NX_G) && (NY_RZ == NY_G))
          { interpolate_OZ = TRUE; }
        else
          { demand(FALSE, "wrong ref Z size"); }
      }

    char *debugPrefix = txtcat(o->outPrefix, "-deb"); /* Prefix for debug file names. */

    /* Data for the current mscale level, saved by the debugging procs: */
    float_image_t *ms_OW[MAX_LEVEL+1]; 
    float_image_t *ms_RZ[MAX_LEVEL+1];
    int32_t k;
    for (k = 0; k <= MAX_LEVEL; k++) { ms_OW[k] = ms_RZ[k] = NULL; }

    int32_t cur_level = -1;

    auto void reportData(int32_t level, float_image_t *cur_G, float_image_t *cur_W);
    auto void reportSys(int32_t level, pst_imgsys_t *cur_S);
    auto void reportHeights(int32_t level, int32_t iter, int32_t change, bool_t final, float_image_t *cur_Z, float_image_t *cur_U);
      /* These procedures are called at various times during the recursive
         multiscale integration. See {pst_integrate_recursive}.
         The {reportHeights} procedure will write all the requested intermediate
         {Z} and {EZ} images and the error summaries, as well as 
         the final ones. */
    
    void reportData(int32_t level, float_image_t *cur_G, float_image_t *cur_W)
      {
        /* This procedure is called once per leve, on the way up. */
        
        assert(level <= MAX_LEVEL);
        int32_t indent = 2*level+2;
        
        if (o->debugG)
          { /* Write out the scaled slope and weight maps: */
            float_image_mscale_write_file(cur_G, debugPrefix, level, -1, "dZ", indent);
            if (cur_W != NULL) 
              { float_image_mscale_write_file(cur_W, debugPrefix, level, -1, "W", indent); }
          }
          
        int32_t NX_cur_RZ = 0;  /* Cols of the reference height map for this level. */
        int32_t NY_cur_RZ = 0;  /* Rows of the reference height map for this level. */
        if (RZ != NULL)
          { /* Compute and save the height reference map: */
            if (level == 0)
              { if (o->verbose) 
                  { fprintf(stderr, "%*sUsing given reference map with size", indent, ""); }
                ms_RZ[level] = RZ; }
            else
              { assert(level == cur_level + 1); 
                assert(ms_RZ[cur_level] != NULL);
                float_image_t *pre_RZ = ms_RZ[cur_level]; /* Previous level's ref map. */
                int32_t NX_pre_IG = pre_RZ->sz[1];  /* Cols of the reference height map for this level. */
                int32_t NY_pre_IG = pre_RZ->sz[2];  /* Rows of the reference height map for this level. */
                if (o->verbose) 
                  { fprintf(stderr, "%*sShrinking reference map from %d × %d to", indent, "", NX_pre_IG, NY_pre_IG); }
                int32_t avgWidth = 2;
                ms_RZ[level] = pst_height_map_shrink(ms_RZ[cur_level]);
              }
            NX_cur_RZ = ms_RZ[level]->sz[1];
            NY_cur_RZ = ms_RZ[level]->sz[2];
            if (o->verbose) { fprintf(stderr, " %d × %d\n", NX_cur_RZ, NY_cur_RZ); }
          }
          
        bool_t needs_W = (RZ != NULL) && (IW != NULL) && (o->debugZ || level == 0);
        if (needs_W)
          { /* Compute and save the height confidence map: */
            if (o->verbose) 
              { fprintf(stderr, "%*sComputing the reduced height confidence map ...\n", indent, ""); }
            ms_W[level] = pst_weight_map_slope_to_height(cur_W, TRUE, NX_cur_RZ, NY_cur_RZ);
          }
        else
          { ms_W[level] = NULL; }
          
        cur_level = level;
      }
      
    void reportSys(int32_t level, pst_imgsys_t *cur_S)
      {
        /* This procedure is called once per level on the way down. */
        assert(level <= MAX_LEVEL);
        int32_t indent = 2*level+2;
        
        if (o->debugSys)
          { pst_imgsys_write_report(cur_S, debugPrefix, level, "S", indent); }
      }
    
    void reportHeights(int32_t level, int32_t iter, int32_t change, bool_t final, float_image_t *ms_Z, float_image_t *cur_U)
      { 
        /* This procedure is called at least once per level on the way down, including
          once with {final=TRUE}. */
        assert(level <= MAX_LEVEL);
        int32_t indent = 2*level+2;
        
        /* Decide whether to write the data, and how: */
        bool_t writeAsIter = (o->debugIter > 0) && (final || (iter % o->debugIter == 0));
        bool_t writeAsLevel = o->debugZ && final;
        bool_t writeAsFinal = (level == 0) && final;
        
        bool_t analyzeError = (RZ != NULL);
        
        if (writeAsIter)
          { bool_t writeImages = o->debugZ;
            bool_t writeError = writeImages && analyzeError;
            if (writeError) {  assert(ms_RZ[level] != NULL); }
            if (writeError && (IW != NULL)) { assert(ms_W[level] != NULL); }
            pst_height_map_level_analyze_and_write
              ( debugPrefix, level, iter, change, 
                ms_Z, ms_RZ[level], ms_W[level], 
                writeImages, writeError
              );
          }
        
        if (writeAsLevel)
          { bool_t writeImages = o->debugZ;
            bool_t writeError = writeImages && analyzeError;
            if (writeError) {  assert(ms_RZ[level] != NULL); }
            if (writeError && (IW != NULL)) { assert(ms_W[level] != NULL); }
            pst_height_map_level_analyze_and_write
              ( debugPrefix, level, -1, change, 
                ms_Z, ms_RZ[level], ms_W[level], 
                writeImages, writeError
              );
          }
        
        if (writeAsFinal)
          { bool_t writeImages = TRUE;
            bool_t writeError = writeImages && analyzeError;
            pst_height_map_level_analyze_and_write
              ( o->outPrefix, -1, -1, change, 
                ms_Z, ms_RZ[level], ms_W[level], 
                writeImages, writeError
              );
          }
      }

    /* Call recursive integrator: */
    float_image_t *Z = NULL;
    float_image_t *W = NULL;
    pst_integrate_recursive
      ( IG, IW, 0, 
        o->maxIter, o->convTol, o->topoSort,
        &Z, &W,
        o->verbose,
        reportData, 
        reportSys, 
        o->debugIter,
        reportHeights
      );
      
    /* Free working storage: */
    free(debugPrefix);
    for (k = 0; k <= MAX_LEVEL; k++) 
      { /* {ms_W[k]} is always NULL or new: */
        float_image_free(ms_W[k]); 
        /* {ms_RZ[0]} is the original: */
        if (k > 0) { float_image_free(ms_RZ[k]); }
      }
  }

float_image_t *read_fni_file(char *fileName)
  { demand(fileName != NULL, "file name not given");
    fprintf(stderr, "Reading %s ...", fileName);
    FILE *rd = open_read(fileName, FALSE);
    float_image_t *I = float_image_read(rd);
    if (rd != stdin) { fclose(rd); }
    fprintf(stderr, "\n");
    return I;
  }

void write_fni_file(float_image_t *I, char *fileName, int32_t indent)???
  { demand(fileName != NULL, "file name not given");
    fprintf(stderr, "%*sWriting %s ...", indent???, "", fileName);
    FILE* wr = open_write(fileName, FALSE);
    float_image_write(wr, I);
    if (wr == stdout) { fflush(wr); } else { fclose(wr); }
    fprintf(stderr, "\n");
  }

options_t *parse_options(int32_t argc, char **argv)
  { argparser_t *pp = argparser_new(stderr, argc, argv);
    argparser_set_help(pp, PROG_NAME " version " PROG_VERS ", usage:\n" PROG_HELP);
    argparser_set_info(pp, PROG_INFO);
    argparser_process_help_info_options(pp);
    
    options_t *o = (options_t *)notnull(malloc(sizeof(options_t)), "no mem"); 

    if (argparser_keyword_present(pp, "-maxIter"))
      { o->maxIter = (int32_t)argparser_get_next_int(pp, 0, INT64_MAX); }
    else
      { o->maxIter = DEFAULT_MAX_ITER; }
    
    if (argparser_keyword_present(pp, "-convTol"))
      { o->convTol = argparser_get_next_double(pp, 0, DBL_MAX); }
    else
      { o->convTol = DEFAULT_CONV_TOL; }
    
    o->topoSort = argparser_keyword_present(pp, "-topoSort");
    
    if (argparser_keyword_present(pp, "-compareZ"))
      { o->refZFileName = argparser_get_next(pp); }
    else
      { o->refZFileName = NULL; }
    
    o->verbose = argparser_keyword_present(pp, "-verbose");
    
    o->debugZ = argparser_keyword_present(pp, "-debugZ");
    o->debugG = argparser_keyword_present(pp, "-debugG");
    o->debugSys = argparser_keyword_present(pp, "-debugSys");
    
    if (argparser_keyword_present(pp, "-debugIter"))
      { o->debugIter = (int32_t)argparser_get_next_int(pp, 0, INT32_MAX); }
    else
      { o->debugIter = 0; }

    argparser_get_keyword(pp, "-slopes");
    o->slopeFileName = argparser_get_next_non_keyword(pp);
    
    if (argparser_keyword_present(pp, "-weights"))
      { o->weightFileName = argparser_get_next(pp); }
    else
      { o->weightFileName = NULL; }
    
    argparser_get_keyword(pp, "-outPrefix");
    o->outPrefix = argparser_get_next(pp);

    argparser_skip_parsed(pp);
    
    argparser_finish(pp);
    
    return o;
  }
