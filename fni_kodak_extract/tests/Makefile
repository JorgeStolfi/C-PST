# Last edited on 2023-02-04 07:02:07 by stolfi

PROG := fni_kodak_extract

PROGDIR := ..

include ${STOLFIHOME}/programs/c/GENERIC-PROGS-TEST.make

VIEW := NO
SHOW := YES
PLOT := YES

# DIR:SCALE:YFLIP

TESTS := \
  mixed-a-1:1.000:N \
  sonyh-a-6:1.000:N

ALL_TESTS := \
  balls-b-0:1.000:N \
  fragm-a-1:1.000:N \
  sonyh-a-6:1.000:N

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
TESTDIR     := ${word 1,${TESTFIELDS}}
SCALE       := ${word 2,${TESTFIELDS}}
YFLIP       := ${word 3,${TESTFIELDS}}

# Construct the file names for this test:

IMGNAME := img

IN_DIR := data/${TESTDIR}
IN_PREFIX  := ${IN_DIR}/${IMGNAME}

IN_PNG := ${IN_PREFIX}-r.png
IN_FNI := ${TMP_PREFIX}-r.fni
IN_EPS := ${IN_PREFIX}-r.eps

IN_CORNERS := ${IN_PREFIX}-chart.corners

OUT_DIR := out/${TESTDIR}
OUT_PREFIX := ${OUT_DIR}/${IMGNAME}

OUT_CHART_FNI := ${TMP_PREFIX}-chart.fni
OUT_CHART_PNG := ${OUT_PREFIX}-chart.png
OUT_CHART_EPS := ${OUT_PREFIX}-chart.eps

OUT_GRAY_SCALE_FNI := ${TMP_PREFIX}-gray-scale.fni
OUT_GRAY_SCALE_PNG := ${OUT_PREFIX}-gray-scale.png
OUT_GRAY_SCALE_EPS := ${OUT_PREFIX}-gray-scale.eps

OUT_BODY_STRIP_FNI := ${TMP_PREFIX}-body-strip.fni
OUT_BODY_STRIP_PNG := ${OUT_PREFIX}-body-strip.png
OUT_BODY_STRIP_EPS := ${OUT_PREFIX}-body-strip.eps

OUT_FRAME_STRIP_FNI := ${TMP_PREFIX}-frame-strip.fni
OUT_FRAME_STRIP_PNG := ${OUT_PREFIX}-frame-strip.png
OUT_FRAME_STRIP_EPS := ${OUT_PREFIX}-frame-strip.eps

OUT_LOG_SCALE_RATIO_FNI := ${TMP_PREFIX}-log-ratio.fni
OUT_LOG_SCALE_RATIO_PNG := ${OUT_PREFIX}-log-ratio.png
OUT_LOG_SCALE_RATIO_EPS := ${OUT_PREFIX}-log-ratio.eps

# Expand the ${TESTARGS} fields into comand line switches:

YFLIP_OPT  := ${subst Y,-yFlip, ${subst N,,${YFLIP}}}

CORNERS := ${shell cat ${IN_CORNERS} | sed -e 's/[\#].*$$//' }

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

do-extract: ${OUT_GRAY_SCALE_FNI}

${OUT_GRAY_SCALE_FNI}: ${PROGDIR}/${PROG} ${IN_FNI}
	@echo "TESTFIELDS = ${TESTFIELDS}"
	mkdir -p ${OUT_DIR}
	${PROGDIR}/${PROG} \
          -corners ${CORNERS} \
          -scale ${SCALE} \
          ${YFLIP_OPT} \
          -grayScaleName ${OUT_GRAY_SCALE_FNI} \
          -bodyStripName ${OUT_BODY_STRIP_FNI} \
          -frameStripName ${OUT_FRAME_STRIP_FNI} \
          < ${IN_FNI} \
          > ${OUT_CHART_FNI}

# ----------------------------------------------------------------------
# Interactive 3D view of images:

do-view: ${OUT_CHART_FNI} ${OUT_DIF_FNI}
	fni_view -scale 50 ${IN_FNI}
	fni_view -scale 50 ${OUT_CHART_FNI}
	fni_view -scale 50  ${OUT_GRAY_SCALE_FNI}
	fni_view -scale 50  ${OUT_BODY_STRIP_FNI}
	fni_view -scale 50  ${OUT_FRAME_STRIP_FNI}

clean-view:

# ----------------------------------------------------------------------
# Show synthetic images and difference image as a PNG file:

PNG_SHOW_ALL :=  \
  ${IN_PNG} \
  ${OUT_CHART_PNG} \
  ${OUT_GRAY_SCALE_PNG} \
  ${OUT_BODY_STRIP_PNG} \
  ${OUT_FRAME_STRIP_PNG}

do-show: ${PNG_SHOW_ALL}
	display -title '%f' ${PNG_SHOW_ALL}

${OUT_CHART_PNG}: ${OUT_CHART_FNI}
	fni_to_pnm \
            -channels 0 1 2 \
            -min 0.00 -max 1.00 \
            < ${OUT_CHART_FNI} \
          | convert PPM:- PNG:- \
          > ${OUT_CHART_PNG}

${OUT_BODY_STRIP_PNG}: ${OUT_BODY_STRIP_FNI}
	fni_to_pnm \
            -channels 0 1 2 \
            -min 0.00 -max 1.00 \
            < ${OUT_BODY_STRIP_FNI} \
          | convert PPM:- PNG:- \
          > ${OUT_BODY_STRIP_PNG}

${OUT_FRAME_STRIP_PNG}: ${OUT_FRAME_STRIP_FNI}
	fni_to_pnm \
            -channels 0 1 2 \
            -min 0.00 -max 1.00 \
            < ${OUT_FRAME_STRIP_FNI} \
          | convert PPM:- PNG:- \
          > ${OUT_FRAME_STRIP_PNG}

${OUT_GRAY_SCALE_PNG}: ${OUT_GRAY_SCALE_FNI}
	fni_to_pnm \
            -channels 0 1 2 \
            -min 0.00 -max 1.00 \
            < ${OUT_GRAY_SCALE_FNI} \
          | convert PPM:- PNG:- \
          > ${OUT_GRAY_SCALE_PNG}

clean-show:
	/bin/rm -f 

# ----------------------------------------------------------------------
# Plot values from chart strips:
        
EPS_PLOT_ALL := \
  ${OUT_GRAY_SCALE_EPS} \
  ${OUT_BODY_STRIP_EPS} \
  ${OUT_FRAME_STRIP_EPS} \
  ${OUT_LOG_SCALE_RATIO_EPS}

do-plot: ${EPS_PLOT_ALL}
	${PSVIEW} ${OUT_GRAY_SCALE_EPS}
	${PSVIEW} ${OUT_BODY_STRIP_EPS}
	${PSVIEW} ${OUT_FRAME_STRIP_EPS}
	${PSVIEW} ${OUT_LOG_SCALE_RATIO_EPS}
        
${OUT_GRAY_SCALE_EPS}: ${OUT_GRAY_SCALE_FNI}
	fni_plot.sh \
            -channel 0 \
            -rows -kodak \
            -title "${TESTDIR} - Kodak Q-13 Gray Scale" \
            < ${OUT_GRAY_SCALE_FNI} \
            > ${OUT_GRAY_SCALE_EPS}
        
${OUT_BODY_STRIP_EPS}: ${OUT_BODY_STRIP_FNI}
	fni_plot.sh \
            -channel 0 \
            -rows -kodak \
            -title "${TESTDIR} - Kodak Q-13 Chart Gray Strip" \
            < ${OUT_BODY_STRIP_FNI} \
            > ${OUT_BODY_STRIP_EPS}
        
${OUT_FRAME_STRIP_EPS}: ${OUT_FRAME_STRIP_FNI}
	fni_plot.sh \
            -channel 0 \
            -rows -kodak \
            -title "${TESTDIR} - Background Strip" \
            < ${OUT_FRAME_STRIP_FNI} \
            > ${OUT_FRAME_STRIP_EPS}
        
${OUT_LOG_SCALE_RATIO_EPS}: ${OUT_GRAY_SCALE_FNI} ${OUT_BODY_STRIP_FNI}
	fni_log_ratio \
            ${OUT_GRAY_SCALE_FNI} \
            ${OUT_BODY_STRIP_FNI} \
            > ${OUT_LOG_SCALE_RATIO_FNI}
	fni_plot.sh \
            -channel 0 \
            -rows -kodakLog \
            -title "${TESTDIR} - Kodak Q-13 Log Scale/Strip Ratio" \
            -range -5.0 +2.0 \
            < ${OUT_LOG_SCALE_RATIO_FNI} \
            > ${OUT_LOG_SCALE_RATIO_EPS}

clean-plot:
	/bin/rm -f ${EPS_PLOT_ALL}

# 
# End make ${TESTARGS}
######################################################################
endif
