#! /bin/bash
# Last edited on 2006-05-02 18:16:28 by stolfi

for f in \
  g-ms-a-0 \
  g-ms-a-1 \
  g-ms-a-2 \
  g-ms-b-0 \
  g-ms-b-1 \
  g-ms-b-2 \
  g-ms-c-0 \
  g-ms-c-1 \
  g-ms-c-2 ;
do
  echo "${f}";
  cat ${f}.fni \
    | fni_to_pnm -min 0 -max 1 \
    | convert PPM:- ${f}.png
done
