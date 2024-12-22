#!/bin/bash
test_sets=( 00 )
charts=( 0 1 )
#gammas=( 045 050 110 200 )
gammas=( 100 )
A=0.4
B=0.0

extract="1"

for i_set in ${test_sets[@]} ; do
	for i_chart in ${charts[@]} ; do
		for i_gamma in ${gammas[@]} ; do
			outchart="tests/f-${i_set}-spots/f-${i_set}-${i_chart}-${i_gamma}-chart"
			outscale="tests/f-${i_set}-spots/f-${i_set}-${i_chart}-${i_gamma}-scale"
			
			if [[ ${extract} == "1" ]] ; then
				fni_nodak_extract \
					-geomFile geomFile.txt \
					`cat tests/f-${i_set}-spots/spotFile_${i_set}_${i_chart}.txt` \
					-chartBorder 2 \
					-outChartSize 400 \
					-yFlip \
					-spotMargin 2.0 \
					-scale 1.0 \
					-outScale ${outscale} 40 40  \
					< tests/f-${i_set}-spots/f-${i_set}-G${i_gamma}-crop.fni \
					> ${outchart}.fni
				fni_to_pnm -min 0 -max 1 < ${outchart}.fni > ${outchart}.ppm
				fni_to_pnm -min 0 -max 1 < ${outscale}.fni > ${outscale}.ppm
			fi
			plot_two_light_scales.sh  \
				${HOME}/Raab/Versoes_${VERSAO_RAAB}/Fontes/fni_nodak_extract/geomFile.txt \
				${outscale}.txt \
				${A} ${B} \
				${outscale}.eps
		done
	done
done