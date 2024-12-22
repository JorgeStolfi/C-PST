# Last edited on 2023-02-04 07:01:21 by stolfi

PROG := slope_to_height

PROGDIR := ..

include ${STOLFIHOME}/programs/c/GENERIC-PROGS-TEST.make

VIEW := NO
PLOT := YES
SHOW := YES
DEBUG := YES

# Harmonic averaging of weights:
HARMONIC := YES

# Height function to use
FUNC := 09

# Sampling parameters:
LZ := 1
NZ := 05
LG := 2
NG := 11

# Type of gradient ("N" numeric, "A" analytic):
GRADTYPE       := A

# Gradient difference threshold for weight mask:
MAXGDIFF := 3.00

# Noise deviations:
SIGMAG  := 0.000
SIGMAW  := 0.000

# Weight map to use ("W" givem "U" uniform):
WOPT    := U

# Ranges for gnuplots:
Z_MIN   := -3.0
Z_MAX   := +17.0
Z_STEP  := 5.0
G_MAX   := 6.0
ERR_MAX := 2.0
  

# ----------------------------------------------------------------------
# PROGRAMS:

SHELL =	/bin/sh

# PSVIEW := ghostview
# PSVIEW := gv
PSVIEW := evince

FNI_VIEW := ../../fni_view/fni_view
FNI_TO_PNM := ../../fni_to_pnm/fni_to_pnm
FNI_PLOT := ../../fni_plot/fni_plot.sh

.PHONY:: \
  tidy \
  run-test \
  compute-height \
  view-height view-zerror delete-views \
  show-height show-zerror delete-shows \
  plot-height plot-slopes plot-weight plot-ref-height plot-zerror delete-plots

# all:
all: run-test

# ====================================================================
# Cleanup

clean::
	-/bin/rm -f out/*.{sys,fni,pgm,eps,ppm}
        
# ======================================================================
# Delete secondary plot files:

tidy:
	-/bin/rm -f *.sys *-d-[0-9][0-9]-{Z,dZ}.fni
	-/bin/rm *.pgm *.eps *.ppm

# ======================================================================
# Run the test:

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

IN_PREFIX := ${IN_DIR}/test-${FUNC}-${PARMS_TAG1}-${PARMS_TAG2}
OUT_PREFIX := ${OUT_DIR}/test-${FUNC}-${PARMS_TAG1}-${PARMS_TAG2}-${WOPT}

IN_RZ_FNI  := ${IN_PREFIX}-Z.fni
IN_G_FNI  := ${IN_PREFIX}-G.fni
IN_N_FNI := ${IN_PREFIX}-N.fni

IN_W_FNI := BUG
ifeq "/${WOPT}" "/W"
  # Te test's weight map:
  IN_W_FNI  := ${IN_PREFIX}-W.fni
endif
ifeq "/${WOPT}" "/U"
  # A uniform weight map:
  IN_W_FNI  := ${IN_DIR}/test-00-0-01-1-05-A-300-0000-0000-W.fni
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
OUT_Z_EPS := ${OUT_PREFIX}-Z.eps
OUT_RZ_EPS := ${OUT_PREFIX}-rZ.eps
OUT_EZ_EPS := ${OUT_PREFIX}-eZ.eps

# Debugging files:

OUT_DEBUG_PREFIX := ${OUT_PREFIX}-d

DEBUG_Z_FNI := ${OUT_DEBUG_PREFIX}-00-Z.fni
DEBUG_Z_EPS := ${OUT_DEBUG_PREFIX}-00-Z.eps

ifeq "/${DEBUG}" "/YES"
  DEBUG_OPTS := -debugSys
else
  DEBUG_OPTS := 
endif

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

ifeq "/${HARMONIC}" "/YES"
  HARM_OPT :=  -harmonicAvgW
else
  HARM_OPT := 
endif

run-test: compute-height ${VIEWACTIONS} ${SHOWACTIONS} ${PLOTACTIONS}

compute-height: ${PROGDIR}/${PROG} ${IN_G_FNI}
	@echo "TESTFIELDS = ${TESTFIELDS}"
	${PROGDIR}/${PROG} \
            ${HARM_OPT} \
            -compareZ ${IN_RZ_FNI} ${OUT_EZ_FNI} \
            -debugDZ -debugZ ${DEBUG_OPTS} -debugPrefix ${OUT_DEBUG_PREFIX} \
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
