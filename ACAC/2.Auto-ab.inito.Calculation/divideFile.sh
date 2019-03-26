#!/bin/sh


linenum=`wc -l COMPOUNDS_LIST | awk '{print $1}'`

for x in {1..9}
do

	init_num=`echo "($x-1)*($linenum/10)" | bc`
	end_num=`echo "$x*($linenum/10)" | bc`
	echo $init_num
	echo $end_num
	awk "{if(NR>$init_num&&NR<=$end_num){print}}" COMPOUNDS_LIST > COMPOUNDS_LIST.$x


done


awk "{if(NR>$end_num){print}}" COMPOUNDS_LIST > COMPOUNDS_LIST.$x
