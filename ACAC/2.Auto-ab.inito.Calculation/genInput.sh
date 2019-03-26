#!/bin/sh

rm qsub.sh

echo "#!/bin/sh" >> qsub.sh
echo "#$ -V" >> qsub.sh
echo "#$ -cwd" >> qsub.sh
echo "#$ -N HTS-Catalyst" >> qsub.sh
echo "#$ -pe mpi_fu 64" >> qsub.sh
echo "#$ -q normal" >> qsub.sh
echo "#$ -R yes" >> qsub.sh
echo "#$ -l h_rt=48:00:00" >> qsub.sh


FILE=COMPOUNDS_LIST

echo "rm -rf THST-Energy.out" >> qsub.sh
echo "rm -rf TIME_LOG.out" >> qsub.sh


function run_VASP(){
	
	echo "mpirun_rsh -np \$NSLOTS -hostfile \$TMPDIR/machines ~/bin/vasp > stdout" >> qsub.sh

}

echo "rm -rf CONTCARDir OUTCARDir OSZICARDir DOSCARDir" >> qsub.sh
echo "mkdir CONTCARDir" >> qsub.sh
echo "mkdir OUTCARDir" >> qsub.sh
echo "mkdir OSZICARDir" >> qsub.sh
echo "mkdir DOSCARDir" >> qsub.sh


while read line
do

	echo "" >> qsub.sh
	echo "" >> qsub.sh
	#echo $line
	A=`echo $line | awk '{print $1}'`
	B=`echo $line | awk '{print $2}'`
	struct=`echo $line | awk '{print $3}'`
	N=`echo $line | awk '{print $4}'`
	a_param=`echo $line | awk '{print $5}'`
	b_param=`echo $line | awk '{print $6}'`
	c_param=`echo $line | awk '{print $7}'`
	
	echo $A $B

	## Generate POSCAR
	FILE=/scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_$A.$B.$struct 

	if [[ -f $FILE ]];
	then
		#echo "cp scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_$A.$B.$struct POSCAR" >> qsub.sh

		echo "cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_$A.$B.$struct POSCAR" >> qsub.sh

	else


		echo "./gen_POSCAR $A $B $N $a_param $b_param $c_param" >> qsub.sh

	fi

	## Generate POTCAR
	echo "./gen_POTCAR.sh $A $B" >> qsub.sh
	## Generate INCAR
	echo "cp INPUT/INCAR ." >> qsub.sh
	echo "./gen_INCAR $A $B INCAR 400" >> qsub.sh
	echo "mv INCAR.out INCAR" >> qsub.sh
	## Generate KPOINT
	echo "cp INPUT/KPOINTS ." >> qsub.sh
	
	echo "rm -rf CHG CHGCAR DOSCAR EIGENVAL WAVECAR" >> qsub.sh
	
	run_VASP

	echo $line
	echo $A $B
	#run_VASP

	#echo "energy=\`grep "entropy" OUTCAR | tail -1 | awk '{print \$4}'\`" >> qsub.sh

	#echo "if [[ -z \$energy4 ]]; then" >> qsub.sh
	#echo "	energy4=0" >> qsub.sh

	#echo "fi" >> qsub.sh

	echo "mv CONTCAR CONTCARDir/CONTCAR_$A.$B.$struct" >> qsub.sh
	echo "mv OUTCAR OUTCARDir/OUTCAR_$A.$B.$struct" >> qsub.sh
	echo "mv OSZICAR OSZICARDir/OSZICAR_$A.$B.$struct" >> qsub.sh
	echo "mv DOSCAR DOSCARDir/DOSCAR_$A.$B.$struct" >> qsub.sh



	echo "date >> TIME_LOG.out" >> qsub.sh



done <$FILE


#exit 0
