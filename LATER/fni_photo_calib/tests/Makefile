# Last edited on 2023-02-04 07:02:23 by stolfi

PROG := fni_kodak_adjust

PROGDIR := ..

include ${STOLFIHOME}/programs/c/GENERIC-PROGS-TEST.make

VIEW := NO
SHOW := YES
PLOT_TAB := YES
PLOT_STR := YES
PLOT_BAS := NO

# DIR:BTYPE:NTERMS:MONOT:USEGRAY:USEWHITE:USESELF

TESTS := \
  synth/mixed-a-1:A:07:0:N:Y:N \
  synth/mixed-a-1:A:07:0:N:N:Y \
  synth/mixed-a-1:A:07:0:Y:N:N

ALL_TESTS := \
  synth/mixed-a-1:A:03:1:Y:Y:Y \
  synth/mixed-a-1:B:04:1:Y:Y:Y \
   \
  synth/mixed-a-1:A:15:1:Y:Y:Y \
  synth/mixed-a-1:A:15:0:Y:Y:Y \
  synth/mixed-a-1:B:15:1:Y:Y:Y \
  synth/mixed-a-1:B:15:0:Y:Y:Y \
  synth/mixed-a-2:A:15:0:Y:Y:Y \
  synth/mixed-a-1:A:15:1:Y:Y:Y \
  synth/mixed-a-2:A:15:1:Y:Y:Y \
   \
  photo/balls-b-0:A:15:1:Y:N:Y \
  photo/fragm-a-1:A:15:1:Y:N:Y
  

SHELL =	/bin/sh

.PHONY:: \
  tidy \
  run-all-tests run-test \
  clean-all-tests clean-test \
  tidy-all-tests tidy-test \
  fit-kodak \
  do-view clean-view \
  do-show clean-show \
  do-plot-tab clean-plot-tab \
  do-plot-str clean-plot-str \
  do-plot-bas clean-plot-bas

# all:
all: run-all-tests

# ====================================================================
# Cleanup

clean:: clean-all-tests

clean-all-tests:
	for t in ${TESTS} ; do \
          ${MAKE} TESTARGS=$$t clean-test ; \
        done
        
# ======================================================================
# Delete secondary plot files:

tidy-all-tests:
	for t in ${TESTS} ; do \
          ${MAKE} TESTARGS=$$t tidy-test ; \
        done

# ====================================================================
# Running tests

run-all-tests: 
	for t in ${TESTS} ; do \
          ${MAKE} TESTARGS=$$t run-test ; \
        done

TESTARGS := TESTARGS.IS.UNDEFINED
ifneq "/${TESTARGS}" "/TESTARGS.IS.UNDEFINED"
#######################################################################
# Recursive "make" to run the test ${TESTARGS}

TESTFIELDS  := ${subst  :, ,${TESTARGS}}
TESTDIR     := ${word 1,${TESTFIELDS}}
BTYPE       := ${word 2,${TESTFIELDS}}
NTERMS      := ${word 3,${TESTFIELDS}}
MONOT   := ${word 4,${TESTFIELDS}}
UGRAY       := ${word 5,${TESTFIELDS}}
UWHITE      := ${word 6,${TESTFIELDS}}
USELF       := ${word 7,${TESTFIELDS}}

# Construct the file names for this test:

IMGNAME := img

IN_DIR := ${TESTDIR}
IN_PREFIX  := ${IN_DIR}/${IMGNAME}

IN_FNI := ${IN_PREFIX}-r.fni
IN_PNG := ${IN_PREFIX}-r.png
IN_EPS := ${IN_PREFIX}-r.eps

IN_CORNERS := ${IN_PREFIX}-chart.corners

OUT_DIR := out/${TESTDIR}
OUT_PREFIX := ${OUT_DIR}/${IMGNAME}-${UGRAY}${UWHITE}${USELF}-${BTYPE}-${NTERMS}-${MONOT}

OUT_ADJ_FNI := ${OUT_PREFIX}-adj.fni
OUT_ADJ_PNG := ${OUT_PREFIX}-adj.png
OUT_ADJ_EPS := ${OUT_PREFIX}-adj.eps

OUT_RAW_CHART_FNI := ${OUT_PREFIX}-chart-raw.fni
OUT_RAW_CHART_PNG := ${OUT_PREFIX}-chart-raw.png
OUT_RAW_CHART_EPS := ${OUT_PREFIX}-chart-raw.eps

OUT_ADJ_CHART_FNI := ${OUT_PREFIX}-chart-adj.fni
OUT_ADJ_CHART_PNG := ${OUT_PREFIX}-chart-adj.png
OUT_ADJ_CHART_EPS := ${OUT_PREFIX}-chart-adj.eps

OUT_RAW_STRIP_FNI := ${OUT_PREFIX}-strip-raw.fni
OUT_RAW_STRIP_PNG := ${OUT_PREFIX}-strip-raw.png
OUT_RAW_STRIP_EPS := ${OUT_PREFIX}-strip-raw.eps

OUT_ADJ_STRIP_FNI := ${OUT_PREFIX}-strip-adj.fni
OUT_ADJ_STRIP_PNG := ${OUT_PREFIX}-strip-adj.png
OUT_ADJ_STRIP_EPS := ${OUT_PREFIX}-strip-adj.eps

OUT_VAL_TABLE_TBL := ${OUT_PREFIX}-val-tbl.fni
OUT_VAL_TABLE_EPS := ${OUT_PREFIX}-val-tbl.eps

OUT_LOG_TABLE_TBL := ${OUT_PREFIX}-log-tbl.fni
OUT_LOG_TABLE_EPS := ${OUT_PREFIX}-log-tbl.eps

OUT_BASIS_TBL := ${OUT_PREFIX}-basis.fni
IXMDLAST := ${shell echo "${NTERMS}-4" | bc -lq | printf "%02d" `cat`}
IXFIN2 := ${shell echo "${NTERMS}-3" | bc -lq | printf "%02d" `cat`}
IXFIN1 := ${shell echo "${NTERMS}-2" | bc -lq | printf "%02d" `cat`}
IXFIN0 := ${shell echo "${NTERMS}-1" | bc -lq | printf "%02d" `cat`}

OUT_BASIS_I0_EPS := ${OUT_PREFIX}-00-00-basis.eps
OUT_BASIS_I1_EPS := ${OUT_PREFIX}-01-01-basis.eps
OUT_BASIS_I2_EPS := ${OUT_PREFIX}-02-02-basis.eps
OUT_BASIS_MD_EPS := ${OUT_PREFIX}-03-${IXMDLAST}-basis.eps
OUT_BASIS_F2_EPS := ${OUT_PREFIX}-${IXFIN2}-${IXFIN2}-basis.eps
OUT_BASIS_F1_EPS := ${OUT_PREFIX}-${IXFIN1}-${IXFIN1}-basis.eps
OUT_BASIS_F0_EPS := ${OUT_PREFIX}-${IXFIN0}-${IXFIN0}-basis.eps

# Expand the ${TESTARGS} fields into comand line switches:

USEGRAY  := ${subst Y,-useGray, ${subst N,,${UGRAY}}}
USEWHITE := ${subst Y,-useWhite,${subst N,,${UWHITE}}}
USESELF  := ${subst Y,-useSelf, ${subst N,,${USELF}}}

MONOTONIC := ${subst 0, ,${subst 1,-monotonic,${MONOT}}}

CORNERS := ${shell cat ${IN_CORNERS} | sed -e 's/[\#].*$$//' }

# PSVIEW := ghostview
PSVIEW := evince

# Expand ${VIEW}, ${SHOW}, ${PLOT_TAB}, ${PLOT_BAS}, ${PLOT_STR} into make actions:

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

ifeq "/${PLOT_TAB}" "/YES"
  PLOT_TAB_ACTIONS :=  clean-plot-tab do-plot-tab
else
  PLOT_TAB_ACTIONS :=  clean-plot-tab
endif

ifeq "/${PLOT_STR}" "/YES"
  PLOT_STR_ACTIONS :=  clean-plot-str do-plot-str
else
  PLOT_STR_ACTIONS :=  clean-plot-str
endif

ifeq "/${PLOT_BAS}" "/YES"
  PLOT_BAS_ACTIONS :=  clean-plot-bas do-plot-bas
else
  PLOT_BAS_ACTIONS :=  clean-plot-bas
endif

run-test: \
          clean-test \
          fit-kodak \
          ${VIEW_ACTIONS} \
          ${SHOW_ACTIONS} \
          ${PLOT_TAB_ACTIONS} \
          ${PLOT_STR_ACTIONS} \
          ${PLOT_BAS_ACTIONS}

clean-test: 
	/bin/rm -f ${OUT_PREFIX}-*.{eps,fni,png}

tidy-test: 
	/bin/rm -f ${OUT_PREFIX}-*.{eps,fni,png}

# ----------------------------------------------------------------------
# Fitting the color map

${IN_FNI}: ${IN_PNG}
	convert ${IN_PNG} PPM:- \
          | pnm_to_fni -min 0 -max 1 \
          > ${IN_FNI}

fit-kodak: ${PROGDIR}/${PROG} ${IN_FNI}
	@echo "TESTFIELDS = ${TESTFIELDS}"
	mkdir -p ${OUT_DIR}
	${PROGDIR}/${PROG} \
          -corners ${CORNERS} \
          -basis ${BTYPE} ${NTERMS} ${MONOTONIC} \
          ${USEGRAY} ${USEWHITE} ${USESELF} \
          -writeChart ${OUT_RAW_CHART_FNI} ${OUT_ADJ_CHART_FNI} \
          -writeStrip ${OUT_RAW_STRIP_FNI} ${OUT_ADJ_STRIP_FNI} \
          -writeTable ${OUT_VAL_TABLE_TBL} ${OUT_LOG_TABLE_TBL} \
          -writeBasis ${OUT_BASIS_TBL} \
          < ${IN_FNI} \
          > ${OUT_ADJ_FNI}

# `cat ${IN_PARMS} | egrep -v '^[ ]*([\#]|$$)'` \

# ----------------------------------------------------------------------
# Interactive 3D view of images:

do-view: ${OUT_LIGHT_PARMS} ${OUT_ADJ_FNI} ${OUT_DIF_FNI}
	fni_view -scale 50 ${IN_FNI}
	fni_view -scale 50 ${OUT_ADJ_FNI}
	fni_view -scale 50  ${OUT_ADJ_CHART_FNI}
	fni_view -scale 50  ${OUT_ADJ_STRIP_FNI}

clean-view:

# ----------------------------------------------------------------------
# Show synthetic images and difference image as a PNG file:

do-show: \
            ${IN_PNG} ${OUT_ADJ_PNG} \
            ${OUT_RAW_CHART_PNG} ${OUT_ADJ_CHART_PNG} \
            ${OUT_RAW_STRIP_PNG} ${OUT_ADJ_STRIP_PNG}
	display -title '%f' \
          ${IN_PNG} ${OUT_ADJ_PNG} \
          ${OUT_RAW_CHART_PNG} ${OUT_ADJ_CHART_PNG} \
            ${OUT_RAW_STRIP_PNG} ${OUT_ADJ_STRIP_PNG}

${OUT_ADJ_PNG}: ${OUT_ADJ_FNI}
	fni_to_pnm \
            -channels 0 1 2 \
            -min 0.00 -max 1.00 \
            < ${OUT_ADJ_FNI} \
          | convert PPM:- PNG:- \
          > ${OUT_ADJ_PNG}

${OUT_RAW_CHART_PNG}: ${OUT_RAW_CHART_FNI}
	fni_to_pnm \
            -channels 0 1 2 \
            -min 0.00 -max 1.00 \
            < ${OUT_RAW_CHART_FNI} \
          | convert PPM:- PNG:- \
          > ${OUT_RAW_CHART_PNG}

${OUT_ADJ_CHART_PNG}: ${OUT_ADJ_CHART_FNI}
	fni_to_pnm \
            -channels 0 1 2 \
            -min 0.00 -max 1.00 \
            < ${OUT_ADJ_CHART_FNI} \
          | convert PPM:- PNG:- \
          > ${OUT_ADJ_CHART_PNG}

${OUT_RAW_STRIP_PNG}: ${OUT_RAW_STRIP_FNI}
	fni_to_pnm \
            -channels 0 1 2 \
            -min 0.00 -max 1.00 \
            < ${OUT_RAW_STRIP_FNI} \
          | convert PPM:- PNG:- \
          > ${OUT_RAW_STRIP_PNG}

${OUT_ADJ_STRIP_PNG}: ${OUT_ADJ_STRIP_FNI}
	fni_to_pnm \
            -channels 0 1 2 \
            -min 0.00 -max 1.00 \
            < ${OUT_ADJ_STRIP_FNI} \
          | convert PPM:- PNG:- \
          > ${OUT_ADJ_STRIP_PNG}

clean-show:
	/bin/rm -f 

# ----------------------------------------------------------------------
# Plot photometric correction table

OUT_TABLE_ALL_EPS := ${OUT_VAL_TABLE_EPS} ${OUT_LOG_TABLE_EPS}

do-plot-tab: ${OUT_TABLE_ALL_EPS}
	${PSVIEW} ${OUT_VAL_TABLE_EPS}
	${PSVIEW} ${OUT_LOG_TABLE_EPS}
        
${OUT_VAL_TABLE_EPS}: ${OUT_VAL_TABLE_TBL}
	table_plot.sh \
            -title "${TESTDIR} - Photometric Correction Table" \
            -range -0.05 1.25 \
            < ${OUT_VAL_TABLE_TBL} \
            > ${OUT_VAL_TABLE_EPS}
        
${OUT_LOG_TABLE_EPS}: ${OUT_LOG_TABLE_TBL}
	table_plot.sh \
            -title "${TESTDIR} - Logspace Photometric Correction Table" \
            < ${OUT_LOG_TABLE_TBL} \
            > ${OUT_LOG_TABLE_EPS}

clean-plot-tab:
	/bin/rm -f ${OUT_TABLE_ALL_EPS}

# ----------------------------------------------------------------------
# Plot values from chart strips:
        
OUT_STRIP_ALL_EPS := ${OUT_RAW_STRIP_EPS} ${OUT_ADJ_STRIP_EPS}

do-plot-str: ${OUT_STRIP_ALL_EPS}
	${PSVIEW} ${OUT_RAW_STRIP_EPS}
	${PSVIEW} ${OUT_ADJ_STRIP_EPS}
        
${OUT_RAW_STRIP_EPS}: ${OUT_RAW_STRIP_FNI}
	fni_plot.sh \
            -channel 0 \
            -rows -kodak \
            -title "${TESTDIR} - Kodak Q-13 Chart Strip" \
            < ${OUT_RAW_STRIP_FNI} \
            > ${OUT_RAW_STRIP_EPS}
        
${OUT_ADJ_STRIP_EPS}: ${OUT_ADJ_STRIP_FNI}
	fni_plot.sh \
            -channel 0 \
            -rows -kodak \
            -title "${TESTDIR} - Kodak Q-13 Chart Strip" \
            < ${OUT_ADJ_STRIP_FNI} \
            > ${OUT_ADJ_STRIP_EPS}

clean-plot-str:
	/bin/rm -f ${OUT_STRIP_ALL_EPS}

# ----------------------------------------------------------------------
# Plot fitting basis:

OUT_BASIS_ALL_EPS := \
          ${OUT_BASIS_I0_EPS} \
	  ${OUT_BASIS_I1_EPS} \
	  ${OUT_BASIS_I2_EPS} \
	  ${OUT_BASIS_MD_EPS} \
	  ${OUT_BASIS_F2_EPS} \
	  ${OUT_BASIS_F1_EPS} \
	  ${OUT_BASIS_F0_EPS}

do-plot-bas: ${OUT_BASIS_ALL_EPS}
	${PSVIEW} ${OUT_BASIS_I0_EPS}
	${PSVIEW} ${OUT_BASIS_I1_EPS}
	${PSVIEW} ${OUT_BASIS_I2_EPS}
	${PSVIEW} ${OUT_BASIS_MD_EPS}
	${PSVIEW} ${OUT_BASIS_F2_EPS}
	${PSVIEW} ${OUT_BASIS_F1_EPS}
	${PSVIEW} ${OUT_BASIS_F0_EPS}

${OUT_BASIS_I0_EPS}: ${OUT_BASIS_TBL}
	basis_plot.sh \
            -xrange -0.1 +1.1 \
            -title "${TESTDIR} - Basis Function 0" \
            -index 0 \
            < ${OUT_BASIS_TBL} \
            > ${OUT_BASIS_I0_EPS}
        
${OUT_BASIS_I1_EPS}: ${OUT_BASIS_TBL}
	basis_plot.sh \
            -xrange -0.1 +1.1 \
            -title "${TESTDIR} - Basis Function 1" \
            -index 1 \
            < ${OUT_BASIS_TBL} \
            > ${OUT_BASIS_I1_EPS}
        
${OUT_BASIS_I2_EPS}: ${OUT_BASIS_TBL}
	basis_plot.sh \
            -xrange -0.1 +1.1 \
            -title "${TESTDIR} - Basis Function 2" \
            -index 2 \
            < ${OUT_BASIS_TBL} \
            > ${OUT_BASIS_I2_EPS}
        
${OUT_BASIS_MD_EPS}: ${OUT_BASIS_TBL}
	basis_plot.sh \
            -xrange -0.1 +1.1 \
            -title "${TESTDIR} - Basis Function 3-${IXMDLAST}" \
            -indices 3 ${IXMDLAST} \
            < ${OUT_BASIS_TBL} \
            > ${OUT_BASIS_MD_EPS}
        
${OUT_BASIS_F2_EPS}: ${OUT_BASIS_TBL}
	basis_plot.sh \
            -xrange -0.1 +1.1 \
            -title "${TESTDIR} - Basis Function ${IXFIN2}" \
            -index ${IXFIN2} \
            < ${OUT_BASIS_TBL} \
            > ${OUT_BASIS_F2_EPS}
        
${OUT_BASIS_F1_EPS}: ${OUT_BASIS_TBL}
	basis_plot.sh \
            -xrange -0.1 +1.1 \
            -title "${TESTDIR} - Basis Function ${IXFIN1}" \
            -index ${IXFIN1} \
            < ${OUT_BASIS_TBL} \
            > ${OUT_BASIS_F1_EPS}
        
${OUT_BASIS_F0_EPS}: ${OUT_BASIS_TBL}
	basis_plot.sh \
            -xrange -0.1 +1.1 \
            -title "${TESTDIR} - Basis Function ${IXFIN0} " \
            -index ${IXFIN0} \
            < ${OUT_BASIS_TBL} \
            > ${OUT_BASIS_F0_EPS}

clean-plot-bas:
	/bin/rm -f ${OUT_BASIS_ALL_EPS}

# 
# End make ${TESTARGS}
######################################################################
endif
