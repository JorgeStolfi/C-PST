# Last edited on 2012-12-15 10:13:26 by stolfilocal

PROGDIR := ..
PROG := fit_ellipse_to_photo

# DISPLAY_OPTS := -filter box -resize '400%'
DISPLAY_OPTS := 

# Fields:
#  ${NAME}/${EXT}/${GTAG}/{DEBUG}/${NOTE}
#
#  ${NAME}    Name of input image in "data" directory, sans extension.
#  ${EXT}     Extension of the same (with '.').
#  ${GTAG}    Letter identifying the gauge + digit identifying the test run.
#  ${DEBUG}   Option to generate plots ('Y' or 'N').
#  ${NOTE}    Abitrary note (without embedded blanks or '/').

# The '0' tests have an intial guess very close to the correct answer.
# Other tests have more distant guesses.

TESTS := \
  blocs-d-002-ymn/ppm/E1/N/wooden_donut

TESTS_DONE := \
  blocs-d-002-rgb/ppm/E1/N/wooden_donut \
  rafas-c-005-lum/pgm/A1/N/wood_sphere_wht \
  rafas-c-005-lum/pgm/B1/N/ping_pong_wht \
  balls-b-005-lum/pgm/A1/N/light_bulb \
  balls-b-005-lum/pgm/B1/N/wood_sphere_wht \
  balls-b-005-lum/pgm/C1/N/ping_pong_wht

SMALL_TESTS := \
  balls-t-005-lum/pgm/A0/Y/light_bulb \
   \
  balls-t-005-lum/pgm/B0/Y/wood_sphere_wht \
   \
  balls-t-005-lum/pgm/C0/Y/ping_pong_wht \

BIG_EASY_TESTS := \
  balls-b-005-lum/pgm/A0/N/light_bulb \
  balls-b-005-lum/pgm/B0/N/wood_sphere_wht \
  balls-b-005-lum/pgm/C0/N/ping_pong_wht \
   \
  rafas-c-005-lum/pgm/A0/N/wood_sphere_wht \
  rafas-c-005-lum/pgm/B0/N/ping_pong_wht \
   \
  blocs-d-002-rgb/ppm/A0/N/mouse_ball_12:00 \
  blocs-d-002-rgb/ppm/B0/N/drawer_knob \
  blocs-d-002-rgb/ppm/C0/N/mouse_ball_08:30 \
  blocs-d-002-rgb/ppm/D0/N/mouse_ball_04:30 \
  blocs-d-002-rgb/ppm/E0/N/wooden_donut \
  blocs-d-002-rgb/ppm/F0/N/printed_circle \
  blocs-d-002-rgb/ppm/G0/N/shadow_of_drawer_knob \
   \
  blocs-d-002-ymn/ppm/E0/N/wooden_donut \

BIG_HARD_TESTS := \
  balls-b-005-lum/pgm/A1/N/light_bulb \
  balls-b-005-lum/pgm/A2/N/light_bulb \
   \
  balls-b-005-lum/pgm/B1/N/wood_sphere_wht \
   \
  balls-b-005-lum/pgm/C1/N/ping_pong_wht \
   \
  rafas-c-005-lum/pgm/A1/N/wood_sphere_wht \
   \
  rafas-c-005-lum/pgm/B1/N/ping_pong_wht \
   \
  blocs-d-002-rgb/ppm/A1/N/mouse_ball_12:00 \
  blocs-d-002-rgb/ppm/B1/N/drawer_knob \
  blocs-d-002-rgb/ppm/C1/N/mouse_ball_08:30 \
  blocs-d-002-rgb/ppm/D1/N/mouse_ball_04:30 \
  blocs-d-002-rgb/ppm/E1/N/wooden_donut \
  blocs-d-002-rgb/ppm/F1/N/printed_circle \
  blocs-d-002-rgb/ppm/G1/N/shadow_of_drawer_knob \
   \
  blocs-d-002-ymn/ppm/E1/N/wooden_donut \

all:
	for t in ${TESTS}; do \
          ${MAKE} TEST="$$t" single-test ; \
        done

include ${STOLFIHOME}/programs/c/GENERIC-PROGS-TEST.make

######################################################################
# For recursive make of a single test run.  The client must
# define ${TEST} to be the parameters of the run.

ifneq "/${TEST}" "/"

TEST_FIELDS := ${subst /, , ${TEST}}
NAME :=   ${word  1,${TEST_FIELDS}}
EXT :=    ${word  2,${TEST_FIELDS}}
GTAG :=   ${word  3,${TEST_FIELDS}}
DEBUG :=  ${word  4,${TEST_FIELDS}}
NOTE :=   ${word  5,${TEST_FIELDS}}

SCRIPT := scripts/${NAME}-${EXT}-${GTAG}.sh

IN_PNM_FILE := data/${NAME}.${EXT}

OUT_PREFIX := out/${NAME}-${EXT}-${GTAG}

OUT_EPAR_FILE := ${OUT_PREFIX}-full.epar
OUT_CPAR_FILE := ${OUT_PREFIX}-full.cpar

OUT_IGU_PNM_FILE := ${OUT_PREFIX}-igu.ppm
OUT_FIT_PNM_FILE := ${OUT_PREFIX}-fit.ppm
OUT_FGR_PNM_FILE := ${OUT_PREFIX}-fgr.ppm
OUT_MSK_PNM_FILE := ${OUT_PREFIX}-msk.pgm

OUT_CLIP_IMG_PNM_FILE := ${OUT_PREFIX}-clip-img.${EXT}
OUT_CLIP_MSK_PNM_FILE := ${OUT_PREFIX}-clip-msk.pgm
OUT_CLIP_EPAR_FILE := ${OUT_PREFIX}-clip.epar
OUT_CLIP_CPAR_FILE := ${OUT_PREFIX}-clip.cpar


ifeq "/${DEBUG}" "/Y"
  OUT_CTR_FNI_FILE := ${OUT_PREFIX}-ctr.fni
  OUT_CTR_PNM_FILE := ${OUT_PREFIX}-ctr.pgm
  OUT_CTR_EPS_FILE := ${OUT_PREFIX}-ctr.eps

  OUT_RAD_FNI_FILE := ${OUT_PREFIX}-rad.fni
  OUT_RAD_PNM_FILE := ${OUT_PREFIX}-rad.pgm
  OUT_RAD_EPS_FILE := ${OUT_PREFIX}-rad.eps
  DEBUG_OPT := -debug
endif
ifeq "/${DEBUG}" "/N"
  OUT_CTR_FNI_FILE :=
  OUT_CTR_PNM_FILE :=
  OUT_CTR_EPS_FILE :=

  OUT_RAD_FNI_FILE :=
  OUT_RAD_PNM_FILE :=
  OUT_RAD_EPS_FILE :=
  DEBUG_OPT :=
endif

OUT_PNM_FILES := \
  ${OUT_IGU_PNM_FILE} \
  ${OUT_FIT_PNM_FILE} \
  ${OUT_FGR_PNM_FILE} \
  ${OUT_MSK_PNM_FILE} \
  ${OUT_CTR_PNM_FILE} \
  ${OUT_RAD_PNM_FILE} \
  ${OUT_CLIP_IMG_PNM_FILE} \
  ${OUT_CLIP_MSK_PNM_FILE}

OUT_EPS_FILES := \
  ${OUT_CTR_EPS_FILE} \
  ${OUT_RAD_EPS_FILE}

single-test: ${OUT_EPAR_FILE} ${OUT_PNM_FILES} ${OUT_EPS_FILES}
	display ${DISPLAY_OPTS} ${OUT_PNM_FILES}
ifeq "/${DEBUG}" "/Y"
	display ${OUT_EPS_FILES}
endif

${OUT_EPAR_FILE}: ${IN_PNM_FILE} ${PROGDIR}/${PROG} ${SCRIPT}
	 ${SCRIPT} ${DEBUG_OPT}

# ----------------------------------------------------------------------
# Dummy actions for other output files:

${OUT_IGU_PNM_FILE}: ${OUT_EPAR_FILE}
	ls -l ${OUT_IGU_PNM_FILE}

${OUT_FIT_PNM_FILE}: ${OUT_EPAR_FILE}
	ls -l ${OUT_FIT_PNM_FILE}

${OUT_FGR_PNM_FILE}: ${OUT_EPAR_FILE}
	ls -l ${OUT_FGR_PNM_FILE}

${OUT_MSK_PNM_FILE}: ${OUT_EPAR_FILE}
	ls -l ${OUT_MSK_PNM_FILE}

${OUT_CLIP_IMG_PNM_FILE}: ${OUT_EPAR_FILE}
	ls -l ${OUT_CLIP_IMG_PNM_FILE}

${OUT_CLIP_MSK_PNM_FILE}: ${OUT_EPAR_FILE}
	ls -l ${OUT_CLIP_MSK_PNM_FILE}

${OUT_CPAR_FILE}: ${OUT_EPAR_FILE}
	ls -l ${OUT_CPAR_FILE}
        
${OUT_CLIP_EPAR_FILE}: ${OUT_EPAR_FILE}
	ls -l ${OUT_CLIP_EPAR_FILE}
        
${OUT_CLIP_CPAR_FILE}: ${OUT_EPAR_FILE}
	ls -l ${OUT_CLIP_CPAR_FILE}

# ----------------------------------------------------------------------
# Conversion of diagnostic images and plots to PNM/EPS:
# Only if ${DEBUG} == Y

ifeq "/${DEBUG}" "/Y"

${OUT_CTR_FNI_FILE}: ${OUT_EPAR_FILE}
	ls -l ${OUT_CTR_FNI_FILE}

${OUT_RAD_FNI_FILE}: ${OUT_EPAR_FILE}
	ls -l ${OUT_RAD_FNI_FILE}


${OUT_CTR_PNM_FILE}: ${OUT_CTR_FNI_FILE}
	fni_to_pnm -min 0 < $< | pnmgamma 2.2 | pamflip -tb > $@

${OUT_RAD_PNM_FILE}: ${OUT_RAD_FNI_FILE}
	fni_to_pnm -min 0 < $< | pnmgamma 2.2 | pamflip -tb > $@


${OUT_CTR_EPS_FILE}: ${OUT_CTR_FNI_FILE}
	fni_plot.sh \
          -title "center adjust" \
          < ${OUT_CTR_FNI_FILE} \
          > ${OUT_CTR_EPS_FILE}

${OUT_RAD_EPS_FILE}: ${OUT_RAD_FNI_FILE}
	fni_plot.sh \
          -title "radius/stretch adjust" \
          < ${OUT_RAD_FNI_FILE} \
          > ${OUT_RAD_EPS_FILE}

endif
# End ${DEBUG} == Y section
# ----------------------------------------------------------------------

endif
# End of ${TEST} section.
######################################################################
