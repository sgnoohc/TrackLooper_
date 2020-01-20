#!/bin/bash

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
fi

if [[ $1 == *"2"* ]]; then
SAMPLE=trackingNtuple.root
SAMPLETAG=e200
PDGID=13
PTBOUND=0
fi

if [[ $1 == *"3"* ]]; then
SAMPLE=${TRACKINGNTUPLEDIR}/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root
SAMPLETAG=pu200_pdgid13
PDGID=13
PTBOUND=0
fi

if [[ $1 == *"4"* ]]; then
SAMPLE=${TRACKINGNTUPLEDIR}/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root
SAMPLETAG=pu200_pdgid211
PDGID=211
PTBOUND=0
fi

if [[ $1 == *"5"* ]]; then
SAMPLE=${TRACKINGNTUPLEDIR}/CMSSW_10_4_0_mtd5/src/trackingNtuple_TTbar_PU200.root
SAMPLETAG=pu200_pdgid11
PDGID=11
PTBOUND=0
fi

if [[ $1 == *"6"* ]]; then
SAMPLE=${TRACKINGNTUPLEDIR}/CMSSW_10_4_0_mtd5/src/trackingNtuple_DisplacedSUSY_stopToChi_Gravitino_M_1000_700_10mm.root
SAMPLETAG=pu200_displaced_pdgid13
PDGID=13
PTBOUND=0
fi

if [[ $1 == *"7"* ]]; then
SAMPLE=${TRACKINGNTUPLEDIR}/CMSSW_10_4_0_mtd5/src/trackingNtuple_GMSB_L100_Ctau100.root
SAMPLETAG=pu200_displaced_gmsb_ctau100_pdgid13
PDGID=13
PTBOUND=0
fi

if [[ $1 == *"8"* ]]; then
SAMPLE=${TRACKINGNTUPLEDIR}/CMSSW_10_4_0_mtd5/src/trackingNtuple_GMSB_L100_Ctau100.root
SAMPLETAG=pu200_displaced_gmsb_ctau100_pdgid11
PDGID=11
PTBOUND=0
fi

if [[ $1 == *"9"* ]]; then
SAMPLE=${TRACKINGNTUPLEDIR}/CMSSW_10_4_0_mtd5/src/trackingNtuple_GMSB_L100_Ctau100.root
SAMPLETAG=pu200_displaced_gmsb_ctau100_pdgid211
PDGID=211
PTBOUND=0
fi

OUTPUTFILE=fulleff_${SAMPLETAG}.root

rm -f ${OUTPUTFILE}

CMD="./doAnalysis -i ${SAMPLE} -n -1 -t trackingNtuple/tree -n -1 -e -p ${PTBOUND} -o ${OUTPUTFILE} -g ${PDGID}"
echo $CMD
${CMD}
mv ${OUTPUTFILE} results/${SAMPLETAG}$2/
python plot.py 1 results/${SAMPLETAG}$2/${OUTPUTFILE} ${SAMPLETAG}
python plot.py 2 results/${SAMPLETAG}$2/${OUTPUTFILE} ${SAMPLETAG}
python plot.py 3 results/${SAMPLETAG}$2/${OUTPUTFILE} ${SAMPLETAG}
python plot.py 4 results/${SAMPLETAG}$2/${OUTPUTFILE} ${SAMPLETAG}

mkdir -p results/${SAMPLETAG}$2/
echo "$3" > results/${SAMPLETAG}$2/description.txt
cp -r plots_${SAMPLETAG}/ results/${SAMPLETAG}$2/

# ./doAnalysis -i ${TRACKINGNTUPLEDIR}/CMSSW_10_4_0/src/trackingNtuple_pt0p5_1p5_10MuGun.root -n -1 -t trackingNtuple/tree -n -1 -e 1 -p 3 -o muonpt0p95to1p05_sgeff_.root -d
# mv debug.root algoeff_md_pt0p5_1p5.root
# ./doAnalysis -i ${TRACKINGNTUPLEDIR}/CMSSW_10_4_0/src/trackingNtuple_pt0p5_1p5_10MuGun.root -n -1 -t trackingNtuple/tree -n -1 -e 2 -p 3 -o muonpt0p95to1p05_sgeff_.root -d
# mv debug.root algoeff_sg_pt0p5_1p5.root
# ./doAnalysis -i ${TRACKINGNTUPLEDIR}/CMSSW_10_4_0/src/trackingNtuple_pt0p5_1p5_10MuGun.root -n -1 -t trackingNtuple/tree -n -1 -e 3 -p 3 -o muonpt0p95to1p05_sgeff_.root -d
# mv debug.root algoeff_tl_pt0p5_1p5.root
# ./doAnalysis -i ${TRACKINGNTUPLEDIR}/CMSSW_10_4_0/src/trackingNtuple_pt0p5_1p5_10MuGun.root -n -1 -t trackingNtuple/tree -n -1 -e 4 -p 3 -o muonpt0p95to1p05_sgeff_.root -d
# mv debug.root algoeff_tc_pt0p5_1p5.root
