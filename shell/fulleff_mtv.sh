#!/bin/bash

usage() {
    echo "Usage:"
    echo ""
    echo "   $0 SAMPLEID TAG DESCRIPTION"
    echo ""
    exit
}

if [ -z "$1" ]; then usage; fi
if [ -z "$2" ]; then usage; fi
if [ -z "$3" ]; then usage; fi

TRACKINGNTUPLEDIR=/home/users/phchang/public_html/analysis/sdl/trackingNtuple

if [[ $1 == *"1"* ]]; then
SAMPLE=${TRACKINGNTUPLEDIR}/CMSSW_10_4_0/src/trackingNtuple_pt0p5_1p5_10MuGun.root
SAMPLE=${TRACKINGNTUPLEDIR}/CMSSW_10_4_0/src/trackingNtuple_100_pt0p5_2p0.root
SAMPLETAG=pt0p5_2p0
SAMPLETAG=pt0p5_2p0_nosimhit13requirement
SAMPLETAG=pt0p5_2p0_nosimhit13requirement_nocurlers
SAMPLETAG=pt0p5_2p0_nosimhit13requirement_nocurlers_v1
SAMPLETAG=pt0p5_2p0_nosimhit13requirement_nocurlers_v2
SAMPLETAG=pt0p5_2p0_nosimhit13requirement_pdgid13
SAMPLETAG=pt0p5_2p0_tracklet_via_map
SAMPLETAG=pt0p5_2p0
PDGID=13
PTBOUND=4
NEVENTS=1000
DOPARALLEL=false
fi

if [[ $1 == *"2"* ]]; then
SAMPLE=trackingNtuple.root
SAMPLETAG=e200
PDGID=13
PTBOUND=0
NEVENTS=-1
DOPARALLEL=false
fi

if [[ $1 == *"3"* ]]; then
SAMPLE=${TRACKINGNTUPLEDIR}/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root
SAMPLETAG=pu200_pdgid13
PDGID=13
PTBOUND=0
NEVENTS=252
DOPARALLEL=true
fi

if [[ $1 == *"4"* ]]; then
SAMPLE=${TRACKINGNTUPLEDIR}/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root
SAMPLETAG=pu200_pdgid211
PDGID=211
PTBOUND=0
NEVENTS=252
DOPARALLEL=true
fi

if [[ $1 == *"5"* ]]; then
SAMPLE=${TRACKINGNTUPLEDIR}/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root
SAMPLETAG=pu200_pdgid11
PDGID=11
PTBOUND=0
NEVENTS=252
DOPARALLEL=true
fi

if [[ $1 == *"6"* ]]; then
SAMPLE=${TRACKINGNTUPLEDIR}/CMSSW_10_4_0_mtd5/src/trackingNtuple_DisplacedSUSY_stopToChi_Gravitino_M_1000_700_10mm.root
SAMPLETAG=pu200_displaced_pdgid13
PDGID=13
PTBOUND=0
NEVENTS=252
DOPARALLEL=true
fi

if [[ $1 == *"7"* ]]; then
SAMPLE=${TRACKINGNTUPLEDIR}/CMSSW_10_4_0_mtd5/src/trackingNtuple_GMSB_L100_Ctau100.root
SAMPLETAG=pu200_displaced_gmsb_ctau100_pdgid13
PDGID=13
PTBOUND=0
NEVENTS=252
DOPARALLEL=true
fi

if [[ $1 == *"8"* ]]; then
SAMPLE=${TRACKINGNTUPLEDIR}/CMSSW_10_4_0_mtd5/src/trackingNtuple_GMSB_L100_Ctau100.root
SAMPLETAG=pu200_displaced_gmsb_ctau100_pdgid11
PDGID=11
PTBOUND=0
NEVENTS=252
DOPARALLEL=true
fi

if [[ $1 == *"9"* ]]; then
SAMPLE=${TRACKINGNTUPLEDIR}/CMSSW_10_4_0_mtd5/src/trackingNtuple_GMSB_L100_Ctau100.root
SAMPLETAG=pu200_displaced_gmsb_ctau100_pdgid211
PDGID=211
PTBOUND=0
NEVENTS=252
DOPARALLEL=true
fi

JOBTAG=$2

# If need to run parallel run in parallel
if [ $DOPARALLEL = true ]; then
    echo "Running parallel"
    rm .jobs.txt
    for i in $(seq 0 251); do
        OUTPUTFILE=fulleff_${SAMPLETAG}_mtv_event${i}.root
        rm -f ${OUTPUTFILE}
        CMD="./doAnalysis -i ${SAMPLE} -t trackingNtuple/tree -n ${NEVENTS} -m -p ${PTBOUND} -o ${OUTPUTFILE} -g ${PDGID} -x ${i}"
        echo $CMD >> .jobs.txt
    done
    sh rooutil/xargs.sh -n 10 .jobs.txt
    OUTPUTFILE=fulleff_${SAMPLETAG}_mtv.root
    rm -f ${OUTPUTFILE}
    hadd -f ${OUTPUTFILE} fulleff_${SAMPLETAG}_mtv_event*.root
else
    OUTPUTFILE=fulleff_${SAMPLETAG}_mtv.root
    rm -f ${OUTPUTFILE}
    CMD="./doAnalysis -i ${SAMPLE} -t trackingNtuple/tree -n ${NEVENTS} -m -p ${PTBOUND} -o ${OUTPUTFILE} -g ${PDGID}"
    echo $CMD
    ${CMD}
fi

#
# Aggregate result
#
mkdir -p results/${SAMPLETAG}_${JOBTAG}/
mv ${OUTPUTFILE} results/${SAMPLETAG}_${JOBTAG}/

#
# Plotting
#
OUTPUTFILE=fulleff_${SAMPLETAG}_mtv.root
rm -rf plots/
rm -rf plots_${SAMPLETAG}
python plot.py 8 results/${SAMPLETAG}_${JOBTAG}/${OUTPUTFILE} ${SAMPLETAG}

echo "$3" > results/${SAMPLETAG}_${JOBTAG}/description.txt
cp -r plots_${SAMPLETAG}/ results/${SAMPLETAG}_${JOBTAG}/

# ./doAnalysis -i ${TRACKINGNTUPLEDIR}/CMSSW_10_4_0/src/trackingNtuple_pt0p5_1p5_10MuGun.root -n -1 -t trackingNtuple/tree -n -1 -e 1 -p 3 -o muonpt0p95to1p05_sgeff_.root -d
# mv debug.root algoeff_md_pt0p5_1p5.root
# ./doAnalysis -i ${TRACKINGNTUPLEDIR}/CMSSW_10_4_0/src/trackingNtuple_pt0p5_1p5_10MuGun.root -n -1 -t trackingNtuple/tree -n -1 -e 2 -p 3 -o muonpt0p95to1p05_sgeff_.root -d
# mv debug.root algoeff_sg_pt0p5_1p5.root
# ./doAnalysis -i ${TRACKINGNTUPLEDIR}/CMSSW_10_4_0/src/trackingNtuple_pt0p5_1p5_10MuGun.root -n -1 -t trackingNtuple/tree -n -1 -e 3 -p 3 -o muonpt0p95to1p05_sgeff_.root -d
# mv debug.root algoeff_tl_pt0p5_1p5.root
# ./doAnalysis -i ${TRACKINGNTUPLEDIR}/CMSSW_10_4_0/src/trackingNtuple_pt0p5_1p5_10MuGun.root -n -1 -t trackingNtuple/tree -n -1 -e 4 -p 3 -o muonpt0p95to1p05_sgeff_.root -d
# mv debug.root algoeff_tc_pt0p5_1p5.root
