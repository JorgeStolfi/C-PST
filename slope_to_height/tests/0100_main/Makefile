# Last edited on 2023-02-04 07:01:11 by stolfi

PROG := slope_to_height

PROGDIR := ../..

include ${STOLFIHOME}/programs/c/GENERIC-PROGS-TEST.make

VIEW := NO
PLOT := YES
SHOW := YES

DEBUG := YES
DEBUG_ITER := 1000000000

# Shal we use topological sort?
TOPO_SORT := YES

# Format:  
# {FUNC}¦{LZ}¦{NZ}¦{LG}¦{NG}¦{GRADTYPE}¦{MAXGDIFF}¦{SIGMAG}¦{SIGMAW}¦{WOPT}¦{ZMIN}¦{ZMAX}¦{ZSTEP}¦{GMAX}¦{ERRMAX}
# where
# {FUNC}...{SIGMAW} as in make_test_slope_maps/tests/Makefile.
# {WOPT} is "U" to use uniform weights, "W" to use the associated weight mask.
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

# point-sampled Z, 1-pixel sampled analytic gradient,
# numeric gradient out, uniform weights, no noise.
# These test the basic accuracy of the method.
SHARP_PIXEL_NUMGRAD_TESTS := \
  00¦0¦01¦1¦05¦N¦3.00¦0.000¦0.000¦U¦-0020¦+0020¦0005¦02.0¦02.0 \
  01¦0¦01¦1¦05¦N¦3.00¦0.000¦0.000¦U¦-0020¦+0020¦0005¦02.0¦02.0 \
  02¦0¦01¦1¦05¦N¦3.00¦0.000¦0.000¦U¦-0020¦+0020¦0005¦02.0¦02.0 \
  03¦0¦01¦1¦05¦N¦3.00¦0.000¦0.000¦U¦-0020¦+0020¦0005¦02.0¦02.0 \
  04¦0¦01¦1¦05¦N¦3.00¦0.000¦0.000¦U¦-0015¦+0010¦0002¦01.0¦02.0 \
  05¦0¦01¦1¦05¦N¦1.00¦0.000¦0.000¦U¦-0005¦+0015¦0005¦06.0¦02.0 \
  06¦0¦01¦1¦05¦N¦1.00¦0.000¦0.000¦U¦-0005¦+0015¦0005¦02.0¦02.0 \
  07¦0¦01¦1¦05¦N¦1.00¦0.000¦0.000¦U¦-0003¦+0017¦0005¦02.0¦02.0 \
  08¦0¦01¦1¦05¦N¦8.00¦0.000¦0.000¦U¦-0020¦+0020¦0005¦20.0¦08.0 \
  09¦0¦01¦1¦05¦N¦3.00¦0.000¦0.000¦U¦-0004¦+0016¦0005¦06.0¦02.0 \
  10¦0¦01¦1¦05¦N¦1.00¦0.000¦0.000¦U¦-0018¦+0012¦0005¦12.0¦05.0 \
  17¦0¦01¦1¦05¦N¦1.00¦0.000¦0.000¦U¦-0003¦+0017¦0005¦12.0¦02.0 \
  18¦0¦01¦1¦05¦N¦1.00¦0.000¦0.000¦U¦-0020¦+0020¦0005¦12.0¦05.0 \
  
# 1-pixel sampled Z, 2-pixel sampled analytic gradient,
# numeric gradient out, uniform weights, no noise.
# These test the method on more realistic data
# where slopes are not consistent with the heights
# because of discontinuities or small-scale detail.
PIXEL_SMOOTH_ANAGRAD_F11_F16_TESTS := \
  11¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦U¦-0025¦+0025¦0005¦02.0¦01.0 \
  12¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦U¦-0025¦+0025¦0005¦02.0¦01.0 \
  13¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦U¦-0025¦+0025¦0005¦20.0¦03.0 \
  14¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦U¦-0025¦+0025¦0005¦20.0¦03.0 \
  15¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦U¦-0025¦+0025¦0005¦40.0¦04.0 \
  16¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦U¦-0025¦+0025¦0005¦40.0¦04.0
PIXEL_SMOOTH_ANAGRAD_TESTS := \
  00¦1¦05¦2¦11¦A¦3.00¦0.000¦0.000¦U¦-0020¦+0020¦0005¦02.0¦02.0 \
  01¦1¦05¦2¦11¦A¦3.00¦0.000¦0.000¦U¦-0020¦+0020¦0005¦02.0¦02.0 \
  02¦1¦05¦2¦11¦A¦3.00¦0.000¦0.000¦U¦-0020¦+0020¦0005¦02.0¦02.0 \
  03¦1¦05¦2¦11¦A¦3.00¦0.000¦0.000¦U¦-0020¦+0020¦0005¦02.0¦02.0 \
  04¦1¦05¦2¦11¦A¦3.00¦0.000¦0.000¦U¦-0015¦+0010¦0002¦01.0¦02.0 \
  05¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦U¦-0005¦+0015¦0005¦06.0¦02.0 \
  06¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦U¦-0005¦+0015¦0005¦02.0¦02.0 \
  07¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦U¦-0003¦+0017¦0005¦02.0¦02.0 \
  08¦1¦05¦2¦11¦A¦8.00¦0.000¦0.000¦U¦-0020¦+0020¦0005¦20.0¦08.0 \
  09¦1¦05¦2¦11¦A¦3.00¦0.000¦0.000¦U¦-0004¦+0016¦0005¦06.0¦02.0 \
  10¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦U¦-0018¦+0012¦0005¦01.5¦15.0 \
  ${PIXEL_SMOOTH_ANAGRAD_F11_F16_TESTS} \
  17¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦U¦-0003¦+0017¦0005¦12.0¦15.0 \
  18¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦U¦-0020¦+0020¦0020¦01.5¦15.0
  
# 1-pixel sampled Z, 2-pixel sampled gradient,
# analytic gradient out, with weights, no noise
PIXEL_SMOOTH_ANAGRAD_WEIGHTED_TESTS := \
  03¦1¦05¦2¦11¦A¦3.00¦0.000¦0.000¦W¦-0020¦+0020¦0005¦02.0¦02.0 \
  04¦1¦05¦2¦11¦A¦3.00¦0.000¦0.000¦W¦-0015¦+0010¦0002¦01.0¦02.0 \
  05¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦W¦-0005¦+0015¦0005¦06.0¦02.0 \
  06¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦W¦-0005¦+0015¦0005¦02.0¦02.0 \
  07¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦W¦-0003¦+0017¦0005¦02.0¦02.0 \
  08¦1¦05¦2¦11¦A¦8.00¦0.000¦0.000¦W¦-0020¦+0020¦0005¦20.0¦08.0 \
  09¦1¦05¦2¦11¦A¦3.00¦0.000¦0.000¦W¦-0004¦+0016¦0005¦06.0¦02.0 \
  10¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦W¦-0018¦+0012¦0005¦01.5¦05.0 \
  17¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦W¦-0003¦+0017¦0005¦12.0¦02.0 \
  18¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦W¦-0020¦+0020¦0005¦01.5¦05.0 \
  
# 1-pixel sampled Z, 2-pixel sampled gradient,
# analytic gradient out, with weights, no noise
PIXEL_SMOOTH_ANAGRAD_NOISYG_WEIGHTED_TESTS := \
  04¦1¦05¦2¦11¦A¦3.00¦0.300¦0.000¦W¦-0015¦+0010¦0002¦01.0¦02.0 \
  05¦1¦05¦2¦11¦A¦1.00¦0.300¦0.000¦W¦-0005¦+0015¦0005¦06.0¦02.0 \
  08¦1¦05¦2¦11¦A¦8.00¦0.300¦0.000¦W¦-0020¦+0020¦0005¦20.0¦08.0 \
  09¦1¦05¦2¦11¦A¦3.00¦0.300¦0.000¦W¦-0004¦+0016¦0005¦06.0¦02.0 \
  10¦1¦05¦2¦11¦A¦1.00¦0.300¦0.000¦W¦-0018¦+0012¦0005¦03.0¦05.0 \
  18¦1¦05¦2¦11¦A¦1.00¦0.300¦0.000¦W¦-0020¦+0020¦0005¦03.0¦05.0 \
  
# 1-pixel sampled Z, 2-pixel sampled gradient,
# analytic gradient out, with weights, no noise
PIXEL_SMOOTH_ANAGRAD_NOISYW_WEIGHTED_TESTS := \
  04¦1¦05¦2¦11¦A¦3.00¦0.000¦1.000¦W¦-0015¦+0010¦0002¦01.0¦02.0 \
  05¦1¦05¦2¦11¦A¦1.00¦0.000¦1.000¦W¦-0005¦+0015¦0005¦06.0¦02.0 \
  08¦1¦05¦2¦11¦A¦8.00¦0.000¦1.000¦W¦-0020¦+0020¦0005¦20.0¦08.0 \
  09¦1¦05¦2¦11¦A¦3.00¦0.000¦1.000¦W¦-0004¦+0016¦0005¦06.0¦02.0 \
  10¦1¦05¦2¦11¦A¦1.00¦0.000¦1.000¦W¦-0018¦+0012¦0005¦01.5¦05.0 \
  18¦1¦05¦2¦11¦A¦1.00¦0.000¦1.000¦W¦-0020¦+0020¦0005¦01.5¦05.0 \
  
# Tests to figure out which sampling method is best.
# Repeats some of the above.
SAMPLING_TESTS := \
  05¦0¦01¦1¦05¦N¦1.00¦0.000¦0.000¦U¦-0005¦+0015¦0005¦06.0¦02.0 \
  05¦1¦05¦1¦05¦N¦1.00¦0.000¦0.000¦U¦-0005¦+0015¦0005¦06.0¦02.0 \
   \
  05¦0¦01¦0¦01¦A¦1.00¦0.000¦0.000¦U¦-0005¦+0015¦0005¦06.0¦02.0 \
  05¦0¦01¦1¦05¦A¦1.00¦0.000¦0.000¦U¦-0005¦+0015¦0005¦06.0¦02.0 \
  05¦0¦01¦2¦11¦A¦1.00¦0.000¦0.000¦U¦-0005¦+0015¦0005¦06.0¦02.0 \
  05¦1¦05¦1¦05¦A¦1.00¦0.000¦0.000¦U¦-0005¦+0015¦0005¦06.0¦02.0 \
  05¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦U¦-0005¦+0015¦0005¦06.0¦02.0 \
   \
  05¦0¦01¦0¦01¦A¦1.00¦0.000¦0.000¦W¦-0005¦+0015¦0005¦06.0¦02.0 \
  05¦0¦01¦1¦05¦A¦1.00¦0.000¦0.000¦W¦-0005¦+0015¦0005¦06.0¦02.0 \
  05¦0¦01¦2¦11¦A¦1.00¦0.000¦0.000¦W¦-0005¦+0015¦0005¦06.0¦02.0 \
  05¦1¦05¦1¦05¦A¦1.00¦0.000¦0.000¦W¦-0005¦+0015¦0005¦06.0¦02.0 \
  05¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦W¦-0005¦+0015¦0005¦06.0¦02.0 \

# Tests with the parabola function.
# Repeats some of the above.
PARABOLA_TESTS := \
  04¦1¦05¦1¦05¦N¦3.00¦0.000¦0.000¦U¦-0015¦+0010¦0002¦01.0¦02.0 \
  04¦1¦05¦2¦11¦A¦3.00¦0.000¦0.000¦U¦-0015¦+0010¦0002¦01.0¦02.0 \
  04¦1¦05¦2¦11¦A¦3.00¦0.000¦0.000¦W¦-0015¦+0010¦0002¦01.0¦02.0 \
  04¦1¦05¦2¦11¦A¦3.00¦0.300¦0.000¦W¦-0015¦+0010¦0002¦01.0¦02.0 \
  04¦1¦05¦2¦11¦A¦3.00¦0.000¦1.000¦W¦-0015¦+0010¦0002¦01.0¦02.0 \

# Tests with the divergent ramps function.
# Repeats some of the above.
ALL_F10_TESTS := \
  10¦1¦05¦1¦05¦N¦1.00¦0.000¦0.000¦U¦-0018¦+0012¦0005¦12.0¦05.0 \
  10¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦U¦-0018¦+0012¦0005¦01.5¦15.0 \
  10¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦W¦-0018¦+0012¦0005¦01.5¦05.0 \
  10¦1¦05¦2¦11¦A¦1.00¦0.000¦1.000¦W¦-0018¦+0012¦0005¦01.5¦05.0 \
  10¦1¦05¦2¦11¦A¦1.00¦0.300¦0.000¦W¦-0018¦+0012¦0005¦03.0¦05.0 \
  
# Tests with the discontinuous babel tower function.
# Repeats some of the above.
ALL_F17_TESTS := \
  17¦0¦01¦1¦05¦N¦1.00¦0.000¦0.000¦U¦-0003¦+0017¦0005¦12.0¦05.0 \
  17¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦U¦-0003¦+0017¦0005¦02.0¦15.0 \
  17¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦W¦-0003¦+0017¦0005¦02.0¦05.0 \

# Tests with the cubic ramp function.
# Repeats some of the above.
ALL_F18_TESTS := \
  18¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦U¦-0020¦+0020¦0020¦01.5¦15.0 \
  18¦0¦01¦1¦05¦N¦1.00¦0.000¦0.000¦U¦-0020¦+0020¦0005¦12.0¦05.0 \
  18¦1¦05¦2¦11¦A¦1.00¦0.000¦0.000¦W¦-0020¦+0020¦0005¦01.5¦05.0 \

# Tests with the leaking dome function.
ALL_F19_TESTS := \
  19¦1¦05¦2¦11¦A¦9.00¦0.000¦0.000¦U¦-0005¦+0015¦0005¦06.0¦02.0 \
  19¦1¦05¦2¦11¦A¦9.00¦0.000¦0.000¦W¦-0005¦+0015¦0005¦06.0¦02.0 \

TESTS := \
  ${PARABOLA_TESTS}
 
TESTS_DONE := \
  ${SAMPLING_TESTS} \
  ${SHARP_PIXEL_NUMGRAD_TESTS} \
  ${PIXEL_SMOOTH_ANAGRAD_TESTS} \
  ${PIXEL_SMOOTH_ANAGRAD_WEIGHTED_TESTS} \
  ${PIXEL_SMOOTH_ANAGRAD_NOISYG_WEIGHTED_TESTS} \
  ${PIXEL_SMOOTH_ANAGRAD_NOISYW_WEIGHTED_TESTS} \
  ${PIXEL_SMOOTH_ANAGRAD_F11_F16_TESTS}

SPECIAL_TESTS := \
  ${ALL_F10_TESTS} \
  ${ALL_F17_TESTS}\
  ${ALL_F18_TESTS} \
  ${ALL_F19_TESTS}

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
  compute-z \
  view-z view-zerror delete-views \
  show-z show-zerror delete-shows \
  plot-z plot-slopes plot-weight plot-ref-z plot-zerror \
  plot-iter-z-zerror-all \
  plot-iter-z plot-iter-zerror \
  delete-plots

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

TESTFIELDS  := ${subst ¦, ,${TEST}}
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
Z_MIN          := ${word 11, ${TESTFIELDS}}
Z_MAX          := ${word 12, ${TESTFIELDS}}
Z_STEP         := ${word 13, ${TESTFIELDS}}
G_MAX          := ${word 14, ${TESTFIELDS}}
ERR_MAX        := ${word 15, ${TESTFIELDS}}

RZ_MIN := ${Z_MIN}
RZ_MAX := ${Z_MAX}

IN_DIR := data
OUT_DIR := out

# Tags for input file names:
MAXGDIFF_TAG := ${subst .,,${MAXGDIFF}}
SIGMAG_TAG   := ${subst .,,${SIGMAG}}
SIGMAW_TAG   := ${subst .,,${SIGMAW}}

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
OUT_Z_EPS := ${OUT_PREFIX}-Z.eps
OUT_RZ_EPS := ${OUT_PREFIX}-rZ.eps
OUT_EZ_EPS := ${OUT_PREFIX}-eZ.eps

# Debugging files:

OUT_DEBUG_PREFIX := ${OUT_PREFIX}-d

DEBUG_Z_FNI := ${OUT_DEBUG_PREFIX}-00-Z.fni
DEBUG_Z_EPS := ${OUT_DEBUG_PREFIX}-00-Z.eps

ifeq "/${DEBUG}" "/YES"
  DEBUG_OPTS := -debugG -debugZ -debugIter ${DEBUG_ITER}
else
  DEBUG_OPTS := 
endif

ifeq "/${VIEW}" "/YES"
  VIEWACTIONS :=  delete-views view-z view-zerror
else
  VIEWACTIONS :=  delete-views
endif

ifeq "/${SHOW}" "/YES"
  SHOWACTIONS :=  delete-shows show-z show-zerror
else
  SHOWACTIONS :=  delete-shows
endif

ifeq "/${PLOT}" "/YES"
  PLOTACTIONS :=  delete-plots plot-iter-z-zerror-all plot-slopes plot-weight plot-ref-z plot-z plot-zerror
else
  PLOTACTIONS :=  delete-plots
endif

ifeq "/${TOPO_SORT}" "/YES"
  TOPO_OPT :=  -topoSort
else
  TOPO_OPT := 
endif

run-test: compute-z ${VIEWACTIONS} ${SHOWACTIONS} ${PLOTACTIONS}

compute-z: ${OUT_Z_FNI} 

${OUT_Z_FNI}: ${PROGDIR}/${PROG} ${IN_G_FNI} Makefile
	@echo "TESTFIELDS = ${TESTFIELDS}"
	-rm -fv ${OUT_PREFIX}-*.*
	${PROGDIR}/${PROG} \
            ${TOPO_OPT} \
            -compareZ ${IN_RZ_FNI} \
            ${DEBUG_OPTS} -debugSys \
            -verbose \
            -slopes ${IN_G_FNI} \
            -weights ${IN_W_FNI} \
            -outPrefix ${OUT_PREFIX}

# ----------------------------------------------------------------------
# Interactive 3D view of height map:
# Should also show reference map.

view-z: ${OUT_Z_FNI} ${IN_N_FNI} ${FNI_VIEW}
	${FNI_VIEW} \
            -channel 0 \
            -scale 1.0 \
            -texture ${IN_N_FNI} \
            ${OUT_Z_FNI}

view-zerror: ${OUT_Z_FNI} ${OUT_EZ_FNI} ${FNI_VIEW}
	${FNI_VIEW} \
            -channel 0 \
	    ${OUT_EZ_FNI}

delete-views:

# ----------------------------------------------------------------------
# Show height map as PGM image:

show-z: ${OUT_Z_FNI} ${FNI_TO_PNM}
	${FNI_TO_PNM} \
            -channel 0 \
            -width 32.000 \
            < ${OUT_Z_FNI} \
            > ${OUT_Z_PGM}
	-display -title '%f' -filter box -resize '400%' ${OUT_Z_PGM}

show-zerror: ${OUT_Z_FNI} ${OUT_EZ_fni} ${FNI_TO_PNM}
	${FNI_TO_PNM} \
            -channel 0 \
            < ${OUT_EZ_FNI} \
            > ${OUT_EZ_PGM}
	-display -title '%f' -filter box -resize '400%' ${OUT_EZ_PGM}

delete-shows:
	-/bin/rm -f ${OUT_Z_PGM} ${OUT_EZ_PGM}

# ----------------------------------------------------------------------
# 3D Postscript plot of height map:

plot-slopes: ${OUT_Z_FNI} ${IN_G_FNI} ${FNI_PLOT}
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

plot-weight: ${OUT_Z_FNI} ${IN_W_FNI} ${FNI_PLOT}
	${FNI_PLOT} \
            -channel 0 -title "W" \
            -range -0.1 2.1 \
            -ztics 0.5 \
            < ${IN_W_FNI} \
            > ${OUT_W_EPS} && \
          ${PSVIEW} ${OUT_W_EPS}

plot-z: ${OUT_Z_FNI}
	${FNI_PLOT} \
            -channel 0 \
            -title "Z(X,Y)" \
            -range ${Z_MIN} ${Z_MAX} \
            -ztics ${Z_STEP} \
            < ${OUT_Z_FNI} \
            > ${OUT_Z_EPS} && \
          ${PSVIEW} ${OUT_Z_EPS}

plot-ref-z: ${OUT_Z_FNI} ${OUT_RZ_FNI}
	${FNI_PLOT} \
            -channel 0 \
            -title "Z*(X,Y)" \
            -range ${RZ_MIN} ${RZ_MAX} \
            -ztics ${Z_STEP} \
            < ${IN_RZ_FNI} \
            > ${OUT_RZ_EPS} && \
          ${PSVIEW} ${OUT_RZ_EPS}

plot-zerror: ${OUT_Z_FNI} ${OUT_EZ_fni}
	${FNI_PLOT} \
            -channel 0 -title "eZ" \
            -range -${ERR_MAX} +${ERR_MAX} \
            < ${OUT_EZ_FNI} \
            > ${OUT_EZ_EPS} && \
          ${PSVIEW} ${OUT_EZ_EPS}

plot-iter-z-zerror-all: ${OUT_Z_FNI}
	for f in `ls -1 ${OUT_PREFIX}-*-Z.fni | sort | egrep -e '[-][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][-]'` ; do \
          ${MAKE} TEST='${TEST}' OUT_ITER_Z_FNI=$$f plot-iter-z plot-iter-zerror ; \
        done
        
OUT_ITER_Z_FNI :=        
ifneq "${OUT_ITER_Z_FNI}" ""
#######################################################################
# Recursive "make" to plot one iteration of test ${TEST},
# whose Z-file is ${OUT_ITER_Z_FNI}

# Get the error file for the height file ${OUT_ITER_Z_FNI}
OUT_ITER_EZ_FNI := ${subst -Z.fni,-eZ.fni,${OUT_ITER_Z_FNI}}

# Get the height and error EPS file names
OUT_ITER_Z_EPS := ${subst -Z.fni,-Z.eps,${OUT_ITER_Z_FNI}}
OUT_ITER_EZ_EPS := ${subst -eZ.fni,-eZ.eps,${OUT_ITER_EZ_FNI}}

ITER_LEVEL := ${shell echo "${OUT_ITER_Z_FNI}" | sed -e 's:^.*-deb-::g' -e 's:-[0-9][0-9][0-9][0-9]*-.*$$::g'}

# Compute a Z range appropriate for this scale. 
# Note that {bc} does not understand unary '+'.
ITER_Z_MIN  := ${shell echo "0${Z_MIN}/(2^${ITER_LEVEL})"  | bc -lq}
ITER_Z_MAX  := ${shell echo "0${Z_MAX}/(2^${ITER_LEVEL})"  | bc -lq}
ITER_Z_STEP := ${shell echo "0${Z_STEP}/(2^${ITER_LEVEL})" | bc -lq}

plot-iter-z: ${OUT_Z_FNI} ${OUT_ITER_Z_FNI}
	@echo "LEVEL = ${ITER_LEVEL} Z_MAX = ${Z_MAX}"
	${FNI_PLOT} \
            -channel 0 \
            -title "Z(X,Y)" \
            -range ${ITER_Z_MIN} ${ITER_Z_MAX} \
            -ztics ${ITER_Z_STEP} \
            < ${OUT_ITER_Z_FNI} \
            > ${OUT_ITER_Z_EPS} && \
          ${PSVIEW} ${OUT_ITER_Z_EPS}

plot-iter-zerror: ${OUT_Z_FNI} ${OUT_ITER_EZ_fni}
	${FNI_PLOT} \
            -channel 0 -title "eZ" \
            -range -${ERR_MAX} +${ERR_MAX} \
            < ${OUT_ITER_EZ_FNI} \
            > ${OUT_ITER_EZ_EPS} && \
          ${PSVIEW} ${OUT_ITER_EZ_EPS}

#
# End make ${TEST} ${OUT_ITER_Z_FNI}
######################################################################
endif

delete-plots:
	-/bin/rm -f ${OUT_PREFIX}-*.eps}

# 
# End make ${TEST}
######################################################################
endif
