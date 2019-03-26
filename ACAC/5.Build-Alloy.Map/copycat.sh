#!/bin/sh

rm -rf TOT_DOSsim-Pd.out
rm -rf TOT_DOSsim-Pt.out
rm -rf TOT_DOSsim-Ru.out

cat TOT_DOSsim.DOSCAR_Pd.Pd.FCC-.out > TOT_DOSsim-Pd.out
cat TOT_DOSsim_HCP.DOSCAR_Pd.Pd.FCC-.out >> TOT_DOSsim-Pd.out

cat TOT_DOSsim.DOSCAR_Pt.Pt.FCC-.out > TOT_DOSsim-Pt.out
cat TOT_DOSsim_HCP.DOSCAR_Pt.Pt.FCC-.out >> TOT_DOSsim-Pt.out

cat TOT_DOSsim.DOSCAR_Ru.Ru.HCP-.out > TOT_DOSsim-Ru.out
cat TOT_DOSsim_HCP.DOSCAR_Ru.Ru.HCP-.out >> TOT_DOSsim-Ru.out
