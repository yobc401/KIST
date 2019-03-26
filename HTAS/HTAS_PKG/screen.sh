#!/bin/sh


paste AUTOMAT_out1.dat AUTOMAT_out2.dat AUTOMAT_out3.dat  > SCREEN_TOTAL_in.dat

# REF VOL DEN PLD CVD VF | REF ASA1 NASA1 SA1 ASA1S NASA1S SA1SA | REF ASA2 NASA2 SA2 $ASA2S $NASA2S $SA2S
#  1   2   3   4   5  6     7   8    9     10  11    12     13      14  15   16    17   18     19      20

# Cond.1 Density
awk '{if ($3 > 0 && $3 <=2.0) { print }}' SCREEN_TOTAL_in.dat > SCREEN_out1.dat

# Cond.2 Surface Area for 1st molecule
awk '{if ($10 > 400.0) { print }}' SCREEN_out1.dat > SCREEN_out2.dat

# Cond.3 Accessibility(ASA/SA) for 2nd molecule
awk '{if($17>0.0){if ($15/$17 > 0.9 || $16/$17 > 0.9) { print }}}' SCREEN_out2.dat > SCREEN_out3.dat

# Cond.4 Pore Size Determination
awk '{if ($4 > 5.0 ) { print }}' SCREEN_out3.dat > SCREEN_out4.dat


