# Tests of the pgmhdyn tool
# Last edited on 2010-03-25 23:44:15 by stolfi

PROG := fni_high_dyn
PROGDIR := ..

# The test images in/B{bbb}_C{ccc}_Y.pgm images were taken
# with the camera on the Asus Eee-Pc 701 with brightness set
# to {bbb} and contrast set to {ccc}.

# Format: {FILENAME}/{VMIN}:{VMAX}

PLOT := YES

THREE_MARS_TESTS_NO_OFFSET := \
  MARS_g050_p000_Y.pgm/010:255 \
  MARS_g100_p000_Y.pgm/010:255 \
  MARS_g200_p000_Y.pgm/020:255 \

THREE_MARS_TESTS_SAME_GAIN := \
  MARS_g100_m050_Y.pgm/000:255 \
  MARS_g100_p000_Y.pgm/010:255 \
  MARS_g100_p050_Y.pgm/150:255 \

THREE_ASUS_TESTS := \
  ASUS_c018_b025_Y.pgm/016:181 \
  ASUS_c018_b125_Y.pgm/016:255 \
  ASUS_c030_b200_Y.pgm/088:255 \

FOUR_ASUS_TESTS := \
  ASUS_c018_b025_Y.pgm/016:181 \
  ASUS_c018_b125_Y.pgm/016:255 \
  ASUS_c030_b125_Y.pgm/016:255 \
  ASUS_c030_b200_Y.pgm/088:255 \

FIVE_ASUS_TESTS := \
  ASUS_c018_b025_Y.pgm/016:181 \
  ASUS_c018_b125_Y.pgm/016:255 \
  ASUS_c030_b025_Y.pgm/016:255 \
  ASUS_c030_b050_Y.pgm/016:255 \
  ASUS_c030_b125_Y.pgm/016:255 \

ALL_ASUS_TESTS := \
  ASUS_c018_b025_Y.pgm/016:181 \
  ASUS_c030_b025_Y.pgm/016:255 \
  ASUS_c030_b050_Y.pgm/016:255 \
  ASUS_c018_b125_Y.pgm/016:255 \
  ASUS_c030_b125_Y.pgm/016:255 \
  ASUS_c018_b200_Y.pgm/088:255 \
  ASUS_c030_b200_Y.pgm/088:255 \
  ASUS_c018_b250_Y.pgm/138:255 \
  ASUS_c030_b250_Y.pgm/138:255
  
THREE_UWE0_TESTS := \
  UWE0_g0100.ppm/000:255 \
  UWE0_g0200.ppm/000:255 \
  UWE0_g0500.ppm/000:255 \
  
ALL_UWE0_TESTS := \
  UWE0_g0100.ppm/000:255 \
  UWE0_g0200.ppm/000:255 \
  UWE0_g0300.ppm/000:255 \
  UWE0_g0400.ppm/000:255 \
  UWE0_g0500.ppm/000:255 \
  UWE0_g0750.ppm/000:255 \
  UWE0_g1000.ppm/000:255 \
  
THREE_UWE1_TESTS := \
  UWE1_g0100.ppm/000:255 \
  UWE1_g0200.ppm/000:255 \
  UWE1_g0500.ppm/000:255 \
  
ALL_UWE1_TESTS := \
  UWE1_g0100.ppm/000:255 \
  UWE1_g0200.ppm/000:255 \
  UWE1_g0300.ppm/000:255 \
  UWE1_g0400.ppm/000:255 \
  UWE1_g0500.ppm/000:255 \
  UWE1_g0750.ppm/000:255 \
  UWE1_g1000.ppm/000:255 \
   
THREE_UWE2_TESTS := \
  UWE2_g0100.ppm/000:255 \
  UWE2_g0200.ppm/000:255 \
  UWE2_g0500.ppm/000:255 \
  
ALL_UWE2_TESTS := \
  UWE2_g0100.ppm/000:255 \
  UWE2_g0200.ppm/000:255 \
  UWE2_g0300.ppm/000:255 \
  UWE2_g0400.ppm/000:255 \
  UWE2_g0500.ppm/000:255 \
  UWE2_g0750.ppm/000:255 \
  UWE2_g1000.ppm/000:255 \
   
THREE_UWE3_TESTS := \
  UWE3_g0100.ppm/000:255 \
  UWE3_g0200.ppm/000:255 \
  UWE3_g0500.ppm/000:255 \
  
ALL_UWE3_TESTS := \
  UWE3_g0100.ppm/000:255 \
  UWE3_g0200.ppm/000:255 \
  UWE3_g0300.ppm/000:255 \
  UWE3_g0400.ppm/000:255 \
  UWE3_g0500.ppm/000:255 \
  UWE3_g0750.ppm/000:255 \
  UWE3_g1000.ppm/000:255 \

# TESTS = ${THREE_MARS_TESTS_NO_OFFSET}
# TESTS = ${THREE_MARS_TESTS_SAME_GAIN}
# TESTS = ${THREE_ASUS_TESTS}
# TESTS = ${FOUR_ASUS_TESTS}
# TESTS = ${FIVE_ASUS_TESTS}
# TESTS = ${THREE_UWE0_TESTS}
# TESTS = ${THREE_UWE1_TESTS}
# TESTS = ${THREE_UWE2_TESTS}
# TESTS = ${THREE_UWE3_TESTS}
TESTS = ${ALL_UWE0_TESTS}

INDIR := in

INFILES := \
  ${addprefix ${INDIR}/, ${subst /,,${dir ${TESTS}}}}

OTDIR := out
OTFILE_FNI := ${OTDIR}/test1.fni
OTFILE_PNM := ${OTDIR}/test1.pgm

MAKEFILE := Makefile

.PHONY:: \
  all debug clean other-actions do-plots do-plot-channel 

all: debug clean ${OTFILE_FNI} other-actions

include ${STOLFIHOME}/programs/c/GENERIC-PROGS-TEST.make

TESTS_MOD := ${addprefix @, ${addsuffix =, ${TESTS}}}

IMAGE_ARGS := \
  ${subst =, / 255 ,${subst @, -image ${INDIR}/,${subst :, / 255 vmax ,${subst /, vmin ,${TESTS_MOD}}}}}

PLOT_PREFIX := ${OTDIR}/test1

ifeq "/${PLOT}" "/YES"
  PLOT_OPT := -plot ${PLOT_PREFIX}
  PLOT_ACTION := do-plots
else
  PLOT_OPT := 
  PLOT_ACTION := 
endif  

debug:
	@echo "INFILES = ${INFILES}"
	@echo "IMAGE_ARGS = ${IMAGE_ARGS}"

${OTFILE_FNI}: ${INFILES} ${MAKEFILE} ${PROGDIR}/${PROG}
	${PROGDIR}/${PROG} \
	    -verbose \
            ${IMAGE_ARGS} \
            ${PLOT_OPT} \
          > ${OTFILE_FNI}
	fni_to_pnm < ${OTFILE_FNI} > ${OTFILE_PNM}
	-display ${OTFILE_PNM} ${INFILES}

other-actions: ${PLOT_ACTION}

do-plots: 
	for pf in ${PLOT_PREFIX}-c*.dat ; do \
          ${MAKE} PLOT_FILE_DAT=$$pf do-plot-channel ; \
        done
        
        
########################################################################
# Recursive make - requires ${PLOT_FILE_DAT}
ifneq "/${PLOT_FILE_DAT}" "/"
        
PLOT_FILE_VV_PNG := ${subst .dat,-VV.png,${PLOT_FILE_DAT}}
PLOT_FILE_VY_PNG := ${subst .dat,-VY.png,${PLOT_FILE_DAT}}
        
do-plot-channel: ${PLOT_FILE_DAT} plot_V_against_Y.sh plot_V_against_V.sh
	plot_V_against_Y.sh ${PLOT_FILE_DAT} ${PLOT_FILE_VY_PNG} ${INFILES}
	-display ${PLOT_FILE_VY_PNG}
	plot_V_against_V.sh ${PLOT_FILE_DAT} ${PLOT_FILE_VV_PNG} ${INFILES}
	-display ${PLOT_FILE_VV_PNG}

endif
# End make ${PLOT_FILE_DAT}
########################################################################

clean::
	rm -f ${OTDIR}/*.p?m ${OTDIR}/*.dat ${OTDIR}/*.png
