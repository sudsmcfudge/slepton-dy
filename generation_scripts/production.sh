#!/bin/bash
#
# script to run over parameter space grid
# 10 GeV spacing in m_slep, m_chi1 space

localdir=`pwd`
projdir=$HOME/local/MadGraph5/mssm_elel_eennj
inputfile=input_table.dat
susyhit_temp=suspect2_lha.template
susyhitdir=$HOME/local/susyhit
suspect_file=$susyhitdir/suspect2_lha.in
susyhit_output=$susyhitdir/susyhit_slha.out 

#ncores=`grep -m 1 "cpu cores" /proc/cpuinfo | gawk '{print $4}'`
#ncores=`grep "processor" /proc/cpuinfo | wc -l`

ncores=4

echo "PROGRAM RUNNING"
echo $localdir
echo $projdir
echo $inputfile
echo $susyhit_temp
echo $suspect_file
echo $susyhitdir
echo $susyhit_output 

# file with params to loop over
mslep_list=(`gawk {'print $1'} $inputfile`)
mchi_list=(`gawk {'print $2'} $inputfile`)

len=${#mchi_list[@]}
len=`expr $len - 1`
echo $len

for i in `seq 0 $len`; do
    mslep=${mslep_list[i]}
    mchi=${mchi_list[i]}

    echo $mslep $mchi

    #fill template and copy to susyhit directory
    sed -e "s/__Mchi1__/$mchi/" -e "s/__Mslep__/$mslep/" $susyhit_temp > $suspect_file

    #run susyhit
    cd $susyhitdir
    ./run #"run" is the name of the susyhit executable
    cd $localdir

    # determine whether there is an error                                  
    grep -q "tachyon" $susyhitdir/slhaspectrum.in
    code=$?
    if [ $code -eq 0 ]; then
        echo ERROR
	exit
    fi

    #copy susyhit output to paramcard    
    cp $susyhit_output $projdir/Cards/param_card.dat
    #make changes to runcard? other cards?

    cd $projdir/bin
    prefix=run0_7TeV_mslep_"$mslep"_mchi_"$mchi"

    if [ ! -d $projdir/Events/$prefix ]; then
	if [ $ncores -gt 1 ]; then
	    echo ">2 cores"
	    ./generate_events 2 $ncores $prefix
	elif [ $ncores -eq 1 ]; then
	    echo "1 core"
	    ./generate_events 0 $prefix
	else
	    echo "invalid number of cores: $ncores"
	    cd $localdir
	    exit
	fi
    fi

    #check run
    if [ ! -e $projdir/Events/$prefix/tag_1_pgs_events.root ]; then
	echo $projdir/Events/$prefix/tag_1_pgs_events.root
	echo "File does not exist!!"
	cd $localdir
	exit
    fi

    # old madgraph versions
    #if [ ! -e $projdir/Events/"$prefix"_pgs_events.root ]; then
    #    echo $projdir/Events/"$prefix"_pgs_events.root
    #    echo "File does not exist!!"
    #    cd $localdir
    #    exit
    #fi

    #analysis
    #cleanup
    rm -f $projdir/Events/$prefix/tag_1_pythia_events.hep.gz

    cd $localdir

done
