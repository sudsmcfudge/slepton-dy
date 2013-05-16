#!/bin/bash

localdir=`pwd`
projdir=$HOME/local/MadGraph5/diboson_eeevj

name=run_7TeV

max=20

cd $projdir/bin

for i in `seq 0 $max`; do
    if [ ! -d $projdir/Events/"$name"_"$i" ]; then
	./generate_events 2 4 "$name"_"$i"
	rm -f $projdir/Events/"$name"_"$i"/tag_1_pythia_events.hep.gz
    fi
done

cd $localdir
