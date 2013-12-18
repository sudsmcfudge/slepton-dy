#!/bin/bash

events_dir=/home/eckel/local/MadGraph5/tt_bbeevvjj/Events

for run in $events_dir/run_14TeV_jetcuts_*; do
#    echo $run

    sigma_pb=`tail -n 1 $run/tag_1_pythia.log | gawk '{print $4}'`

    echo $sigma_pb

done
