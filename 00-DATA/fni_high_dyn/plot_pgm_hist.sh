#! /bin/bash
# Last edited on 2010-03-23 09:48:05 by stolfi

hfile="$1"; shift
pfile="$1"; shift

cat ${hfile} \
  | gawk \
      ' BEGIN { vmin = 999999; vmax = 0; }
        /^ *[0-9]/ {
          v = $1; n = $2;
          if (n > 0) { 
            if (v > vmax) { vmax = v; }
            if (v < vmin) { vmin = v; }
          }
        }
        END { printf " min = %d max = %d\n", vmin, vmax > "/dev/stderr"; }
      '

gnuplot <<EOF
set terminal png truecolor medium size 640,480 \
  xffffff x000000 x333333 \
  xff0000 x007700 x0000ff xff7700 \
  x0055ff xaa00ff x773300 x5500ff
set output "${pfile}"
set xrange [-1:256]
plot "${hfile}" using 1:2 with histeps
quit
EOF
