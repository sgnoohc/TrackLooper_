#include "StudySDLEfficiencyv2.h"

StudySDLEfficiencyv2::StudySDLEfficiencyv2(
        const char* studyName,
        StudySDLEfficiencyv2::StudySDLEfficiencyv2Mode eff_mode_,
        std::vector<float> ptbounds)
{

    studyname = studyName;

    eff_mode = eff_mode_;

    pt_boundaries = ptbounds;

    switch (eff_mode)
    {
        case kStudySDLBBBBBB: eff_modename = "bbbbbb"; break;
        case kStudySDLBBBBBE: eff_modename = "bbbbbe"; break;
        case kStudySDLBBBBEE: eff_modename = "bbbbee"; break;
        case kStudySDLBBBEEE: eff_modename = "bbbeee"; break;
        case kStudySDLBBEEEE: eff_modename = "bbeeee"; break;
        case kStudySDLBEEEEE: eff_modename = "beeeee"; break;
        case kStudySDLPixel: eff_modename = "pixel"; break;
        default: eff_modename = "UNDEFINED"; break;
    }

}

void StudySDLEfficiencyv2::bookStudy()
{
    // Book Histograms
    const int nlayers = NLAYERS;

    const float etamax = 2.5;

    const int eta_nbins = 50;

    const float dxymax = 10;

    for (int ii = 0; ii < nlayers; ++ii)
    {
        ana.histograms.addVecHistogram(TString::Format("md_%s_matched_track_pt_by_layer%d", eff_modename, ii), pt_boundaries, [&, ii]() { return md_matched_track_pt_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("md_%s_all_track_pt_by_layer%d", eff_modename, ii), pt_boundaries, [&, ii]() { return md_all_track_pt_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("md_%s_matched_track_eta_by_layer%d", eff_modename, ii), eta_nbins, -1*etamax, etamax, [&, ii]() { return md_matched_track_eta_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("md_%s_all_track_eta_by_layer%d", eff_modename, ii), eta_nbins, -1*etamax, etamax, [&, ii]() { return md_all_track_eta_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("md_%s_matched_track_dxy_by_layer%d", eff_modename, ii), 50, -1*dxymax, 2.5*dxymax, [&, ii]() { return md_matched_track_dxy_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("md_%s_all_track_dxy_by_layer%d", eff_modename, ii), 50, -1*dxymax, 2.5*dxymax, [&, ii]() { return md_all_track_dxy_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("md_%s_matched_track_dz_by_layer%d", eff_modename, ii), 50, -20, 20, [&, ii]() { return md_matched_track_dz_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("md_%s_all_track_dz_by_layer%d", eff_modename, ii), 50, -20, 20, [&, ii]() { return md_all_track_dz_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("md_%s_matched_track_pt_mtv_by_layer%d", eff_modename, ii), pt_boundaries, [&, ii]() { return md_matched_track_pt_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("md_%s_all_track_pt_mtv_by_layer%d", eff_modename, ii), pt_boundaries, [&, ii]() { return md_all_track_pt_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("md_%s_matched_track_eta_mtv_by_layer%d", eff_modename, ii), eta_nbins, -1*etamax, etamax, [&, ii]() { return md_matched_track_eta_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("md_%s_all_track_eta_mtv_by_layer%d", eff_modename, ii), eta_nbins, -1*etamax, etamax, [&, ii]() { return md_all_track_eta_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("md_%s_matched_track_dxy_mtv_by_layer%d", eff_modename, ii), 50, -1*dxymax, 2.5*dxymax, [&, ii]() { return md_matched_track_dxy_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("md_%s_all_track_dxy_mtv_by_layer%d", eff_modename, ii), 50, -1*dxymax, 2.5*dxymax, [&, ii]() { return md_all_track_dxy_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("md_%s_matched_track_dz_mtv_by_layer%d", eff_modename, ii), 50, -20, 20, [&, ii]() { return md_matched_track_dz_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("md_%s_all_track_dz_mtv_by_layer%d", eff_modename, ii), 50, -20, 20, [&, ii]() { return md_all_track_dz_mtv_by_layer[ii]; } );
    }

    for (int ii = 0; ii < nlayers; ++ii)
    {
        ana.histograms.addVecHistogram(TString::Format("sg_%s_matched_track_pt_by_layer%d", eff_modename, ii), pt_boundaries, [&, ii]() { return sg_matched_track_pt_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("sg_%s_all_track_pt_by_layer%d", eff_modename, ii), pt_boundaries, [&, ii]() { return sg_all_track_pt_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("sg_%s_matched_track_eta_by_layer%d", eff_modename, ii), eta_nbins, -1*etamax, etamax, [&, ii]() { return sg_matched_track_eta_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("sg_%s_all_track_eta_by_layer%d", eff_modename, ii), eta_nbins, -1*etamax, etamax, [&, ii]() { return sg_all_track_eta_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("sg_%s_matched_track_dxy_by_layer%d", eff_modename, ii), 50, -1*dxymax, 2.5*dxymax, [&, ii]() { return sg_matched_track_dxy_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("sg_%s_all_track_dxy_by_layer%d", eff_modename, ii), 50, -1*dxymax, 2.5*dxymax, [&, ii]() { return sg_all_track_dxy_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("sg_%s_matched_track_dz_by_layer%d", eff_modename, ii), 50, -20, 20, [&, ii]() { return sg_matched_track_dz_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("sg_%s_all_track_dz_by_layer%d", eff_modename, ii), 50, -20, 20, [&, ii]() { return sg_all_track_dz_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("sg_%s_matched_track_pt_mtv_by_layer%d", eff_modename, ii), pt_boundaries, [&, ii]() { return sg_matched_track_pt_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("sg_%s_all_track_pt_mtv_by_layer%d", eff_modename, ii), pt_boundaries, [&, ii]() { return sg_all_track_pt_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("sg_%s_matched_track_eta_mtv_by_layer%d", eff_modename, ii), eta_nbins, -1*etamax, etamax, [&, ii]() { return sg_matched_track_eta_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("sg_%s_all_track_eta_mtv_by_layer%d", eff_modename, ii), eta_nbins, -1*etamax, etamax, [&, ii]() { return sg_all_track_eta_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("sg_%s_matched_track_dxy_mtv_by_layer%d", eff_modename, ii), 50, -1*dxymax, 2.5*dxymax, [&, ii]() { return sg_matched_track_dxy_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("sg_%s_all_track_dxy_mtv_by_layer%d", eff_modename, ii), 50, -1*dxymax, 2.5*dxymax, [&, ii]() { return sg_all_track_dxy_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("sg_%s_matched_track_dz_mtv_by_layer%d", eff_modename, ii), 50, -20, 20, [&, ii]() { return sg_matched_track_dz_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("sg_%s_all_track_dz_mtv_by_layer%d", eff_modename, ii), 50, -20, 20, [&, ii]() { return sg_all_track_dz_mtv_by_layer[ii]; } );
    }

    for (int ii = 0; ii < nlayers; ++ii)
    {
        ana.histograms.addVecHistogram(TString::Format("tl_%s_matched_track_pt_by_layer%d", eff_modename, ii), pt_boundaries, [&, ii]() { return tl_matched_track_pt_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_all_track_pt_by_layer%d", eff_modename, ii), pt_boundaries, [&, ii]() { return tl_all_track_pt_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_matched_track_eta_by_layer%d", eff_modename, ii), eta_nbins, -1*etamax, etamax, [&, ii]() { return tl_matched_track_eta_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_all_track_eta_by_layer%d", eff_modename, ii), eta_nbins, -1*etamax, etamax, [&, ii]() { return tl_all_track_eta_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_matched_track_dxy_by_layer%d", eff_modename, ii), 50, -1*dxymax, 2.5*dxymax, [&, ii]() { return tl_matched_track_dxy_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_all_track_dxy_by_layer%d", eff_modename, ii), 50, -1*dxymax, 2.5*dxymax, [&, ii]() { return tl_all_track_dxy_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_matched_track_dz_by_layer%d", eff_modename, ii), 50, -20, 20, [&, ii]() { return tl_matched_track_dz_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_all_track_dz_by_layer%d", eff_modename, ii), 50, -20, 20, [&, ii]() { return tl_all_track_dz_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_matched_track_pt_mtv_by_layer%d", eff_modename, ii), pt_boundaries, [&, ii]() { return tl_matched_track_pt_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_all_track_pt_mtv_by_layer%d", eff_modename, ii), pt_boundaries, [&, ii]() { return tl_all_track_pt_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_matched_track_eta_mtv_by_layer%d", eff_modename, ii), eta_nbins, -1*etamax, etamax, [&, ii]() { return tl_matched_track_eta_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_all_track_eta_mtv_by_layer%d", eff_modename, ii), eta_nbins, -1*etamax, etamax, [&, ii]() { return tl_all_track_eta_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_matched_track_dxy_mtv_by_layer%d", eff_modename, ii), 50, -1*dxymax, 2.5*dxymax, [&, ii]() { return tl_matched_track_dxy_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_all_track_dxy_mtv_by_layer%d", eff_modename, ii), 50, -1*dxymax, 2.5*dxymax, [&, ii]() { return tl_all_track_dxy_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_matched_track_dz_mtv_by_layer%d", eff_modename, ii), 50, -20, 20, [&, ii]() { return tl_matched_track_dz_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_all_track_dz_mtv_by_layer%d", eff_modename, ii), 50, -20, 20, [&, ii]() { return tl_all_track_dz_mtv_by_layer[ii]; } );
    }

    for (int ii = 0; ii < nlayers; ++ii)
    {
        ana.histograms.addVecHistogram(TString::Format("tc_%s_matched_track_pt_by_layer%d", eff_modename, ii), pt_boundaries, [&, ii]() { return tc_matched_track_pt_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tc_%s_all_track_pt_by_layer%d", eff_modename, ii), pt_boundaries, [&, ii]() { return tc_all_track_pt_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tc_%s_matched_track_eta_by_layer%d", eff_modename, ii), eta_nbins, -1*etamax, etamax, [&, ii]() { return tc_matched_track_eta_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tc_%s_all_track_eta_by_layer%d", eff_modename, ii), eta_nbins, -1*etamax, etamax, [&, ii]() { return tc_all_track_eta_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tc_%s_matched_track_dxy_by_layer%d", eff_modename, ii), 50, -1*dxymax, 2.5*dxymax, [&, ii]() { return tc_matched_track_dxy_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tc_%s_all_track_dxy_by_layer%d", eff_modename, ii), 50, -1*dxymax, 2.5*dxymax, [&, ii]() { return tc_all_track_dxy_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tc_%s_matched_track_dz_by_layer%d", eff_modename, ii), 50, -20, 20, [&, ii]() { return tc_matched_track_dz_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tc_%s_all_track_dz_by_layer%d", eff_modename, ii), 50, -20, 20, [&, ii]() { return tc_all_track_dz_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tc_%s_matched_track_pt_mtv_by_layer%d", eff_modename, ii), pt_boundaries, [&, ii]() { return tc_matched_track_pt_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tc_%s_all_track_pt_mtv_by_layer%d", eff_modename, ii), pt_boundaries, [&, ii]() { return tc_all_track_pt_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tc_%s_matched_track_eta_mtv_by_layer%d", eff_modename, ii), eta_nbins, -1*etamax, etamax, [&, ii]() { return tc_matched_track_eta_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tc_%s_all_track_eta_mtv_by_layer%d", eff_modename, ii), eta_nbins, -1*etamax, etamax, [&, ii]() { return tc_all_track_eta_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tc_%s_matched_track_dxy_mtv_by_layer%d", eff_modename, ii), 50, -1*dxymax, 2.5*dxymax, [&, ii]() { return tc_matched_track_dxy_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tc_%s_all_track_dxy_mtv_by_layer%d", eff_modename, ii), 50, -1*dxymax, 2.5*dxymax, [&, ii]() { return tc_all_track_dxy_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tc_%s_matched_track_dz_mtv_by_layer%d", eff_modename, ii), 50, -20, 20, [&, ii]() { return tc_matched_track_dz_mtv_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tc_%s_all_track_dz_mtv_by_layer%d", eff_modename, ii), 50, -20, 20, [&, ii]() { return tc_all_track_dz_mtv_by_layer[ii]; } );
    }

}

void StudySDLEfficiencyv2::doStudy(SDL::Event& event, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents)
{
    // Each do study is performed per event

    // First clear all the output variables that will be used to fill the histograms for this event
    for (int ii = 0; ii < NLAYERS; ++ii)
    {

        md_matched_track_pt_by_layer[ii].clear();
        md_all_track_pt_by_layer[ii].clear();
        md_matched_track_eta_by_layer[ii].clear();
        md_all_track_eta_by_layer[ii].clear();
        md_matched_track_dxy_by_layer[ii].clear();
        md_all_track_dxy_by_layer[ii].clear();
        md_matched_track_dz_by_layer[ii].clear();
        md_all_track_dz_by_layer[ii].clear();
        md_matched_track_pt_mtv_by_layer[ii].clear();
        md_all_track_pt_mtv_by_layer[ii].clear();
        md_matched_track_eta_mtv_by_layer[ii].clear();
        md_all_track_eta_mtv_by_layer[ii].clear();
        md_matched_track_dxy_mtv_by_layer[ii].clear();
        md_all_track_dxy_mtv_by_layer[ii].clear();
        md_matched_track_dz_mtv_by_layer[ii].clear();
        md_all_track_dz_mtv_by_layer[ii].clear();

        sg_matched_track_pt_by_layer[ii].clear();
        sg_all_track_pt_by_layer[ii].clear();
        sg_matched_track_eta_by_layer[ii].clear();
        sg_all_track_eta_by_layer[ii].clear();
        sg_matched_track_dxy_by_layer[ii].clear();
        sg_all_track_dxy_by_layer[ii].clear();
        sg_matched_track_dz_by_layer[ii].clear();
        sg_all_track_dz_by_layer[ii].clear();
        sg_matched_track_pt_mtv_by_layer[ii].clear();
        sg_all_track_pt_mtv_by_layer[ii].clear();
        sg_matched_track_eta_mtv_by_layer[ii].clear();
        sg_all_track_eta_mtv_by_layer[ii].clear();
        sg_matched_track_dxy_mtv_by_layer[ii].clear();
        sg_all_track_dxy_mtv_by_layer[ii].clear();
        sg_matched_track_dz_mtv_by_layer[ii].clear();
        sg_all_track_dz_mtv_by_layer[ii].clear();

        tl_matched_track_pt_by_layer[ii].clear();
        tl_all_track_pt_by_layer[ii].clear();
        tl_matched_track_eta_by_layer[ii].clear();
        tl_all_track_eta_by_layer[ii].clear();
        tl_matched_track_dxy_by_layer[ii].clear();
        tl_all_track_dxy_by_layer[ii].clear();
        tl_matched_track_dz_by_layer[ii].clear();
        tl_all_track_dz_by_layer[ii].clear();
        tl_matched_track_pt_mtv_by_layer[ii].clear();
        tl_all_track_pt_mtv_by_layer[ii].clear();
        tl_matched_track_eta_mtv_by_layer[ii].clear();
        tl_all_track_eta_mtv_by_layer[ii].clear();
        tl_matched_track_dxy_mtv_by_layer[ii].clear();
        tl_all_track_dxy_mtv_by_layer[ii].clear();
        tl_matched_track_dz_mtv_by_layer[ii].clear();
        tl_all_track_dz_mtv_by_layer[ii].clear();

        tc_matched_track_pt_by_layer[ii].clear();
        tc_all_track_pt_by_layer[ii].clear();
        tc_matched_track_eta_by_layer[ii].clear();
        tc_all_track_eta_by_layer[ii].clear();
        tc_matched_track_dxy_by_layer[ii].clear();
        tc_all_track_dxy_by_layer[ii].clear();
        tc_matched_track_dz_by_layer[ii].clear();
        tc_all_track_dz_by_layer[ii].clear();
        tc_matched_track_pt_mtv_by_layer[ii].clear();
        tc_all_track_pt_mtv_by_layer[ii].clear();
        tc_matched_track_eta_mtv_by_layer[ii].clear();
        tc_all_track_eta_mtv_by_layer[ii].clear();
        tc_matched_track_dxy_mtv_by_layer[ii].clear();
        tc_all_track_dxy_mtv_by_layer[ii].clear();
        tc_matched_track_dz_mtv_by_layer[ii].clear();
        tc_all_track_dz_mtv_by_layer[ii].clear();

    }

    //***********************
    // Efficiency calculation
    //***********************

    // Eta bounds
    // std::array<float, 6> etabounds_bbbbbb = {2.2, 1.8, 1.45, 1.2, 1, 0.8};
    std::array<float, 6> etabounds_bbbbbb = {2.5, 2.5, 2.5, 2.5, 2.5, 2.5};
    std::array<float, 6> etabounds_bbbbbe = {2.5, 2.5, 2.5, 2.5, 2.5, 2.5};
    std::array<float, 6> etabounds_bbbbee = {2.5, 2.5, 2.5, 2.5, 2.5, 2.5};
    std::array<float, 6> etabounds_bbbeee = {2.5, 2.5, 2.5, 2.5, 2.5, 2.5};
    std::array<float, 6> etabounds_bbeeee = {2.5, 2.5, 2.5, 2.5, 2.5, 2.5};
    std::array<float, 6> etabounds_beeeee = {2.5, 2.5, 2.5, 2.5, 2.5, 2.5};
    std::array<float, 6> etabounds_pixel  = {2.5, 2.5, 2.5, 2.5, 2.5, 2.5};

    // Eta inner bounds
    std::array<float, 6> etainnerbounds_bbbbbb = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    std::array<float, 6> etainnerbounds_bbbbbe = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    std::array<float, 6> etainnerbounds_bbbbee = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    std::array<float, 6> etainnerbounds_bbbeee = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    std::array<float, 6> etainnerbounds_bbeeee = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    std::array<float, 6> etainnerbounds_beeeee = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    std::array<float, 6> etainnerbounds_pixel  = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    // Select eta bounds
    std::array<float, 6> etabounds;
    if (eff_mode == kStudySDLBBBBBB) etabounds = etabounds_bbbbbb;
    if (eff_mode == kStudySDLBBBBBE) etabounds = etabounds_bbbbbe;
    if (eff_mode == kStudySDLBBBBEE) etabounds = etabounds_bbbbee;
    if (eff_mode == kStudySDLBBBEEE) etabounds = etabounds_bbbeee;
    if (eff_mode == kStudySDLBBEEEE) etabounds = etabounds_bbeeee;
    if (eff_mode == kStudySDLBEEEEE) etabounds = etabounds_beeeee;
    if (eff_mode == kStudySDLPixel ) etabounds = etabounds_pixel;

    // Select etainner bounds
    std::array<float, 6> etainnerbounds;
    if (eff_mode == kStudySDLBBBBBB) etainnerbounds = etainnerbounds_bbbbbb;
    if (eff_mode == kStudySDLBBBBBE) etainnerbounds = etainnerbounds_bbbbbe;
    if (eff_mode == kStudySDLBBBBEE) etainnerbounds = etainnerbounds_bbbbee;
    if (eff_mode == kStudySDLBBBEEE) etainnerbounds = etainnerbounds_bbbeee;
    if (eff_mode == kStudySDLBBEEEE) etainnerbounds = etainnerbounds_bbeeee;
    if (eff_mode == kStudySDLBEEEEE) etainnerbounds = etainnerbounds_beeeee;
    if (eff_mode == kStudySDLPixel ) etainnerbounds = etainnerbounds_pixel;

    // Logical layer index maps
    std::vector<int> logical_layer_rawidxmap_bbbbbb = {1, 2, 3, 4, 5, 6};
    std::vector<int> logical_layer_rawidxmap_bbbbbe = {1, 2, 3, 4, 5, 1};
    std::vector<int> logical_layer_rawidxmap_bbbbee = {1, 2, 3, 4, 1, 2};
    std::vector<int> logical_layer_rawidxmap_bbbeee = {1, 2, 3, 1, 2, 3};
    std::vector<int> logical_layer_rawidxmap_bbeeee = {1, 2, 1, 2, 3, 4};
    std::vector<int> logical_layer_rawidxmap_beeeee = {1, 1, 2, 3, 4, 5};
    std::vector<int> logical_layer_rawidxmap_pixel  = {0, 1, 2, 3, 4, 5};

    std::vector<bool> logical_layer_subdetmap_bbbbbb = {true , true  , true  , true  , true  , true};
    std::vector<bool> logical_layer_subdetmap_bbbbbe = {true , true  , true  , true  , true  , false};
    std::vector<bool> logical_layer_subdetmap_bbbbee = {true , true  , true  , true  , false , false};
    std::vector<bool> logical_layer_subdetmap_bbbeee = {true , true  , true  , false , false , false};
    std::vector<bool> logical_layer_subdetmap_bbeeee = {true , true  , false , false , false , false};
    std::vector<bool> logical_layer_subdetmap_beeeee = {true , false , false , false , false , false};
    std::vector<bool> logical_layer_subdetmap_pixel  = {true , true  , true  , true  , true  , true};

    std::map<std::pair<int, bool>, int> logical_layer_map_bbbbbb;
    std::map<std::pair<int, bool>, int> logical_layer_map_bbbbbe;
    std::map<std::pair<int, bool>, int> logical_layer_map_bbbbee;
    std::map<std::pair<int, bool>, int> logical_layer_map_bbbeee;
    std::map<std::pair<int, bool>, int> logical_layer_map_bbeeee;
    std::map<std::pair<int, bool>, int> logical_layer_map_beeeee;
    std::map<std::pair<int, bool>, int> logical_layer_map_pixel;

    for (unsigned int i = 0; i < 6; ++i)
    {
        logical_layer_map_bbbbbb[std::make_pair(logical_layer_rawidxmap_bbbbbb[i], logical_layer_subdetmap_bbbbbb[i])] = i;
        logical_layer_map_bbbbbe[std::make_pair(logical_layer_rawidxmap_bbbbbe[i], logical_layer_subdetmap_bbbbbe[i])] = i;
        logical_layer_map_bbbbee[std::make_pair(logical_layer_rawidxmap_bbbbee[i], logical_layer_subdetmap_bbbbee[i])] = i;
        logical_layer_map_bbbeee[std::make_pair(logical_layer_rawidxmap_bbbeee[i], logical_layer_subdetmap_bbbeee[i])] = i;
        logical_layer_map_bbeeee[std::make_pair(logical_layer_rawidxmap_bbeeee[i], logical_layer_subdetmap_bbeeee[i])] = i;
        logical_layer_map_beeeee[std::make_pair(logical_layer_rawidxmap_beeeee[i], logical_layer_subdetmap_beeeee[i])] = i;
        logical_layer_map_pixel [std::make_pair(logical_layer_rawidxmap_pixel [i], logical_layer_subdetmap_pixel [i])] = i;
    }

    // select logical layer map
    std::map<std::pair<int, bool>, int> logical_layer_map;
    if (eff_mode == kStudySDLBBBBBB) logical_layer_map = logical_layer_map_bbbbbb;
    if (eff_mode == kStudySDLBBBBBE) logical_layer_map = logical_layer_map_bbbbbe;
    if (eff_mode == kStudySDLBBBBEE) logical_layer_map = logical_layer_map_bbbbee;
    if (eff_mode == kStudySDLBBBEEE) logical_layer_map = logical_layer_map_bbbeee;
    if (eff_mode == kStudySDLBBEEEE) logical_layer_map = logical_layer_map_bbeeee;
    if (eff_mode == kStudySDLBEEEEE) logical_layer_map = logical_layer_map_beeeee;
    if (eff_mode == kStudySDLPixel ) logical_layer_map = logical_layer_map_pixel;

    // select logical layer map
    std::vector<bool> logical_layer_subdetmap;
    if (eff_mode == kStudySDLBBBBBB) logical_layer_subdetmap = logical_layer_subdetmap_bbbbbb;
    if (eff_mode == kStudySDLBBBBBE) logical_layer_subdetmap = logical_layer_subdetmap_bbbbbe;
    if (eff_mode == kStudySDLBBBBEE) logical_layer_subdetmap = logical_layer_subdetmap_bbbbee;
    if (eff_mode == kStudySDLBBBEEE) logical_layer_subdetmap = logical_layer_subdetmap_bbbeee;
    if (eff_mode == kStudySDLBBEEEE) logical_layer_subdetmap = logical_layer_subdetmap_bbeeee;
    if (eff_mode == kStudySDLBEEEEE) logical_layer_subdetmap = logical_layer_subdetmap_beeeee;
    if (eff_mode == kStudySDLPixel ) logical_layer_subdetmap = logical_layer_subdetmap_pixel;

    // Loop over track events
    for (auto& simtrkevent : simtrkevents)
    {

        // Unpack the tuple (sim_track_index, SDL::Event containing reco hits only matched to the given sim track)
        unsigned int& isimtrk = std::get<0>(simtrkevent);
        SDL::Event& trackevent = *(std::get<1>(simtrkevent));

        // auto [has_missing_hits, is_clean_punch_through, nbarrel, nendcap] = getDenomSimTrackTypeForAlgoEff(isimtrk);

        // switch (eff_mode)
        // {
        //     case kStudySDLBBBBBB:
        //         if (not (nbarrel == 6 and is_clean_punch_through))
        //             continue;
        //         break;
        //     case kStudySDLBBBBBE:
        //         if (not (nbarrel == 5 and is_clean_punch_through))
        //             continue;
        //         break;
        //     case kStudySDLBBBBEE:
        //         if (not (nbarrel == 4 and is_clean_punch_through))
        //             continue;
        //         break;
        //     case kStudySDLBBBEEE:
        //         if (not (nbarrel == 3 and is_clean_punch_through))
        //             continue;
        //         break;
        //     case kStudySDLBBEEEE:
        //         if (not (nbarrel == 2 and is_clean_punch_through))
        //             continue;
        //         break;
        //     case kStudySDLBEEEEE:
        //         if (not (nbarrel == 1 and is_clean_punch_through))
        //             continue;
        //         break;
        //     default:
        //         break;
        // }

        switch (eff_mode)
        {
            case kStudySDLBBBBBB:
                if (not hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 6))
                    continue;
                break;
            case kStudySDLBBBBBE:
                if (not (hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 5) and not hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 6)))
                    continue;
                break;
            case kStudySDLBBBBEE:
                if (not (hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 4) and not hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 5) and not hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 6)))
                    continue;
                break;
            case kStudySDLBBBEEE:
                if (not (hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 3) and not hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 4) and not hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 5) and not hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 6)))
                    continue;
                break;
            case kStudySDLBBEEEE:
                if (not (hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 2) and not hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 3) and not hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 4) and not hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 5) and not hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 6)))
                    continue;
                break;
            case kStudySDLBEEEEE:
                if (not (hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 1) and not hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 2) and not hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 3) and not hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 4) and not hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 5) and not hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 6)))
                    continue;
                break;
            case kStudySDLPixel:
                if (not hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 6))
                    continue;
                break;
            default:
                break;
        }

        // switch (eff_mode)
        // {
        //     case kStudySDLBBBBBB:
        //         if (not (hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 6)))
        //             continue;
        //         break;
        //     case kStudySDLBBBBBE:
        //         if (not (hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 5)))
        //             continue;
        //         break;
        //     case kStudySDLBBBBEE:
        //         if (not (hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 4)))
        //             continue;
        //         break;
        //     case kStudySDLBBBEEE:
        //         if (not (hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 3)))
        //             continue;
        //         break;
        //     case kStudySDLBBEEEE:
        //         if (not (hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 2)))
        //             continue;
        //         break;
        //     case kStudySDLBEEEEE:
        //         if (not (hasAll12HitsWithNBarrelUsingModuleMap(isimtrk, 1)))
        //             continue;
        //         break;
        //     default:
        //         break;
        // }

        // switch (eff_mode)
        // {
        //     case kStudySDLBBBBBB:
        //         if (not (hasAll12HitsWithNBarrel(isimtrk, 6)))
        //             continue;
        //         break;
        //     case kStudySDLBBBBBE:
        //         if (not (hasAll12HitsWithNBarrel(isimtrk, 5)))
        //             continue;
        //         break;
        //     case kStudySDLBBBBEE:
        //         if (not (hasAll12HitsWithNBarrel(isimtrk, 4)))
        //             continue;
        //         break;
        //     case kStudySDLBBBEEE:
        //         if (not (hasAll12HitsWithNBarrel(isimtrk, 3)))
        //             continue;
        //         break;
        //     case kStudySDLBBEEEE:
        //         if (not (hasAll12HitsWithNBarrel(isimtrk, 2)))
        //             continue;
        //         break;
        //     case kStudySDLBEEEEE:
        //         if (not (hasAll12HitsWithNBarrel(isimtrk, 1)))
        //             continue;
        //         break;
        //     default:
        //         break;
        // }

        // Create list of booleans
        std::array<bool, 6> md_trackmatch_by_layer; md_trackmatch_by_layer[0] = false; md_trackmatch_by_layer[1] = false; md_trackmatch_by_layer[2] = false; md_trackmatch_by_layer[3] = false; md_trackmatch_by_layer[4] = false; md_trackmatch_by_layer[5] = false;
        std::array<bool, 6> sg_trackmatch_by_layer; sg_trackmatch_by_layer[0] = false; sg_trackmatch_by_layer[1] = false; sg_trackmatch_by_layer[2] = false; sg_trackmatch_by_layer[3] = false; sg_trackmatch_by_layer[4] = false; sg_trackmatch_by_layer[5] = false;
        std::array<bool, 6> tl_trackmatch_by_layer; tl_trackmatch_by_layer[0] = false; tl_trackmatch_by_layer[1] = false; tl_trackmatch_by_layer[2] = false; tl_trackmatch_by_layer[3] = false; tl_trackmatch_by_layer[4] = false; tl_trackmatch_by_layer[5] = false;
        std::array<bool, 6> tc_trackmatch_by_layer; tc_trackmatch_by_layer[0] = false; tc_trackmatch_by_layer[1] = false; tc_trackmatch_by_layer[2] = false; tc_trackmatch_by_layer[3] = false; tc_trackmatch_by_layer[4] = false; tc_trackmatch_by_layer[5] = false;
        std::array<bool, 6> md_trackmatch_mtv_by_layer; md_trackmatch_mtv_by_layer[0] = false; md_trackmatch_mtv_by_layer[1] = false; md_trackmatch_mtv_by_layer[2] = false; md_trackmatch_mtv_by_layer[3] = false; md_trackmatch_mtv_by_layer[4] = false; md_trackmatch_mtv_by_layer[5] = false;
        std::array<bool, 6> sg_trackmatch_mtv_by_layer; sg_trackmatch_mtv_by_layer[0] = false; sg_trackmatch_mtv_by_layer[1] = false; sg_trackmatch_mtv_by_layer[2] = false; sg_trackmatch_mtv_by_layer[3] = false; sg_trackmatch_mtv_by_layer[4] = false; sg_trackmatch_mtv_by_layer[5] = false;
        std::array<bool, 6> tl_trackmatch_mtv_by_layer; tl_trackmatch_mtv_by_layer[0] = false; tl_trackmatch_mtv_by_layer[1] = false; tl_trackmatch_mtv_by_layer[2] = false; tl_trackmatch_mtv_by_layer[3] = false; tl_trackmatch_mtv_by_layer[4] = false; tl_trackmatch_mtv_by_layer[5] = false;
        std::array<bool, 6> tc_trackmatch_mtv_by_layer; tc_trackmatch_mtv_by_layer[0] = false; tc_trackmatch_mtv_by_layer[1] = false; tc_trackmatch_mtv_by_layer[2] = false; tc_trackmatch_mtv_by_layer[3] = false; tc_trackmatch_mtv_by_layer[4] = false; tc_trackmatch_mtv_by_layer[5] = false;

        // Parse pt and eta of this track
        float pt = std::min((double) trk.sim_pt()[isimtrk], 49.999);
        float eta = trk.sim_eta()[isimtrk];
        float dxy = trk.sim_pca_dxy()[isimtrk];
        float dz = trk.sim_pca_dz()[isimtrk];

        //********************************
        // Mini-doublet/Segment efficiency
        //********************************

        // Loop over the lower modules that contains mini-doublets or segments for this track
        for (auto& lowerModulePtr_Track : trackevent.getLowerModulePtrs())
        {

            // Parse the layer index later to be used for indexing
            int raw_layer_idx = lowerModulePtr_Track->layer();
            bool isbarrel = (lowerModulePtr_Track->subdet() == SDL::Module::Barrel);
            if (logical_layer_map.find(std::make_pair(raw_layer_idx, isbarrel)) == logical_layer_map.end())
                continue;
            int layer_idx = logical_layer_map.at(std::make_pair(raw_layer_idx, isbarrel));

            // If there is at least one mini-doublet it means this layer had found a mini-doublet for this sim track
            if (lowerModulePtr_Track->getMiniDoubletPtrs().size() > 0)
            {
                md_trackmatch_by_layer[layer_idx] = true;
                md_trackmatch_mtv_by_layer[layer_idx] = true;
            }

            // If there is at least one segment it means this layer had found a segment for this sim track
            if (lowerModulePtr_Track->getSegmentPtrs().size() > 0)
            {
                // Loop over the segments to check whether it matches the type asked
                for (auto& sg : lowerModulePtr_Track->getSegmentPtrs())
                {
                    // If there is at least one segment of the type that matches with the type of denom track it targets
                    if (sg->innerMiniDoubletPtr()->anchorHitPtr()->getModule().subdet() == (logical_layer_subdetmap[layer_idx+0] ? SDL::Module::Barrel : SDL::Module::Endcap) and
                        sg->outerMiniDoubletPtr()->anchorHitPtr()->getModule().subdet() == (logical_layer_subdetmap[layer_idx+1] ? SDL::Module::Barrel : SDL::Module::Endcap))
                    {
                        sg_trackmatch_by_layer[layer_idx] = true;
                        sg_trackmatch_mtv_by_layer[layer_idx] = true;
                        break;
                    }
                }
            }

        }

        // Loop over the layers that contains tracklets and/or track candidates
        for (auto& layerPtr_Track : trackevent.getLayerPtrs())
        {

            // Parse the layer index later to be used for indexing
            int raw_layer_idx = layerPtr_Track->layerIdx();
            bool isbarrel = (layerPtr_Track->subdet() == SDL::Layer::Barrel);
            if (logical_layer_map.find(std::make_pair(raw_layer_idx, isbarrel)) == logical_layer_map.end())
                continue;
            int layer_idx = logical_layer_map.at(std::make_pair(raw_layer_idx, isbarrel));

            // If there is at least one tracklet it means this layer had found a tracklet for this sim track
            if (layerPtr_Track->getTrackletPtrs().size() > 0)
            {
                // Loop over the tracklets to check whether it matches the type asked
                for (auto& tl : layerPtr_Track->getTrackletPtrs())
                {
                    // If there is at least one tracklet of the type that matches with the type of denom track it targets
                    if (tl->innerSegmentPtr()->innerMiniDoubletPtr()->anchorHitPtr()->getModule().subdet() == (logical_layer_subdetmap[layer_idx+0] ? SDL::Module::Barrel : SDL::Module::Endcap) and
                        tl->innerSegmentPtr()->outerMiniDoubletPtr()->anchorHitPtr()->getModule().subdet() == (logical_layer_subdetmap[layer_idx+1] ? SDL::Module::Barrel : SDL::Module::Endcap) and
                        tl->outerSegmentPtr()->innerMiniDoubletPtr()->anchorHitPtr()->getModule().subdet() == (logical_layer_subdetmap[layer_idx+2] ? SDL::Module::Barrel : SDL::Module::Endcap) and
                        tl->outerSegmentPtr()->outerMiniDoubletPtr()->anchorHitPtr()->getModule().subdet() == (logical_layer_subdetmap[layer_idx+3] ? SDL::Module::Barrel : SDL::Module::Endcap)
                       )
                    {
                        tl_trackmatch_by_layer[layer_idx] = true;
                        tl_trackmatch_mtv_by_layer[layer_idx] = true;
                        break;
                    }
                }
            }

            // If there is at least one tracklet it means this layer had found a tracklet for this sim track
            if (layerPtr_Track->getTrackCandidatePtrs().size() > 0)
            {
                // Loop over the tracklets to check whether it matches the type asked
                for (auto& tc : layerPtr_Track->getTrackCandidatePtrs())
                {
                    // If there is at least one tracklet of the type that matches with the type of denom track it targets
                    if (tc->innerTrackletPtr()->innerSegmentPtr()->innerMiniDoubletPtr()->anchorHitPtr()->getModule().subdet() == (logical_layer_subdetmap[layer_idx+0] ? SDL::Module::Barrel : SDL::Module::Endcap) and
                        tc->innerTrackletPtr()->innerSegmentPtr()->outerMiniDoubletPtr()->anchorHitPtr()->getModule().subdet() == (logical_layer_subdetmap[layer_idx+1] ? SDL::Module::Barrel : SDL::Module::Endcap) and
                        tc->outerTrackletPtr()->innerSegmentPtr()->innerMiniDoubletPtr()->anchorHitPtr()->getModule().subdet() == (logical_layer_subdetmap[layer_idx+2] ? SDL::Module::Barrel : SDL::Module::Endcap) and
                        tc->outerTrackletPtr()->innerSegmentPtr()->outerMiniDoubletPtr()->anchorHitPtr()->getModule().subdet() == (logical_layer_subdetmap[layer_idx+3] ? SDL::Module::Barrel : SDL::Module::Endcap) and
                        tc->outerTrackletPtr()->outerSegmentPtr()->innerMiniDoubletPtr()->anchorHitPtr()->getModule().subdet() == (logical_layer_subdetmap[layer_idx+4] ? SDL::Module::Barrel : SDL::Module::Endcap) and
                        tc->outerTrackletPtr()->outerSegmentPtr()->outerMiniDoubletPtr()->anchorHitPtr()->getModule().subdet() == (logical_layer_subdetmap[layer_idx+5] ? SDL::Module::Barrel : SDL::Module::Endcap)
                       )
                    {
                        tc_trackmatch_by_layer[layer_idx] = true;
                        tc_trackmatch_mtv_by_layer[layer_idx] = true;
                        break;
                    }
                }
            }

        }

        // Studying Pixel Segment and Tracklets
        bool pix_sg_trackmatch_by_layer = trackevent.getPixelLayer().getSegmentPtrs().size() > 0;
        if (ana.verbose != 0)
        {
            std::cout <<  " pix_sg_trackmatch_by_layer: " << pix_sg_trackmatch_by_layer <<  std::endl;
            std::cout <<  " trackevent.getPixelLayer().getTrackletPtrs().size(): " << trackevent.getPixelLayer().getTrackletPtrs().size() <<  std::endl;
        }
        for (auto& tlPtr : trackevent.getPixelLayer().getTrackletPtrs())
        {
            tlPtr->runTrackletAlgo(SDL::Default_TLAlgo);
            bool pass = tlPtr->passesTrackletAlgo(SDL::Default_TLAlgo);
            int passbit = tlPtr->getPassBitsDefaultAlgo();
            float _pt = trk.sim_pt()[isimtrk];
            float _eta = trk.sim_eta()[isimtrk];
            float _dxy = trk.sim_pca_dxy()[isimtrk];
            float _dz = trk.sim_pca_dz()[isimtrk];
            float _charge = trk.sim_q()[isimtrk];
            if (ana.verbose != 0)
            {
                std::cout <<  " _pt: " << _pt <<  " _eta: " << _eta <<  " _dxy: " << _dxy <<  " _dz: " << _dz <<  " _charge: " << _charge <<  std::endl;
                // std::cout <<  " tlPtr->getRecoVar('rawBetaIn'): " << tlPtr->getRecoVar("rawBetaIn") <<  std::endl;
                // std::cout <<  " tlPtr->getRecoVar('betaIn'): " << tlPtr->getRecoVar("betaIn") <<  std::endl;
                // std::cout <<  " tlPtr->getRecoVar('betaOut'): " << tlPtr->getRecoVar("betaOut") <<  std::endl;
                // std::cout <<  " tlPtr->getDeltaBeta(): " << tlPtr->getDeltaBeta() <<  std::endl;
                // std::cout <<  " tlPtr->getDeltaBetaCut(): " << tlPtr->getDeltaBetaCut() <<  std::endl;
                // std::cout <<  " pass: " << pass <<  std::endl;
                // std::bitset<8> x(passbit);
                // std::cout <<  " passbit: " << x <<  std::endl;
                std::cout <<  " tlPtr->outerSegmentPtr()->innerMiniDoubletPtr()->anchorHitPtr()->getModule().layer(): " << tlPtr->outerSegmentPtr()->innerMiniDoubletPtr()->anchorHitPtr()->getModule().layer() <<  std::endl;
                std::cout <<  " tlPtr->outerSegmentPtr()->outerMiniDoubletPtr()->anchorHitPtr()->getModule().layer(): " << tlPtr->outerSegmentPtr()->outerMiniDoubletPtr()->anchorHitPtr()->getModule().layer() <<  std::endl;
            }
        }

        // *****************
        // Mini Doublet
        // *****************
        for (unsigned int i = 0; i < 6; ++i)
        {

            int offset = 0;
            float etamaxbound = etabounds[i+offset];
            float etaminbound = etainnerbounds[i+offset];

            if (abs(eta) < etamaxbound and abs(dxy) < 3.5 and abs(eta) >= etaminbound)
            {
                md_all_track_pt_by_layer[i].push_back(pt);
                if (md_trackmatch_by_layer[i]) md_matched_track_pt_by_layer[i].push_back(pt);
            }

            if (abs(pt) > 1.5 and abs(dxy) < 3.5 and abs(eta) < etamaxbound and abs(eta) >= etaminbound)
            {

                md_all_track_eta_by_layer[i].push_back(eta);
                if (md_trackmatch_by_layer[i]) md_matched_track_eta_by_layer[i].push_back(eta);
            }

            if (abs(pt) > 1.5 and abs(eta) < etamaxbound and abs(eta) >= etaminbound)
            {
                md_all_track_dxy_by_layer[i].push_back(dxy);
                if (md_trackmatch_by_layer[i]) md_matched_track_dxy_by_layer[i].push_back(dxy);
            }

            if (abs(pt) > 1.5 and abs(dxy) < 3.5 and abs(eta) < etamaxbound and abs(eta) >= etaminbound)
            {

                md_all_track_dz_by_layer[i].push_back(dz);
                if (md_trackmatch_by_layer[i]) md_matched_track_dz_by_layer[i].push_back(dz);
            }

        }

        // *****************
        // Segment
        // *****************
        for (unsigned int i = 0; i < 5; ++i)
        {

            int offset = 1;
            float etamaxbound = etabounds[i+offset];
            float etaminbound = etainnerbounds[i+offset];

            if (abs(eta) < etamaxbound and abs(dxy) < 3.5 and abs(eta) >= etaminbound)
            {
                sg_all_track_pt_by_layer[i].push_back(pt);
                if (sg_trackmatch_by_layer[i]) sg_matched_track_pt_by_layer[i].push_back(pt);
            }

            if (abs(pt) > 1.5 and abs(dxy) < 3.5 and abs(eta) < etamaxbound and abs(eta) >= etaminbound)
            {
                sg_all_track_eta_by_layer[i].push_back(eta);
                if (sg_trackmatch_by_layer[i]) sg_matched_track_eta_by_layer[i].push_back(eta);
            }

            if (abs(pt) > 1.5 and abs(eta) < etamaxbound and abs(eta) >= etaminbound)
            {
                sg_all_track_dxy_by_layer[i].push_back(dxy);
                if (sg_trackmatch_by_layer[i]) sg_matched_track_dxy_by_layer[i].push_back(dxy);
            }

        }

        if (eff_mode == kStudySDLBEEEEE)
        {

            if (not sg_trackmatch_by_layer[0] and pt >= 1.5)
            {

                std::cout << "======================================" << std::endl;
                std::cout << "DEBUGDEBUGDEBUG: Found trk not matched" << std::endl;
                std::cout << "======================================" << std::endl;

                bool has_layer2_barrel = false;
                int nmu = 0;
                std::vector<unsigned int> modules;

                float _pt = trk.sim_pt()[isimtrk];
                float _eta = trk.sim_eta()[isimtrk];
                float _phi = trk.sim_phi()[isimtrk];
                float _charge = trk.sim_q()[isimtrk];
                float _vx = trk.simvtx_x()[0];
                float _vy = trk.simvtx_y()[0];
                float _vz = trk.simvtx_z()[0];

                std::cout <<  " _pt: " << _pt <<  " _eta: " << _eta <<  " _phi: " << _phi <<  " _vx: " << _vx <<  " _vy: " << _vy <<  " _vz: " << _vz <<  " _charge: " << _charge <<  std::endl;

                std::cout <<  " hasAll12HitsWithNBarrelUsingModuleMap(isimtrk,2): " << hasAll12HitsWithNBarrelUsingModuleMap(isimtrk,2) <<  std::endl;
                std::cout <<  " hasAll12HitsWithNBarrelUsingModuleMap(isimtrk,3): " << hasAll12HitsWithNBarrelUsingModuleMap(isimtrk,3) <<  std::endl;
                std::cout <<  " hasAll12HitsWithNBarrelUsingModuleMap(isimtrk,4): " << hasAll12HitsWithNBarrelUsingModuleMap(isimtrk,4) <<  std::endl;
                std::cout <<  " hasAll12HitsWithNBarrelUsingModuleMap(isimtrk,5): " << hasAll12HitsWithNBarrelUsingModuleMap(isimtrk,5) <<  std::endl;
                std::cout <<  " hasAll12HitsWithNBarrelUsingModuleMap(isimtrk,6): " << hasAll12HitsWithNBarrelUsingModuleMap(isimtrk,6) <<  std::endl;

                for (auto& isimhit : trk.sim_simHitIdx()[isimtrk])
                {

                    nmu = 0;

                    if (trk.simhit_subdet()[isimhit] == 4 or trk.simhit_subdet()[isimhit] == 5)
                    {
                        std::cout << "===============================================" << std::endl;
                        SDL::Module module(trk.simhit_detId()[isimhit]);
                        std::cout <<  " module.layer(): " << module.layer() <<  std::endl;
                        std::cout <<  " module.subdet(): " << module.subdet() <<  std::endl;
                        modules.push_back(module.detId());
                        if (module.isLower())
                        {
                            std::cout << trk.simhit_detId()[isimhit] << std::endl;
                        }
                        else
                        {
                            std::cout << "upper:" << trk.simhit_detId()[isimhit] << std::endl;
                        }

                        std::cout <<  " trk.simhit_particle()[isimhit]: " << trk.simhit_particle()[isimhit] <<  std::endl;

                        if (module.layer() == 2 and module.subdet() == 5)
                        {
                            std::cout << "HAS LAYER 2 BARREL HIT" << std::endl;
                            has_layer2_barrel = true;
                        }

                        if (abs(trk.simhit_particle()[isimhit]) == 13)
                        {
                            nmu++;
                        }

                        for (unsigned int irecohit = 0; irecohit < trk.simhit_hitIdx()[isimhit].size(); ++irecohit)
                        {
                            std::cout <<  " trk.simhit_hitIdx()[isimhit][irecohit]: " << trk.simhit_hitIdx()[isimhit][irecohit] <<  std::endl;
                            SDL::Module recomodule(trk.ph2_detId()[trk.simhit_hitIdx()[isimhit][irecohit]]);
                            std::cout <<  " recomodule.detId(): " << recomodule.detId() <<  std::endl;
                            std::cout <<  " recomodule.layer(): " << recomodule.layer() <<  std::endl;
                            std::cout <<  " recomodule.subdet(): " << recomodule.subdet() <<  std::endl;
                        }
                    }
                }

                if (has_layer2_barrel)
                {
                    std::cout << "DEBUGDEBUGDEBUG: HAS LAYER2 BARREL" << std::endl;
                    std::cout << "DEBUGDEBUGDEBUG: NMU" << nmu << std::endl;
                }
                else
                {
                    std::cout << "DEBUG1 ======" << std::endl;
                    for (auto& module : modules)
                    {
                        std::cout << "DEBUG1 " << module << std::endl;
                    }
                }

            }

        }

        // *****************
        // Tracklet
        // *****************
        for (unsigned int i = 0; i < 3; ++i)
        {

            int offset = 3;
            float etamaxbound = etabounds[i+offset];
            float etaminbound = etainnerbounds[i+offset];

            if (abs(eta) < etamaxbound and abs(dxy) < 3.5 and abs(eta) >= etaminbound)
            {
                tl_all_track_pt_by_layer[i].push_back(pt);
                if (tl_trackmatch_by_layer[i]) tl_matched_track_pt_by_layer[i].push_back(pt);
            }

            if (abs(pt) > 1.5 and abs(dxy) < 3.5 and abs(eta) < etamaxbound and abs(eta) >= etaminbound)
            {
                tl_all_track_eta_by_layer[i].push_back(eta);
                if (tl_trackmatch_by_layer[i]) tl_matched_track_eta_by_layer[i].push_back(eta);
            }

            if (abs(pt) > 1.5 and abs(eta) < etamaxbound and abs(eta) >= etaminbound)
            {
                tl_all_track_dxy_by_layer[i].push_back(dxy);
                if (tl_trackmatch_by_layer[i]) tl_matched_track_dxy_by_layer[i].push_back(dxy);
            }

        }

        // *****************
        // Track Candidate
        // *****************
        for (unsigned int i = 0; i < 1; ++i)
        {

            int offset = 5;
            float etamaxbound = etabounds[i+offset];
            float etaminbound = etainnerbounds[i+offset];

            if (abs(eta) < etamaxbound and abs(dxy) < 3.5 and abs(eta) >= etaminbound)
            {
                tc_all_track_pt_by_layer[i].push_back(pt);
                if (tc_trackmatch_by_layer[i]) tc_matched_track_pt_by_layer[i].push_back(pt);
            }

            if (abs(pt) > 1.5 and abs(dxy) < 3.5 and abs(eta) < etamaxbound and abs(eta) >= etaminbound)
            {
                tc_all_track_eta_by_layer[i].push_back(eta);
                if (tc_trackmatch_by_layer[i]) tc_matched_track_eta_by_layer[i].push_back(eta);
            }

            if (abs(pt) > 1.5 and abs(eta) < etamaxbound and abs(eta) >= etaminbound)
            {
                tc_all_track_dxy_by_layer[i].push_back(dxy);
                if (tc_trackmatch_by_layer[i]) tc_matched_track_dxy_by_layer[i].push_back(dxy);
            }

        }

    }

}

