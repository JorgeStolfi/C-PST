#! /bin/bash
# Last edited on 2010-03-25 11:08:55 by stolfi

lamp="$1"; shift

exdir="${STOLFIHOME}/EXPORT/projects/photo-stereo/images/fni_hygh_dyn/2010-03-25"
 
mv -vi out/test1.fni ${exdir}/UWE${lamp}.fni && gzip ${exdir}/UWE${lamp}.fni
mv -vi out/test1.pgm ${exdir}/UWE${lamp}.pgm
mv -vi out/test1-c00.png ${exdir}/UWE${lamp}-c00.png
mv -vi out/test1-c01.png ${exdir}/UWE${lamp}-c01.png
mv -vi out/test1-c02.png ${exdir}/UWE${lamp}-c02.png
