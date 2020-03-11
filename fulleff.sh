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
SAMPLE=/hadoop/cms/store/user/slava77/CMSSW_10_4_0_patch1-tkNtuple/pass-e072c1a/27411.0_TenMuExtendedE_0_200/trackingNtuple.root
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

if [[ $1 == *"10"* ]]; then
SAMPLE=${TRACKINGNTUPLEDIR}/CMSSW_10_4_0/src/trackingNtuple_100_pt0p5_3p0.root
SAMPLETAG=pt0p5_3p0
PDGID=13
PTBOUND=5
fi

if [[ $1 == *"11"* ]]; then
SAMPLE=${TRACKINGNTUPLEDIR}/CMSSW_10_4_0/src/trackingNtuple_10_pt0p5_5p0.root
SAMPLETAG=pt0p5_5p0
PDGID=13
PTBOUND=6
fi

OUTPUTFILE=fulleff_${SAMPLETAG}.root

rm -f ${OUTPUTFILE}

CMD="./doAnalysis -i ${SAMPLE} -n -1 -t trackingNtuple/tree -e -p ${PTBOUND} -o ${OUTPUTFILE} -g ${PDGID}"
echo $CMD
mkdir -p results/${SAMPLETAG}$2/
${CMD}
mv ${OUTPUTFILE} results/${SAMPLETAG}$2/
echo "$3" > results/${SAMPLETAG}$2/description.txt

# plotting
sh fulleff_plot.sh ${SAMPLETAG} $2
