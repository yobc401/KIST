#!/bin/sh

rm -rf NAMES VALUES

if [[ $# -ne 1 ]] ; then
    echo "Usage ./scriptDOSsim.sh DOSCAR_BASE"
    exit 1
fi

cp $1 DOSCAR_BASE

for entry in `ls ../DOSCARDir/`
do

	#echo $entry

	cp ../DOSCARDir/$entry .


	linenum=`wc -l $entry | awk '{print $1}'`

	if [[ $linenum -ne 5 ]]; then
		echo $entry >> NAMES
		./cal_DOS_sim DOSCAR_BASE $entry  >> VALUES
	fi

	rm -rf $entry

done


paste NAMES VALUES > TOT_DOSsim


awk '{print $5}'  TOT_DOSsim > TEMP1

sed -e 's/\./ /g' TOT_DOSsim > TEMP2
sed -e 's/_/ /g' TEMP2 > TEMP3

awk '{print $2,$3,$4}' TEMP3 > TEMP4

paste TEMP4 TEMP1 > TOT_DOSsim.$1.out


rm NAMES VALUES TOT_DOSsim TEMP*
