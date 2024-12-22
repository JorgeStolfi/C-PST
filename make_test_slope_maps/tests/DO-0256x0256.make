# Last edited on 2012-01-16 00:04:44 by stolfilocal

# To be included by the main Makefile

VIEW := NO
SHOW := YES
PLOT := NO
HIST := NO

# ----------------------------------------------------------------------
# Size of slope map (4 digits)

NX = 0256
NY = 0256

include ALL-TESTS.make

FUNCTIONS := ALL
              
TESTS := \
  ${PIXEL_SMOOTH_ANAGRAD_TESTS}

NON_TESTS := \
  22¦1¦05¦2¦11¦N¦1.00¦0.000¦0.000 \
  23¦1¦05¦2¦11¦N¦1.00¦0.000¦0.000 \

include COMMON.make
