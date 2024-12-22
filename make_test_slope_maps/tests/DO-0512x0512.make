# Last edited on 2018-06-30 23:25:08 by stolfilocal

# To be included by the main Makefile

VIEW := YES
SHOW := YES
PLOT := NO
HIST := NO

# ----------------------------------------------------------------------
# Size of slope map (4 digits)

NX = 0512
NY = 0512

include ALL-TESTS.make

FUNCTIONS := 24:25:26:27
              
TESTS := \
  ${PIXEL_SMOOTH_ANAGRAD_TESTS}

NON_TESTS := \
  22¦1¦05¦2¦11¦N¦1.00¦0.000¦0.000 \
  23¦1¦05¦2¦11¦N¦1.00¦0.000¦0.000 \

include COMMON.make
