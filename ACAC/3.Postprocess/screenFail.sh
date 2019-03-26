#!/bin/sh

rm -rf 2.TOTAL_AB
while read line 
do
	#echo $line

	A=`echo $line | awk '{print $1}'`
	B=`echo $line | awk '{print $2}'`
	
	echo "$A $B FCC" >> 2.TOTAL_AB
	echo "$A $B CsCl" >> 2.TOTAL_AB
	echo "$A $B NaCl" >> 2.TOTAL_AB
	echo "$A $B Wurt" >> 2.TOTAL_AB
	echo "$A $B Zinc" >> 2.TOTAL_AB
	echo "$A $B B33" >> 2.TOTAL_AB
	echo "$A $B B19" >> 2.TOTAL_AB
	echo "$A $B B11" >> 2.TOTAL_AB
	echo "$A $B B27" >> 2.TOTAL_AB
	echo "$A $B L11" >> 2.TOTAL_AB


done < ALLOY_LIST_TABLE

cp 2.TOTAL_AB 3.FAIL_AB

while read line
do

#	echo $line

	grep -v "$line" 3.FAIL_AB > TEMP_AB

	mv TEMP_AB 3.FAIL_AB


done <1.SUCCESS_AB

./gen_compounds ATOM_INFO 3.FAIL_AB
