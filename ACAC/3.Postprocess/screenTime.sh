#!/bin/sh


grep "User time" ../OUTCARDir/* > temp
awk '{print $5,$1,$2}' temp1 > 0.USER_TIME

rm temp
