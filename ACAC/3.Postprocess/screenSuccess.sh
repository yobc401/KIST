#!/bin/sh


grep "Maximum memory used" ../OUTCARDir/* > temp1

awk '{print $1}' temp1 > temp2

sed -e 's/\./ /g' temp2 > temp3
sed -e 's/_/ /g' temp3 > temp4 
sed -e 's/:/ /g' temp4 > temp5

awk '{print $2,$3,$4}' temp5 > 1.SUCCESS_AB 

rm temp*

