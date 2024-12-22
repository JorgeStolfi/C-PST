#! /bin/bash 
# Last edited on 2012-12-08 21:40:29 by stolfilocal
 
PROG_NAME=${0##*/}
PROG_DESC="make a Postscript plot of a photometric correction table"
PROG_HELP=(
  "${PROG_NAME} \\"
  "\n    [ -title {TITLESRING} ] \\"
  "\n    [ -range {VMIN} {VMAX} ] \\"
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
  "\n  Reads from standard input a photometric correction table,"
  "\n such as the ones created by fni_kodak_adjust(1), and"
  "\n generates an Encapsulated Postscript plot of it,"
  "\n using gnuplot(1)."
  "\n"
  "\n  The \"-range\" option specifies the nominal range of values"
  "\n for vertical scale setting."
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
vrange=0
vmin=
vmax=
while [[ ( $# -ge 1 ) && ( "/$1" =~ /-.* ) ]]; do
  if [[ ( $# -ge 2 ) && ( $1 == "-title" ) ]]; then 
    title="$2"; shift; shift;
  elif [[ ( $# -ge 3 ) && ( $1 == "-range" ) ]]; then 
    vrange=1; vmin="$2"; vmax="$3"; shift; shift; shift;
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
  title="Photometric correction function"
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

# Get number of columns to plot:
tmpnum="${tmp}.num"
gawk '/^NC[ ]*[=]/ { gsub(/[=]/, " = ", $0); print $3; }' ${tmpfni} > ${tmpnum}
NC=`cat ${tmpnum}`
echo "NC = ${NC}" 1>&2

# Preparations for vertical range:
if [[ ${vrange} -ne 0 ]]; then
  rangevars="vmin=(${vmin}); vmax=(${vmax}); dv=0.02*(vmax-vmin)"
  setrange="set xrange [(vmin-dv):(vmax+dv)]; set yrange [(vmin-dv):(vmax+dv)]"
else
  rangevars=""
  setrange=""
fi
  
# Create the gnuplot command file:
tmpplt="${tmp}.gnuplot"
cat > ${tmpplt} <<EOF
set terminal postscript eps color 
set output
set size 2,1.5
${rangevars}
${setrange}
set nokey
set ytics 0.1
set mytics 5
set grid mytics lt 3, lt 0
set title "${title}"
EOF

channel=1
ltype=( 1 2 3 )
it=0
sep=""
printf "plot \\\\\n" >> ${tmpplt}
while [[ ${channel} -lt ${NC} ]]; do
  col=$(( ${channel} + 3))
  echo "channel = ${channel}  file column = ${col}" 1>&2
  printf "%s\"${tmpdat}\" using 3:%d with lines lt %d lw 3.0 \\\\\n" \
      "${sep}" "${col}" "${ltype[${it}]}" \
    >> ${tmpplt}
  sep=','
  it=$(( ${it} + 1 ))
  if [[ ${it} -ge 3 ]]; then it=0; fi
  channel=$(( ${channel} + 1 ))
done

printf "\n" >> ${tmpplt}
printf "quit\n" >> ${tmpplt}

gnuplot < ${tmpplt}

# /bin/rm -f ${tmpfni} ${tmpdat} ${tmpnum} ${tmpplt}
