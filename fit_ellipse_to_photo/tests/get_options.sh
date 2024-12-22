#! /bin/bash
# Last edited on 2012-12-08 21:39:03 by stolfilocal

# Script to be source'd by the test scripts.
# Parses the command line and sets some options.

options=( )
while [[ ( $# -ge 1 ) && ( "/$1" =~ /-.* ) ]]; do 
  if [[ ( $# -ge 1 ) && ( "/$1" == "/-debug" ) ]]; then
    options=( "${options[@]}" "$1" ); shift;
  else
    echo 'bad or incomplete option "'"$1"'"' 1>&2;
  fi
done
