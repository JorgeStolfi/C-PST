# Last edited on 2023-02-04 07:01:40 by stolfi

PROG := make_test_slope_maps
        
PROGDIR := ..

include ${STOLFIHOME}/programs/c/GENERIC-PROGS-TEST.make

VIEW := NO
SHOW := YES
PLOT := NO
HIST := NO

# ----------------------------------------------------------------------

# Size of slope map
NX = 16
NY = 16

# Test runs
# Format: {FUNC}LZ}NZ}LG}NG}GRADTYPE}MAXGDIFF}SIGMAG}SIGMAW}
# where {GRADTYPE} is "N" for numeric, "A" for analytic.

# Test groups
# First and 2nd part of group name refers
# to how the Z and G are sampled:
#   SHARP = single point sampling.
#   PIXEL = uniform average in 1-pixel window.
#   SMOOTH = Hann weighted average in 2-pixel window.

# 1-pixel sampled Z, 2-pixel sampled gradient,
# analytic gradient out, no noise
PIXEL_SMOOTH_ANAGRAD_TESTS := \
  00񓱂1񔄮5�3.00�0.000�0.000 \
  05񔄮5񔘛1�1.00�0.000�0.000 \
  06񔄮5񔘛1�1.00�0.000�0.000 \
  07񔄮5񔘛1�1.00�0.000�0.000 \
  08񔄮5񔘛1�8.00�0.000�0.000 \
  09񔄮5񔘛1�3.00�0.000�0.000 \
  17񔄮5񔘛1�0.50�0.000�0.000
  
FOO := \
  17񔄮5񔘛1�0.50�0.000�0.000
              
TESTS := \
  ${FOO}

TESTS_DONE := \
  ${PIXEL_SMOOTH_ANAGRAD_TESTS}

TESTS_DONE :=

SHELL =	/bin/sh

# PSVIEW := ghostview
# PSVIEW := gv
PSVIEW := evince

.PHONY:: \
  runtest-all show-all runtest \
  make-fni-files \
  plotheight plotslopes plotweights plotnormals cleanplots \
  histheight histslopes histweights histnormals cleanhists \
  showheight showslopes showweights shownormals cleanshows \
  viewheight viewslopes viewweights viewnormals cleanviews

all: runtest-all

# ====================================================================
# Cleanup

clean::
	-/bin/rm -f *.fni *.pgm *.ppm *.eps

# ====================================================================
# Remove only plot files:

tidy:
	-/bin/rm -f *.pgm *.ppm *.eps

# ====================================================================
# Running tests

runtest-all: 
	for tt in ${TESTS} ; do \
          ${MAKE} TEST=$$tt runtest ; \
        done

show-all: 
	for tt in ${TESTS} ; do \
          ${MAKE} TEST=$$tt showheight showslopes showweight shownormals ; \
        done

TEST := 
ifneq "/${TEST}" "/"
#######################################################################
# Recursive "make" to create the test ${FUNC} with noise ${SIGMA}

TESTARGS := ${subst �, ,${TEST}}

FUNC           := ${word 1, ${TESTARGS}}
LZ             := ${word 2, ${TESTARGS}}
NZ             := ${word 3, ${TESTARGS}}
LG             := ${word 4, ${TESTARGS}}
NG             := ${word 5, ${TESTARGS}}
GRADTYPE       := ${word 6, ${TESTARGS}}
MAXGDIFF       := ${word 7, ${TESTARGS}}
SIGMAG         := ${word 8, ${TESTARGS}}
SIGMAW         := ${word 9, ${TESTARGS}}

NUMGRAD_OPT := BUG
ifeq "/${GRADTYPE}" "/N"
  NUMGRAD_OPT := -numGrad
endif
ifeq "/${GRADTYPE}" "/A"
  NUMGRAD_OPT := 
endif

# Tags for file names:
MAXGDIFF_TAG := ${subst .,,${MAXGDIFF}}
SIGMAG_TAG    := ${subst .,,${SIGMAG}}
SIGMAW_TAG    := ${subst .,,${SIGMAW}}

PARMS_TAG1 := ${LZ}-${NZ}-${LG}-${NG}-${GRADTYPE}
PARMS_TAG2 := ${MAXGDIFF_TAG}-${SIGMAG_TAG}-${SIGMAW_TAG}

OUT_PREF := out/test-${FUNC}-${PARMS_TAG1}-${PARMS_TAG2}
OUT_Z := ${OUT_PREF}-Z
OUT_G := ${OUT_PREF}-G
OUT_W := ${OUT_PREF}-W
OUT_GX := ${OUT_PREF}-GX
OUT_GDY := ${OUT_PREF}-GY
OUT_N := ${OUT_PREF}-N
OUT_NX := ${OUT_PREF}-NX
OUT_NY := ${OUT_PREF}-NY
OUT_NZ := ${OUT_PREF}-NZ

ifeq "/${VIEW}" "/YES"
  VIEWACTIONS := cleanviews viewheight viewslopes viewweight viewnormals
else
  VIEWACTIONS := cleanviews
endif

ifeq "/${SHOW}" "/YES"
  SHOWACTIONS := cleanshows showheight showslopes showweight shownormals
else
  SHOWACTIONS := cleanshows
endif

ifeq "/${PLOT}" "/YES"
  PLOTACTIONS := cleanplots plotheight plotslopes plotweight plotnormals
else
  PLOTACTIONS := cleanplots
endif

ifeq "/${HIST}" "/YES"
  HISTACTIONS := cleanhists histheight histslopes histweight histnormals
else
  HISTACTIONS := cleanhists
endif

runtest: make-fni-files ${VIEWACTIONS} ${SHOWACTIONS} ${PLOTACTIONS} ${HISTACTIONS}

make-fni-files: ${PROGDIR}/${PROG}
	@echo "TEST = ${TEST}"
	${PROGDIR}/${PROG} \
            -function ${FUNC} \
            -size ${NX} ${NY} \
            -smoothZ ${LZ} ${NZ} \
            -smoothG ${LG} ${NG} \
            ${NUMGRAD_OPT} \
            -maxGDiff ${MAXGDIFF} \
            -noiseG ${SIGMAG} \
            -noiseW ${SIGMAW} \
            -outPrefix ${OUT_PREF}

# ======================================================================
# 3D view of image with fni_view(1)

viewheight: ${OUT_Z}.fni
	fni_view \
            -channel 0 \
	    -texture ${OUT_N}.fni \
            ${OUT_Z}.fni

viewslopes: ${OUT_G}.fni
	fni_view \
            -channel 0 \
            -scale 5 \
            ${OUT_G}.fni

viewweight: ${OUT_W}.fni
	fni_view \
            -channel 0 \
	    ${OUT_W}.fni

viewnormals: ${OUT_N}.fni
	fni_view \
            -channel 0 \
            -scale 15 \
            ${OUT_N}.fni

cleanviews: 

# ======================================================================
# Show image converted to PPM with fni_to_pnm

showheight: ${OUT_Z}.fni
	fni_to_pnm \
            -channel 0 \
            < ${OUT_Z}.fni \
            > ${OUT_Z}.pgm
	-display -title '%f' -filter box -resize '400%' ${OUT_Z}.pgm

showslopes: ${OUT_G}.fni
	fni_to_pnm \
            -channels 0 1 0 \
            -center 0 -uniform \
            < ${OUT_G}.fni \
            > ${OUT_G}.ppm
	-display -title '%f' -filter box -resize '400%' ${OUT_G}.ppm

showweight: ${OUT_W}.fni
	fni_to_pnm \
            -channel 0 \
            -min 0 \
            -max 1 \
            < ${OUT_W}.fni \
            > ${OUT_W}.pgm && \
          display -title '%f' -filter box -resize '400%' ${OUT_W}.pgm

shownormals: ${OUT_N}.fni
	fni_to_pnm \
            -channels 0 1 2 \
            -min -1 \
            -max +1 \
            < ${OUT_N}.fni \
            > ${OUT_N}.ppm
	-display -title '%f' -filter box -resize '400%' ${OUT_N}.ppm

cleanshows: 
	/bin/rm -f ${OUT_Z}.pgm 
	/bin/rm -f ${OUT_G}.ppm 
	/bin/rm -f ${OUT_W}.ppm 
	/bin/rm -f ${OUT_N}.ppm

# ======================================================================
# 3D Postscript plots of samples, with fni_plot.sh(1)

plotheight: ${OUT_Z}.fni
	fni_plot.sh \
            -channel 0 -title "Z" \
            < ${OUT_Z}.fni \
            > ${OUT_Z}.eps && \
          ${PSVIEW} ${OUT_Z}.eps

plotslopes: ${OUT_G}.fni
	fni_plot.sh \
            -channel 0 -title "dZ/dX" \
            < ${OUT_G}.fni \
            > ${OUT_GX}.eps && \
          ${PSVIEW} ${OUT_GX}.eps
	fni_plot.sh \
            -channel 1 -title "dZ/dY" \
            < ${OUT_G}.fni \
            > ${OUT_GDY}.eps && \
          ${PSVIEW} ${OUT_GDY}.eps

plotweight: ${OUT_W}.fni
	fni_plot.sh \
            -channel 0 -title "W" \
            < ${OUT_W}.fni \
            > ${OUT_W}.eps && \
          ${PSVIEW} ${OUT_W}.eps

plotnormals: ${OUT_N}.fni
	fni_plot.sh \
            -channel 0 -title "nrm.X" \
            < ${OUT_N}.fni \
            > ${OUT_NZ}.eps && \
          ${PSVIEW} ${OUT_NZ}.eps
	fni_plot.sh \
            -channel 1 -title "nrm.Y" \
            < ${OUT_N}.fni \
            > ${OUT_NY}.eps && \
          ${PSVIEW} ${OUT_NY}.eps
	fni_plot.sh \
            -channel 2 -title "nrm.Z" \
            < ${OUT_N}.fni \
            > ${OUT_NZ}.eps && \
          ${PSVIEW} ${OUT_NZ}.eps

cleanplots: 
	/bin/rm -f ${OUT_Z}.eps 
	/bin/rm -f ${OUT_GX}.eps ${OUT_GDY}.eps
	/bin/rm -f ${OUT_W}.eps
	/bin/rm -f ${OUT_NX}.eps ${OUT_NY}.eps ${OUT_NZ}.eps

# ======================================================================
# Postscript plots of value histograms, with fni_hist(1)

histheight: ${OUT_Z}.fni
	fni_hist \
            -channel 0 -title "Z" \
            -step 0.250 \
            < ${OUT_Z}.fni \
            > ${OUT_Z}-h.eps && \
          ${PSVIEW} ${OUT_Z}-h.eps

histslopes: ${OUT_G}.fni
	fni_hist \
            -channel 0 -title "dZ/DX" \
            -step 0.250 \
            < ${OUT_G}.fni \
            > ${OUT_GX}-h.eps && \
          ${PSVIEW} ${OUT_GX}-h.eps
	fni_hist \
            -channel 1 -title "dZ/dY" \
            -step 0.250 \
            < ${OUT_G}.fni \
            > ${OUT_GDY}-h.eps && \
          ${PSVIEW} ${OUT_GDY}-h.eps

histweight: ${OUT_W}.fni
	fni_hist \
            -channel 0 -title "W" \
            -step 0.250 \
            < ${OUT_W}.fni \
            > ${OUT_W}-h.eps && \
          ${PSVIEW} ${OUT_W}-h.eps

histnormals: ${OUT_N}.fni
	@echo "** don't know how to make normal histograms"; exit 1

cleanhists: 
	/bin/rm -f ${OUT_Z}-h.eps
	/bin/rm -f ${OUT_GX}-h.eps ${OUT_GDY}-h.eps
	/bin/rm -f ${OUT_W}-h.eps
	/bin/rm -f ${OUT_NX}-h.eps ${OUT_NY}-h.eps ${OUT_NZ}-h.eps

# 
# End make with ${TEST}
######################################################################
endif
