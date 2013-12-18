#!/bin/bash

# sm_eevvj

#events_dir=/home/eckel/local/MadGraph5/sm_eevvj/Events

# ttbar

#events_dir=/home/eckel/local/MadGraph5/tt_bbeevvjj/Events

# signal

#events_dir=/home/eckel/local/MadGraph5/mssm_diselec_eennj/Events
events_dir=/home/eckel/local/MadGraph5/mssm_dismuon_mmnnj/Events

for run in $events_dir/run1_8TeV_mslep_*_mchi_*; do
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

    #n_arr=(`./elec_tree.exe $run/tag_*_delphes.root "temp.root" | tr "" "\n"`)
    #n_pcuts=`./elec_cuts.exe "temp.root" | tail -n 1`
    n_arr=(`./muon_tree.exe $run/tag_*_delphes.root "temp.root" | tr "" "\n"`)
    n_pcuts=`./muon_cuts.exe "temp.root" | tail -n 1`

#    n_pcuts=`./mt2_cuts.exe "temp.root" | tail -n 1`

    n_gen=${n_arr[0]}
    n_matched=${n_arr[1]}

    #echo $mslep $mchi $n_pcuts $n_matched $n_gen $sigma_pb >> binoLSP_8TeV_table_full_elec.dat
    echo $mslep $mchi $n_pcuts $n_matched $n_gen $sigma_pb >> binoLSP_8TeV_table_full_muon.dat

done

