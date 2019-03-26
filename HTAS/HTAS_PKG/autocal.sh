#!/bin/sh

MOL1=1.86  ## N2 
MOL2=2.34  ## C3H6

path=$1

### Preprocessing
rm -rf GCMC_input
mkdir GCMC_input
rm -rf AUTOMAT_out1.dat AUTOMAT_out2.dat AUTOMAT_out3.dat

### Main Loop
for entry in `ls $path`
do
	name=`echo $entry | sed 's/....$//'`
	echo $name

	cp $path/$name.cif . 
 
	./calculator -cif $name-frac.cif $name.cif
	./calculator -xyz $name.xyz $name.cif
	./gen_config_mol $name-frac.cif $name.xyz $name

	./mol_connect $name.mol 0.15 $name-frac.cif

	### Calculate Physical Properties 
	./calculator -res $name.new.cif
	./calculator -vol $MOL1 $MOL1 5000 $name.new.cif

	## Molecule 1
	./calculator -sa $MOL1 $MOL1 2000 $name.new.cif

	VOL=`awk '{if(NR==1){print $4}}' $name.new.sa | bc`
	DEN=`awk '{if(NR==1){print $6}}' $name.new.sa | bc`
	
	ASA1=`awk '{if(NR==1){print $12}}' $name.new.sa | bc`
	NASA1=`awk '{if(NR==1){print $18}}' $name.new.sa | bc`
	SA1=`echo "$ASA1+$NASA1" | bc`

	### Generate Supercell ###
	./organize_cif $name.new.cif $name-frac_og.cif
	./expand_supercell.py -i $name-frac_og.cif -o $name-supercell.cif -b 2 2 2 -r

	./calculator -sa $MOL1 $MOL1 2000 $name-supercell.cif

	ASA1S=`awk '{if(NR==1){print $12}}' $name-supercell.sa |bc`
	NASA1S=`awk '{if(NR==1){print $18}}' $name-supercell.sa |bc`
	SA1S=`echo "$ASA2S+$NASA2S" | bc`

	## Molecule 2
	./calculator -sa $MOL2 $MOL2 2000 $name.new.cif
	
	ASA2=`awk '{if(NR==1){print $12}}' $name.new.sa | bc`
	NASA2=`awk '{if(NR==1){print $18}}' $name.new.sa | bc`
	SA2=`echo "$ASA2+$NASA2" | bc`

	### Generate Supercell ###
	./organize_cif $name.new.cif $name-frac_og.cif
	./expand_supercell.py -i $name-frac_og.cif -o $name-supercell.cif -b 2 2 2 -r

	./calculator -sa $MOL2 $MOL2 2000 $name-supercell.cif

	ASA2S=`awk '{if(NR==1){print $12}}' $name-supercell.sa |bc`
	NASA2S=`awk '{if(NR==1){print $18}}' $name-supercell.sa |bc`
	SA2S=`echo "$ASA2S+$NASA2S" | bc`

	## Porosity; Volume
	PLD=`cat $name.new.res | tail -1 | awk '{print $3}'`
	CVD=`cat $name.new.res | tail -1 | awk '{print $4}'`

	ASA_frac=`cat $name.new.vol | head -1 | awk '{print $10}'`
	NASA_frac=`cat $name.new.vol | head -1 | awk '{print $16}'`
	VF=`echo "$ASA_frac+$NASA_frac" | bc`

	### Save Crystal Information
	printf "%10s %10.3f %10.3f %10.3f %10.3f %10.3f\n" $name $VOL  $DEN   $PLD  $CVD  $VF >> AUTOMAT_out1.dat
	### Save Porosity in terms of 1st molecule
	printf "%10s %10.3f %10.3f %10.3f %10.3f %10.3f %10.3f\n" $name $ASA1 $NASA1 $SA1 $ASA1S $NASA1S $SA1S >> AUTOMAT_out2.dat
	### Save Porosity in terms of 2nd molecule
	printf "%10s %10.3f %10.3f %10.3f %10.3f %10.3f %10.3f\n" $name $ASA2 $NASA2 $SA2 $ASA2S $NASA2S $SA2S >> AUTOMAT_out3.dat


	### Clean
	rm $name-frac_og.cif $name-supercell.cif $name-supercell.sa
	rm $name.cif $name-frac.cif $name.xyz $name.new.res $name.new.vol $name.new.sa $name.mol $name.new.xyz $name.new.cif


	### Move GCMC Sim. input File 
	mv $name.new.mol GCMC_input/$name.mol 

done


