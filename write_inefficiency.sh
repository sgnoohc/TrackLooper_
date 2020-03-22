#!/bin/bash

if [ -z $1 ]; then
    echo "Usage:"
    echo "   sh $0 TAG"
    exit
fi

TAG=$1

mkdir -p debug_ntuple_output/
rm debug_ntuple_output/debug_${TAG}_*.root
rm debug_ntuple_output/debug_${TAG}_*.log
NJOBS=16
for i in $(seq 0 $((NJOBS-1))); do
    (set -x ;./doAnalysis -j ${NJOBS} -I ${i} -i /home/users/phchang/public_html/analysis/sdl/trackingNtuple/CMSSW_10_4_0/src/trackingNtuple_100_pt0p5_2p0.root -t trackingNtuple/tree -p 4 -g 13 -l 0 -n -1 -o debug_ntuple_output/debug_${TAG}_${i}.root > debug_ntuple_output/debug_${TAG}_${i}.log) &
done

sleep 1
echo "<== Submitted parallel jobs ..."
wait
