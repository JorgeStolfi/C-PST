# Last edited on 2008-01-15 00:38:54 by stolfi

SHOW := YES

# TAG:RADIUS:FIELDS:SOURCES:CHANNELS:SCENE

TESTS := \
  t3:020:3:1:1:data/test-3-000 \
  t3:020:3:2:3:data/test-3-000 \
  t4:020:3:3:3:data/test-4-000 \
  t5:020:3:1:1:data/test-5-000 \
  t6:020:3:1:1:data/test-6-000
  
ALL_TESTS :=

SHELL =	/bin/sh

.PHONY:: \
  run-all-tests run-test \
  create-files show-pnms delete-pnms

# all:
all: run-all-tests

# ====================================================================
# Cleanup

clean:
	-/bin/rm -f *.fni *.ppm *.pgm

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

TESTFIELDS  := ${subst :, ,${TESTARGS}}
TAG    := ${word 1,${TESTFIELDS}}
RADIUS    := ${word 2,${TESTFIELDS}}
FIELDS := ${word 3,${TESTFIELDS}}
SOURCES   := ${word 4,${TESTFIELDS}}
CHANNELS  := ${word 5,${TESTFIELDS}}
SCENE     := ${word 6,${TESTFIELDS}}

ifeq "/${SHOW}" "/YES"
  run-test: create-files show-pnms
else
  run-test: create-files delete-pnms
endif

PREFIX := ${TAG}-${RADIUS}-${FIELDS}-${SOURCES}-${CHANNELS}

create-files: make_fake_test make-normal_to_photo-calls
	@echo "TESTFIELDS = ${TESTFIELDS}"
	make_fake_test \
          -radius ${RADIUS} \
          -fields ${FIELDS} \
          -lamps ${SOURCES} \
          -channels ${CHANNELS} \
          -prefix ${PREFIX} \
          < ${SCENE}-dZ.fni

show-pnms: ${PREFIX}-ref-nrm.ppm
	display -title '%f' \
          ${PREFIX}-ref-nrm.ppm \
          ${PREFIX}-S-[0-9].p?m \
          ${PREFIX}-G-a-nrm.ppm \
          ${PREFIX}-G-a-[0-9].p?m

delete-pnms: 
	rm -f \
          ${PREFIX}-ref-nrm.ppm \
          ${PREFIX}-S-[0-9].p?m \
          ${PREFIX}-G-a-nrm.ppm \
          ${PREFIX}-G-a-[0-9].p?m

# 
# End make ${TESTARGS}
######################################################################
endif
