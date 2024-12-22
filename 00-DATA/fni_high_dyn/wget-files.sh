#! /bin/bash
# Last edited on 2010-03-25 10:01:31 by stolfi

dir="http://www.cems.uwe.ac.uk/~rfvsarac/correction/gauges"
# for lamp in 0 1 2 3 ; do \
for lamp in 1 2 3 ; do
  wget -nv "${dir}/100/im${lamp}.ppm"  -O "UWE${lamp}_g0100.ppm"
  wget -nv "${dir}/200/im${lamp}.ppm"  -O "UWE${lamp}_g0200.ppm"
  wget -nv "${dir}/300/im${lamp}.ppm"  -O "UWE${lamp}_g0300.ppm"
  wget -nv "${dir}/400/im${lamp}.ppm"  -O "UWE${lamp}_g0400.ppm"
  wget -nv "${dir}/500/im${lamp}.ppm"  -O "UWE${lamp}_g0500.ppm"
  wget -nv "${dir}/750/im${lamp}.ppm"  -O "UWE${lamp}_g0750.ppm"
  wget -nv "${dir}/1000/im${lamp}.ppm" -O "UWE${lamp}_g1000.ppm"
done
