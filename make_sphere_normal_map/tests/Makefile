# Last edited on 2023-02-04 07:01:45 by stolfi
        
PROG := make_sphere_normal_map

PROGDIR := ..

include ${STOLFIHOME}/programs/c/GENERIC-PROGS-TEST.make

VIEW := YES
SHOW := YES
PLOT := NO

# ${PREFIX}:${NX}:${NY}:${CTRX}:${CTRY}:${RAD}:${STRX}:${STRY}:${RES}:${NOISE}

TESTS := \
  G:064:048:032:024:020:00:00:00200:0000 \
  G:064:048:032:024:020:06:04:00200:0000 \
  G:064:048:032:024:020:00:00:00200:0500
  
ALL_TESTS :=

SHELL =	/bin/sh

# PSVIEW := ghostview
PSVIEW := evince

.PHONY:: \
  run-all run-test \
  create-normals \
  view-normals view-clean \
  show-normals show-clean \
  plot-normals plot-clean

all: run-all

# ====================================================================
# Cleanup

clean::
	-/bin/rm -f *.fni *.pgm *.ppm *.eps

# ====================================================================
# Running tests

run-all: 
	for t in ${TESTS} ; do \
          ${MAKE} TESTARGS=$$t run-test ; \
        done

TESTARGS := TESTARGS.IS.UNDEFINED
ifneq "/${TESTARGS}" "/TESTARGS.IS.UNDEFINED"
#######################################################################
# Recursive "make" to run the test ${TESTARGS}

TESTFIELDS  := ${subst  :, ,${TESTARGS}}
PREFIX := ${word  1,${TESTFIELDS}}
NX     := ${word  2,${TESTFIELDS}}
NY     := ${word  3,${TESTFIELDS}}
CTRX   := ${word  4,${TESTFIELDS}}
CTRY   := ${word  5,${TESTFIELDS}}
RAD    := ${word  6,${TESTFIELDS}}
STRX   := ${word  7,${TESTFIELDS}}
STRY   := ${word  8,${TESTFIELDS}}
RES    := ${word  9,${TESTFIELDS}}
NOISE  := ${word 10,${TESTFIELDS}}

SUBSAMPLE := 3

TESTNAME := ${PREFIX}-${NX}-${NY}-${CTRX}-${CTRY}-${RAD}-${STR}X-${STRY}-${RES}-${NOISE}
OUTNAME := out/${TESTNAME}

ifeq "/${VIEW}" "/YES"
  VIEW_ACTION := view-clean view-normals
else
  VIEW_ACTION := view-clean
endif

ifeq "/${SHOW}" "/YES"
  SHOW_ACTION := show-clean show-normals
else
  SHOW_ACTION := show-clean
endif

ifeq "/${PLOT}" "/YES"
  PLOT_ACTION := plot-clean plot-normals
else
  PLOT_ACTION := plot-clean
endif

run-test: create-normals ${VIEW_ACTION} ${SHOW_ACTION} ${PLOT_ACTION}

create-normals: ${PROGDIR}/${PROG}
	@echo "TESTARGS = ${TESTARGS}"
	${PROGDIR}/${PROG} \
          -size ${NX} ${NY} \
          -sphere \
            center ${CTRX} ${CTRY} \
            radius ${RAD} \
            stretch ${STRX} ${STRY} \
          -camera \
            resolution 0.${RES} \
          -noise 0.${NOISE} \
          -subsample ${SUBSAMPLE} \
          > ${OUTNAME}.fni

view-normals: ${OUTNAME}.fni
	fni_view \
            -channel 0 \
            -scale 20.0 \
            ${OUTNAME}.fni

view-clean: 

show-normals: ${OUTNAME}.fni
	fni_to_pnm \
            -channels 0 1 2 \
            < ${OUTNAME}.fni \
            > ${OUTNAME}.ppm && \
          display -title '%f' ${OUTNAME}.ppm

show-clean: 
	/bin/rm -f ${OUTNAME}-{X,Y,Z}.eps ${OUTNAME}.ppm

plot-normals: ${OUTNAME}.fni
	fni_plot.sh \
            -channel 0 -title "nX" \
            < ${OUTNAME}.fni \
            > ${OUTNAME}-X.eps && \
          ${PSVIEW} ${OUTNAME}-X.eps
	fni_plot.sh \
            -channel 1 -title "nY" \
            < ${OUTNAME}.fni \
            > ${OUTNAME}-Y.eps && \
          ${PSVIEW} ${OUTNAME}-Y.eps
	fni_plot.sh \
            -channel 2 -title "nZ" \
            < ${OUTNAME}.fni \
            > ${OUTNAME}-Z.eps && \
          ${PSVIEW} ${OUTNAME}-Z.eps

plot-clean: 
	/bin/rm -f ${OUTNAME}-{X,Y,Z}.eps ${OUTNAME}.ppm

# 
# End make ${TESTARGS}
######################################################################
endif
