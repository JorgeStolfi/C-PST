#! /bin/bash
# Last edited on 2010-03-25 22:28:28 by stolfi

dat_file="$1"; shift
png_file="$1"; shift
img_files=( $@ )
tmp_prefix="/tmp/$$-p"
tmp_files=( )

i=4;
k=1;
while [[ ${k} -lt ${#img_files[@]} ]] ; do
  tmp_png_file="${tmp_prefix}-${k}.png"
  gnuplot <<EOF
  set terminal png truecolor medium size 320,300 \
    xffffff x000000 x333333 \
    x0000ff xff0000 x007700 xff7700 \
    x0055ff xaa00ff x773300 x5500ff
  set output "${tmp_png_file}"
  set xrange [-0.05:1.05]
  set yrange [-0.05:1.05]
  set ylabel "${img_files[${k}]}"
  set xlabel "${img_files[$((k - 1))]}"
  set nokey
  plot "${dat_file}" using ${i}:$((i + 1)) with points 
  quit
EOF
  tmp_files=( ${tmp_files[@]} ${tmp_png_file} )
  i=$(( ${i} + 1 ))
  k=$(( ${k} + 1 ))
done

convert ${tmp_files[@]} +append ${png_file}

rm -f ${tmp_files[@]}
