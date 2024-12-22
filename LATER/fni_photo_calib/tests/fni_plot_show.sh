#! /bin/bash
# Last edited on 2012-12-15 10:12:14 by stolfilocal
 
PROG_NAME=${0##*/}
PROG_DESC="create an  EPS plot of a FNI image and display it"
PROG_HELP=(
  "  ${PROG_NAME} \\"
  "\n    [ -rows ] \\"
  "\n    [ -blur {HNUM} {VNUM} ] \\"
  "\n    [ -kodak ] \\"
  "\n    [ -range {VMIN} {VMAX} ] \\"
  "\n    {NAME} {CHANNEL}"
)
PROG_INFO=(
  "\nNAME"
  "\n  ${PROG_NAME} - ${PROG_DESC}."
  "\n"
  "\nSYNOPSIS"
  "\n${PROG_HELP[@]}"
  "\n"
  "\nDESCRIPTION"
  "\n  Reads the image file \"{NAME}.fni\" and creates an Encapsulated"
  "\n PostScript file \"{NAME}.eps\" with a plot of the intensities"
  "\n of the selected {CHANNEL}, using fni_plot.sh(1).  Then shows that"
  "\n file with ghostview(1)."
  "\n"
  "\n  If \"-blur\" is used, the image is passed through a"
  "\n smoothing filter with a window of width {HNUM} and"
  "\n height {VNUM}."
  "\n"
  "\n  The \"-rows\", \"-range\", and \"-kodak\" options are"
  "\n passed to fni_plot.sh(1)."
  "\nAUTHOR"
  "\n  Created 2006-04-16 by Jorge Stolfi, Unicamp"
)

# ----------------------------------------------------------------------
# INTERNAL OPTIONS

# ----------------------------------------------------------------------
# COMMAND LINE PARSING

# Parse command line switches: 
plotops=( )
while [[ ( $# -ge 1 ) && ( "/$1" =~ /-.* ) ]]; do
  if [[ ( $# -ge 1 ) && ( "/$1" == "/-rows" ) ]]; then 
    plotops=( ${plotops[@]} "$1" ); shift;
  elif [[ ( $# -ge 1 ) && ( "/$1" == "/-kodak" ) ]]; then 
    plotops=( ${plotops[@]} "$1" ); shift;
  elif [[ ( $# -ge 3 ) && ( "/$1" == "/-range" ) ]]; then 
    plotops=( ${plotops[@]} "$1" "$2" "$3" ); shift; shift; shift;
  elif [[ ( $# -ge 3 ) && ( "/$1" == "/-blur" ) ]]; then 
    plotops=( ${plotops[@]} "$1" "$2" "$3" ); shift; shift; shift;
  else
    echo "unknown option $1" 1>&2 ;
    echo -e "usage:\n  ${PROG_HELP[@]}" 1>&2 ; exit 1 
  fi
done 

# Get positional parameters
if [[ $# -ge 2 ]]; then
  name=$1; shift;
  channel=$1; shift;
else
  echo 'wrong number of arguments "'"$1"'" ...' 1>&2 ;
  echo -e "usage:\n  ${PROG_HELP[@]}" 1>&2 ; exit 1 
fi

# Check for leftover arguments:
if [[ $# -ne 0 ]]; then
  echo 'missing image name "'"$1"'" ...' 1>&2 ;
  echo -e "usage:\n  ${PROG_HELP[@]}" 1>&2 ; exit 1 
fi

# END COMMAND LINE PARSING
# ----------------------------------------------------------------------

# Remove ".fni" extension from ${name}, if present:
name=${name%.fni}
# echo "name = ${name}" 1>&2

echo "${PROG_NAME}: name = ${name} channel = ${channel} ops = ( ${plotops[@]} )"  1>&2

infni="${name}.fni"
oteps="${name}.eps"

# Create EPS file:
fni_plot.sh \
    ${plotops[@]} \
    -channel ${channel} \
    -title "${infni} ${channel}" \
  < ${infni} \
  > ${oteps} \
  && ghostview ${oteps}

 
