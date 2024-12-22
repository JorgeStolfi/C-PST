#! /bin/bash 
# Last edited on 2012-12-08 21:39:21 by stolfilocal
 
PROG_NAME=${0##*/}
PROG_DESC="make Postscript plots of a function basis for photometric correction"
PROG_HELP=(
  "${PROG_NAME} \\"
  "\n    [ -title {TITLESRING} ] \\"
  "\n    [ -index {IX} ].. \\"
  "\n    [ -indices {IX1} {IX2} ].. \\"
  "\n    [ -xrange {XMIN} {XMAX} ] \\"
  "\n    [ -yrange {YMIN} {YMAX} ] \\"
  "\n    < {INFILE}.tbl > {OUTFILE}.eps"
)
PROG_INFO=(
  "\nNAME"
  "\n  ${PROG_NAME} - ${PROG_DESC}."
  "\n"
  "\nSYNOPSIS"
  "\n  ${PROG_HELP[@]}"
  "\n"
  "\nDESCRIPTION"
  "\n  Reads from standard input a FNI file contaning sample"
  "\n values from a function basis for photometric correction,"
  "\n such as the bases implemented in {pst_kodak.h}, and"
  "\n generates an Encapsulated Postscript plot of selected elements,"
  "\n using gnuplot(1)."
  "\n"
  "\n  The \"-xrange\" and \"-yrange\" options specify the nominal range of values"
  "\n for horizontal and vertical scale setting."
  "\n"
  "\n  The \"-index\" option specifies which element of the basis"
  "\n to show in the plot.  It may be given multiple times to show"
  "\n two or more elements on the same plot.  The option \"-indices"
  "\n {IX1} {IX2}\" is equivalent to \"-index {IX}\" for all {IX}"
  "\n from {IX1} to {IX2}, inclusive."
  "\n"
  "\n  The script assumes that the file has only one row of pixels, and"
  "\n that each column corresponds to a different argument"
  "\n value {X}.  The sample in channel 0 is the value of {X}.  The"
  "\n result of evaluating basis element number {IX} at"
  "\n the argument {X} should be channel number {IX+1} of"
  "\n that same pixel."
  "\n ."
  "\n"
  "\nAUTHOR"
  "\n  Created 2006-05-12 by Jorge Stolfi, Unicamp"
)

# ----------------------------------------------------------------------
# INTERNAL OPTIONS

# ----------------------------------------------------------------------
# COMMAND LINE PARSING

# Parse command line switches: 
title=""
xrange=0
xmin=
xmax=
yrange=1
ymin="-1.5"
ymax="+1.5"
indices=( )
while [[ ( $# -ge 1 ) && ( "/$1" =~ /-.* ) ]]; do
  if [[ ( $# -ge 2 ) && ( $1 == "-title" ) ]]; then 
    title="$2"; shift; shift;
  elif [[ ( $# -ge 3 ) && ( $1 == "-xrange" ) ]]; then 
    xrange=1; xmin="$2"; xmax="$3"; shift; shift; shift;
   elif [[ ( $# -ge 3 ) && ( $1 == "-yrange" ) ]]; then 
    yrange=1; ymin="$2"; ymax="$3"; shift; shift; shift;
  elif [[ ( $# -ge 2 ) && ( $1 == "-index" ) ]]; then 
    indices=( ${indices[@]} "$2"); shift; shift;
  elif [[ ( $# -ge 3 ) && ( $1 == "-indices" ) ]]; then 
    ini="$2"; fin="$3";
    indices=( ${indices[@]} `count ${ini} ${fin}`); 
    shift; shift; shift;
  elif [[ ( $# -ge 1 ) && ( ( "/$1" == "/-help" ) || ( "/$1" == "/--help" ) ) ]]; then 
    echo -e "usage:\n  ${PROG_HELP[@]}"; exit 0;
  elif [[ ( $# -ge 1 ) && ( ( "/$1" == "/-info" ) || ( "/$1" == "/--info" ) ) ]]; then 
    echo -e "${PROG_INFO[@]}"; exit 0;
  else
    echo "unknown option $1" 1>&2 ;
    echo -e "usage:\n  ${PROG_HELP[@]}" 1>&2 ; exit 1 
  fi
done 

if [[ "/${title}" == "/" ]]; then
  title="Photometric correction basis"
fi

if [[ ${#indices[@]} -eq 0 ]]; then
  echo "no \"-index\" specified" 1>&2 ;
  echo -e "usage:\n  ${PROG_HELP[@]}" 1>&2 ; exit 1 
fi

# Get positional parameters

# Check for leftover arguments:
if [[ $# -gt 0 ]]; then
  echo 'excess arguments "'"$1"'" ...' 1>&2 ;
  echo -e "usage:\n  ${PROG_HELP[@]}" 1>&2 ; exit 1 
fi

# END COMMAND LINE PARSING
# ----------------------------------------------------------------------

# Prefix for temporary file names
tmp="/tmp/$$"

# Save input data in temp file:
tmpfni="${tmp}.fni"
cat > ${tmpfni}

# Extract plottable data, save in another temp file:
tmpdat="${tmp}.dat"
gawk '/^[ ]*[-+]?[0-9]/ { print; }' ${tmpfni} > ${tmpdat}

# Preparations for vertical range:
if [[ ${yrange} -ne 0 ]]; then
  yrangevars="ymin=(${ymin}); ymax=(${ymax}); dv=0.02*(ymax-ymin)"
  setyrange="set yrange [(ymin-dv):(ymax+dv)]"
else
  yrangevars=""
  setyrange=""
fi
if [[ ${xrange} -ne 0 ]]; then
  xrangevars="xmin=(${xmin}); xmax=(${xmax}); dv=0.02*(xmax-xmin)"
  setxrange="set xrange [(xmin-dv):(xmax+dv)]"
else
  xrangevars=""
  setxrange=""
fi
  
# Create the gnuplot command file:
tmpplt="${tmp}.gnuplot"
cat > ${tmpplt} <<EOF
set terminal postscript eps color 
set output
set size 2,0.75
${xrangevars}
${setxrange}
${yrangevars}
${setyrange}
set xzeroaxis 
set yzeroaxis
set nokey
set ytics 0.5
set mytics 5
set grid mytics lt 0, lt 3
set title "${title}"
EOF

ltype=( 1 2 3 )
itype=0
sep=""
iplot=0;
printf "plot \\\\\n" >> ${tmpplt}
while [[ ${iplot} -lt ${#indices[@]} ]]; do
  ix=${indices[${iplot}]}
  channel=$(( ${ix} + 1 ))
  printf "%s\"${tmpdat}\" using 3:%d title \"bas[%02d]\" with lines lt %d lw 3.0 \\\\\n" \
      "${sep}" "$(( ${channel} + 3))" "${ix}" "${ltype[${itype}]}" \
    >> ${tmpplt}
  sep=','
  itype=$(( ${itype} + 1 ))
  if [[ ${itype} -ge 3 ]]; then itype=0; fi
  iplot=$(( ${iplot} + 1 ))
done

printf "\n" >> ${tmpplt}
printf "quit\n" >> ${tmpplt}

gnuplot < ${tmpplt}

# /bin/rm -f ${tmpfni} ${tmpdat} ${tmpnum} ${tmpplt}
