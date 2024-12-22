# Last edited on 2012-01-15 23:49:39 by stolfilocal

# To be included by the main Makefile

VIEW := NO
SHOW := YES
PLOT := YES
HIST := NO

# ----------------------------------------------------------------------
# Size of slope map (4 digits)

NX := 0064
NY := 0048

include ALL-TESTS.make 
 
FUNCTIONS := ALL

TESTS := \
  ${PIXEL_SMOOTH_ANAGRAD_TESTS} \
  ${PIXEL_SMOOTH_ANAGRAD_NOISYG_TESTS} \
  ${PIXEL_SMOOTH_ANAGRAD_NOISYW_TESTS} \
  ${UNIFORM_WEIGHT_MASK} \
  ${SAMPLING_TESTS}
  
TESTS_NOT := \
  ${SHARP_PIXEL_NUMGRAD_TESTS} \
  ${SHARP_PIXEL_ANAGRAD_TESTS}

include COMMON.make 
