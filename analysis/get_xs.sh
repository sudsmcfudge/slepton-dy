#!/bin/bash

events_dir=/home/eckel/local/MadGraph5/diboson_eeevj/Events

for run in $events_dir/run*; do
#    echo $run

    sigma_pb=`tail -n 1 $run/tag_1_pythia.log | gawk '{print $4}'`

    echo $sigma_pb

done
