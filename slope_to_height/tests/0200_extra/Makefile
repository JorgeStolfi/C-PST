# Last edited on 2023-02-04 07:01:16 by stolfi

PROG := slope_to_height

PROGDIR := ../..

include ${STOLFIHOME}/programs/c/GENERIC-PROGS-TEST.make

VIEW := NO
PLOT := YES
SHOW := YES
DEBUG := YES

# Harmonic averaging of weights:
HARMONIC := YES

# Format:  
# {FUNC}LZ}NZ}LG}NG}GRADTYPE}MAXGDIFF}SIGMAG}SIGMAW}WOPT}AVGW}NSTY}ZMIN}ZMAX}ZSTEP}GMAX}ERRMAX}
# where
# {FUNC}...{SIGMAW} as in make_test_slope_maps/tests/Makefile.
# {WOPT} is "U" to use uniform weights, "W" to use the associated weight mask.
# {AVGW} width of kernel window for map reduction.
# {NSTY} 0 use old base for recursion, 1 use the new one.
# {ZMIN},{ZMAX} height range for gnuplot.
# {ZSTEP} height tic mark step for gnuplot.
# {GMAX} max abs value of derivative for gnuplot.
# {ERRMAX} max height error for gnuplot.

# For best plots, {GMAX}/2 and {ERRMAX}/4 should be simple
# numbers.

# Test groups
# First and 2nd part of group name refers
# to how the Z and G are sampled:
#   SHARP = single point sampling.
#   PIXEL = uniform average in 1-pixel window.
#   SMOOTH = Hann weighted average in 2-pixel window.
   
# 1-pixel sampled Z, 2-pixel sampled gradient,
# uses analytic gradient, with weights, no noise,
# averaging kernel width 2, old style recursion.
TESTS_AVG2_OLDSTY_FUNCA := \
  00񔄮5񔘛1�3.00�0.000�0.000�2LD�-0020�+0020�0005�02.0�02.0 \
  01񔄮5񔘛1�3.00�0.000�0.000�2LD�-0020�+0020�0005�02.0�02.0 \
  02񔄮5񔘛1�3.00�0.000�0.000�2LD�-0020�+0020�0005�02.0�02.0 \
  03񔄮5񔘛1�3.00�0.000�0.000�2LD�-0020�+0020�0005�02.0�02.0 \
  04񔄮5񔘛1�3.00�0.000�0.000�2LD�-0015�+0010�0002�01.0�02.0 \
  05񔄮5񔘛1�1.00�0.000�0.000�2LD�-0005�+0015�0005�06.0�02.0 \
  09񔄮5񔘛1�3.00�0.000�0.000�2LD�-0004�+0016�0005�06.0�02.0 \
  10񔄮5񔘛1�1.00�0.000�0.000�2LD�-0018�+0012�0005�01.5�05.0 \
  11񔄮5񔘛1�1.00�0.000�0.000�2LD�-0025�+0025�0005�02.0�01.0 \
  13񔄮5񔘛1�1.00�0.000�0.000�2LD�-0025�+0025�0005�20.0�03.0 \
  15񔄮5񔘛1�1.00�0.000�0.000�2LD�-0025�+0025�0005�40.0�04.0
TESTS_AVG2_OLDSTY_FUNCB := \
  06񔄮5񔘛1�1.00�0.000�0.000�2LD�-0005�+0015�0005�02.0�02.0 \
  07񔄮5񔘛1�1.00�0.000�0.000�2LD�-0003�+0017�0005�02.0�02.0 \
  08񔄮5񔘛1�8.00�0.000�0.000�2LD�-0020�+0020�0005�20.0�08.0 \
  12񔄮5񔘛1�1.00�0.000�0.000�2LD�-0025�+0025�0005�02.0�01.0 \
  14񔄮5񔘛1�1.00�0.000�0.000�2LD�-0025�+0025�0005�20.0�03.0 \
  16񔄮5񔘛1�1.00�0.000�0.000�2LD�-0025�+0025�0005�40.0�04.0 \
  17񔄮5񔘛1�1.00�0.000�0.000�2LD�-0003�+0017�0005�12.0�02.0 \
  18񔄮5񔘛1�1.00�0.000�0.000�2LD�-0020�+0020�0005�01.5�05.0 \
 
# 1-pixel sampled Z, 2-pixel sampled gradient,
# uses analytic gradient, with weights, no noise,
# averaging kernel width 4, old style recursion.
TESTS_AVG4_OLDSTY_FUNCA := \
  00񔄮5񔘛1�3.00�0.000�0.000�4LD�-0020�+0020�0005�02.0�02.0 \
  01񔄮5񔘛1�3.00�0.000�0.000�4LD�-0020�+0020�0005�02.0�02.0 \
  02񔄮5񔘛1�3.00�0.000�0.000�4LD�-0020�+0020�0005�02.0�02.0 \
  03񔄮5񔘛1�3.00�0.000�0.000�4LD�-0020�+0020�0005�02.0�02.0 \
  04񔄮5񔘛1�3.00�0.000�0.000�4LD�-0015�+0010�0002�01.0�02.0 \
  05񔄮5񔘛1�1.00�0.000�0.000�4LD�-0005�+0015�0005�06.0�02.0 \
  09񔄮5񔘛1�3.00�0.000�0.000�4LD�-0004�+0016�0005�06.0�02.0 \
  10񔄮5񔘛1�1.00�0.000�0.000�4LD�-0018�+0012�0005�01.5�05.0 \
  11񔄮5񔘛1�1.00�0.000�0.000�4LD�-0025�+0025�0005�02.0�01.0 \
  13񔄮5񔘛1�1.00�0.000�0.000�4LD�-0025�+0025�0005�20.0�03.0 \
  15񔄮5񔘛1�1.00�0.000�0.000�4LD�-0025�+0025�0005�40.0�04.0
TESTS_AVG4_OLDSTY_FUNCB := \
  06񔄮5񔘛1�1.00�0.000�0.000�4LD�-0005�+0015�0005�02.0�02.0 \
  07񔄮5񔘛1�1.00�0.000�0.000�4LD�-0003�+0017�0005�02.0�02.0 \
  08񔄮5񔘛1�8.00�0.000�0.000�4LD�-0020�+0020�0005�20.0�08.0 \
  12񔄮5񔘛1�1.00�0.000�0.000�4LD�-0025�+0025�0005�02.0�01.0 \
  14񔄮5񔘛1�1.00�0.000�0.000�4LD�-0025�+0025�0005�20.0�03.0 \
  16񔄮5񔘛1�1.00�0.000�0.000�4LD�-0025�+0025�0005�40.0�04.0 \
  17񔄮5񔘛1�1.00�0.000�0.000�4LD�-0003�+0017�0005�12.0�02.0 \
  18񔄮5񔘛1�1.00�0.000�0.000�4LD�-0020�+0020�0005�01.5�05.0 \
  
# 1-pixel sampled Z, 2-pixel sampled gradient,
# uses analytic gradient, with weights, no noise,
# averaging kernel width 2, new style recursion.
TESTS_AVG2_NEWSTY_FUNCA := \
  00񔄮5񔘛1�3.00�0.000�0.000�2EW�-0020�+0020�0005�02.0�02.0 \
  01񔄮5񔘛1�3.00�0.000�0.000�2EW�-0020�+0020�0005�02.0�02.0 \
  02񔄮5񔘛1�3.00�0.000�0.000�2EW�-0020�+0020�0005�02.0�02.0 \
  03񔄮5񔘛1�3.00�0.000�0.000�2EW�-0020�+0020�0005�02.0�02.0 \
  04񔄮5񔘛1�3.00�0.000�0.000�2EW�-0015�+0010�0002�01.0�02.0 \
  05񔄮5񔘛1�1.00�0.000�0.000�2EW�-0005�+0015�0005�06.0�02.0 \
  09񔄮5񔘛1�3.00�0.000�0.000�2EW�-0004�+0016�0005�06.0�02.0 \
  10񔄮5񔘛1�1.00�0.000�0.000�2EW�-0018�+0012�0005�01.5�05.0 \
  11񔄮5񔘛1�1.00�0.000�0.000�2EW�-0025�+0025�0005�02.0�01.0 \
  13񔄮5񔘛1�1.00�0.000�0.000�2EW�-0025�+0025�0005�20.0�03.0 \
  15񔄮5񔘛1�1.00�0.000�0.000�2EW�-0025�+0025�0005�40.0�04.0
TESTS_AVG2_NEWSTY_FUNCB := \
  06񔄮5񔘛1�1.00�0.000�0.000�2EW�-0005�+0015�0005�02.0�02.0 \
  07񔄮5񔘛1�1.00�0.000�0.000�2EW�-0003�+0017�0005�02.0�02.0 \
  08񔄮5񔘛1�8.00�0.000�0.000�2EW�-0020�+0020�0005�20.0�08.0 \
  12񔄮5񔘛1�1.00�0.000�0.000�2EW�-0025�+0025�0005�02.0�01.0 \
  14񔄮5񔘛1�1.00�0.000�0.000�2EW�-0025�+0025�0005�20.0�03.0 \
  16񔄮5񔘛1�1.00�0.000�0.000�2EW�-0025�+0025�0005�40.0�04.0 \
  17񔄮5񔘛1�1.00�0.000�0.000�2EW�-0003�+0017�0005�12.0�02.0 \
  18񔄮5񔘛1�1.00�0.000�0.000�2EW�-0020�+0020�0005�01.5�05.0 \

TESTS := \
  ${TESTS_AVG2_OLDSTY_FUNCA} \
  ${TESTS_AVG2_OLDSTY_FUNCB}
 
TESTS_DONE := \
  ${TESTS_AVG4_OLDSTY_FUNCA}\
  ${TESTS_AVG2_NEWSTY_FUNCA} \
  ${TESTS_AVG4_OLDSTY_FUNCB}\
  ${TESTS_AVG2_NEWSTY_FUNCB}

LATER_TESTS :=

# ----------------------------------------------------------------------
# PROGRAMS:

SHELL =	/bin/sh

# PSVIEW := ghostview
# PSVIEW := gv
PSVIEW := evince

FNI_VIEW := ${PROGDIR}/../fni_view/fni_view
FNI_TO_PNM := ${PROGDIR}/../fni_to_pnm/fni_to_pnm
FNI_PLOT := ${PROGDIR}/../fni_plot/fni_plot.sh

.PHONY:: \
  tidy \
  run-all-tests run-test \
  compute-height \
  view-height view-zerror delete-views \
  show-height show-zerror delete-shows \
  plot-height plot-slopes plot-weight plot-ref-height plot-zerror delete-plots

# all:
all: run-all-tests

# ====================================================================
# Cleanup

clean::
	-/bin/rm -f out/*.{sys,fni,pgm,eps,ppm}
        
# ======================================================================
# Delete secondary plot files:

tidy:
	-/bin/rm -f *.sys *-d-[0-9][0-9]-{Z,dZ}.fni
	-/bin/rm *.pgm *.eps *.ppm

# ====================================================================
# Running tests

run-all-tests: 
	mkdir -p out
	for t in ${TESTS} ; do \
          ${MAKE} TEST=$$t run-test ; \
        done

TEST := 
ifneq "/${TEST}" "/"
#######################################################################
# Recursive "make" to run the test ${TEST}

TESTFIELDS  := ${subst �, ,${TEST}}
FUNC           := ${word  1, ${TESTFIELDS}}
LZ             := ${word  2, ${TESTFIELDS}}
NZ             := ${word  3, ${TESTFIELDS}}
LG             := ${word  4, ${TESTFIELDS}}
NG             := ${word  5, ${TESTFIELDS}}
GRADTYPE       := ${word  6, ${TESTFIELDS}}
MAXGDIFF       := ${word  7, ${TESTFIELDS}}
SIGMAG         := ${word  8, ${TESTFIELDS}}
SIGMAW         := ${word  9, ${TESTFIELDS}}
WOPT           := ${word 10, ${TESTFIELDS}}
AVG_WD         := ${word 11, ${TESTFIELDS}}
STYLE          := ${word 12, ${TESTFIELDS}}
Z_MIN          := ${word 13, ${TESTFIELDS}}
Z_MAX          := ${word 14, ${TESTFIELDS}}
Z_STEP         := ${word 15, ${TESTFIELDS}}
G_MAX          := ${word 16, ${TESTFIELDS}}
ERR_MAX        := ${word 17, ${TESTFIELDS}}

RZ_MIN := ${Z_MIN}
RZ_MAX := ${Z_MAX}

IN_DIR := data
OUT_DIR := out

# Tags for input file names:
MAXGDIFF_TAG := ${subst .,,${MAXGDIFF}}
SIGMAG_TAG    := ${subst .,,${SIGMAG}}
SIGMAW_TAG    := ${subst .,,${SIGMAW}}

PARMS_TAG1 := ${LZ}-${NZ}-${LG}-${NG}-${GRADTYPE}
PARMS_TAG2 := ${MAXGDIFF_TAG}-${SIGMAG_TAG}-${SIGMAW_TAG}
PARMS_TAG_OUT := ${WOPT}-A${AVG_WD}-${STYLE}

IN_PREFIX := ${IN_DIR}/test-${FUNC}-${PARMS_TAG1}-${PARMS_TAG2}
OUT_PREFIX := ${OUT_DIR}/test-${FUNC}-${PARMS_TAG1}-${PARMS_TAG2}-${PARMS_TAG_OUT}

IN_RZ_FNI  := ${IN_PREFIX}-Z.fni
IN_G_FNI  := ${IN_PREFIX}-G.fni
IN_N_FNI := ${IN_PREFIX}-N.fni

IN_W_FNI := BUG
ifeq "/${WOPT}" "/W"
  # The test's weight map:
  IN_W_FNI  := ${IN_PREFIX}-W.fni
endif
ifeq "/${WOPT}" "/U"
  # A uniform weight map:
  IN_W_FNI  := ${IN_DIR}/test-00-1-05-2-11-A-300-0000-0000-W.fni
endif

# Computed FNI files:
OUT_Z_FNI := ${OUT_PREFIX}-Z.fni
OUT_EZ_FNI := ${OUT_PREFIX}-eZ.fni

# PGM versions of FNI files:
OUT_Z_PGM := ${OUT_PREFIX}-Z.pgm
OUT_RZ_PGM := ${OUT_PREFIX}-rZ.pgm
OUT_EZ_PGM := ${OUT_PREFIX}-eZ.pgm

# EPS plot files:
OUT_GX_EPS := ${OUT_PREFIX}-GX.eps
OUT_GY_EPS := ${OUT_PREFIX}-GY.eps
OUT_W_EPS  := ${OUT_PREFIX}-W.eps
OUT_Z_EPS  := ${OUT_PREFIX}-Z.eps
OUT_RZ_EPS := ${OUT_PREFIX}-rZ.eps
OUT_EZ_EPS := ${OUT_PREFIX}-eZ.eps

# Debugging files:

OUT_DEBUG_PREFIX := ${OUT_PREFIX}-d

DEBUG_Z_FNI := ${OUT_DEBUG_PREFIX}-00-Z.fni
DEBUG_Z_EPS := ${OUT_DEBUG_PREFIX}-00-Z.eps

ifeq "/${DEBUG}" "/YES"
  DEBUG_OPTS := -debugZ -debugSys -debugPrefix ${OUT_DEBUG_PREFIX}
else
  DEBUG_OPTS := 
endif

# Actions to perform:

ifeq "/${VIEW}" "/YES"
  VIEWACTIONS :=  delete-views view-height view-zerror
else
  VIEWACTIONS :=  delete-views
endif

ifeq "/${SHOW}" "/YES"
  SHOWACTIONS :=  delete-shows show-height show-zerror
else
  SHOWACTIONS :=  delete-shows
endif

ifeq "/${PLOT}" "/YES"
  PLOTACTIONS :=  delete-plots plot-slopes plot-weight plot-ref-height plot-height plot-zerror
else
  PLOTACTIONS :=  delete-plots
endif

# Program options:

STYLE_OPT := -BUG
ifeq "/${STYLE}" "/NEW"
  STYLE_OPT :=  -newStyle
endif
ifeq "/${STYLE}" "/OLD"
  STYLE_OPT :=  
endif

HARM_OPT :=  -BUG
ifeq "/${HARMONIC}" "/YES"
  HARM_OPT :=  -harmonicAvgW
endif
ifeq "/${HARMONIC}" "/NO"
  HARM_OPT := 
endif

run-test: compute-height ${VIEWACTIONS} ${SHOWACTIONS} ${PLOTACTIONS}

compute-height: ${PROGDIR}/${PROG} ${IN_G_FNI}
	@echo "TESTFIELDS = ${TESTFIELDS}"
	${PROGDIR}/${PROG} \
	    -avgWidth ${AVG_WD} \
            ${HARM_OPT} \
            ${STYLE_OPT} \
            -compareZ ${IN_RZ_FNI} ${OUT_EZ_FNI} \
            ${DEBUG_OPTS} \
          ${IN_G_FNI} \
          ${IN_W_FNI} \
          > ${OUT_Z_FNI}

# ----------------------------------------------------------------------
# Interactive 3D view of height map:
# Should also show reference map.

view-height: ${OUT_Z_FNI} ${IN_N_FNI} ${FNI_VIEW}
	${FNI_VIEW} \
            -channel 0 \
            -scale 1.0 \
            -texture ${IN_N_FNI} \
            ${OUT_Z_FNI}

view-zerror: ${OUT_EZ_FNI} ${FNI_VIEW}
	${FNI_VIEW} \
            -channel 0 \
	    ${OUT_EZ_FNI}

delete-views:

# ----------------------------------------------------------------------
# Show height map as PGM image:

show-height: ${OUT_Z_FNI} ${FNI_TO_PNM}
	${FNI_TO_PNM} \
            -channel 0 \
            -width 32.000 \
            < ${OUT_Z_FNI} \
            > ${OUT_Z_PGM}
	-display -title '%f' -filter box -resize '400%' ${OUT_Z_PGM}

show-zerror: ${OUT_EZ_fni} ${FNI_TO_PNM}
	${FNI_TO_PNM} \
            -channel 0 \
            < ${OUT_EZ_FNI} \
            > ${OUT_EZ_PGM}
	-display -title '%f' -filter box -resize '400%' ${OUT_EZ_PGM}

delete-shows:
	-/bin/rm -f ${OUT_Z_PGM} ${OUT_EZ_PGM}

# ----------------------------------------------------------------------
# 3D Postscript plot of height map:

plot-slopes: ${IN_G_FNI} ${FNI_PLOT}
	${FNI_PLOT} \
            -channel 0 -title "dZ/dX" \
            -range -${G_MAX} ${G_MAX} \
            < ${IN_G_FNI} \
            > ${OUT_GX_EPS} && \
          ${PSVIEW} ${OUT_GX_EPS}
	${FNI_PLOT} \
            -channel 1 -title "dZ/dY" \
            -range -${G_MAX} ${G_MAX} \
            < ${IN_G_FNI} \
            > ${OUT_GY_EPS} && \
          ${PSVIEW} ${OUT_GY_EPS}

plot-weight: ${IN_W_FNI} ${FNI_PLOT}
	${FNI_PLOT} \
            -channel 0 -title "W" \
            -range -0.1 2.1 \
            -ztics 0.5 \
            < ${IN_W_FNI} \
            > ${OUT_W_EPS} && \
          ${PSVIEW} ${OUT_W_EPS}

plot-height: ${OUT_Z_FNI}
	${FNI_PLOT} \
            -channel 0 \
            -title "Z(X,Y)" \
            -range ${Z_MIN} ${Z_MAX} \
            -ztics ${Z_STEP} \
            < ${OUT_Z_FNI} \
            > ${OUT_Z_EPS} && \
          ${PSVIEW} ${OUT_Z_EPS}

plot-ref-height: ${OUT_RZ_FNI}
	${FNI_PLOT} \
            -channel 0 \
            -title "Z*(X,Y)" \
            -range ${RZ_MIN} ${RZ_MAX} \
            -ztics ${Z_STEP} \
            < ${IN_RZ_FNI} \
            > ${OUT_RZ_EPS} && \
          ${PSVIEW} ${OUT_RZ_EPS}

plot-zerror: ${OUT_EZ_fni}
	${FNI_PLOT} \
            -channel 0 -title "eZ" \
            -range -${ERR_MAX} +${ERR_MAX} \
            < ${OUT_EZ_FNI} \
            > ${OUT_EZ_EPS} && \
          ${PSVIEW} ${OUT_EZ_EPS}

delete-plots:
	-/bin/rm -f ${OUT_PREFIX}-*.eps}

# 
# End make ${TEST}
######################################################################
endif
