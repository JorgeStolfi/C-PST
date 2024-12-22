#!/bin/bash
# Last edited on 2010-03-20 17:11:20 by stolfi

test_folder=$(pwd)
lights_folder=${test_folder}/lights
results_folder=${test_folder}/results
temp_folder=/tmp
iext=ppm
oext=fni

info_folder=${test_folder}/gauge_coords

light_set=( 0 1 2 3 )

# gauge_set=( A B C D E F G H I J K L M  )
gauge_set=( B )

# exposure_set=( 300 400 500  )
# exposure_set=(100)
exposure_set=( 300 )

function cvf() {
  # Convert PNM or FNI file $1 to PNG file $2
  afile="$1"; shift;
  bfile="$1"; shift;
  aext="${afile##*.}"
  if [[ ( "/${aext}" == "/pgm" ) || ( "/${aext}" == "/ppm" ) ]]; then
    convert ${afile} ${bfile}
  elif [[ "/${aext}" == "/fni" ]]; then
    cat ${afile} | fni_to_pnm -min 0 -max 1 | convert PNM:- ${bfile}
  fi
}

for exposure in ${exposure_set[@]}  ; do
  mkdir -p results/${exposure}
  for gab_sufix in ${gauge_set[@]} ; do
  #   GCenterX=`head -1 ${test_folder}/Gab_Extract/t-${gab_sufix}-clip.epar | cut -d" "  -f2`
  #   GCenterY=`head -1 ${test_folder}/Gab_Extract/t-${gab_sufix}-clip.epar | cut -d" "  -f3`
  #   GRadius=`head -2 ${test_folder}/Gab_Extract/t-${gab_sufix}-clip.epar |tail -1 | cut -d" "  -f2`
    
    GCenterX=`head -1 ${info_folder}/t-${gab_sufix}-clip.epar | cut -d" "  -f2`
    GCenterY=`head -1 ${info_folder}/t-${gab_sufix}-clip.epar | cut -d" "  -f3`
    GRadius=`head -2 ${info_folder}/t-${gab_sufix}-clip.epar |tail -1 | cut -d" "  -f2` 
    rowfiles=()
    indexfile="results/${exposure}/results_G${gab_sufix}.png"
    rm -f ${indexfile}
    for i in ${light_set[@]} ; do
      num=`printf "%02d" ${i}` 
      
      ifile="data/${exposure}/im_G${gab_sufix}_L${num}.${iext}"
      ifile_png="data/${exposure}/im_G${gab_sufix}_L${num}.png"

      oprefix="results/${exposure}/im_G${gab_sufix}_L${num}"
      
      pfile="${oprefix}-parms.txt"

      mfile="${oprefix}-imask.${oext}"
      mfile_png="${oprefix}-imask.png"
      
      ofile="${oprefix}.${oext}"
      ofile_png="${oprefix}.png"

      rowfile_png="${oprefix}_row.png"
#       convert images/${exposure}/im${i}.bmp  ${ifile}
      rm -f ${pfile} ${ofile} ${ofile_png} ${mfile} ${mfile_png}
      ../virtual_gauge \
	-gauge \
            image ${ifile} \
	    center ${GCenterX} ${GCenterY} \
	    radius ${GRadius} \
            albedo 1.0 1.0 1.0 \
 	-backPlane \
	-paramsOut ${pfile} \
	-maskOut ${mfile} \
	-virtual \
            image ${ofile} \
            albedo 0.9 0.9 0.9
            
      # Put the three images side by side:
      cvf ${ifile} ${ifile_png}
      iofiles=( ${ifile_png} )
      if [[ -s ${ofile} ]]; then 
        ls -l ${ofile}
        cvf ${ofile} ${ofile_png}
        iofiles=( ${iofiles[@]} ${ofile_png} )
      fi
      
      if [[ -s ${mfile} ]]; then 
        ls -l ${mfile}
        cvf ${mfile} ${mfile_png}
        iofiles=( ${iofiles[@]} ${mfile_png} )
      fi
      
      echo "iofiles = ${#iofiles[@]}" 1>&2
      if [[ ${#iofiles[@]} -gt 0 ]]; then 
        convert ${iofiles[@]} -background 'black' -gravity center +append ${rowfile_png}
        display ${rowfile_png}
        rowfiles=( ${rowfiles[@]} ${rowfile_png} )
      fi
    done
    if [[ ${#rowfiles[@]} -gt 0 ]]; then
      convert ${rowfiles[@]} -append ${indexfile}
      display ${indexfile}
    fi
  done
done
