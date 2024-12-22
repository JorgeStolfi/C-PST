# Last edited on 2009-02-05 12:24:02 by stolfi

PROGDIR := ..
PROG := fit_sphere_to_photo

TESTS := \
  balls-b:005,012,023
  
ALL_TESTS := \
  balls-b:005,012,023 \
  rafas-b:005,006,023

all:
	for t in ${TESTS}; do \
          ${MAKE} TEST="$$t" single-test ; \
        done

include ${STOLFIHOME}/programs/c/GENERIC-PROGS-TEST.make

######################################################################
# For recursive make of a single test run.  The client must
# define ${TEST} to be the parameters of the run.

ifneq "/${TEST}" "/"

COMMA := ,

TEST_FIELDS := ${subst :, , ${TEST}}
NAME :=   ${word 1,${TEST_FIELDS}}
NUMS :=   ${subst ${COMMA}, , ${word 2,${TEST_FIELDS}}}

IN_FNI_FILES := ${addprefix fni/${NAME}-, ${addsuffix .fni, ${NUMS}}}

OUT_PREFIX := out/${NAME}

OUT_FILE := ${OUT_PREFIX}-sphere.parms

single-test: ${OUT_FILE}

${OUT_FILE}: ${IN_FNI_FILES} ${PROGDIR}/${PROG}
	 ${PROGDIR}/${PROG} \
             -images ${IN_FNI_FILES} \
             -sphere \
               radius 84 adjust 1 \
               center 126 179 adjust 1 \
               stretch 2.23 -0.62 adjust 0.5 \
               step 1 \
             -lamp direction 0 0 1 radius 0.1 \
             -minNormalZ 0.2 \
             -iterations 10 \
             -outPrefix ${OUT_PREFIX}
         
fni/%.fni: data/%.pgm
	pnm_to_fni -min 0 -max 1 < $< > $@

endif
# End of ${TEST} section.
######################################################################
