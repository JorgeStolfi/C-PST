# Last edited on 2009-02-25 22:24:08 by stolfi


ifeq "/${KIND}" "/S"
  KIND_OPT := -sphere
  STR_OPT := 
  RES_OPT := resolution ${RES} adjust ${ADJRES}
endif
ifeq "/${KIND}" "/E"
  KIND_OPT := -ellipse
  STR_OPT := stretch adjust ${ADJSTR}
  RES_OPT := 
endif
ifeq "/${KIND}" "/C"
  KIND_OPT := -circle
  STR_OPT := stretch adjust ${ADJSTR}
  RES_OPT := 
endif

${OUT_EPAR_FILE}: Makefile ${IN_PNM_FILE} ${PROGDIR}/${PROG}
	 ${PROGDIR}/${PROG} \
             -image ${IN_PNM_FILE} \
             -minRadius 6 \
             -noise 0.05 \
             ${DEBUG_OPT} \
             ${KIND_OPT} \
               center ${XCTR} ${YCTR} adjust ${ADJCTR} \
               radius ${RADIUS} adjust ${ADJCTR} \
               ${STR_OPT} \
             -camera \
               ${RES_OPT} \
             -outPrefix ${OUT_PREFIX}

# ----------------------------------------------------------------------
# Conversion of input images to PNM, for display:

fni/%.fni: data/%.pgm
	pnm_to_fni -min 0 -max 1 < $< > $@

# ----------------------------------------------------------------------
# Conversion of output images to PNM, for display:

${OUT_IGU_PNM_FILE}: ${OUT_IGU_FNI_FILE}
	fni_to_pnm -min 0 -max 1 < $< | pnmgamma 2.2 | pamflip -tb > $@

${OUT_FIT_PNM_FILE}: ${OUT_FIT_FNI_FILE}
	fni_to_pnm -min 0 -max 1 < $< | pnmgamma 2.2 | pamflip -tb > $@


${OUT_FGR_PNM_FILE}: ${OUT_FGR_FNI_FILE}
	fni_to_pnm -min 0 -max 1 < $< | pnmgamma 2.2 | pamflip -tb > $@


${OUT_MSK_PNM_FILE}: ${OUT_MSK_FNI_FILE}
	fni_to_pnm -min 0 -max 1 < $< | pnmgamma 2.2 | pamflip -tb > $@


${OUT_CLIP_IMG_PNM_FILE}: ${OUT_CLIP_IMG_FNI_FILE}
	fni_to_pnm -min 0 -max 1 < $< | pnmgamma 2.2 | pamflip -tb > $@

${OUT_CLIP_MSK_PNM_FILE}: ${OUT_CLIP_MSK_FNI_FILE}
	fni_to_pnm -min 0 -max 1 < $< | pnmgamma 2.2 | pamflip -tb > $@

