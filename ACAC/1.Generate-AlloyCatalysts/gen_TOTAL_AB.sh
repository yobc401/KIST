#!/bin/sh

rm -rf ALLOY_LIST_TABLE

while read line1
do
	while read line2
	do
		A=`echo $line1 | awk '{print $1}'`
		B=`echo $line2 | awk '{print $1}'`

		echo "$A $B" >> ALLOY_LIST_TABLE



	done < INPUT_B_LIST



done < INPUT_A_LIST


rm -rf TOTAL_AB
while read line 
do
	#echo $line

	A=`echo $line | awk '{print $1}'`
	B=`echo $line | awk '{print $2}'`
	
	echo "$A $B FCC" >> TOTAL_AB
	echo "$A $B CsCl" >> TOTAL_AB
	echo "$A $B NaCl" >> TOTAL_AB
	echo "$A $B Wurt" >> TOTAL_AB
	echo "$A $B Zinc" >> TOTAL_AB
	echo "$A $B HCP" >> TOTAL_AB
	echo "$A $B B33" >> TOTAL_AB
	echo "$A $B B19" >> TOTAL_AB
	echo "$A $B B11" >> TOTAL_AB
	echo "$A $B B27" >> TOTAL_AB
	echo "$A $B L11" >> TOTAL_AB



done < ALLOY_LIST_TABLE

