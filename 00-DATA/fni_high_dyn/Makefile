#Last edited on 2010-03-25 08:41:48 by stolfi

PGM_FILES := ${wildcard *.pgm}
PPM_FILES := ${wildcard *.ppm}

.PHONY: all \
  pgm-histograms pgm-hist-single \
  ppm-histograms ppm-hist-single ppm-channel-hist-single

all: pgm-histograms ppm-histograms

pgm-histograms:
	for f in ${PGM_FILES} ; do \
          ${MAKE} PGM_FILE=$$f pgm-hist-single ; \
        done
        
ppm-histograms:
	for f in ${PPM_FILES} ; do \
          ${MAKE} PPM_FILE=$$f ppm-hist-single ; \
        done
        
########################################################################
# Recursive make - requires ${PGM_FILE}
ifneq "/${PGM_FILE}" "/"

PGM_HIST_FILE := ${subst .pgm,-pgm.his,${PGM_FILE}}
PGM_PLOT_FILE := ${subst .pgm,-pgm.png,${PGM_FILE}}

# pgm-hist-single: pgm-clean-single ${PGM_PLOT_FILE}
pgm-hist-single: ${PGM_PLOT_FILE}

pgm-clean-single: 
	-rm -f ${PGM_HIST_FILE} ${PGM_PLOT_FILE} 

${PGM_PLOT_FILE}: ${PGM_HIST_FILE}
	plot_pgm_hist.sh ${PGM_HIST_FILE} ${PGM_PLOT_FILE}
	-display ${PGM_PLOT_FILE}

${PGM_HIST_FILE}: ${PGM_FILE}
	pgmhist < ${PGM_FILE} > ${PGM_HIST_FILE}


endif
# End make ${PGM_FILE}
########################################################################
        
########################################################################
# Recursive make - requires ${PPM_FILE}
ifneq "/${PPM_FILE}" "/"

# ppm-hist-single: ppm-clean-single
ppm-hist-single: 
	for ch in 0 1 2 ; do \
          ${MAKE} CHANNEL=$$ch PPM_FILE=${PPM_FILE} ppm-channel-hist-single ; \
        done
        

ppm-clean-single: 
	for ch in 0 1 2 ; do \
          ${MAKE} CHANNEL=$$ch PPM_FILE=${PPM_FILE} ppm-channel-clean-single ; \
        done
        
########################################################################
# Recursive make - requires ${CHANNEL}
ifneq "/${CHANNEL}" "/"

ifeq "/${CHANNEL}" "/0"
  CHANNEL_PGM_FILE := noname.red
endif
ifeq "/${CHANNEL}" "/1"
  CHANNEL_PGM_FILE := noname.grn
endif
ifeq "/${CHANNEL}" "/2"
  CHANNEL_PGM_FILE := noname.blu
endif

CHANNEL_HIST_FILE := ${subst .ppm,-ppm-c${CHANNEL}.his,${PPM_FILE}}
CHANNEL_PLOT_FILE := ${subst .ppm,-ppm-c${CHANNEL}.png,${PPM_FILE}}

# ppm-channel-hist-single: ppm-channel-clean-single ${CHANNEL_PLOT_FILE}
ppm-channel-hist-single: ${CHANNEL_PLOT_FILE}

ppm-channel-clean-single: 
	-rm -f ${CHANNEL_HIST_FILE} ${CHANNEL_PLOT_FILE} 

${CHANNEL_PLOT_FILE}: ${CHANNEL_HIST_FILE}
	plot_pgm_hist.sh ${CHANNEL_HIST_FILE} ${CHANNEL_PLOT_FILE}
	-display ${CHANNEL_PLOT_FILE}

${CHANNEL_HIST_FILE}: ${PPM_FILE}
	cat ${PPM_FILE} | ppmtorgb3
	pgmhist < ${CHANNEL_PGM_FILE} > ${CHANNEL_HIST_FILE}
	echo rm -f noname.red noname.grn noname.blu

endif
# End make ${CHANNEL}
########################################################################

endif
# End make ${PPM_FILE}
########################################################################
