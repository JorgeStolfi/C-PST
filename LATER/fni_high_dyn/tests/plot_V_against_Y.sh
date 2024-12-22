#! /bin/bash
# Last edited on 2010-03-23 23:21:25 by stolfi

dat_file="$1"; shift
png_file="$1"; shift
img_files=( $@ )
gpl_file="/tmp/$$.gpl"

cat > ${gpl_file} <<EOF
set terminal png truecolor medium size 640,480 \
  xffffff x000000 x333333 \
  xff0000 x007700 x0000ff xff7700 \
  x0055ff xaa00ff x773300 x5500ff
set output "${png_file}"
set xrange [-0.05:1.05]
EOF

printf "plot " >> ${gpl_file}
sep=""
i=4;
for img in ${img_files[@]} ; do
  printf '%s \\\n' "${sep}" >> ${gpl_file}
  printf '  "%s" using 3:%s with points' "${dat_file}" "${i}" >> ${gpl_file}
  i=$(( ${i} + 1 ))
  sep=","
done

printf '\n' >>${gpl_file}
printf "quit" >>${gpl_file}

gnuplot < ${gpl_file}

rm -f ${gpl_file}
