# Last edited on 2023-02-04 07:02:00 by stolfi

PROG := fni_lin_fit

PROGDIR  := ..

include ${STOLFIHOME}/programs/c/GENERIC-PROGS-TEST.make

TESTS := \
  t1 \
  t2 \
  t3

NON_TESTS :=
  
.PHONY:: run-all run-single

all: run-all

clean:: 
	( cd out && rm *.ppm *.pgm *.fni )

run-all: ; \
  for tst in ${TESTS}; do \
    ${MAKE} TEST_ARGS=$${tst} run-single; \
  done

######################################################################
# Recursive section -- client must define ${TEST}
TEST_ARGS := 
ifneq "/${TEST_ARGS}" "/"

TEST_FIELDS := ${subst :, ,${TEST_ARGS}}
TNAME   := ${word 1, ${TEST_FIELDS}}

OUT_PREFIX := out/${TNAME}

GAIN_FNI := ${OUT_PREFIX}-g.fni
GAIN_PNG := ${OUT_PREFIX}-g.png

OFFS_FNI := ${OUT_PREFIX}-o.fni
OFFS_PNG := ${OUT_PREFIX}-o.png

ORIG_FNI := ${OUT_PREFIX}-s.fni
ORIG_PNG := ${OUT_PREFIX}-s.png

SHOWIMG := display -title '%f'
# PSVIEW := gv
PSVIEW := evince

run-single: ${GAIN_FNI}
	fni_to_pnm -min 0 -max 1 < ${GAIN_FNI} | convert PPM:- ${GAIN_PNG}
	if [[ -s ${OFFS_FNI} ]] ; then \
	  fni_to_pnm -min 0.00 -max 1.00 < ${OFFS_FNI} | convert PPM:- ${OFFS_PNG}; \
        fi
	if [[ -s ${ORIG_FNI} ]] ; then \
	  fni_to_pnm -min -1.00 -max 0.00 < ${ORIG_FNI} | convert PPM:- ${ORIG_PNG}; \
        fi
	-${SHOWIMG} ${OUT_PREFIX}-*.png

out/t1-g.fni: ${wildcard data/t1-*.fni}
	${PROGDIR}/${PROG} \
            -image 0.25 data/t1-025.fni \
            -image 0.50 data/t1-050.fni \
            -image 0.75 data/t1-075.fni \
            -offset ${OFFS_FNI} \
            -gain   ${GAIN_FNI} \
            -verbose

out/t2-g.fni: ${wildcard data/t2-*.fni}
	${PROGDIR}/${PROG} \
            -image 0.25 data/t2-025.fni \
            -image 0.50 data/t2-050.fni \
            -image 0.75 data/t2-075.fni \
            -gain   ${GAIN_FNI} \
            -verbose

out/t3-g.fni: ${wildcard data/t3-*.fni}
	${PROGDIR}/${PROG} \
            -image 0.25 data/t3-025.fni \
            -image 0.50 data/t3-050.fni \
            -image 0.75 data/t3-075.fni \
            -gain   ${GAIN_FNI} \
            -origin ${ORIG_FNI} \
            -verbose

endif
# End ${TEST_ARGS} section
######################################################################
