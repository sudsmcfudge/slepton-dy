#!/bin/bash


for f in Bino_LSP_slepLslepL.dat Bino_LSP_slepRslepR.dat Bino_LSP_slepsnu.dat Bino_LSP_snusnu.dat Higgsino_LSP_slepLslepL.dat Higgsino_LSP_slepRslepR.dat Higgsino_LSP_slepsnu.dat Higgsino_LSP_snusnu.dat Wino_LSP_slepLslepL.dat Wino_LSP_slepRslepR.dat Wino_LSP_slepsnu.dat Wino_LSP_snusnu.dat; do
    echo $f

    arr=(`echo $f | tr "." "\n"`)

    fn=${arr[0]}_cls.dat 
    #echo $fn

    ./conf.exe $f > $fn


done