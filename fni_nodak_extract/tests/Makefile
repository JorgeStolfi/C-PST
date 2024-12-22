# Last edited on 2023-02-04 07:01:54 by stolfi

PROG := fni_nodak_extract

PROGDIR := ..

include ${STOLFIHOME}/programs/c/GENERIC-PROGS-TEST.make

VIEW := NO
SHOW := YES
PLOT := YES

# IMAGE:CHART:SCALE

TESTS := \
  f-00:0:1.000 \
  f-00:1:1.000

ALL_TESTS := \
  f-00:0:1.000 \
  f-00:1:1.000

SHELL =	/bin/sh

.PHONY:: \
  tidy \
  run-all-tests run-test \
  clean-all-tests clean-test \
  tidy-all-tests tidy-test \
  do-extract \
  do-view clean-view \
  do-show clean-show \
  do-plot clean-plot
  
TMP_PREFIX := /tmp/fke

# all:
all: run-all-tests

# ====================================================================
# Cleanup

clean:: clean-all-tests

clean-all-tests:
	for t in ${TESTS} ; do \
          ${MAKE} TMP_PREFIX=${TMP_PREFIX} TESTARGS=$$t clean-test ; \
        done
        
# ======================================================================
# Delete secondary plot files:

tidy-all-tests:
	for t in ${TESTS} ; do \
          ${MAKE} TMP_PREFIX=${TMP_PREFIX} TESTARGS=$$t tidy-test ; \
        done

# ====================================================================
# Running tests:
# Redefine ${ACTIONS} to perform selected actions.

ACTIONS := run-test

run-all-tests: 
	for t in ${TESTS} ; do \
          ${MAKE} TMP_PREFIX=${TMP_PREFIX} TESTARGS=$$t ${ACTIONS} ; \
        done

TESTARGS := TESTARGS.IS.UNDEFINED
ifneq "/${TESTARGS}" "/TESTARGS.IS.UNDEFINED"
#######################################################################
# Recursive "make" to run the test ${TESTARGS}

TESTFIELDS  := ${subst  :, ,${TESTARGS}}
TESTIMG     := ${word 1,${TESTFIELDS}}
CHART       := ${word 2,${TESTFIELDS}}
SCALE       := ${word 3,${TESTFIELDS}}

# Construct the file names for this test:

IMGNAME := img

IN_PREFIX  := data/${TESTIMG}

IN_PNG := ${IN_PREFIX}.png
IN_FNI := ${TMP_PREFIX}.fni
IN_EPS := ${IN_PREFIX}.eps

IN_SPOTS := ${IN_PREFIX}-${CHART}.spots

IN_GEOM := ${IN_PREFIX}-${CHART}.geom

OUT_PREFIX := out/${TESTIMG}-${CHART}-out

OUT_CHART_FNI := ${TMP_PREFIX}-chart.fni
OUT_CHART_PNG := ${OUT_PREFIX}-chart.png
OUT_CHART_EPS := ${OUT_PREFIX}-chart.eps

OUT_SCALE_ARG := ${TMP_PREFIX}-scale
OUT_SCALE_FNI := ${OUT_SCALE_ARG}.fni
OUT_SCALE_TXT := ${OUT_PREFIX}.txt
OUT_SCALE_PNG := ${OUT_PREFIX}-scale.png
OUT_SCALE_EPS := ${OUT_PREFIX}-scale.eps

SPOT_OPS := ${shell cat ${IN_SPOTS} | sed -e 's/[\#].*$$//' }

# PSVIEW := ghostview
PSVIEW := evince

# Expand ${VIEW}, ${SHOW}, ${PLOT} into make actions:

ifeq "/${VIEW}" "/YES"
  VIEW_ACTIONS :=  clean-view do-view
else
  VIEW_ACTIONS :=  clean-view
endif

ifeq "/${SHOW}" "/YES"
  SHOW_ACTIONS :=  clean-show do-show
else
  SHOW_ACTIONS :=  clean-show
endif

ifeq "/${PLOT}" "/YES"
  PLOT_ACTIONS :=  clean-plot do-plot
else
  PLOT_ACTIONS :=  clean-plot
endif

run-test: \
          clean-test \
          do-extract \
          ${VIEW_ACTIONS} \
          ${SHOW_ACTIONS} \
          ${PLOT_ACTIONS}

clean-test: 
	/bin/rm -f ${OUT_PREFIX}-*.{eps,fni,png} ${TMP_PREFIX}-*.{eps,fni,png}

tidy-test: 
	/bin/rm -f ${OUT_PREFIX}-*.{eps,fni,png} ${TMP_PREFIX}-*.{eps,fni,png}

# ----------------------------------------------------------------------
# Fitting the color map

${IN_FNI}: ${IN_PNG}
	convert ${IN_PNG} PPM:- \
          | pnm_to_fni -min 0 -max 1 \
          > ${IN_FNI}

do-extract: ${OUT_CHART_FNI} ${OUT_SCALE_FNI} ${OUT_SCALE_TXT}

${OUT_CHART_FNI}: ${PROGDIR}/${PROG} ${IN_FNI}
	@echo "TESTFIELDS = ${TESTFIELDS}"
	${PROGDIR}/${PROG} \
          -geomFile ${IN_GEOM} \
          -chartBorder 2.0 \
	  -yFlip \
          ${SPOT_OPS} \
          -scale ${SCALE} \
          -outChartSize 320 \
          -outScale ${OUT_SCALE_ARG} 30 30 \
          -spotMargin 1 \
          < ${IN_FNI} \
          > ${OUT_CHART_FNI}

${OUT_SCALE_FNI}: ${OUT_CHART_FNI}
	@echo "should have created ${OUT_SCALE_FNI} too"

${OUT_SCALE_TXT}: ${OUT_CHART_FNI}
	@echo "should have created ${OUT_SCALE_TXT} too"
	mv -v ${OUT_SCALE_ARG}.txt ${OUT_SCALE_TXT}
        
# ----------------------------------------------------------------------
# Interactive 3D view of images:

do-view: ${OUT_CHART_FNI} ${OUT_DIF_FNI}
	fni_view -scale 50 ${IN_FNI}
	fni_view -scale 50 ${OUT_CHART_FNI}
	fni_view -scale 50 ${OUT_SCALE_FNI}

clean-view:

# ----------------------------------------------------------------------
# Show synthetic images and difference image as a PNG file:

PNG_SHOW_ALL :=  \
  ${IN_PNG} \
  ${OUT_CHART_PNG} \
  ${OUT_SCALE_PNG}

do-show: ${PNG_SHOW_ALL}
	display -title '%f' ${PNG_SHOW_ALL}

${OUT_CHART_PNG}: ${OUT_CHART_FNI}
	fni_to_pnm \
            -channels 0 1 2 \
            -min 0.00 -max 1.00 \
            < ${OUT_CHART_FNI} \
          | convert PPM:- PNG:- \
          > ${OUT_CHART_PNG}

${OUT_SCALE_PNG}: ${OUT_SCALE_FNI}
	fni_to_pnm \
            -channels 0 1 2 \
            -min 0.00 -max 1.00 \
            < ${OUT_SCALE_FNI} \
          | convert PPM:- PNG:- \
          > ${OUT_SCALE_PNG}

clean-show:
	/bin/rm -f 

# ----------------------------------------------------------------------
# Plot values from chart strips:
        
EPS_PLOT_ALL := \
  ${OUT_SCALE_EPS}

do-plot: ${EPS_PLOT_ALL}
	${PSVIEW} ${OUT_SCALE_EPS}
        
${OUT_SCALE_EPS}: ${OUT_SCALE_FNI}
	fni_plot.sh \
            -channel 0 \
            -rows -kodak \
            -title "${TESTIMG} - N-Spot Chart" \
            < ${OUT_SCALE_FNI} \
            > ${OUT_SCALE_EPS}

clean-plot:
	/bin/rm -f ${EPS_PLOT_ALL}

# 
# End make ${TESTARGS}
######################################################################
endif
