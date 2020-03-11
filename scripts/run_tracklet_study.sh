#!/bin/bash

function usage {
    echo "Usage:"
    echo "    $0 TAG"
    exit
}

if [ -z $1 ]; then
    usage
fi

TAG=$1

git st > gitversion.txt
git diff >> gitversion.txt
cd SDL/
git st >> ../gitversion.txt
git diff >> ../gitversion.txt
cd ../

rm pu200_*_${TAG}.root
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_0_${TAG}.root  -v 1 -x 0  > pu200_0.log 2>&1 " >  .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_1_${TAG}.root  -v 1 -x 1  > pu200_1.log 2>&1 " >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_2_${TAG}.root  -v 1 -x 2  > pu200_2.log 2>&1 " >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_3_${TAG}.root  -v 1 -x 3  > pu200_3.log 2>&1 " >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_4_${TAG}.root  -v 1 -x 4  > pu200_4.log 2>&1 " >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_5_${TAG}.root  -v 1 -x 5  > pu200_5.log 2>&1 " >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_6_${TAG}.root  -v 1 -x 6  > pu200_6.log 2>&1 " >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_7_${TAG}.root  -v 1 -x 7  > pu200_7.log 2>&1 " >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_8_${TAG}.root  -v 1 -x 8  > pu200_8.log 2>&1 " >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_9_${TAG}.root  -v 1 -x 9  > pu200_9.log 2>&1 " >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_10_${TAG}.root -v 1 -x 10 > pu200_10.log 2>&1" >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_11_${TAG}.root -v 1 -x 11 > pu200_11.log 2>&1" >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_12_${TAG}.root -v 1 -x 12 > pu200_12.log 2>&1" >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_13_${TAG}.root -v 1 -x 13 > pu200_13.log 2>&1" >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_14_${TAG}.root -v 1 -x 14 > pu200_14.log 2>&1" >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_15_${TAG}.root -v 1 -x 15 > pu200_15.log 2>&1" >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_16_${TAG}.root -v 1 -x 16 > pu200_16.log 2>&1" >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_17_${TAG}.root -v 1 -x 17 > pu200_17.log 2>&1" >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_18_${TAG}.root -v 1 -x 18 > pu200_18.log 2>&1" >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_19_${TAG}.root -v 1 -x 19 > pu200_19.log 2>&1" >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_20_${TAG}.root -v 1 -x 20 > pu200_20.log 2>&1" >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_21_${TAG}.root -v 1 -x 21 > pu200_21.log 2>&1" >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_22_${TAG}.root -v 1 -x 22 > pu200_22.log 2>&1" >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_23_${TAG}.root -v 1 -x 23 > pu200_23.log 2>&1" >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_24_${TAG}.root -v 1 -x 24 > pu200_24.log 2>&1" >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_25_${TAG}.root -v 1 -x 25 > pu200_25.log 2>&1" >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_26_${TAG}.root -v 1 -x 26 > pu200_26.log 2>&1" >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_27_${TAG}.root -v 1 -x 27 > pu200_27.log 2>&1" >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_28_${TAG}.root -v 1 -x 28 > pu200_28.log 2>&1" >> .jobs.txt
echo "time ./doAnalysis -i ../trackingNtuple/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root -n -1 -t trackingNtuple/tree -o pu200_29_${TAG}.root -v 1 -x 29 > pu200_29.log 2>&1" >> .jobs.txt

sh rooutil/xargs.sh -n 5 .jobs.txt

hadd -f pu200_${TAG}.root pu200_*_${TAG}.root

mkdir -p results/${TAG}

mv pu200_${TAG}.root results/${TAG}
mv pu200_*_${TAG}.root results/${TAG}
mv pu200_*.log results/${TAG}
mv gitversion.txt results/${TAG}


