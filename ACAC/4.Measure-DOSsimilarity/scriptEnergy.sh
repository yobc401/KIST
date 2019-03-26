#!/bin/sh


rm -rf TOT_Energy.out

while read line
do
	A=`echo $line | awk '{print $1}'`
	B=`echo $line | awk '{print $2}'`
	Struct=`echo $line | awk '{print $3}'`

	E=`tail -1 ../OSZICARDir/OSZICAR_$A.$B.$Struct | awk '{print $5}'`

	printf "%3s %3s %6s %10.6f\n" $A $B $Struct $E >> TOT_Energy.out



done < 1.SUCCESS_AB


