#!/bin/bash

SAMPLE=$1
DESCRIPTION=$2
TAG=$3
EFFTYPE=$4
MDFILE=${SAMPLE}_${TAG}

echo "" > ${MDFILE}.md

if [[ ${EFFTYPE} == *"algo_eff"* ]]; then
    echo "# Efficiency plots" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "${DESCRIPTION}" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "## Algorithmic efficiency" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "### MiniDoublet" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "#### Efficiency" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "   * [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/mdeff/?md_eff_bbbbbb_pt_by_layer._eff)" >> ${MDFILE}.md
    echo "   * [ptzoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/mdeff/?md_eff_bbbbbb_ptzoom_by_layer._eff)" >> ${MDFILE}.md
    echo "   * [eta](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/mdeff/?md_eff_bbbbbb_eta_by_layer._eff)" >> ${MDFILE}.md
    echo "   * [etazoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/mdeff/?md_eff_bbbbbb_etazoom_by_layer._eff)" >> ${MDFILE}.md
    echo "   * [dxy](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/mdeff/?md_eff_bbbbbb_dxy_by_layer._eff)" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "#### Numerator and Denominator overlay" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "   * [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/mdeff/?md_eff_bbbbbb_pt_by_layer._numden)" >> ${MDFILE}.md
    echo "   * [ptzoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/mdeff/?md_eff_bbbbbb_ptzoom_by_layer._numden)" >> ${MDFILE}.md
    echo "   * [eta](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/mdeff/?md_eff_bbbbbb_eta_by_layer._numden)" >> ${MDFILE}.md
    echo "   * [etazoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/mdeff/?md_eff_bbbbbb_etazoom_by_layer._numden)" >> ${MDFILE}.md
    echo "   * [dxy](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/mdeff/?md_eff_bbbbbb_dxy_by_layer._numden)" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "### Segment" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "#### Efficiency" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "   * [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/sgeff/?sg_eff_bbbbbb_pt_by_layer._eff)" >> ${MDFILE}.md
    echo "   * [ptzoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/sgeff/?sg_eff_bbbbbb_ptzoom_by_layer._eff)" >> ${MDFILE}.md
    echo "   * [eta](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/sgeff/?sg_eff_bbbbbb_eta_by_layer._eff)" >> ${MDFILE}.md
    echo "   * [etazoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/sgeff/?sg_eff_bbbbbb_etazoom_by_layer._eff)" >> ${MDFILE}.md
    echo "   * [dxy](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/sgeff/?sg_eff_bbbbbb_dxy_by_layer._eff)" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "#### Numerator and Denominator overlay" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "   * [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/sgeff/?sg_eff_bbbbbb_pt_by_layer._numden)" >> ${MDFILE}.md
    echo "   * [ptzoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/sgeff/?sg_eff_bbbbbb_ptzoom_by_layer._numden)" >> ${MDFILE}.md
    echo "   * [eta](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/sgeff/?sg_eff_bbbbbb_eta_by_layer._numden)" >> ${MDFILE}.md
    echo "   * [etazoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/sgeff/?sg_eff_bbbbbb_etazoom_by_layer._numden)" >> ${MDFILE}.md
    echo "   * [dxy](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/sgeff/?sg_eff_bbbbbb_dxy_by_layer._numden)" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "### Tracklet" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "#### Efficiency" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "   * [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tleff/?tl_eff_bbbbbb_pt_by_layer._eff)" >> ${MDFILE}.md
    echo "   * [ptzoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tleff/?tl_eff_bbbbbb_ptzoom_by_layer._eff)" >> ${MDFILE}.md
    echo "   * [eta](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tleff/?tl_eff_bbbbbb_eta_by_layer._eff)" >> ${MDFILE}.md
    echo "   * [etazoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tleff/?tl_eff_bbbbbb_etazoom_by_layer._eff)" >> ${MDFILE}.md
    echo "   * [dxy](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tleff/?tl_eff_bbbbbb_dxy_by_layer._eff)" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "#### Numerator and Denominator overlay" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "   * [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tleff/?tl_eff_bbbbbb_pt_by_layer._numden)" >> ${MDFILE}.md
    echo "   * [ptzoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tleff/?tl_eff_bbbbbb_ptzoom_by_layer._numden)" >> ${MDFILE}.md
    echo "   * [eta](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tleff/?tl_eff_bbbbbb_eta_by_layer._numden)" >> ${MDFILE}.md
    echo "   * [etazoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tleff/?tl_eff_bbbbbb_etazoom_by_layer._numden)" >> ${MDFILE}.md
    echo "   * [dxy](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tleff/?tl_eff_bbbbbb_dxy_by_layer._numden)" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "### Track Candidate" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "#### Efficiency" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "   * [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tceff/?tc_eff_bbbbbb_pt_by_layer._eff)" >> ${MDFILE}.md
    echo "   * [ptzoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tceff/?tc_eff_bbbbbb_ptzoom_by_layer._eff)" >> ${MDFILE}.md
    echo "   * [eta](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tceff/?tc_eff_bbbbbb_eta_by_layer._eff)" >> ${MDFILE}.md
    echo "   * [etazoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tceff/?tc_eff_bbbbbb_etazoom_by_layer._eff)" >> ${MDFILE}.md
    echo "   * [dxy](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tceff/?tc_eff_bbbbbb_dxy_by_layer._eff)" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "#### Numerator and Denominator overlay" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "   * [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tceff/?tc_eff_bbbbbb_pt_by_layer._numden)" >> ${MDFILE}.md
    echo "   * [ptzoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tceff/?tc_eff_bbbbbb_ptzoom_by_layer._numden)" >> ${MDFILE}.md
    echo "   * [eta](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tceff/?tc_eff_bbbbbb_eta_by_layer._numden)" >> ${MDFILE}.md
    echo "   * [etazoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tceff/?tc_eff_bbbbbb_etazoom_by_layer._numden)" >> ${MDFILE}.md
    echo "   * [dxy](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tceff/?tc_eff_bbbbbb_dxy_by_layer._numden)" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
else
    echo "## MTV like efficiency" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "### Track Candidate" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "#### Efficiency (eta plots with pt > 1.5 and the rest have |eta| < 0.8)" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "   * [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_pt_mtv_eff)" >> ${MDFILE}.md
    echo "   * [ptzoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_ptzoom_mtv_eff)" >> ${MDFILE}.md
    echo "   * [eta](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_eta_mtv_eff)" >> ${MDFILE}.md
    echo "   * [etazoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_etazoom_mtv_eff)" >> ${MDFILE}.md
    echo "   * [dxy](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_dxy_mtv_eff)" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "#### Numerator and Denominator overlay (eta plots with pt > 1.5 and the rest have |eta| < 0.8)" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "   * [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_pt_mtv_numden)" >> ${MDFILE}.md
    echo "   * [ptzoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_ptzoom_mtv_numden)" >> ${MDFILE}.md
    echo "   * [eta](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_eta_mtv_numden)" >> ${MDFILE}.md
    echo "   * [etazoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_etazoom_mtv_numden)" >> ${MDFILE}.md
    echo "   * [dxy](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_dxy_mtv_numden)" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "#### Efficiency (eta plots with pt > 1.5 and the rest have |eta| < 0.4)" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "   * [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_pt_mtv_eta0_0p4_eff)" >> ${MDFILE}.md
    echo "   * [ptzoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_ptzoom_mtv_eta0_0p4_eff)" >> ${MDFILE}.md
    echo "   * [eta](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_eta_mtv_eta0_0p4_eff)" >> ${MDFILE}.md
    echo "   * [etazoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_etazoom_mtv_eta0_0p4_eff)" >> ${MDFILE}.md
    echo "   * [dxy](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_dxy_mtv_eta0_0p4_eff)" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "#### Numerator and Denominator overlay (eta plots with pt > 1.5 and the rest have |eta| < 0.4)" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "   * [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_pt_mtv_eta0_0p4_numden)" >> ${MDFILE}.md
    echo "   * [ptzoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_ptzoom_mtv_eta0_0p4_numden)" >> ${MDFILE}.md
    echo "   * [eta](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_eta_mtv_eta0_0p4_numden)" >> ${MDFILE}.md
    echo "   * [etazoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_etazoom_mtv_eta0_0p4_numden)" >> ${MDFILE}.md
    echo "   * [dxy](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_dxy_mtv_eta0_0p4_numden)" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "#### Efficiency (eta plots with pt > 1.5 and the rest have |eta| > 0.4 and |eta| < 0.8)" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "   * [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_pt_mtv_eta0p4_0p8_eff)" >> ${MDFILE}.md
    echo "   * [ptzoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_ptzoom_mtv_eta0p4_0p8_eff)" >> ${MDFILE}.md
    echo "   * [eta](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_eta_mtv_eta0p4_0p8_eff)" >> ${MDFILE}.md
    echo "   * [etazoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_etazoom_mtv_eta0p4_0p8_eff)" >> ${MDFILE}.md
    echo "   * [dxy](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_dxy_mtv_eta0p4_0p8_eff)" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "#### Numerator and Denominator overlay (eta plots with pt > 1.5 and the rest have |eta| > 0.4 and |eta| < 0.8)" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "   * [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_pt_mtv_eta0p4_0p8_numden)" >> ${MDFILE}.md
    echo "   * [ptzoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_ptzoom_mtv_eta0p4_0p8_numden)" >> ${MDFILE}.md
    echo "   * [eta](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_eta_mtv_eta0p4_0p8_numden)" >> ${MDFILE}.md
    echo "   * [etazoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_etazoom_mtv_eta0p4_0p8_numden)" >> ${MDFILE}.md
    echo "   * [dxy](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_dxy_mtv_eta0p4_0p8_numden)" >> ${MDFILE}.md

fi

/home/users/phchang/local/bin/pandoc ${MDFILE}.md -f markdown -t html -s -o index.html
