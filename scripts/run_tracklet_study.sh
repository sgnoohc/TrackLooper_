#!/bin/bash

function usage {
    echo "Usage:"
    echo "    $0 TAG [DATASET]"
    exit
}

if [ -z $1 ]; then
    usage
fi

TAG=$1

if [ -z $2 ]; then
    DATASET=0
else
    DATASET=$2
fi

git st > gitversion.txt
git diff >> gitversion.txt
cd SDL/
git st >> ../gitversion.txt
git diff >> ../gitversion.txt
cd ../

TRACKINGNTUPLEDIR=/home/users/phchang/public_html/analysis/sdl/trackingNtuple

if [[ $DATASET == *"0"* ]]; then
    SAMPLETYPE=pu200
    rm ${SAMPLETYPE}_*_${TAG}.root
    PU200SAMPLE=/nfs-7/userdata/bsathian/SDL_trackingNtuple/ttbar_highPU/trackingNtuple_with_PUinfo_500_evts.root
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_0_${TAG}.root  -v 1 -x 0  > ${SAMPLETYPE}_0.log 2>&1 " >  .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_1_${TAG}.root  -v 1 -x 1  > ${SAMPLETYPE}_1.log 2>&1 " >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_2_${TAG}.root  -v 1 -x 2  > ${SAMPLETYPE}_2.log 2>&1 " >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_3_${TAG}.root  -v 1 -x 3  > ${SAMPLETYPE}_3.log 2>&1 " >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_4_${TAG}.root  -v 1 -x 4  > ${SAMPLETYPE}_4.log 2>&1 " >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_5_${TAG}.root  -v 1 -x 5  > ${SAMPLETYPE}_5.log 2>&1 " >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_6_${TAG}.root  -v 1 -x 6  > ${SAMPLETYPE}_6.log 2>&1 " >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_7_${TAG}.root  -v 1 -x 7  > ${SAMPLETYPE}_7.log 2>&1 " >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_8_${TAG}.root  -v 1 -x 8  > ${SAMPLETYPE}_8.log 2>&1 " >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_9_${TAG}.root  -v 1 -x 9  > ${SAMPLETYPE}_9.log 2>&1 " >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_10_${TAG}.root -v 1 -x 10 > ${SAMPLETYPE}_10.log 2>&1" >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_11_${TAG}.root -v 1 -x 11 > ${SAMPLETYPE}_11.log 2>&1" >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_12_${TAG}.root -v 1 -x 12 > ${SAMPLETYPE}_12.log 2>&1" >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_13_${TAG}.root -v 1 -x 13 > ${SAMPLETYPE}_13.log 2>&1" >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_14_${TAG}.root -v 1 -x 14 > ${SAMPLETYPE}_14.log 2>&1" >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_15_${TAG}.root -v 1 -x 15 > ${SAMPLETYPE}_15.log 2>&1" >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_16_${TAG}.root -v 1 -x 16 > ${SAMPLETYPE}_16.log 2>&1" >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_17_${TAG}.root -v 1 -x 17 > ${SAMPLETYPE}_17.log 2>&1" >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_18_${TAG}.root -v 1 -x 18 > ${SAMPLETYPE}_18.log 2>&1" >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_19_${TAG}.root -v 1 -x 19 > ${SAMPLETYPE}_19.log 2>&1" >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_20_${TAG}.root -v 1 -x 20 > ${SAMPLETYPE}_20.log 2>&1" >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_21_${TAG}.root -v 1 -x 21 > ${SAMPLETYPE}_21.log 2>&1" >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_22_${TAG}.root -v 1 -x 22 > ${SAMPLETYPE}_22.log 2>&1" >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_23_${TAG}.root -v 1 -x 23 > ${SAMPLETYPE}_23.log 2>&1" >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_24_${TAG}.root -v 1 -x 24 > ${SAMPLETYPE}_24.log 2>&1" >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_25_${TAG}.root -v 1 -x 25 > ${SAMPLETYPE}_25.log 2>&1" >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_26_${TAG}.root -v 1 -x 26 > ${SAMPLETYPE}_26.log 2>&1" >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_27_${TAG}.root -v 1 -x 27 > ${SAMPLETYPE}_27.log 2>&1" >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_28_${TAG}.root -v 1 -x 28 > ${SAMPLETYPE}_28.log 2>&1" >> .jobs.txt
    echo "time ./doAnalysis -i ${PU200SAMPLE} -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_29_${TAG}.root -v 1 -x 29 > ${SAMPLETYPE}_29.log 2>&1" >> .jobs.txt
fi

if [[ $DATASET == *"1"* ]]; then
    SAMPLETYPE=pt0p95_1p05
    rm ${SAMPLETYPE}_*_${TAG}.root
    echo "time ./doAnalysis -i ${TRACKINGNTUPLEDIR}/CMSSW_10_4_0/src/trackingNtuple_pt0p95_1p05_10MuGun.root -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_0_${TAG}.root | tee ${SAMPLETYPE}_0.log 2>&1 " >  .jobs.txt
fi

if [[ $DATASET == *"2"* ]]; then
    SAMPLETYPE=pt0p5_2p0
    rm ${SAMPLETYPE}_*_${TAG}.root
    echo "time ./doAnalysis -i ${TRACKINGNTUPLEDIR}/CMSSW_10_4_0/src/trackingNtuple_100_pt0p5_2p0.root -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_0_${TAG}.root | tee ${SAMPLETYPE}_0.log 2>&1 " >  .jobs.txt
fi

if [[ $DATASET == *"3"* ]]; then
    SAMPLETYPE=pt0p5_3p0
    rm ${SAMPLETYPE}_*_${TAG}.root
    echo "time ./doAnalysis -i ${TRACKINGNTUPLEDIR}/CMSSW_10_4_0/src/trackingNtuple_100_pt0p5_3p0.root -n -1 -t trackingNtuple/tree -o ${SAMPLETYPE}_0_${TAG}.root -n 1000 | tee ${SAMPLETYPE}_0.log 2>&1 " >  .jobs.txt
fi

sh rooutil/xargs.sh -n 10 .jobs.txt

hadd -f ${SAMPLETYPE}_${TAG}.root ${SAMPLETYPE}_*_${TAG}.root

mkdir -p results/${TAG}

mv ${SAMPLETYPE}_${TAG}.root results/${TAG}
mv ${SAMPLETYPE}_*_${TAG}.root results/${TAG}
mv ${SAMPLETYPE}_*.log results/${TAG}
mv gitversion.txt results/${TAG}


