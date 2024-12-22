# Last edited on 2012-01-15 23:49:09 by stolfilocal

# To be included by the main Makefile

VIEW := NO
SHOW := YES
PLOT := NO
HIST := NO

# ----------------------------------------------------------------------
# Size of slope map (4 digits)

NX = 0032
NY = 0032

include ALL-TESTS.make
 
FUNCTIONS := 21
             
TESTS := \
  ${PIXEL_SMOOTH_ANAGRAD_TESTS}

include COMMON.make
