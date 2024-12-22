# Last edited on 2019-04-09 18:44:28 by jstolfi

  
PROGS_MISSING_LIBS := \
  
PROGS_TO_FINISH := \
  LATER/make_sphere_normal_map \
  LATER/fni_high_dyn \
  LATER/fni_arith \
  LATER/fit_sphere_to_photo \
  LATER/virtual_gauge \
  LATER/outlines3d \
  LATER/fni_photo_correct \
  LATER/fni_photo_calib \

IGNOREDIRS := \
  ${PROGS_TO_FINISH}

ACTIONS := depend build install

all: actions

include ${STOLFIHOME}/programs/c/GENERIC-ROOT-DIR.make
