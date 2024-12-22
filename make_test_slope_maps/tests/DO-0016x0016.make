# Last edited on 2012-01-15 23:49:24 by stolfilocal

# To be included by the main Makefile

VIEW := NO
SHOW := YES
PLOT := NO
HIST := NO

# ----------------------------------------------------------------------
# Size of slope map (4 digits)

NX = 0016
NY = 0016

include ALL-TESTS.make 

FUNCTIONS := ALL
              
TESTS := \
  ${PIXEL_SMOOTH_ANAGRAD_TESTS}

TESTS_DONE := \
  ${PIXEL_SMOOTH_ANAGRAD_TESTS}

TESTS_DONE :=

include COMMON.make
