#!/bin/sh

if [[ $# -ne 2 ]] ; then
	echo "Error argument"
	exit 1
fi

rm -rf POTCAR

dir1=`ls ../PAW_PBE | grep "$1_" | head -1`
if [[ -z $dir1 ]]; then
	dir1=`ls ../PAW_PBE | grep "$1" | head -1`
fi

cat ../PAW_PBE/$dir1/POTCAR >> POTCAR

dir2=`ls ../PAW_PBE | grep "$2_" | head -1`
if [[ -z $dir2 ]]; then
	dir2=`ls ../PAW_PBE | grep "$2" | head -1`
fi

cat ../PAW_PBE/$dir2/POTCAR >> POTCAR


