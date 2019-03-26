#!/bin/sh
#$ -V
#$ -cwd
#$ -N HTS-Catalyst
#$ -pe mpi_fu 64
#$ -q normal
#$ -R yes
#$ -l h_rt=48:00:00
rm -rf THST-Energy.out
rm -rf TIME_LOG.out
rm -rf CONTCARDir OUTCARDir OSZICARDir DOSCARDir
mkdir CONTCARDir
mkdir OUTCARDir
mkdir OSZICARDir
mkdir DOSCARDir


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Ti.FCC POSCAR
./gen_POTCAR.sh Sc Ti
cp INPUT/INCAR .
./gen_INCAR Sc Ti INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Ti.FCC
mv OUTCAR OUTCARDir/OUTCAR_Sc.Ti.FCC
mv OSZICAR OSZICARDir/OSZICAR_Sc.Ti.FCC
mv DOSCAR DOSCARDir/DOSCAR_Sc.Ti.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.V.Wurt POSCAR
./gen_POTCAR.sh Sc V
cp INPUT/INCAR .
./gen_INCAR Sc V INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.V.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Sc.V.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Sc.V.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Sc.V.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Cr.FCC POSCAR
./gen_POTCAR.sh Sc Cr
cp INPUT/INCAR .
./gen_INCAR Sc Cr INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Cr.FCC
mv OUTCAR OUTCARDir/OUTCAR_Sc.Cr.FCC
mv OSZICAR OSZICARDir/OSZICAR_Sc.Cr.FCC
mv DOSCAR DOSCARDir/DOSCAR_Sc.Cr.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Co.FCC POSCAR
./gen_POTCAR.sh Sc Co
cp INPUT/INCAR .
./gen_INCAR Sc Co INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Co.FCC
mv OUTCAR OUTCARDir/OUTCAR_Sc.Co.FCC
mv OSZICAR OSZICARDir/OSZICAR_Sc.Co.FCC
mv DOSCAR DOSCARDir/DOSCAR_Sc.Co.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Co.CsCl POSCAR
./gen_POTCAR.sh Sc Co
cp INPUT/INCAR .
./gen_INCAR Sc Co INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Co.CsCl
mv OUTCAR OUTCARDir/OUTCAR_Sc.Co.CsCl
mv OSZICAR OSZICARDir/OSZICAR_Sc.Co.CsCl
mv DOSCAR DOSCARDir/DOSCAR_Sc.Co.CsCl
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Co.Wurt POSCAR
./gen_POTCAR.sh Sc Co
cp INPUT/INCAR .
./gen_INCAR Sc Co INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Co.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Sc.Co.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Sc.Co.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Sc.Co.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Ni.FCC POSCAR
./gen_POTCAR.sh Sc Ni
cp INPUT/INCAR .
./gen_INCAR Sc Ni INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Ni.FCC
mv OUTCAR OUTCARDir/OUTCAR_Sc.Ni.FCC
mv OSZICAR OSZICARDir/OSZICAR_Sc.Ni.FCC
mv DOSCAR DOSCARDir/DOSCAR_Sc.Ni.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Ni.Wurt POSCAR
./gen_POTCAR.sh Sc Ni
cp INPUT/INCAR .
./gen_INCAR Sc Ni INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Ni.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Sc.Ni.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Sc.Ni.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Sc.Ni.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Cu.FCC POSCAR
./gen_POTCAR.sh Sc Cu
cp INPUT/INCAR .
./gen_INCAR Sc Cu INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Cu.FCC
mv OUTCAR OUTCARDir/OUTCAR_Sc.Cu.FCC
mv OSZICAR OSZICARDir/OSZICAR_Sc.Cu.FCC
mv DOSCAR DOSCARDir/DOSCAR_Sc.Cu.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Cu.Wurt POSCAR
./gen_POTCAR.sh Sc Cu
cp INPUT/INCAR .
./gen_INCAR Sc Cu INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Cu.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Sc.Cu.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Sc.Cu.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Sc.Cu.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Cu.Zinc POSCAR
./gen_POTCAR.sh Sc Cu
cp INPUT/INCAR .
./gen_INCAR Sc Cu INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Cu.Zinc
mv OUTCAR OUTCARDir/OUTCAR_Sc.Cu.Zinc
mv OSZICAR OSZICARDir/OSZICAR_Sc.Cu.Zinc
mv DOSCAR DOSCARDir/DOSCAR_Sc.Cu.Zinc
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Zn.FCC POSCAR
./gen_POTCAR.sh Sc Zn
cp INPUT/INCAR .
./gen_INCAR Sc Zn INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Zn.FCC
mv OUTCAR OUTCARDir/OUTCAR_Sc.Zn.FCC
mv OSZICAR OSZICARDir/OSZICAR_Sc.Zn.FCC
mv DOSCAR DOSCARDir/DOSCAR_Sc.Zn.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Y.FCC POSCAR
./gen_POTCAR.sh Sc Y
cp INPUT/INCAR .
./gen_INCAR Sc Y INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Y.FCC
mv OUTCAR OUTCARDir/OUTCAR_Sc.Y.FCC
mv OSZICAR OSZICARDir/OSZICAR_Sc.Y.FCC
mv DOSCAR DOSCARDir/DOSCAR_Sc.Y.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Y.CsCl POSCAR
./gen_POTCAR.sh Sc Y
cp INPUT/INCAR .
./gen_INCAR Sc Y INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Y.CsCl
mv OUTCAR OUTCARDir/OUTCAR_Sc.Y.CsCl
mv OSZICAR OSZICARDir/OSZICAR_Sc.Y.CsCl
mv DOSCAR DOSCARDir/DOSCAR_Sc.Y.CsCl
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Zr.Wurt POSCAR
./gen_POTCAR.sh Sc Zr
cp INPUT/INCAR .
./gen_INCAR Sc Zr INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Zr.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Sc.Zr.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Sc.Zr.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Sc.Zr.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Nb.FCC POSCAR
./gen_POTCAR.sh Sc Nb
cp INPUT/INCAR .
./gen_INCAR Sc Nb INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Nb.FCC
mv OUTCAR OUTCARDir/OUTCAR_Sc.Nb.FCC
mv OSZICAR OSZICARDir/OSZICAR_Sc.Nb.FCC
mv DOSCAR DOSCARDir/DOSCAR_Sc.Nb.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Nb.Wurt POSCAR
./gen_POTCAR.sh Sc Nb
cp INPUT/INCAR .
./gen_INCAR Sc Nb INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Nb.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Sc.Nb.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Sc.Nb.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Sc.Nb.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Mo.FCC POSCAR
./gen_POTCAR.sh Sc Mo
cp INPUT/INCAR .
./gen_INCAR Sc Mo INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Mo.FCC
mv OUTCAR OUTCARDir/OUTCAR_Sc.Mo.FCC
mv OSZICAR OSZICARDir/OSZICAR_Sc.Mo.FCC
mv DOSCAR DOSCARDir/DOSCAR_Sc.Mo.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Mo.Wurt POSCAR
./gen_POTCAR.sh Sc Mo
cp INPUT/INCAR .
./gen_INCAR Sc Mo INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Mo.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Sc.Mo.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Sc.Mo.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Sc.Mo.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Tc.FCC POSCAR
./gen_POTCAR.sh Sc Tc
cp INPUT/INCAR .
./gen_INCAR Sc Tc INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Tc.FCC
mv OUTCAR OUTCARDir/OUTCAR_Sc.Tc.FCC
mv OSZICAR OSZICARDir/OSZICAR_Sc.Tc.FCC
mv DOSCAR DOSCARDir/DOSCAR_Sc.Tc.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Tc.Wurt POSCAR
./gen_POTCAR.sh Sc Tc
cp INPUT/INCAR .
./gen_INCAR Sc Tc INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Tc.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Sc.Tc.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Sc.Tc.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Sc.Tc.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Ru.FCC POSCAR
./gen_POTCAR.sh Sc Ru
cp INPUT/INCAR .
./gen_INCAR Sc Ru INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Ru.FCC
mv OUTCAR OUTCARDir/OUTCAR_Sc.Ru.FCC
mv OSZICAR OSZICARDir/OSZICAR_Sc.Ru.FCC
mv DOSCAR DOSCARDir/DOSCAR_Sc.Ru.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Rh.FCC POSCAR
./gen_POTCAR.sh Sc Rh
cp INPUT/INCAR .
./gen_INCAR Sc Rh INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Rh.FCC
mv OUTCAR OUTCARDir/OUTCAR_Sc.Rh.FCC
mv OSZICAR OSZICARDir/OSZICAR_Sc.Rh.FCC
mv DOSCAR DOSCARDir/DOSCAR_Sc.Rh.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Pd.FCC POSCAR
./gen_POTCAR.sh Sc Pd
cp INPUT/INCAR .
./gen_INCAR Sc Pd INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Pd.FCC
mv OUTCAR OUTCARDir/OUTCAR_Sc.Pd.FCC
mv OSZICAR OSZICARDir/OSZICAR_Sc.Pd.FCC
mv DOSCAR DOSCARDir/DOSCAR_Sc.Pd.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Ag.CsCl POSCAR
./gen_POTCAR.sh Sc Ag
cp INPUT/INCAR .
./gen_INCAR Sc Ag INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Ag.CsCl
mv OUTCAR OUTCARDir/OUTCAR_Sc.Ag.CsCl
mv OSZICAR OSZICARDir/OSZICAR_Sc.Ag.CsCl
mv DOSCAR DOSCARDir/DOSCAR_Sc.Ag.CsCl
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Ag.Wurt POSCAR
./gen_POTCAR.sh Sc Ag
cp INPUT/INCAR .
./gen_INCAR Sc Ag INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Ag.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Sc.Ag.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Sc.Ag.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Sc.Ag.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Cd.Wurt POSCAR
./gen_POTCAR.sh Sc Cd
cp INPUT/INCAR .
./gen_INCAR Sc Cd INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Cd.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Sc.Cd.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Sc.Cd.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Sc.Cd.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Lu.NaCl POSCAR
./gen_POTCAR.sh Sc Lu
cp INPUT/INCAR .
./gen_INCAR Sc Lu INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Lu.NaCl
mv OUTCAR OUTCARDir/OUTCAR_Sc.Lu.NaCl
mv OSZICAR OSZICARDir/OSZICAR_Sc.Lu.NaCl
mv DOSCAR DOSCARDir/DOSCAR_Sc.Lu.NaCl
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Lu.Wurt POSCAR
./gen_POTCAR.sh Sc Lu
cp INPUT/INCAR .
./gen_INCAR Sc Lu INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Lu.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Sc.Lu.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Sc.Lu.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Sc.Lu.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Lu.Zinc POSCAR
./gen_POTCAR.sh Sc Lu
cp INPUT/INCAR .
./gen_INCAR Sc Lu INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Lu.Zinc
mv OUTCAR OUTCARDir/OUTCAR_Sc.Lu.Zinc
mv OSZICAR OSZICARDir/OSZICAR_Sc.Lu.Zinc
mv DOSCAR DOSCARDir/DOSCAR_Sc.Lu.Zinc
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Hf.FCC POSCAR
./gen_POTCAR.sh Sc Hf
cp INPUT/INCAR .
./gen_INCAR Sc Hf INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Hf.FCC
mv OUTCAR OUTCARDir/OUTCAR_Sc.Hf.FCC
mv OSZICAR OSZICARDir/OSZICAR_Sc.Hf.FCC
mv DOSCAR DOSCARDir/DOSCAR_Sc.Hf.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Ta.Wurt POSCAR
./gen_POTCAR.sh Sc Ta
cp INPUT/INCAR .
./gen_INCAR Sc Ta INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Ta.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Sc.Ta.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Sc.Ta.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Sc.Ta.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.W.FCC POSCAR
./gen_POTCAR.sh Sc W
cp INPUT/INCAR .
./gen_INCAR Sc W INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.W.FCC
mv OUTCAR OUTCARDir/OUTCAR_Sc.W.FCC
mv OSZICAR OSZICARDir/OSZICAR_Sc.W.FCC
mv DOSCAR DOSCARDir/DOSCAR_Sc.W.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.W.Wurt POSCAR
./gen_POTCAR.sh Sc W
cp INPUT/INCAR .
./gen_INCAR Sc W INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.W.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Sc.W.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Sc.W.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Sc.W.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Re.Wurt POSCAR
./gen_POTCAR.sh Sc Re
cp INPUT/INCAR .
./gen_INCAR Sc Re INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Re.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Sc.Re.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Sc.Re.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Sc.Re.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Ir.CsCl POSCAR
./gen_POTCAR.sh Sc Ir
cp INPUT/INCAR .
./gen_INCAR Sc Ir INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Ir.CsCl
mv OUTCAR OUTCARDir/OUTCAR_Sc.Ir.CsCl
mv OSZICAR OSZICARDir/OSZICAR_Sc.Ir.CsCl
mv DOSCAR DOSCARDir/DOSCAR_Sc.Ir.CsCl
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Ir.Wurt POSCAR
./gen_POTCAR.sh Sc Ir
cp INPUT/INCAR .
./gen_INCAR Sc Ir INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Ir.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Sc.Ir.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Sc.Ir.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Sc.Ir.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Au.FCC POSCAR
./gen_POTCAR.sh Sc Au
cp INPUT/INCAR .
./gen_INCAR Sc Au INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Au.FCC
mv OUTCAR OUTCARDir/OUTCAR_Sc.Au.FCC
mv OSZICAR OSZICARDir/OSZICAR_Sc.Au.FCC
mv DOSCAR DOSCARDir/DOSCAR_Sc.Au.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Au.Wurt POSCAR
./gen_POTCAR.sh Sc Au
cp INPUT/INCAR .
./gen_INCAR Sc Au INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Au.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Sc.Au.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Sc.Au.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Sc.Au.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Sc.Hg.Wurt POSCAR
./gen_POTCAR.sh Sc Hg
cp INPUT/INCAR .
./gen_INCAR Sc Hg INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Sc.Hg.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Sc.Hg.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Sc.Hg.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Sc.Hg.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.V.Zinc POSCAR
./gen_POTCAR.sh Ti V
cp INPUT/INCAR .
./gen_INCAR Ti V INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.V.Zinc
mv OUTCAR OUTCARDir/OUTCAR_Ti.V.Zinc
mv OSZICAR OSZICARDir/OSZICAR_Ti.V.Zinc
mv DOSCAR DOSCARDir/DOSCAR_Ti.V.Zinc
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Cr.FCC POSCAR
./gen_POTCAR.sh Ti Cr
cp INPUT/INCAR .
./gen_INCAR Ti Cr INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Cr.FCC
mv OUTCAR OUTCARDir/OUTCAR_Ti.Cr.FCC
mv OSZICAR OSZICARDir/OSZICAR_Ti.Cr.FCC
mv DOSCAR DOSCARDir/DOSCAR_Ti.Cr.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Cr.Wurt POSCAR
./gen_POTCAR.sh Ti Cr
cp INPUT/INCAR .
./gen_INCAR Ti Cr INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Cr.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Ti.Cr.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Ti.Cr.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Ti.Cr.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Mn.FCC POSCAR
./gen_POTCAR.sh Ti Mn
cp INPUT/INCAR .
./gen_INCAR Ti Mn INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Mn.FCC
mv OUTCAR OUTCARDir/OUTCAR_Ti.Mn.FCC
mv OSZICAR OSZICARDir/OSZICAR_Ti.Mn.FCC
mv DOSCAR DOSCARDir/DOSCAR_Ti.Mn.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Mn.Wurt POSCAR
./gen_POTCAR.sh Ti Mn
cp INPUT/INCAR .
./gen_INCAR Ti Mn INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Mn.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Ti.Mn.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Ti.Mn.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Ti.Mn.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Fe.FCC POSCAR
./gen_POTCAR.sh Ti Fe
cp INPUT/INCAR .
./gen_INCAR Ti Fe INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Fe.FCC
mv OUTCAR OUTCARDir/OUTCAR_Ti.Fe.FCC
mv OSZICAR OSZICARDir/OSZICAR_Ti.Fe.FCC
mv DOSCAR DOSCARDir/DOSCAR_Ti.Fe.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Fe.CsCl POSCAR
./gen_POTCAR.sh Ti Fe
cp INPUT/INCAR .
./gen_INCAR Ti Fe INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Fe.CsCl
mv OUTCAR OUTCARDir/OUTCAR_Ti.Fe.CsCl
mv OSZICAR OSZICARDir/OSZICAR_Ti.Fe.CsCl
mv DOSCAR DOSCARDir/DOSCAR_Ti.Fe.CsCl
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Fe.Wurt POSCAR
./gen_POTCAR.sh Ti Fe
cp INPUT/INCAR .
./gen_INCAR Ti Fe INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Fe.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Ti.Fe.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Ti.Fe.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Ti.Fe.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Co.FCC POSCAR
./gen_POTCAR.sh Ti Co
cp INPUT/INCAR .
./gen_INCAR Ti Co INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Co.FCC
mv OUTCAR OUTCARDir/OUTCAR_Ti.Co.FCC
mv OSZICAR OSZICARDir/OSZICAR_Ti.Co.FCC
mv DOSCAR DOSCARDir/DOSCAR_Ti.Co.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Co.Wurt POSCAR
./gen_POTCAR.sh Ti Co
cp INPUT/INCAR .
./gen_INCAR Ti Co INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Co.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Ti.Co.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Ti.Co.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Ti.Co.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Ni.FCC POSCAR
./gen_POTCAR.sh Ti Ni
cp INPUT/INCAR .
./gen_INCAR Ti Ni INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Ni.FCC
mv OUTCAR OUTCARDir/OUTCAR_Ti.Ni.FCC
mv OSZICAR OSZICARDir/OSZICAR_Ti.Ni.FCC
mv DOSCAR DOSCARDir/DOSCAR_Ti.Ni.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Ni.CsCl POSCAR
./gen_POTCAR.sh Ti Ni
cp INPUT/INCAR .
./gen_INCAR Ti Ni INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Ni.CsCl
mv OUTCAR OUTCARDir/OUTCAR_Ti.Ni.CsCl
mv OSZICAR OSZICARDir/OSZICAR_Ti.Ni.CsCl
mv DOSCAR DOSCARDir/DOSCAR_Ti.Ni.CsCl
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Ni.Wurt POSCAR
./gen_POTCAR.sh Ti Ni
cp INPUT/INCAR .
./gen_INCAR Ti Ni INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Ni.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Ti.Ni.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Ti.Ni.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Ti.Ni.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Cu.FCC POSCAR
./gen_POTCAR.sh Ti Cu
cp INPUT/INCAR .
./gen_INCAR Ti Cu INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Cu.FCC
mv OUTCAR OUTCARDir/OUTCAR_Ti.Cu.FCC
mv OSZICAR OSZICARDir/OSZICAR_Ti.Cu.FCC
mv DOSCAR DOSCARDir/DOSCAR_Ti.Cu.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Cu.CsCl POSCAR
./gen_POTCAR.sh Ti Cu
cp INPUT/INCAR .
./gen_INCAR Ti Cu INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Cu.CsCl
mv OUTCAR OUTCARDir/OUTCAR_Ti.Cu.CsCl
mv OSZICAR OSZICARDir/OSZICAR_Ti.Cu.CsCl
mv DOSCAR DOSCARDir/DOSCAR_Ti.Cu.CsCl
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Cu.Wurt POSCAR
./gen_POTCAR.sh Ti Cu
cp INPUT/INCAR .
./gen_INCAR Ti Cu INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Cu.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Ti.Cu.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Ti.Cu.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Ti.Cu.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Zn.FCC POSCAR
./gen_POTCAR.sh Ti Zn
cp INPUT/INCAR .
./gen_INCAR Ti Zn INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Zn.FCC
mv OUTCAR OUTCARDir/OUTCAR_Ti.Zn.FCC
mv OSZICAR OSZICARDir/OSZICAR_Ti.Zn.FCC
mv DOSCAR DOSCARDir/DOSCAR_Ti.Zn.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Zn.Wurt POSCAR
./gen_POTCAR.sh Ti Zn
cp INPUT/INCAR .
./gen_INCAR Ti Zn INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Zn.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Ti.Zn.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Ti.Zn.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Ti.Zn.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Y.Wurt POSCAR
./gen_POTCAR.sh Ti Y
cp INPUT/INCAR .
./gen_INCAR Ti Y INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Y.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Ti.Y.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Ti.Y.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Ti.Y.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Zr.Wurt POSCAR
./gen_POTCAR.sh Ti Zr
cp INPUT/INCAR .
./gen_INCAR Ti Zr INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Zr.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Ti.Zr.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Ti.Zr.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Ti.Zr.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Nb.FCC POSCAR
./gen_POTCAR.sh Ti Nb
cp INPUT/INCAR .
./gen_INCAR Ti Nb INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Nb.FCC
mv OUTCAR OUTCARDir/OUTCAR_Ti.Nb.FCC
mv OSZICAR OSZICARDir/OSZICAR_Ti.Nb.FCC
mv DOSCAR DOSCARDir/DOSCAR_Ti.Nb.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Tc.FCC POSCAR
./gen_POTCAR.sh Ti Tc
cp INPUT/INCAR .
./gen_INCAR Ti Tc INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Tc.FCC
mv OUTCAR OUTCARDir/OUTCAR_Ti.Tc.FCC
mv OSZICAR OSZICARDir/OSZICAR_Ti.Tc.FCC
mv DOSCAR DOSCARDir/DOSCAR_Ti.Tc.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Ru.FCC POSCAR
./gen_POTCAR.sh Ti Ru
cp INPUT/INCAR .
./gen_INCAR Ti Ru INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Ru.FCC
mv OUTCAR OUTCARDir/OUTCAR_Ti.Ru.FCC
mv OSZICAR OSZICARDir/OSZICAR_Ti.Ru.FCC
mv DOSCAR DOSCARDir/DOSCAR_Ti.Ru.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Ru.Wurt POSCAR
./gen_POTCAR.sh Ti Ru
cp INPUT/INCAR .
./gen_INCAR Ti Ru INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Ru.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Ti.Ru.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Ti.Ru.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Ti.Ru.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Ru.Zinc POSCAR
./gen_POTCAR.sh Ti Ru
cp INPUT/INCAR .
./gen_INCAR Ti Ru INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Ru.Zinc
mv OUTCAR OUTCARDir/OUTCAR_Ti.Ru.Zinc
mv OSZICAR OSZICARDir/OSZICAR_Ti.Ru.Zinc
mv DOSCAR DOSCARDir/DOSCAR_Ti.Ru.Zinc
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Pd.FCC POSCAR
./gen_POTCAR.sh Ti Pd
cp INPUT/INCAR .
./gen_INCAR Ti Pd INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Pd.FCC
mv OUTCAR OUTCARDir/OUTCAR_Ti.Pd.FCC
mv OSZICAR OSZICARDir/OSZICAR_Ti.Pd.FCC
mv DOSCAR DOSCARDir/DOSCAR_Ti.Pd.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Ag.FCC POSCAR
./gen_POTCAR.sh Ti Ag
cp INPUT/INCAR .
./gen_INCAR Ti Ag INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Ag.FCC
mv OUTCAR OUTCARDir/OUTCAR_Ti.Ag.FCC
mv OSZICAR OSZICARDir/OSZICAR_Ti.Ag.FCC
mv DOSCAR DOSCARDir/DOSCAR_Ti.Ag.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Cd.FCC POSCAR
./gen_POTCAR.sh Ti Cd
cp INPUT/INCAR .
./gen_INCAR Ti Cd INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Cd.FCC
mv OUTCAR OUTCARDir/OUTCAR_Ti.Cd.FCC
mv OSZICAR OSZICARDir/OSZICAR_Ti.Cd.FCC
mv DOSCAR DOSCARDir/DOSCAR_Ti.Cd.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Lu.FCC POSCAR
./gen_POTCAR.sh Ti Lu
cp INPUT/INCAR .
./gen_INCAR Ti Lu INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Lu.FCC
mv OUTCAR OUTCARDir/OUTCAR_Ti.Lu.FCC
mv OSZICAR OSZICARDir/OSZICAR_Ti.Lu.FCC
mv DOSCAR DOSCARDir/DOSCAR_Ti.Lu.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Lu.NaCl POSCAR
./gen_POTCAR.sh Ti Lu
cp INPUT/INCAR .
./gen_INCAR Ti Lu INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Lu.NaCl
mv OUTCAR OUTCARDir/OUTCAR_Ti.Lu.NaCl
mv OSZICAR OSZICARDir/OSZICAR_Ti.Lu.NaCl
mv DOSCAR DOSCARDir/DOSCAR_Ti.Lu.NaCl
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Lu.Wurt POSCAR
./gen_POTCAR.sh Ti Lu
cp INPUT/INCAR .
./gen_INCAR Ti Lu INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Lu.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Ti.Lu.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Ti.Lu.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Ti.Lu.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Lu.Zinc POSCAR
./gen_POTCAR.sh Ti Lu
cp INPUT/INCAR .
./gen_INCAR Ti Lu INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Lu.Zinc
mv OUTCAR OUTCARDir/OUTCAR_Ti.Lu.Zinc
mv OSZICAR OSZICARDir/OSZICAR_Ti.Lu.Zinc
mv DOSCAR DOSCARDir/DOSCAR_Ti.Lu.Zinc
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Hf.Wurt POSCAR
./gen_POTCAR.sh Ti Hf
cp INPUT/INCAR .
./gen_INCAR Ti Hf INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Hf.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Ti.Hf.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Ti.Hf.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Ti.Hf.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Ta.FCC POSCAR
./gen_POTCAR.sh Ti Ta
cp INPUT/INCAR .
./gen_INCAR Ti Ta INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Ta.FCC
mv OUTCAR OUTCARDir/OUTCAR_Ti.Ta.FCC
mv OSZICAR OSZICARDir/OSZICAR_Ti.Ta.FCC
mv DOSCAR DOSCARDir/DOSCAR_Ti.Ta.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.W.Wurt POSCAR
./gen_POTCAR.sh Ti W
cp INPUT/INCAR .
./gen_INCAR Ti W INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.W.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Ti.W.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Ti.W.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Ti.W.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Re.FCC POSCAR
./gen_POTCAR.sh Ti Re
cp INPUT/INCAR .
./gen_INCAR Ti Re INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Re.FCC
mv OUTCAR OUTCARDir/OUTCAR_Ti.Re.FCC
mv OSZICAR OSZICARDir/OSZICAR_Ti.Re.FCC
mv DOSCAR DOSCARDir/DOSCAR_Ti.Re.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Re.Wurt POSCAR
./gen_POTCAR.sh Ti Re
cp INPUT/INCAR .
./gen_INCAR Ti Re INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Re.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Ti.Re.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Ti.Re.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Ti.Re.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Os.Wurt POSCAR
./gen_POTCAR.sh Ti Os
cp INPUT/INCAR .
./gen_INCAR Ti Os INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Os.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Ti.Os.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Ti.Os.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Ti.Os.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Ir.Wurt POSCAR
./gen_POTCAR.sh Ti Ir
cp INPUT/INCAR .
./gen_INCAR Ti Ir INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Ir.Wurt
mv OUTCAR OUTCARDir/OUTCAR_Ti.Ir.Wurt
mv OSZICAR OSZICARDir/OSZICAR_Ti.Ir.Wurt
mv DOSCAR DOSCARDir/DOSCAR_Ti.Ir.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Pt.CsCl POSCAR
./gen_POTCAR.sh Ti Pt
cp INPUT/INCAR .
./gen_INCAR Ti Pt INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Pt.CsCl
mv OUTCAR OUTCARDir/OUTCAR_Ti.Pt.CsCl
mv OSZICAR OSZICARDir/OSZICAR_Ti.Pt.CsCl
mv DOSCAR DOSCARDir/DOSCAR_Ti.Pt.CsCl
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Au.FCC POSCAR
./gen_POTCAR.sh Ti Au
cp INPUT/INCAR .
./gen_INCAR Ti Au INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Au.FCC
mv OUTCAR OUTCARDir/OUTCAR_Ti.Au.FCC
mv OSZICAR OSZICARDir/OSZICAR_Ti.Au.FCC
mv DOSCAR DOSCARDir/DOSCAR_Ti.Au.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_Ti.Hg.FCC POSCAR
./gen_POTCAR.sh Ti Hg
cp INPUT/INCAR .
./gen_INCAR Ti Hg INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_Ti.Hg.FCC
mv OUTCAR OUTCARDir/OUTCAR_Ti.Hg.FCC
mv OSZICAR OSZICARDir/OSZICAR_Ti.Hg.FCC
mv DOSCAR DOSCARDir/DOSCAR_Ti.Hg.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_V.V.Wurt POSCAR
./gen_POTCAR.sh V V
cp INPUT/INCAR .
./gen_INCAR V V INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_V.V.Wurt
mv OUTCAR OUTCARDir/OUTCAR_V.V.Wurt
mv OSZICAR OSZICARDir/OSZICAR_V.V.Wurt
mv DOSCAR DOSCARDir/DOSCAR_V.V.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_V.Cr.FCC POSCAR
./gen_POTCAR.sh V Cr
cp INPUT/INCAR .
./gen_INCAR V Cr INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_V.Cr.FCC
mv OUTCAR OUTCARDir/OUTCAR_V.Cr.FCC
mv OSZICAR OSZICARDir/OSZICAR_V.Cr.FCC
mv DOSCAR DOSCARDir/DOSCAR_V.Cr.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_V.Cr.Wurt POSCAR
./gen_POTCAR.sh V Cr
cp INPUT/INCAR .
./gen_INCAR V Cr INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_V.Cr.Wurt
mv OUTCAR OUTCARDir/OUTCAR_V.Cr.Wurt
mv OSZICAR OSZICARDir/OSZICAR_V.Cr.Wurt
mv DOSCAR DOSCARDir/DOSCAR_V.Cr.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_V.Mn.FCC POSCAR
./gen_POTCAR.sh V Mn
cp INPUT/INCAR .
./gen_INCAR V Mn INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_V.Mn.FCC
mv OUTCAR OUTCARDir/OUTCAR_V.Mn.FCC
mv OSZICAR OSZICARDir/OSZICAR_V.Mn.FCC
mv DOSCAR DOSCARDir/DOSCAR_V.Mn.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_V.Mn.CsCl POSCAR
./gen_POTCAR.sh V Mn
cp INPUT/INCAR .
./gen_INCAR V Mn INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_V.Mn.CsCl
mv OUTCAR OUTCARDir/OUTCAR_V.Mn.CsCl
mv OSZICAR OSZICARDir/OSZICAR_V.Mn.CsCl
mv DOSCAR DOSCARDir/DOSCAR_V.Mn.CsCl
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_V.Mn.NaCl POSCAR
./gen_POTCAR.sh V Mn
cp INPUT/INCAR .
./gen_INCAR V Mn INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_V.Mn.NaCl
mv OUTCAR OUTCARDir/OUTCAR_V.Mn.NaCl
mv OSZICAR OSZICARDir/OSZICAR_V.Mn.NaCl
mv DOSCAR DOSCARDir/DOSCAR_V.Mn.NaCl
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_V.Mn.Wurt POSCAR
./gen_POTCAR.sh V Mn
cp INPUT/INCAR .
./gen_INCAR V Mn INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_V.Mn.Wurt
mv OUTCAR OUTCARDir/OUTCAR_V.Mn.Wurt
mv OSZICAR OSZICARDir/OSZICAR_V.Mn.Wurt
mv DOSCAR DOSCARDir/DOSCAR_V.Mn.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_V.Fe.FCC POSCAR
./gen_POTCAR.sh V Fe
cp INPUT/INCAR .
./gen_INCAR V Fe INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_V.Fe.FCC
mv OUTCAR OUTCARDir/OUTCAR_V.Fe.FCC
mv OSZICAR OSZICARDir/OSZICAR_V.Fe.FCC
mv DOSCAR DOSCARDir/DOSCAR_V.Fe.FCC
date >> TIME_LOG.out


./gen_POSCAR V Fe 2 3.175 0.000
./gen_POTCAR.sh V Fe
cp INPUT/INCAR .
./gen_INCAR V Fe INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_V.Fe.CsCl
mv OUTCAR OUTCARDir/OUTCAR_V.Fe.CsCl
mv OSZICAR OSZICARDir/OSZICAR_V.Fe.CsCl
mv DOSCAR DOSCARDir/DOSCAR_V.Fe.CsCl
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_V.Fe.NaCl POSCAR
./gen_POTCAR.sh V Fe
cp INPUT/INCAR .
./gen_INCAR V Fe INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_V.Fe.NaCl
mv OUTCAR OUTCARDir/OUTCAR_V.Fe.NaCl
mv OSZICAR OSZICARDir/OSZICAR_V.Fe.NaCl
mv DOSCAR DOSCARDir/DOSCAR_V.Fe.NaCl
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_V.Fe.Wurt POSCAR
./gen_POTCAR.sh V Fe
cp INPUT/INCAR .
./gen_INCAR V Fe INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_V.Fe.Wurt
mv OUTCAR OUTCARDir/OUTCAR_V.Fe.Wurt
mv OSZICAR OSZICARDir/OSZICAR_V.Fe.Wurt
mv DOSCAR DOSCARDir/DOSCAR_V.Fe.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_V.Co.FCC POSCAR
./gen_POTCAR.sh V Co
cp INPUT/INCAR .
./gen_INCAR V Co INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_V.Co.FCC
mv OUTCAR OUTCARDir/OUTCAR_V.Co.FCC
mv OSZICAR OSZICARDir/OSZICAR_V.Co.FCC
mv DOSCAR DOSCARDir/DOSCAR_V.Co.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_V.Co.Wurt POSCAR
./gen_POTCAR.sh V Co
cp INPUT/INCAR .
./gen_INCAR V Co INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_V.Co.Wurt
mv OUTCAR OUTCARDir/OUTCAR_V.Co.Wurt
mv OSZICAR OSZICARDir/OSZICAR_V.Co.Wurt
mv DOSCAR DOSCARDir/DOSCAR_V.Co.Wurt
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_V.Ni.FCC POSCAR
./gen_POTCAR.sh V Ni
cp INPUT/INCAR .
./gen_INCAR V Ni INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_V.Ni.FCC
mv OUTCAR OUTCARDir/OUTCAR_V.Ni.FCC
mv OSZICAR OSZICARDir/OSZICAR_V.Ni.FCC
mv DOSCAR DOSCARDir/DOSCAR_V.Ni.FCC
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_V.Ni.CsCl POSCAR
./gen_POTCAR.sh V Ni
cp INPUT/INCAR .
./gen_INCAR V Ni INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_V.Ni.CsCl
mv OUTCAR OUTCARDir/OUTCAR_V.Ni.CsCl
mv OSZICAR OSZICARDir/OSZICAR_V.Ni.CsCl
mv DOSCAR DOSCARDir/DOSCAR_V.Ni.CsCl
date >> TIME_LOG.out


cp /scratch2/x1241ybc/HTS-Catalysts/CONTCARDir/CONTCAR_V.Ni.Wurt POSCAR
./gen_POTCAR.sh V Ni
cp INPUT/INCAR .
./gen_INCAR V Ni INCAR 400
mv INCAR.out INCAR
cp INPUT/KPOINTS .
rm CHG CHGCAR DOSCAR EIGENVAL WAVECAR
mpirun_rsh -np $NSLOTS -hostfile $TMPDIR/machines ~/bin/vasp > stdout
energy=`grep entropy OUTCAR | tail -1 | awk '{print $4}'`
if [[ -z $energy4 ]]; then
	energy4=0
fi
mv CONTCAR CONTCARDir/CONTCAR_V.Ni.Wurt
mv OUTCAR OUTCARDir/OUTCAR_V.Ni.Wurt
mv OSZICAR OSZICARDir/OSZICAR_V.Ni.Wurt
mv DOSCAR DOSCARDir/DOSCAR_V.Ni.Wurt
date >> TIME_LOG.out
