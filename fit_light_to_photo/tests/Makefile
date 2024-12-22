# Makefile for generic C program
# Last edited on 2023-02-04 07:02:18 by stolfi

PROG := fit_light_to_photo

PROGDIR := ..

include ${STOLFIHOME}/programs/c/GENERIC-PROGS-TEST.make

VIEW := YES
SHOW := YES
PLOT := NO

# DIRECTORY:SCENE:LIGHT:RUN:MAXITER:DIRSTEP

TESTS := \
  photo/balls-a:g-ms-a:0:A:003:0.30

ALL_TESTS := \
  synth/balls-a:g-ms-a:0:A:003:0.30 \
   \
  photo/balls-a:g-ms-a:0:A:003:0.30 \
  photo/balls-a:g-ms-a:0:B:003:0.05 \
  photo/balls-a:g-ms-a:0:C:003:0.05 \
  photo/balls-a:g-ms-a:0:D:003:0.30 \
  photo/balls-a:g-ms-a:0:E:005:0.30

SHELL =	/bin/sh

# PSVIEW := ghostview
PSVIEW := evince

.PHONY:: \
  tidy \
  run-all-tests run-test \
  fit-light \
  do-view clean-view \
  do-show clean-show \
  do-plot clean-plot

# all:
all: run-all-tests

# ====================================================================
# Cleanup

clean::
	-/bin/rm -f *.sys *.fni *.pgm *.eps *.ppm
        
# ======================================================================
# Delete secondary plot files:

tidy:
	-/bin/rm -f *.sys *-d-[0-9][0-9]-{Z,dZ}.fni *.pgm *.eps *.ppm

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
DIR         := ${word 1,${TESTFIELDS}}
OBJECT      := ${word 2,${TESTFIELDS}}
LIGHT       := ${word 3,${TESTFIELDS}}
RUN         := ${word 4,${TESTFIELDS}}
MAXITER     := ${word 5,${TESTFIELDS}}
DIRSTEP     := ${word 6,${TESTFIELDS}}

IN_DIR := ${DIR}
OUT_DIR := out/${DIR}

IN_PREFIX  := ${IN_DIR}/${OBJECT}

IN_ACTUAL_FNI := ${IN_PREFIX}-${LIGHT}.fni
IN_ACTUAL_PNG := ${IN_PREFIX}-${LIGHT}.png
IN_ACTUAL_EPS := ${IN_PREFIX}-${LIGHT}.eps

IN_NORMAL_FNI := ${IN_PREFIX}-nrm.fni
IN_NORMAL_PNG := ${IN_PREFIX}-nrm.png
IN_NORMAL_X_EPS := ${IN_PREFIX}-nrm-X.eps
IN_NORMAL_Y_EPS := ${IN_PREFIX}-nrm-Y.eps
IN_NORMAL_Z_EPS := ${IN_PREFIX}-nrm-Z.eps

IN_PARMS := ${IN_PREFIX}-${LIGHT}-${RUN}-in.parms

OUT_PREFIX := ${OUT_DIR}/${OBJECT}-${LIGHT}-${RUN}

OUT_SYN_FNI := ${OUT_PREFIX}-fit.fni
OUT_SYN_PNG := ${OUT_PREFIX}-fit.png
OUT_SYN_EPS := ${OUT_PREFIX}-fit.eps

OUT_DIF_FNI := ${OUT_PREFIX}-dif.fni
OUT_DIF_PNG := ${OUT_PREFIX}-dif.png
OUT_DIF_EPS := ${OUT_PREFIX}-dif.eps

OUT_LIGHT_PARMS := ${OUT_PREFIX}-light.parms

ifeq "/${VIEW}" "/YES"
  VIEWACTIONS :=  clean-view do-view
else
  VIEWACTIONS :=  clean-view
endif

ifeq "/${SHOW}" "/YES"
  SHOWACTIONS :=  clean-show do-show
else
  SHOWACTIONS :=  clean-show
endif

ifeq "/${PLOT}" "/YES"
  PLOTACTIONS :=  clean-plot do-plot
else
  PLOTACTIONS :=  clean-plot
endif

run-test: fit-light ${VIEWACTIONS} ${SHOWACTIONS} ${PLOTACTIONS}

fit-light: ${PROGDIR}/${PROG} ${IN_ACTUAL_FNI} ${IN_NORMAL_FNI} ${IN_PARMS}
	@echo "TESTFIELDS = ${TESTFIELDS}"
	mkdir -p ${OUT_DIR}
	${PROGDIR}/${PROG} \
            -showLights \
            -image ${IN_ACTUAL_FNI} \
            -normal ${IN_NORMAL_FNI} \
            `cat ${IN_PARMS} | egrep -v '^[ ]*([\#]|$$)'` \
            -adjustDir 0 ${DIRSTEP} \
            -weightBias 0.01 \
            -iterations ${MAXITER} \
            -outPrefix ${OUT_PREFIX}

# ----------------------------------------------------------------------
# Interactive 3D view of synthetic images, difference image, and light setup:
# Should also show reference map and difference image.

do-view: ${OUT_LIGHT_PARMS} ${OUT_SYN_FNI} ${OUT_DIF_FNI}
	fni_view -scale 50 ${IN_ACTUAL_FNI}
	fni_view -scale 50 ${OUT_SYN_FNI}
	fni_view -scale 200  ${OUT_DIF_FNI}
	echo lamp-view `cat ${OUT_LIGHT_PARMS}`

clean-view:

# ----------------------------------------------------------------------
# Show synthetic images and difference image as a PNG file:

do-show: ${IN_ACTUAL_PNG} ${IN_NORMAL_PNG} ${OUT_SYN_PNG} ${OUT_DIF_PNG}
	display -title '%f' -resize '500%' ${IN_ACTUAL_PNG} ${OUT_SYN_PNG} ${OUT_DIF_PNG}

${IN_ACTUAL_PNG}: ${IN_ACTUAL_FNI}
	fni_to_pnm \
            -channel 0 \
            -min 00.00 -max +1.00 \
            < ${IN_ACTUAL_FNI} \
          | convert PPM:- PNG:- \
          > ${IN_ACTUAL_PNG}

${IN_NORMAL_PNG}: ${IN_NORMAL_FNI}
	fni_to_pnm \
            -channels 0 1 2 \
            -min -1.00 -max +1.00 \
            < ${IN_NORMAL_FNI} \
          | convert PPM:- PNG:- \
          > ${IN_NORMAL_PNG}

${OUT_SYN_PNG}: ${OUT_SYN_FNI}
	fni_to_pnm \
            -channel 0 \
            -min 00.00 -max +1.00 \
            < ${OUT_SYN_FNI} \
          | convert PPM:- PNG:- \
          > ${OUT_SYN_PNG}

${OUT_DIF_PNG}: ${OUT_DIF_FNI}
	fni_to_pnm \
            -channel 0 \
            -min -0.10 -max +0.10 \
            < ${OUT_DIF_FNI} \
          | convert PPM:- PNG:- \
          > ${OUT_DIF_PNG}

clean-show:
	/bin/rm -f 

# ----------------------------------------------------------------------
# 3D Postscript plot of light setup:

do-plot: ${OUT_DIF_EPS}
	${PSVIEW} ${OUT_DIF_EPS}
        
${OUT_DIF_EPS}: ${OUT_DIF_FNI}
	fni_plot.sh \
            -channel 0 \
            -title "difference" \
            < ${OUT_DIF_FNI} \
            > ${OUT_DIF_EPS}

clean-plot:

# 
# End make ${TESTARGS}
######################################################################
endif
