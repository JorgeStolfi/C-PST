#! /bin/bash -f
# Last edited on 2010-06-22 10:54:49 by stolfi

function mix() {
  tag="$1"; shift
  sa="$1"; shift; xa=`echo "${sa}" | tr -d '.'`
  ima="$1"; shift;
  sb="$1"; shift; xb=`echo "${sb}" | tr -d '.'`
  imb="$1"; shift;
  oname="${tag}-${xb}"
  pnmxarith -mix ${sa} ${sb} ${ima}.ppm ${imb}.ppm > ${oname}.ppm;
  pnm_to_fni -min 0 -max 1 < ${oname}.ppm > ${oname}.fni
}

# A test dataset with offset:
mix t1 0.25 base-o 0.25 base-g
mix t1 0.25 base-o 0.50 base-g
mix t1 0.25 base-o 0.75 base-g

# A test dataset without offset:
mix t2 0.00 base-o 0.25 base-g
mix t2 0.00 base-o 0.50 base-g
mix t2 0.00 base-o 0.75 base-g

# A test dataset with parameter shift:
mix t3 0.25 base-og 0.25 base-g
mix t3 0.25 base-og 0.50 base-g
mix t3 0.25 base-og 0.75 base-g

display -title '%f' *.ppm 
