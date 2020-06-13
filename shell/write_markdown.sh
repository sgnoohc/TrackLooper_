#!/bin/bash

SAMPLE=$1
DESCRIPTION=$2
TAG=$3
EFFTYPE=$4
MDFILE=${SAMPLE}_${TAG}

echo "" > ${MDFILE}.md

width=450

if [[ ${EFFTYPE} == *"algo_eff"* ]]; then
    echo "# Efficiency plots" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "${DESCRIPTION}" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "## Summary Algorithmic Efficiency plots" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "### Track Candidate Algorithmic Efficiency plots" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "  ![](plots_${SAMPLE}/tceff/summary_tc_algo_eff.png){width=${width}px}" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "### Tracklet Algorithmic Efficiency plots" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "  ![Tracklet algorithmic efficiencies](plots_${SAMPLE}/tleff/summary_tl_algo_eff_bbbbbb.png){width=${width}px}" >> ${MDFILE}.md
    echo "  ![Tracklet algorithmic efficiencies](plots_${SAMPLE}/tleff/summary_tl_algo_eff_bbbbbe.png){width=${width}px}" >> ${MDFILE}.md
    echo "  ![Tracklet algorithmic efficiencies](plots_${SAMPLE}/tleff/summary_tl_algo_eff_bbbbee.png){width=${width}px}" >> ${MDFILE}.md
    echo "  ![Tracklet algorithmic efficiencies](plots_${SAMPLE}/tleff/summary_tl_algo_eff_bbbeee.png){width=${width}px}" >> ${MDFILE}.md
    echo "  ![Tracklet algorithmic efficiencies](plots_${SAMPLE}/tleff/summary_tl_algo_eff_bbeeee.png){width=${width}px}" >> ${MDFILE}.md
    echo "  ![Tracklet algorithmic efficiencies](plots_${SAMPLE}/tleff/summary_tl_algo_eff_beeeee.png){width=${width}px}" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "### Segment Algorithmic Efficiency plots" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "  ![Segment algorithmic efficiencies](plots_${SAMPLE}/sgeff/summary_sg_algo_eff_bbbbbb.png){width=${width}px}" >> ${MDFILE}.md
    echo "  ![Segment algorithmic efficiencies](plots_${SAMPLE}/sgeff/summary_sg_algo_eff_bbbbbe.png){width=${width}px}" >> ${MDFILE}.md
    echo "  ![Segment algorithmic efficiencies](plots_${SAMPLE}/sgeff/summary_sg_algo_eff_bbbbee.png){width=${width}px}" >> ${MDFILE}.md
    echo "  ![Segment algorithmic efficiencies](plots_${SAMPLE}/sgeff/summary_sg_algo_eff_bbbeee.png){width=${width}px}" >> ${MDFILE}.md
    echo "  ![Segment algorithmic efficiencies](plots_${SAMPLE}/sgeff/summary_sg_algo_eff_bbeeee.png){width=${width}px}" >> ${MDFILE}.md
    echo "  ![Segment algorithmic efficiencies](plots_${SAMPLE}/sgeff/summary_sg_algo_eff_beeeee.png){width=${width}px}" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "### Mini-Doublet Algorithmic Efficiency plots" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "  ![Mini-doublet algorithmic efficiencies](plots_${SAMPLE}/mdeff/summary_md_algo_eff_bbbbbb.png){width=${width}px}" >> ${MDFILE}.md
    echo "  ![Mini-doublet algorithmic efficiencies](plots_${SAMPLE}/mdeff/summary_md_algo_eff_bbbbbe.png){width=${width}px}" >> ${MDFILE}.md
    echo "  ![Mini-doublet algorithmic efficiencies](plots_${SAMPLE}/mdeff/summary_md_algo_eff_bbbbee.png){width=${width}px}" >> ${MDFILE}.md
    echo "  ![Mini-doublet algorithmic efficiencies](plots_${SAMPLE}/mdeff/summary_md_algo_eff_bbbeee.png){width=${width}px}" >> ${MDFILE}.md
    echo "  ![Mini-doublet algorithmic efficiencies](plots_${SAMPLE}/mdeff/summary_md_algo_eff_bbeeee.png){width=${width}px}" >> ${MDFILE}.md
    echo "  ![Mini-doublet algorithmic efficiencies](plots_${SAMPLE}/mdeff/summary_md_algo_eff_beeeee.png){width=${width}px}" >> ${MDFILE}.md
    # echo "   * Mini-doublet algorithmic efficiency: [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/mdeff/?summary)" >> ${MDFILE}.md
    # echo "   * Segment algorithmic efficiency: [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/sgeff/?summary)" >> ${MDFILE}.md
    # echo "   * Tracklet algorithmic efficiency: [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tleff/?summary)" >> ${MDFILE}.md
    # echo "   * Track candidate algorithmic efficiency: [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/${EFFTYPE}/${MDFILE}/plots_${SAMPLE}/tceff/?summary)" >> ${MDFILE}.md
    echo "-------------------------------------------------" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "## Detailed Algorithmic efficiency" >> ${MDFILE}.md
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
    echo "#### Efficiency" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "   * [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_pt_mtv.*_eff)" >> ${MDFILE}.md
    echo "   * [ptzoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_ptzoom_mtv.*_eff)" >> ${MDFILE}.md
    echo "   * [eta](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_eta_mtv.*_eff)" >> ${MDFILE}.md
    echo "   * [etazoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_etazoom_mtv.*_eff)" >> ${MDFILE}.md
    echo "   * [dxy](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_dxy_mtv.*_eff)" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "#### Numerator and Denominator overlay" >> ${MDFILE}.md
    echo "" >> ${MDFILE}.md
    echo "   * [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_pt_mtv.*_numden)" >> ${MDFILE}.md
    echo "   * [ptzoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_ptzoom_mtv.*_numden)" >> ${MDFILE}.md
    echo "   * [eta](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_eta_mtv.*_numden)" >> ${MDFILE}.md
    echo "   * [etazoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_etazoom_mtv.*_numden)" >> ${MDFILE}.md
    echo "   * [dxy](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_dxy_mtv.*_numden)" >> ${MDFILE}.md
    # echo "" >> ${MDFILE}.md
    # echo "#### Efficiency (eta plots with pt > 1.5 and the rest have |eta| < 0.4)" >> ${MDFILE}.md
    # echo "" >> ${MDFILE}.md
    # echo "   * [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_pt_mtv_eta0_0p4_eff)" >> ${MDFILE}.md
    # echo "   * [ptzoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_ptzoom_mtv_eta0_0p4_eff)" >> ${MDFILE}.md
    # echo "   * [eta](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_eta_mtv_eta0_0p4_eff)" >> ${MDFILE}.md
    # echo "   * [etazoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_etazoom_mtv_eta0_0p4_eff)" >> ${MDFILE}.md
    # echo "   * [dxy](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_dxy_mtv_eta0_0p4_eff)" >> ${MDFILE}.md
    # echo "" >> ${MDFILE}.md
    # echo "#### Numerator and Denominator overlay (eta plots with pt > 1.5 and the rest have |eta| < 0.4)" >> ${MDFILE}.md
    # echo "" >> ${MDFILE}.md
    # echo "   * [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_pt_mtv_eta0_0p4_numden)" >> ${MDFILE}.md
    # echo "   * [ptzoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_ptzoom_mtv_eta0_0p4_numden)" >> ${MDFILE}.md
    # echo "   * [eta](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_eta_mtv_eta0_0p4_numden)" >> ${MDFILE}.md
    # echo "   * [etazoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_etazoom_mtv_eta0_0p4_numden)" >> ${MDFILE}.md
    # echo "   * [dxy](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_dxy_mtv_eta0_0p4_numden)" >> ${MDFILE}.md
    # echo "" >> ${MDFILE}.md
    # echo "#### Efficiency (eta plots with pt > 1.5 and the rest have |eta| > 0.4 and |eta| < 0.8)" >> ${MDFILE}.md
    # echo "" >> ${MDFILE}.md
    # echo "   * [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_pt_mtv_eta0p4_0p8_eff)" >> ${MDFILE}.md
    # echo "   * [ptzoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_ptzoom_mtv_eta0p4_0p8_eff)" >> ${MDFILE}.md
    # echo "   * [eta](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_eta_mtv_eta0p4_0p8_eff)" >> ${MDFILE}.md
    # echo "   * [etazoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_etazoom_mtv_eta0p4_0p8_eff)" >> ${MDFILE}.md
    # echo "   * [dxy](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_dxy_mtv_eta0p4_0p8_eff)" >> ${MDFILE}.md
    # echo "" >> ${MDFILE}.md
    # echo "#### Numerator and Denominator overlay (eta plots with pt > 1.5 and the rest have |eta| > 0.4 and |eta| < 0.8)" >> ${MDFILE}.md
    # echo "" >> ${MDFILE}.md
    # echo "   * [pt](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_pt_mtv_eta0p4_0p8_numden)" >> ${MDFILE}.md
    # echo "   * [ptzoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_ptzoom_mtv_eta0p4_0p8_numden)" >> ${MDFILE}.md
    # echo "   * [eta](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_eta_mtv_eta0p4_0p8_numden)" >> ${MDFILE}.md
    # echo "   * [etazoom](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_etazoom_mtv_eta0p4_0p8_numden)" >> ${MDFILE}.md
    # echo "   * [dxy](http://uaf-10.t2.ucsd.edu/~phchang//analysis/sdl/TrackLooper_/results/mtv_eff/${MDFILE}/plots_${SAMPLE}/mtveff/?tc_eff_dxy_mtv_eta0p4_0p8_numden)" >> ${MDFILE}.md

fi

/home/users/phchang/local/bin/pandoc ${MDFILE}.md -f markdown -t html -s -o index.html --number-sections
