# Last edited on 2023-02-04 07:01:26 by stolfi

PROG := photo_to_normal

PROGDIR := ..

include ${STOLFIHOME}/programs/c/GENERIC-PROGS-TEST.make

PLOT := YES

# PREFIX:GAB2:GAB2:GAB3

TESTS := \
  synth:t3-020-3-2-3:a:@:@ \
  synth:t4-020-3-3-3:a:@:@ \
  synth:t5-020-3-1-1:a:@:@ \
  synth:t6-020-3-1-1:a:@:@

ALL_TESTS := \
  synth:t3-020-3-1-1:a:@:@ \
  synth:t3-020-3-2-3:a:@:@ \
  synth:t4-020-3-3-3:a:@:@ \
  synth:t5-020-3-1-1:a:@:@ \
  synth:t6-020-3-1-1:a:@:@

SHELL := /bin/sh

# PSVIEW := ghostview
PSVIEW := evince

.PHONY:: \
  runalltests runtest \
  computenormals \
  showppmnormals showepsnormals deleteplots

# all:
all: runalltests

# ====================================================================
# Cleanup

clean::
	-/bin/rm -f *.fni *.ppm *.pgm *.eps

# ====================================================================
# Running tests

runalltests: 
	for t in ${TESTS} ; do \
          ${MAKE} TESTARGS=$$t runtest ; \
        done

TESTARGS := TESTARGS.IS.UNDEFINED
ifneq "/${TESTARGS}" "/TESTARGS.IS.UNDEFINED"
#######################################################################
# Recursive "make" to run the test ${TESTARGS}

TESTFIELDS  := ${subst  :, ,${TESTARGS}}
TESTDIR  := ${word 1,${TESTFIELDS}}
PREFIX   := ${word 2,${TESTFIELDS}}
GTAG_1   := ${word 3,${TESTFIELDS}}
GTAG_2   := ${word 4,${TESTFIELDS}}
GTAG_3   := ${word 5,${TESTFIELDS}}

IN_DIR := ${TESTDIR}
IN_PREFIX  := ${IN_DIR}/${PREFIX}

OUT_DIR := out/${TESTDIR}
OUT_PREFIX := ${OUT_DIR}/${PREFIX}

# Input scene images:
SCENE_PHOTOS := ${shell ls ${IN_PREFIX}-S-[0-9].fni | sort}

IN_ALL := \
  ${SCENE_PHOTOS}

# Light gauge options: 
ifeq "/${GTAG_1}" "/@"
  G1_NRM := 
  G1_PHOTOS := 
  G1_OPTS := 
else
  G1_NRM := ${IN_PREFIX}-G-${GTAG_1}-nrm
  G1_PHOTOS := ${shell ls ${IN_PREFIX}-G-${GTAG_1}-[0-9].fni | sort}
  G1_OPTS := \
    -gauge \
      000 000 \
      ${G1_NRM}.fni \
      ${G1_PHOTOS}
  IN_ALL := \
    ${IN_ALL} \
    ${G1_NRM}.fni \
    ${G1_PHOTOS}
endif
ifeq "/${GTAG_2}" "/@"
  G2_NRM := 
  G2_PHOTOS := 
  G2_OPTS := 
else
  G2_NRM := ${IN_PREFIX}-G-${GTAG_2}-nrm
  G2_PHOTOS := ${shell ls ${IN_PREFIX}-G-${GTAG_2}-[0-9].fni | sort}
  G2_OPTS := \
    -gauge \
      000 000 \
      ${G2_NRM}.fni \
      ${G2_PHOTOS}
  IN_ALL := \
    ${IN_ALL} \
    ${G2_NRM}.fni \
    ${G2_PHOTOS}
endif
ifeq "/${GTAG_3}" "/@"
  G3_NRM := 
  G3_PHOTOS := 
  G3_OPTS := 
else
  G3_NRM := ${IN_PREFIX}-G-${GTAG_3}-nrm
  G3_PHOTOS := ${shell ls ${IN_PREFIX}-G-${GTAG_3}-[0-9].fni | sort}
  G3_OPTS := \
    -gauge \
      000 000 \
      ${G3_NRM}.fni \
      ${G3_PHOTOS}
  IN_ALL := \
    ${IN_ALL} \
    ${G3_NRM}.fni \
    ${G3_PHOTOS}
endif

# Output files:
OUT_CLR := ${OUT_PREFIX}-clr
OUT_NRM := ${OUT_PREFIX}-nrm

# Correct output files (for checking):
REF_CLR := ${IN_PREFIX}-ref-clr
REF_NRM := ${IN_PREFIX}-ref-nrm

# Plot files:
OUT_NRM_X := ${OUT_PREFIX}-nrm-X
OUT_NRM_Y := ${OUT_PREFIX}-nrm-Y
OUT_NRM_Z := ${OUT_PREFIX}-nrm-Z

REF_NRM_X := ${REF_PREFIX}-nrm-X
REF_NRM_Y := ${REF_PREFIX}-nrm-Y
REF_NRM_Z := ${REF_PREFIX}-nrm-Z

ifeq "/${PLOT}" "/YES"
  runtest: computenormals showppmnormals
else
  runtest: computenormals deleteplots
endif

computenormals: ${PROGDIR}/${PROG} ${IN_ALL}
	@echo "TESTFIELDS = ${TESTFIELDS}"
	mkdir -p ${OUT_DIR}
	${PROGDIR}/${PROG} \
            -scene ${SCENE_PHOTOS} \
            -maxval 255 -noise 0.005 \
            ${G1_OPTS} \
            ${G2_OPTS} \
            ${G3_OPTS} \
            -outPrefix ${OUT_PREFIX}

showppmnormals: ${OUT_NRM}.fni ${REF_NRM}.fni
	fni_to_pnm \
            -channels 0 1 2 \
            -min -1.0 -1.0 -1.0 \
            -max +1.0 +1.0 +1.0 \
            < ${OUT_NRM}.fni \
            > ${OUT_NRM}.ppm && \
	fni_to_pnm \
            -channels 0 1 2 \
            -min -1.0 -1.0 -1.0 \
            -max +1.0 +1.0 +1.0 \
            < ${REF_NRM}.fni \
            > ${REF_NRM}.ppm && \
          display -title '%f' ${OUT_NRM}.ppm ${REF_NRM}.ppm

showepsnormals: ${OUT_NRM}.fni
	fni_plot.sh \
            -channel 0 \
            -title "NX(X,Y)" \
            < ${OUT_NRM}.fni \
            > ${OUT_NRM_X}.eps && \
          ${PSVIEW} ${OUT_NRM_X}.eps
	fni_plot.sh \
            -channel 1 \
            -title "NY(X,Y)" \
            < ${OUT_NRM}.fni \
            > ${OUT_NRM_Y}.eps && \
          ${PSVIEW} ${OUT_NRM_Y}.eps
	fni_plot.sh \
            -channel 2 \
            -title "NZ(X,Y)" \
            < ${OUT_NRM}.fni \
            > ${OUT_NRM_Z}.eps && \
          ${PSVIEW} ${OUT_NRM_Z}.eps


# 
# End make ${TESTARGS}
######################################################################
endif

# Rebuild the program if needed:

${PROGDIR}/${PROG}: ${PROGDIR}
	( cd ${PROGDIR} && ${MAKE} ${PROG} )
