#!/bin/bash

# sm_eevvj

#events_dir=/home/eckel/local/MadGraph5/sm_eevvj/Events

# ttbar

#events_dir=/home/eckel/local/MadGraph5/tt_bbeevvjj/Events

# signal

events_dir=/home/eckel/local/MadGraph5/mssm_elel_eennj/Events

for run in $events_dir/run0_7TeV_mslep_*_mchi_*; do
    echo $run
    file=${run##*/} #get the filename

    arr=(`echo $file | tr "_" "\n"`)

#    mslep=${arr[2]}
#    mchi=${arr[4]}
    mslep=${arr[3]}
    mchi=${arr[5]}

    echo $file
#    n_matched=`grep "All included subprocesses" $run/tag_1_pythia.log | tail -n 1 | gawk '{print $7}'`
#    n_gen=`grep "All included subprocesses" $run/tag_1_pythia.log | tail -n 1 | gawk '{print $8}'`
    sigma_mb=`grep "All included subprocesses" $run/tag_1_pythia.log | tail -n 1 | gawk '{print $10}'`

    sigma_pb=`tail -n 1 $run/tag_1_pythia.log | gawk '{print $4}'`

    n_arr=(`./mt2_tree.exe $run/tag_*_pgs_events.root "needsaname.root" | tr "" "\n"`)
    n_pcuts=`./mt2_cuts.exe "needsaname.root" | tail -n 1`
#    n_pcuts=`./mt2_cuts.exe "needsaname.root" | tail -n 1`

    n_gen=${n_arr[0]}
    n_matched=${n_arr[1]}

    echo $mslep $mchi $n_pcuts $n_matched $n_gen $sigma_pb >> binoLSP_7TeV_table.dat

done

