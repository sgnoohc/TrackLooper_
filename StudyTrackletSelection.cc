#include "StudyTrackletSelection.h"

StudyTrackletSelection::StudyTrackletSelection(const char* studyName, StudyTrackletSelection::StudyTrackletSelectionMode mode_)
{

    studyname = studyName;
    mode = mode_;
    switch (mode)
    {
        case kStudySelAll: modename = "all"; break;
        case kStudySelBarrelBarrelBarrelBarrel: modename = "barrelbarrelbarrelbarrel"; break;
        case kStudySelBarrelBarrelEndcapEndcap: modename = "barrelbarrelendcapendcap"; break;
        case kStudySelBB1BB3: modename = "bb1bb3"; break;
        case kStudySelBB1BB4: modename = "bb1bb4"; break;
        case kStudySelBB1BB5: modename = "bb1bb5"; break;
        case kStudySelBB2BB4: modename = "bb2bb4"; break;
        case kStudySelBB3BB5: modename = "bb3bb5"; break;
        case kStudySelSpecific: modename = "specific"; break;
        default: modename = "UNDEFINED"; break;
    }

}

void StudyTrackletSelection::bookStudy()
{
    // Book Histograms
    for (int ii = 0; ii < 7; ++ii)
    {
        ana.histograms.addVecHistogram(TString::Format("tl_%s_deltaBeta_ptbin%d", modename, ii), 180, -0.15, 0.15, [&, ii]() { return tl_deltaBeta_ptslice[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_deltaBeta_postCut_ptbin%d", modename, ii), 180, -0.15, 0.15, [&, ii]() { return tl_deltaBeta_postCut_ptslice[ii]; } );
    }
    ana.histograms.addVecHistogram(TString::Format("tl_%s_deltaBeta", modename), 180, -0.15, 0.15, [&]() { return tl_deltaBeta; } );
    ana.histograms.addVecHistogram(TString::Format("tl_%s_deltaBeta_zoom", modename), 180, -0.06, 0.06, [&]() { return tl_deltaBeta; } );
    ana.histograms.addVecHistogram(TString::Format("tl_%s_deltaBeta_slava", modename), 400, -0.15, 0.15, [&]() { return tl_deltaBeta; } );
    ana.histograms.addVecHistogram(TString::Format("tl_%s_deltaBeta_postCut", modename), 180, -0.15, 0.15, [&]() { return tl_deltaBeta_postCut; } );
    ana.histograms.addVecHistogram(TString::Format("tl_%s_deltaBeta_dcut", modename), 180, -0.15, 0.15, [&]() { return tl_deltaBeta_dcut; } );
    ana.histograms.addVecHistogram(TString::Format("tl_%s_betaOut", modename), 180, -0.15, 0.15, [&]() { return tl_betaOut; } );
    ana.histograms.addVecHistogram(TString::Format("tl_%s_betaOut_wide", modename), 180, -0.6, 0.6, [&]() { return tl_betaOut; } );
    ana.histograms.addVecHistogram(TString::Format("tl_%s_betaOut_dcut", modename), 180, -0.15, 0.15, [&]() { return tl_betaOut_dcut; } );
    ana.histograms.addVecHistogram(TString::Format("tl_%s_betaOut_dcut_wide", modename), 180, -0.6, 0.6, [&]() { return tl_betaOut_dcut; } );
    ana.histograms.addVecHistogram(TString::Format("tl_%s_betaOut_cutthresh", modename), 180, 0., 0.6, [&]() { return tl_betaOut_cutthresh; } );
    ana.histograms.addVecHistogram(TString::Format("tl_%s_betaIn", modename), 180, -0.15, 0.15, [&]() { return tl_betaIn; } );
    ana.histograms.addVecHistogram(TString::Format("tl_%s_betaIn_wide", modename), 180, -0.6, 0.6, [&]() { return tl_betaIn; } );
    ana.histograms.addVecHistogram(TString::Format("tl_%s_betaIn_dcut", modename), 180, -0.15, 0.15, [&]() { return tl_betaIn_dcut; } );
    ana.histograms.addVecHistogram(TString::Format("tl_%s_betaIn_dcut_wide", modename), 180, -0.6, 0.6, [&]() { return tl_betaIn_dcut; } );
    ana.histograms.addVecHistogram(TString::Format("tl_%s_betaIn_cutthresh", modename), 180, 0., 0.6, [&]() { return tl_betaIn_cutthresh; } );
    ana.histograms.addVecHistogram(TString::Format("tl_%s_cutflow", modename), 8, 0, 8, [&]() { return tl_cutflow; } );

    const int nlayers = NLAYERS;
    for (int ii = 0; ii < nlayers; ++ii)
    {
        for (int jj = 0; jj < 7; ++jj)
        {
            ana.histograms.addVecHistogram(TString::Format("tl_%s_deltaBeta_ptbin%d_by_layer%d", modename, jj, ii), 180, -0.15, 0.15, [&, ii, jj]() { return tl_deltaBeta_ptslice_by_layer[ii][jj]; } );
            ana.histograms.addVecHistogram(TString::Format("tl_%s_deltaBeta_postCut_ptbin%d_by_layer%d", modename, jj, ii), 180, -0.15, 0.15, [&, ii, jj]() { return tl_deltaBeta_postCut_ptslice_by_layer[ii][jj]; } );
        }
        ana.histograms.addVecHistogram(TString::Format("tl_%s_deltaBeta_by_layer%d", modename, ii), 180, -0.15, 0.15, [&, ii]() { return tl_deltaBeta_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_deltaBeta_postCut_by_layer%d", modename, ii), 180, -0.15, 0.15, [&, ii]() { return tl_deltaBeta_postCut_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_deltaBeta_dcut_by_layer%d", modename, ii), 180, -0.15, 0.15, [&, ii]() { return tl_deltaBeta_dcut_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_betaOut_by_layer%d", modename, ii), 180, -0.15, 0.15, [&, ii]() { return tl_betaOut_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_betaOut_wide_by_layer%d", modename, ii), 180, -0.6, 0.6, [&, ii]() { return tl_betaOut_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_betaOut_dcut_by_layer%d", modename, ii), 180, -0.15, 0.15, [&, ii]() { return tl_betaOut_dcut_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_betaOut_dcut_wide_by_layer%d", modename, ii), 180, -0.6, 0.6, [&, ii]() { return tl_betaOut_dcut_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_betaOut_cutthresh_by_layer%d", modename, ii), 180, 0., 0.6, [&, ii]() { return tl_betaOut_cutthresh_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_betaIn_by_layer%d", modename, ii), 180, -0.15, 0.15, [&, ii]() { return tl_betaIn_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_betaIn_wide_by_layer%d", modename, ii), 180, -0.6, 0.6, [&, ii]() { return tl_betaIn_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_betaIn_dcut_by_layer%d", modename, ii), 180, -0.15, 0.15, [&, ii]() { return tl_betaIn_dcut_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_betaIn_dcut_wide_by_layer%d", modename, ii), 180, -0.6, 0.6, [&, ii]() { return tl_betaIn_dcut_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_betaIn_cutthresh_by_layer%d", modename, ii), 180, 0., 0.6, [&, ii]() { return tl_betaIn_cutthresh_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("tl_%s_cutflow_by_layer%d", modename, ii), 8, 0, 8, [&, ii]() { return tl_cutflow_by_layer[ii]; } );
    }

    // ana.tx->createBranch<float>("sinAlphaMax");
    // ana.tx->createBranch<float>("betaIn");
    // ana.tx->createBranch<float>("betaInRHmax");
    // ana.tx->createBranch<float>("betaInRHmin");
    // ana.tx->createBranch<float>("betaOut");
    // ana.tx->createBranch<float>("betaOutRHmax");
    // ana.tx->createBranch<float>("betaOutRHmin");
    // ana.tx->createBranch<float>("dBeta");
    // ana.tx->createBranch<float>("dBetaCut2");
    // ana.tx->createBranch<float>("dBetaLum2");
    // ana.tx->createBranch<float>("dBetaMuls");
    // ana.tx->createBranch<float>("dBetaRIn2");
    // ana.tx->createBranch<float>("dBetaROut2");
    // ana.tx->createBranch<float>("dBetaRes");
    // ana.tx->createBranch<float>("deltaZLum");
    // ana.tx->createBranch<float>("dr");
    // ana.tx->createBranch<float>("dzDrtScale");
    // ana.tx->createBranch<float>("innerSgInnerMdDetId");
    // ana.tx->createBranch<float>("innerSgOuterMdDetId");
    // ana.tx->createBranch<float>("k2Rinv1GeVf");
    // ana.tx->createBranch<float>("kRinv1GeVf");
    // ana.tx->createBranch<float>("outerSgInnerMdDetId");
    // ana.tx->createBranch<float>("outerSgOuterMdDetId");
    // ana.tx->createBranch<float>("pixelPSZpitch");
    // ana.tx->createBranch<float>("ptCut");
    // ana.tx->createBranch<float>("pt_betaIn");
    // ana.tx->createBranch<float>("pt_betaOut");
    // ana.tx->createBranch<float>("rtIn");
    // ana.tx->createBranch<float>("rtOut");
    // ana.tx->createBranch<float>("rtOut_o_rtIn");
    // ana.tx->createBranch<float>("sdIn_d");
    // ana.tx->createBranch<float>("sdOut_d");
    // ana.tx->createBranch<float>("sdlSlope");
    // ana.tx->createBranch<float>("strip2SZpitch");
    // ana.tx->createBranch<float>("zGeom");
    // ana.tx->createBranch<float>("zIn");
    // ana.tx->createBranch<float>("zLo");
    // ana.tx->createBranch<float>("zOut");
    // ana.tx->createBranch<float>("betacormode");
    // ana.tx->createBranch<float>("sdIn_alpha");
    // ana.tx->createBranch<float>("sdOut_alphaOut");
    // ana.tx->createBranch<float>("rawBetaInCorrection");
    // ana.tx->createBranch<float>("rawBetaOutCorrection");
    // ana.tx->createBranch<float>("rawBetaIn");
    // ana.tx->createBranch<float>("rawBetaOut");

}

void StudyTrackletSelection::doStudy(SDL::Event& event, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents)
{

    // Each do study is performed per event

    // The study assumes that the createTracklets has been run with "AllComb" algorithm
    // The DefaultAlgo will be run individually here

    // First clear all the output variables that will be used to fill the histograms for this event
    tl_deltaBeta.clear();
    tl_deltaBeta_postCut.clear();
    tl_deltaBeta_dcut.clear();
    tl_betaOut.clear();
    tl_betaOut_dcut.clear();
    tl_betaOut_cutthresh.clear();
    tl_betaIn.clear();
    tl_betaIn_dcut.clear();
    tl_betaIn_cutthresh.clear();
    tl_cutflow.clear();
    for (int ii = 0; ii < 7; ++ii)
    {
        tl_deltaBeta_ptslice[ii].clear();
        tl_deltaBeta_postCut_ptslice[ii].clear();
    }
    for (int ii = 0; ii < NLAYERS; ++ii)
    {
        tl_deltaBeta_postCut_by_layer[ii].clear();
        tl_deltaBeta_by_layer[ii].clear();
        tl_deltaBeta_dcut_by_layer[ii].clear();
        tl_betaOut_by_layer[ii].clear();
        tl_betaOut_dcut_by_layer[ii].clear();
        tl_betaOut_cutthresh_by_layer[ii].clear();
        tl_betaIn_by_layer[ii].clear();
        tl_betaIn_dcut_by_layer[ii].clear();
        tl_betaIn_cutthresh_by_layer[ii].clear();
        tl_cutflow_by_layer[ii].clear();
        for (int jj = 0; jj < 7; ++jj)
        {
            tl_deltaBeta_ptslice_by_layer[ii][jj].clear();
            tl_deltaBeta_postCut_ptslice_by_layer[ii][jj].clear();
        }
    }

    //***********************
    // Studying selections and cutflows for the recoed events
    //***********************

    // Loop over tracklets in event
    for (auto& layerPtr : event.getLayerPtrs())
    {

        // Parse the layer index later to be used for indexing
        int layer_idx = layerPtr->layerIdx() - 1;

        // This means no tracklets in this layer
        if (layerPtr->getTrackletPtrs().size() == 0)
        {
            continue;
        }

        // Assuming I have at least one tracklets from this track
        std::vector<SDL::Tracklet*> tls_of_interest;
        for (auto& tl : layerPtr->getTrackletPtrs())
        {
            const SDL::Module& innerSgInnerMDLowerHitModule = tl->innerSegmentPtr()->innerMiniDoubletPtr()->anchorHitPtr()->getModule();
            const SDL::Module& outerSgInnerMDLowerHitModule = tl->outerSegmentPtr()->innerMiniDoubletPtr()->anchorHitPtr()->getModule();
            const SDL::Module& innerSgOuterMDLowerHitModule = tl->innerSegmentPtr()->outerMiniDoubletPtr()->anchorHitPtr()->getModule();
            const SDL::Module& outerSgOuterMDLowerHitModule = tl->outerSegmentPtr()->outerMiniDoubletPtr()->anchorHitPtr()->getModule();
            const int innerSgInnerLayerIdx = innerSgInnerMDLowerHitModule.layer();
            const int outerSgInnerLayerIdx = outerSgInnerMDLowerHitModule.layer();
            const bool innerSgInnerLayerBarrel = innerSgInnerMDLowerHitModule.subdet() == SDL::Module::Barrel;
            const bool outerSgInnerLayerBarrel = outerSgInnerMDLowerHitModule.subdet() == SDL::Module::Barrel;
            const bool innerSgOuterLayerBarrel = innerSgOuterMDLowerHitModule.subdet() == SDL::Module::Barrel;
            const bool outerSgOuterLayerBarrel = outerSgOuterMDLowerHitModule.subdet() == SDL::Module::Barrel;
            const bool outerSgInnerLayerEndcap = outerSgInnerMDLowerHitModule.subdet() == SDL::Module::Endcap;
            const bool innerSgInnerLayerEndcap = innerSgInnerMDLowerHitModule.subdet() == SDL::Module::Endcap;
            const bool outerSgOuterLayerEndcap = outerSgOuterMDLowerHitModule.subdet() == SDL::Module::Endcap;
            const bool innerSgOuterLayerEndcap = innerSgOuterMDLowerHitModule.subdet() == SDL::Module::Endcap;
            const bool innerSgInnerLayerBarrelFlat = innerSgInnerMDLowerHitModule.subdet() == SDL::Module::Barrel and innerSgInnerMDLowerHitModule.side() == SDL::Module::Center;
            const bool outerSgInnerLayerBarrelFlat = outerSgInnerMDLowerHitModule.subdet() == SDL::Module::Barrel and outerSgInnerMDLowerHitModule.side() == SDL::Module::Center;
            const bool innerSgInnerLayerBarrelTilt = innerSgInnerMDLowerHitModule.subdet() == SDL::Module::Barrel and innerSgInnerMDLowerHitModule.side() != SDL::Module::Center;
            const bool outerSgInnerLayerBarrelTilt = outerSgInnerMDLowerHitModule.subdet() == SDL::Module::Barrel and outerSgInnerMDLowerHitModule.side() != SDL::Module::Center;
            const bool innerSgOuterLayerBarrelFlat = innerSgOuterMDLowerHitModule.subdet() == SDL::Module::Barrel and innerSgOuterMDLowerHitModule.side() == SDL::Module::Center;
            const bool outerSgOuterLayerBarrelFlat = outerSgOuterMDLowerHitModule.subdet() == SDL::Module::Barrel and outerSgOuterMDLowerHitModule.side() == SDL::Module::Center;
            const bool innerSgOuterLayerBarrelTilt = innerSgOuterMDLowerHitModule.subdet() == SDL::Module::Barrel and innerSgOuterMDLowerHitModule.side() != SDL::Module::Center;
            const bool outerSgOuterLayerBarrelTilt = outerSgOuterMDLowerHitModule.subdet() == SDL::Module::Barrel and outerSgOuterMDLowerHitModule.side() != SDL::Module::Center;
            const bool innerSgInnerLayerPS = innerSgInnerMDLowerHitModule.moduleType() == SDL::Module::PS;
            const bool innerSgOuterLayerPS = innerSgOuterMDLowerHitModule.moduleType() == SDL::Module::PS;
            const bool outerSgInnerLayerPS = outerSgInnerMDLowerHitModule.moduleType() == SDL::Module::PS;
            const bool outerSgOuterLayerPS = outerSgOuterMDLowerHitModule.moduleType() == SDL::Module::PS;
            const bool outerSgInnerLayer2S = outerSgInnerMDLowerHitModule.moduleType() == SDL::Module::TwoS;
            const bool outerSgOuterLayer2S = outerSgOuterMDLowerHitModule.moduleType() == SDL::Module::TwoS;

            // Depending on the mode, only include a subset of interested tracklets
            switch (mode)
            {
                case kStudySelAll: /* do nothing */ break;
                case kStudySelBarrelBarrelBarrelBarrel:
                                                                  if (not (innerSgInnerLayerBarrel
                                                                              and outerSgInnerLayerBarrel
                                                                              and innerSgOuterLayerBarrel
                                                                              and outerSgOuterLayerBarrel))
                                                                      continue;
                                                                  break;
                case kStudySelBarrelBarrelEndcapEndcap:
                                                                  if (not (innerSgInnerLayerBarrel
                                                                              and outerSgInnerLayerEndcap
                                                                              and innerSgOuterLayerBarrel
                                                                              and outerSgOuterLayerEndcap
                                                                              and innerSgInnerLayerPS
                                                                              and innerSgOuterLayerPS
                                                                              and outerSgInnerLayer2S
                                                                              and outerSgOuterLayer2S
                                                                          ))
                                                                      continue;
                                                                  break;
                case kStudySelBB1BB3:
                                                                  if (not (
                                                                              innerSgInnerLayerIdx == 1
                                                                              and outerSgInnerLayerIdx == 3
                                                                              and innerSgInnerLayerBarrel
                                                                              and outerSgInnerLayerBarrel
                                                                              and innerSgOuterLayerBarrel
                                                                              and outerSgOuterLayerBarrel
                                                                              ))
                                                                      continue;
                                                                  break;
                case kStudySelBB1BB4:
                                                                  if (not (
                                                                              innerSgInnerLayerIdx == 1
                                                                              and outerSgInnerLayerIdx == 4
                                                                              and innerSgInnerLayerBarrel
                                                                              and outerSgInnerLayerBarrel
                                                                              and innerSgOuterLayerBarrel
                                                                              and outerSgOuterLayerBarrel
                                                                              ))
                                                                      continue;
                                                                  break;
                case kStudySelBB1BB5:
                                                                  if (not (
                                                                              innerSgInnerLayerIdx == 1
                                                                              and outerSgInnerLayerIdx == 5
                                                                              and innerSgInnerLayerBarrel
                                                                              and outerSgInnerLayerBarrel
                                                                              and innerSgOuterLayerBarrel
                                                                              and outerSgOuterLayerBarrel
                                                                              ))
                                                                      continue;
                                                                  break;
                case kStudySelBB2BB4:
                                                                  if (not (
                                                                              innerSgInnerLayerIdx == 2
                                                                              and outerSgInnerLayerIdx == 4
                                                                              and innerSgInnerLayerBarrel
                                                                              and outerSgInnerLayerBarrel
                                                                              and innerSgOuterLayerBarrel
                                                                              and outerSgOuterLayerBarrel
                                                                              ))
                                                                      continue;
                                                                  break;
                case kStudySelBB3BB5:
                                                                  if (not (
                                                                              innerSgInnerLayerIdx == 3
                                                                              and outerSgInnerLayerIdx == 5
                                                                              and innerSgInnerLayerBarrel
                                                                              and outerSgInnerLayerBarrel
                                                                              and innerSgOuterLayerBarrel
                                                                              and outerSgOuterLayerBarrel
                                                                              ))
                                                                      continue;
                                                                  break;
                case kStudySelSpecific:
                                                                  if (not (
                                                                              layer_idx == 0
                                                                              and innerSgInnerLayerIdx == 1
                                                                              and outerSgInnerLayerIdx == 3
                                                                              and innerSgInnerLayerBarrel
                                                                              and outerSgInnerLayerBarrel
                                                                              and innerSgOuterLayerBarrel
                                                                              and outerSgOuterLayerBarrel
                                                                              ))
                                                                      continue;
                                                                  break;
                default: /* skip everything should not be here anyways...*/ continue; break;
            }

            // If this tracklet passes the condition that it is of interest then, add to the list of tracklets of interest
            tls_of_interest.push_back(tl);

        }

        // If no tls of interest are found then skip
        if (tls_of_interest.size() == 0)
            continue;

        // // Ghost removing
        // std::vector<int> tls_of_interest_mask;
        // std::vector<SDL::Tracklet*> tls_of_interest_ghost_removed;

        // for (auto& tl : tls_of_interest)
        // {
        //     tls_of_interest_mask.push_back(1);
        // }

        // for (unsigned int ii = 0; ii < tls_of_interest.size(); ++ii)
        // {
        //     if (tls_of_interest_mask[ii])
        //     {
        //         for (unsigned int jj = ii + 1; jj < tls_of_interest.size(); ++jj)
        //         {

        //             if (tls_of_interest[ii]->isAnchorHitIdxMatched(*tls_of_interest[jj]))
        //             {
        //                 tls_of_interest_mask[jj] = 0;
        //             }

        //         }
        //     }
        // }

        // for (unsigned int ii = 0; ii < tls_of_interest.size(); ++ii)
        // {
        //     if (tls_of_interest_mask[ii])
        //     {
        //         tls_of_interest_ghost_removed.push_back(tls_of_interest[ii]);
        //     }
        // }

        // Evaluate which pt bin it is
        // iptbin = -1;

        // The tls_of_interest holds only the tl "candidate" that we think are of interest for the given study mode
        for (auto& tl : tls_of_interest)
        {

            tl->runTrackletAlgo(SDL::Default_TLAlgo);

            // Cutflow
            //------------------------
            tl_cutflow.push_back(0);
            tl_cutflow_by_layer[layer_idx].push_back(0);

            const int& passbit = tl->getPassBitsDefaultAlgo();

            for (unsigned int i = 0; i < SDL::Tracklet::TrackletSelection::nCut; ++i)
            {
                if (passbit & (1 << i))
                {
                    tl_cutflow.push_back(i + 1);
                    tl_cutflow_by_layer[layer_idx].push_back(i + 1);
                }
                else
                {
                    break;
                }
            }

            // DeltaBeta post cut
            //------------------------
            if (passbit & (1 << SDL::Tracklet::TrackletSelection::dBeta))
            {

                const float deltaBeta = tl->getDeltaBeta();

                tl_deltaBeta_postCut.push_back(deltaBeta);

                tl_deltaBeta_postCut_by_layer[layer_idx].push_back(deltaBeta);


                // std::cout << tl << std::endl;
                const std::vector<int>& simhitidx_innerSg_innerMD_lowerHit_vector = trk.ph2_simHitIdx()[tl->innerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->idx()];
                const std::vector<int>& simhitidx_innerSg_innerMD_upperHit_vector = trk.ph2_simHitIdx()[tl->innerSegmentPtr()->innerMiniDoubletPtr()->upperHitPtr()->idx()];
                const std::vector<int>& simhitidx_innerSg_outerMD_lowerHit_vector = trk.ph2_simHitIdx()[tl->innerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->idx()];
                const std::vector<int>& simhitidx_innerSg_outerMD_upperHit_vector = trk.ph2_simHitIdx()[tl->innerSegmentPtr()->outerMiniDoubletPtr()->upperHitPtr()->idx()];
                const std::vector<int>& simhitidx_outerSg_innerMD_lowerHit_vector = trk.ph2_simHitIdx()[tl->outerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->idx()];
                const std::vector<int>& simhitidx_outerSg_innerMD_upperHit_vector = trk.ph2_simHitIdx()[tl->outerSegmentPtr()->innerMiniDoubletPtr()->upperHitPtr()->idx()];
                const std::vector<int>& simhitidx_outerSg_outerMD_lowerHit_vector = trk.ph2_simHitIdx()[tl->outerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->idx()];
                const std::vector<int>& simhitidx_outerSg_outerMD_upperHit_vector = trk.ph2_simHitIdx()[tl->outerSegmentPtr()->outerMiniDoubletPtr()->upperHitPtr()->idx()];

                const int& simhitidx_innerSg_innerMD_lowerHit = simhitidx_innerSg_innerMD_lowerHit_vector.size() > 0 ? simhitidx_innerSg_innerMD_lowerHit_vector[0] : -999;
                const int& simhitidx_innerSg_innerMD_upperHit = simhitidx_innerSg_innerMD_upperHit_vector.size() > 0 ? simhitidx_innerSg_innerMD_upperHit_vector[0] : -999;
                const int& simhitidx_innerSg_outerMD_lowerHit = simhitidx_innerSg_outerMD_lowerHit_vector.size() > 0 ? simhitidx_innerSg_outerMD_lowerHit_vector[0] : -999;
                const int& simhitidx_innerSg_outerMD_upperHit = simhitidx_innerSg_outerMD_upperHit_vector.size() > 0 ? simhitidx_innerSg_outerMD_upperHit_vector[0] : -999;
                const int& simhitidx_outerSg_innerMD_lowerHit = simhitidx_outerSg_innerMD_lowerHit_vector.size() > 0 ? simhitidx_outerSg_innerMD_lowerHit_vector[0] : -999;
                const int& simhitidx_outerSg_innerMD_upperHit = simhitidx_outerSg_innerMD_upperHit_vector.size() > 0 ? simhitidx_outerSg_innerMD_upperHit_vector[0] : -999;
                const int& simhitidx_outerSg_outerMD_lowerHit = simhitidx_outerSg_outerMD_lowerHit_vector.size() > 0 ? simhitidx_outerSg_outerMD_lowerHit_vector[0] : -999;
                const int& simhitidx_outerSg_outerMD_upperHit = simhitidx_outerSg_outerMD_upperHit_vector.size() > 0 ? simhitidx_outerSg_outerMD_upperHit_vector[0] : -999;

                int simhit_particle_innerSg_innerMD_lowerHit = simhitidx_innerSg_innerMD_lowerHit >= 0 ? trk.simhit_particle()[simhitidx_innerSg_innerMD_lowerHit] : -999;
                int simhit_particle_innerSg_innerMD_upperHit = simhitidx_innerSg_innerMD_upperHit >= 0 ? trk.simhit_particle()[simhitidx_innerSg_innerMD_upperHit] : -999;
                int simhit_particle_innerSg_outerMD_lowerHit = simhitidx_innerSg_outerMD_lowerHit >= 0 ? trk.simhit_particle()[simhitidx_innerSg_outerMD_lowerHit] : -999;
                int simhit_particle_innerSg_outerMD_upperHit = simhitidx_innerSg_outerMD_upperHit >= 0 ? trk.simhit_particle()[simhitidx_innerSg_outerMD_upperHit] : -999;
                int simhit_particle_outerSg_innerMD_lowerHit = simhitidx_outerSg_innerMD_lowerHit >= 0 ? trk.simhit_particle()[simhitidx_outerSg_innerMD_lowerHit] : -999;
                int simhit_particle_outerSg_innerMD_upperHit = simhitidx_outerSg_innerMD_upperHit >= 0 ? trk.simhit_particle()[simhitidx_outerSg_innerMD_upperHit] : -999;
                int simhit_particle_outerSg_outerMD_lowerHit = simhitidx_outerSg_outerMD_lowerHit >= 0 ? trk.simhit_particle()[simhitidx_outerSg_outerMD_lowerHit] : -999;
                int simhit_particle_outerSg_outerMD_upperHit = simhitidx_outerSg_outerMD_upperHit >= 0 ? trk.simhit_particle()[simhitidx_outerSg_outerMD_upperHit] : -999;

                int simhit_simTrkIdx_innerSg_innerMD_lowerHit = simhitidx_innerSg_innerMD_lowerHit >= 0 ? trk.simhit_simTrkIdx()[simhitidx_innerSg_innerMD_lowerHit] : -999;
                int simhit_simTrkIdx_innerSg_innerMD_upperHit = simhitidx_innerSg_innerMD_upperHit >= 0 ? trk.simhit_simTrkIdx()[simhitidx_innerSg_innerMD_upperHit] : -999;
                int simhit_simTrkIdx_innerSg_outerMD_lowerHit = simhitidx_innerSg_outerMD_lowerHit >= 0 ? trk.simhit_simTrkIdx()[simhitidx_innerSg_outerMD_lowerHit] : -999;
                int simhit_simTrkIdx_innerSg_outerMD_upperHit = simhitidx_innerSg_outerMD_upperHit >= 0 ? trk.simhit_simTrkIdx()[simhitidx_innerSg_outerMD_upperHit] : -999;
                int simhit_simTrkIdx_outerSg_innerMD_lowerHit = simhitidx_outerSg_innerMD_lowerHit >= 0 ? trk.simhit_simTrkIdx()[simhitidx_outerSg_innerMD_lowerHit] : -999;
                int simhit_simTrkIdx_outerSg_innerMD_upperHit = simhitidx_outerSg_innerMD_upperHit >= 0 ? trk.simhit_simTrkIdx()[simhitidx_outerSg_innerMD_upperHit] : -999;
                int simhit_simTrkIdx_outerSg_outerMD_lowerHit = simhitidx_outerSg_outerMD_lowerHit >= 0 ? trk.simhit_simTrkIdx()[simhitidx_outerSg_outerMD_lowerHit] : -999;
                int simhit_simTrkIdx_outerSg_outerMD_upperHit = simhitidx_outerSg_outerMD_upperHit >= 0 ? trk.simhit_simTrkIdx()[simhitidx_outerSg_outerMD_upperHit] : -999;

                // std::cout <<  " ===============dbeta passed===============" << std::endl;
                // std::cout <<  " ==============simhit_particle=============" << std::endl;
                // std::cout <<  " simhit_particle_innerSg_innerMD_lowerHit: " << simhit_particle_innerSg_innerMD_lowerHit <<  std::endl;
                // std::cout <<  " simhit_particle_innerSg_innerMD_upperHit: " << simhit_particle_innerSg_innerMD_upperHit <<  std::endl;
                // std::cout <<  " simhit_particle_innerSg_outerMD_lowerHit: " << simhit_particle_innerSg_outerMD_lowerHit <<  std::endl;
                // std::cout <<  " simhit_particle_innerSg_outerMD_upperHit: " << simhit_particle_innerSg_outerMD_upperHit <<  std::endl;
                // std::cout <<  " simhit_particle_outerSg_innerMD_lowerHit: " << simhit_particle_outerSg_innerMD_lowerHit <<  std::endl;
                // std::cout <<  " simhit_particle_outerSg_innerMD_upperHit: " << simhit_particle_outerSg_innerMD_upperHit <<  std::endl;
                // std::cout <<  " simhit_particle_outerSg_outerMD_lowerHit: " << simhit_particle_outerSg_outerMD_lowerHit <<  std::endl;
                // std::cout <<  " simhit_particle_outerSg_outerMD_upperHit: " << simhit_particle_outerSg_outerMD_upperHit <<  std::endl;

                // std::cout <<  " ==============simhit_simTrkIdx============" << std::endl;
                // std::cout <<  " simhit_simTrkIdx_innerSg_innerMD_lowerHit: " << simhit_simTrkIdx_innerSg_innerMD_lowerHit <<  std::endl;
                // std::cout <<  " simhit_simTrkIdx_innerSg_innerMD_upperHit: " << simhit_simTrkIdx_innerSg_innerMD_upperHit <<  std::endl;
                // std::cout <<  " simhit_simTrkIdx_innerSg_outerMD_lowerHit: " << simhit_simTrkIdx_innerSg_outerMD_lowerHit <<  std::endl;
                // std::cout <<  " simhit_simTrkIdx_innerSg_outerMD_upperHit: " << simhit_simTrkIdx_innerSg_outerMD_upperHit <<  std::endl;
                // std::cout <<  " simhit_simTrkIdx_outerSg_innerMD_lowerHit: " << simhit_simTrkIdx_outerSg_innerMD_lowerHit <<  std::endl;
                // std::cout <<  " simhit_simTrkIdx_outerSg_innerMD_upperHit: " << simhit_simTrkIdx_outerSg_innerMD_upperHit <<  std::endl;
                // std::cout <<  " simhit_simTrkIdx_outerSg_outerMD_lowerHit: " << simhit_simTrkIdx_outerSg_outerMD_lowerHit <<  std::endl;
                // std::cout <<  " simhit_simTrkIdx_outerSg_outerMD_upperHit: " << simhit_simTrkIdx_outerSg_outerMD_upperHit <<  std::endl;

                // std::cout << std::endl;
                // std::cout <<  "dbeta passed";
                // std::cout <<  " : ";
                // std::cout << std::setw(4) << simhit_particle_innerSg_innerMD_lowerHit <<  " : ";
                // std::cout << std::setw(4) << simhit_particle_innerSg_innerMD_upperHit <<  " : ";
                // std::cout << std::setw(4) << simhit_particle_innerSg_outerMD_lowerHit <<  " : ";
                // std::cout << std::setw(4) << simhit_particle_innerSg_outerMD_upperHit <<  " : ";
                // std::cout << std::setw(4) << simhit_particle_outerSg_innerMD_lowerHit <<  " : ";
                // std::cout << std::setw(4) << simhit_particle_outerSg_innerMD_upperHit <<  " : ";
                // std::cout << std::setw(4) << simhit_particle_outerSg_outerMD_lowerHit <<  " : ";
                // std::cout << std::setw(4) << simhit_particle_outerSg_outerMD_upperHit;
                // std::cout <<  " : ";
                // std::cout << std::setw(4) << simhit_simTrkIdx_innerSg_innerMD_lowerHit <<  " : ";
                // std::cout << std::setw(4) << simhit_simTrkIdx_innerSg_innerMD_upperHit <<  " : ";
                // std::cout << std::setw(4) << simhit_simTrkIdx_innerSg_outerMD_lowerHit <<  " : ";
                // std::cout << std::setw(4) << simhit_simTrkIdx_innerSg_outerMD_upperHit <<  " : ";
                // std::cout << std::setw(4) << simhit_simTrkIdx_outerSg_innerMD_lowerHit <<  " : ";
                // std::cout << std::setw(4) << simhit_simTrkIdx_outerSg_innerMD_upperHit <<  " : ";
                // std::cout << std::setw(4) << simhit_simTrkIdx_outerSg_outerMD_lowerHit <<  " : ";
                // std::cout << std::setw(4) << simhit_simTrkIdx_outerSg_outerMD_upperHit;
                // std::cout <<  " : ";
                // std::cout << std::setw(8) << (simhit_simTrkIdx_innerSg_innerMD_lowerHit ? trk.sim_pt()[simhit_simTrkIdx_innerSg_innerMD_lowerHit] : -99) << " : ";
                // std::cout << std::setw(8) << (simhit_simTrkIdx_innerSg_innerMD_upperHit ? trk.sim_pt()[simhit_simTrkIdx_innerSg_innerMD_upperHit] : -99) << " : ";
                // std::cout << std::setw(8) << (simhit_simTrkIdx_innerSg_outerMD_lowerHit ? trk.sim_pt()[simhit_simTrkIdx_innerSg_outerMD_lowerHit] : -99) << " : ";
                // std::cout << std::setw(8) << (simhit_simTrkIdx_innerSg_outerMD_upperHit ? trk.sim_pt()[simhit_simTrkIdx_innerSg_outerMD_upperHit] : -99) << " : ";
                // std::cout << std::setw(8) << (simhit_simTrkIdx_outerSg_innerMD_lowerHit ? trk.sim_pt()[simhit_simTrkIdx_outerSg_innerMD_lowerHit] : -99) << " : ";
                // std::cout << std::setw(8) << (simhit_simTrkIdx_outerSg_innerMD_upperHit ? trk.sim_pt()[simhit_simTrkIdx_outerSg_innerMD_upperHit] : -99) << " : ";
                // std::cout << std::setw(8) << (simhit_simTrkIdx_outerSg_outerMD_lowerHit ? trk.sim_pt()[simhit_simTrkIdx_outerSg_outerMD_lowerHit] : -99) << " : ";
                // std::cout << std::setw(8) << (simhit_simTrkIdx_outerSg_outerMD_upperHit ? trk.sim_pt()[simhit_simTrkIdx_outerSg_outerMD_upperHit] : -99);
                // std::cout <<  " : ";
                // std::cout << std::setw(4) << (simhit_simTrkIdx_innerSg_innerMD_lowerHit ? trk.sim_pdgId()[simhit_simTrkIdx_innerSg_innerMD_lowerHit] : -99) << " : ";
                // std::cout << std::setw(4) << (simhit_simTrkIdx_innerSg_innerMD_upperHit ? trk.sim_pdgId()[simhit_simTrkIdx_innerSg_innerMD_upperHit] : -99) << " : ";
                // std::cout << std::setw(4) << (simhit_simTrkIdx_innerSg_outerMD_lowerHit ? trk.sim_pdgId()[simhit_simTrkIdx_innerSg_outerMD_lowerHit] : -99) << " : ";
                // std::cout << std::setw(4) << (simhit_simTrkIdx_innerSg_outerMD_upperHit ? trk.sim_pdgId()[simhit_simTrkIdx_innerSg_outerMD_upperHit] : -99) << " : ";
                // std::cout << std::setw(4) << (simhit_simTrkIdx_outerSg_innerMD_lowerHit ? trk.sim_pdgId()[simhit_simTrkIdx_outerSg_innerMD_lowerHit] : -99) << " : ";
                // std::cout << std::setw(4) << (simhit_simTrkIdx_outerSg_innerMD_upperHit ? trk.sim_pdgId()[simhit_simTrkIdx_outerSg_innerMD_upperHit] : -99) << " : ";
                // std::cout << std::setw(4) << (simhit_simTrkIdx_outerSg_outerMD_lowerHit ? trk.sim_pdgId()[simhit_simTrkIdx_outerSg_outerMD_lowerHit] : -99) << " : ";
                // std::cout << std::setw(4) << (simhit_simTrkIdx_outerSg_outerMD_upperHit ? trk.sim_pdgId()[simhit_simTrkIdx_outerSg_outerMD_upperHit] : -99);
                // std::cout << std::endl;

            }

            // DeltaBeta
            //------------------------
            if (passbit & (1 << SDL::Tracklet::TrackletSelection::dAlphaOut))
            {

                const float deltaBeta = tl->getDeltaBeta();
                const float deltaBetaCut = fabs(deltaBeta) - tl->getDeltaBetaCut();

                tl_deltaBeta.push_back(deltaBeta);
                tl_deltaBeta_dcut.push_back(deltaBetaCut);

                tl_deltaBeta_by_layer[layer_idx].push_back(deltaBeta);
                tl_deltaBeta_dcut_by_layer[layer_idx].push_back(deltaBetaCut);

                if (fabs(deltaBeta) > 0.01 and fabs(deltaBeta) < 0.02)
                {

                    // std::cout << tl << std::endl;
                    const std::vector<int>& simhitidx_innerSg_innerMD_lowerHit_vector = trk.ph2_simHitIdx()[tl->innerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->idx()];
                    const std::vector<int>& simhitidx_innerSg_innerMD_upperHit_vector = trk.ph2_simHitIdx()[tl->innerSegmentPtr()->innerMiniDoubletPtr()->upperHitPtr()->idx()];
                    const std::vector<int>& simhitidx_innerSg_outerMD_lowerHit_vector = trk.ph2_simHitIdx()[tl->innerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->idx()];
                    const std::vector<int>& simhitidx_innerSg_outerMD_upperHit_vector = trk.ph2_simHitIdx()[tl->innerSegmentPtr()->outerMiniDoubletPtr()->upperHitPtr()->idx()];
                    const std::vector<int>& simhitidx_outerSg_innerMD_lowerHit_vector = trk.ph2_simHitIdx()[tl->outerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->idx()];
                    const std::vector<int>& simhitidx_outerSg_innerMD_upperHit_vector = trk.ph2_simHitIdx()[tl->outerSegmentPtr()->innerMiniDoubletPtr()->upperHitPtr()->idx()];
                    const std::vector<int>& simhitidx_outerSg_outerMD_lowerHit_vector = trk.ph2_simHitIdx()[tl->outerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->idx()];
                    const std::vector<int>& simhitidx_outerSg_outerMD_upperHit_vector = trk.ph2_simHitIdx()[tl->outerSegmentPtr()->outerMiniDoubletPtr()->upperHitPtr()->idx()];

                    const int& simhitidx_innerSg_innerMD_lowerHit = simhitidx_innerSg_innerMD_lowerHit_vector.size() > 0 ? simhitidx_innerSg_innerMD_lowerHit_vector[0] : -999;
                    const int& simhitidx_innerSg_innerMD_upperHit = simhitidx_innerSg_innerMD_upperHit_vector.size() > 0 ? simhitidx_innerSg_innerMD_upperHit_vector[0] : -999;
                    const int& simhitidx_innerSg_outerMD_lowerHit = simhitidx_innerSg_outerMD_lowerHit_vector.size() > 0 ? simhitidx_innerSg_outerMD_lowerHit_vector[0] : -999;
                    const int& simhitidx_innerSg_outerMD_upperHit = simhitidx_innerSg_outerMD_upperHit_vector.size() > 0 ? simhitidx_innerSg_outerMD_upperHit_vector[0] : -999;
                    const int& simhitidx_outerSg_innerMD_lowerHit = simhitidx_outerSg_innerMD_lowerHit_vector.size() > 0 ? simhitidx_outerSg_innerMD_lowerHit_vector[0] : -999;
                    const int& simhitidx_outerSg_innerMD_upperHit = simhitidx_outerSg_innerMD_upperHit_vector.size() > 0 ? simhitidx_outerSg_innerMD_upperHit_vector[0] : -999;
                    const int& simhitidx_outerSg_outerMD_lowerHit = simhitidx_outerSg_outerMD_lowerHit_vector.size() > 0 ? simhitidx_outerSg_outerMD_lowerHit_vector[0] : -999;
                    const int& simhitidx_outerSg_outerMD_upperHit = simhitidx_outerSg_outerMD_upperHit_vector.size() > 0 ? simhitidx_outerSg_outerMD_upperHit_vector[0] : -999;

                    int simhit_particle_innerSg_innerMD_lowerHit = simhitidx_innerSg_innerMD_lowerHit >= 0 ? trk.simhit_particle()[simhitidx_innerSg_innerMD_lowerHit] : -999;
                    int simhit_particle_innerSg_innerMD_upperHit = simhitidx_innerSg_innerMD_upperHit >= 0 ? trk.simhit_particle()[simhitidx_innerSg_innerMD_upperHit] : -999;
                    int simhit_particle_innerSg_outerMD_lowerHit = simhitidx_innerSg_outerMD_lowerHit >= 0 ? trk.simhit_particle()[simhitidx_innerSg_outerMD_lowerHit] : -999;
                    int simhit_particle_innerSg_outerMD_upperHit = simhitidx_innerSg_outerMD_upperHit >= 0 ? trk.simhit_particle()[simhitidx_innerSg_outerMD_upperHit] : -999;
                    int simhit_particle_outerSg_innerMD_lowerHit = simhitidx_outerSg_innerMD_lowerHit >= 0 ? trk.simhit_particle()[simhitidx_outerSg_innerMD_lowerHit] : -999;
                    int simhit_particle_outerSg_innerMD_upperHit = simhitidx_outerSg_innerMD_upperHit >= 0 ? trk.simhit_particle()[simhitidx_outerSg_innerMD_upperHit] : -999;
                    int simhit_particle_outerSg_outerMD_lowerHit = simhitidx_outerSg_outerMD_lowerHit >= 0 ? trk.simhit_particle()[simhitidx_outerSg_outerMD_lowerHit] : -999;
                    int simhit_particle_outerSg_outerMD_upperHit = simhitidx_outerSg_outerMD_upperHit >= 0 ? trk.simhit_particle()[simhitidx_outerSg_outerMD_upperHit] : -999;

                    int simhit_simTrkIdx_innerSg_innerMD_lowerHit = simhitidx_innerSg_innerMD_lowerHit >= 0 ? trk.simhit_simTrkIdx()[simhitidx_innerSg_innerMD_lowerHit] : -999;
                    int simhit_simTrkIdx_innerSg_innerMD_upperHit = simhitidx_innerSg_innerMD_upperHit >= 0 ? trk.simhit_simTrkIdx()[simhitidx_innerSg_innerMD_upperHit] : -999;
                    int simhit_simTrkIdx_innerSg_outerMD_lowerHit = simhitidx_innerSg_outerMD_lowerHit >= 0 ? trk.simhit_simTrkIdx()[simhitidx_innerSg_outerMD_lowerHit] : -999;
                    int simhit_simTrkIdx_innerSg_outerMD_upperHit = simhitidx_innerSg_outerMD_upperHit >= 0 ? trk.simhit_simTrkIdx()[simhitidx_innerSg_outerMD_upperHit] : -999;
                    int simhit_simTrkIdx_outerSg_innerMD_lowerHit = simhitidx_outerSg_innerMD_lowerHit >= 0 ? trk.simhit_simTrkIdx()[simhitidx_outerSg_innerMD_lowerHit] : -999;
                    int simhit_simTrkIdx_outerSg_innerMD_upperHit = simhitidx_outerSg_innerMD_upperHit >= 0 ? trk.simhit_simTrkIdx()[simhitidx_outerSg_innerMD_upperHit] : -999;
                    int simhit_simTrkIdx_outerSg_outerMD_lowerHit = simhitidx_outerSg_outerMD_lowerHit >= 0 ? trk.simhit_simTrkIdx()[simhitidx_outerSg_outerMD_lowerHit] : -999;
                    int simhit_simTrkIdx_outerSg_outerMD_upperHit = simhitidx_outerSg_outerMD_upperHit >= 0 ? trk.simhit_simTrkIdx()[simhitidx_outerSg_outerMD_upperHit] : -999;

                    // std::cout <<  " =============dbeta 0.01 to 0.02===========" << std::endl;
                    // std::cout <<  " ==============simhit_particle=============" << std::endl;
                    // std::cout <<  " simhit_particle_innerSg_innerMD_lowerHit: " << simhit_particle_innerSg_innerMD_lowerHit <<  std::endl;
                    // std::cout <<  " simhit_particle_innerSg_innerMD_upperHit: " << simhit_particle_innerSg_innerMD_upperHit <<  std::endl;
                    // std::cout <<  " simhit_particle_innerSg_outerMD_lowerHit: " << simhit_particle_innerSg_outerMD_lowerHit <<  std::endl;
                    // std::cout <<  " simhit_particle_innerSg_outerMD_upperHit: " << simhit_particle_innerSg_outerMD_upperHit <<  std::endl;
                    // std::cout <<  " simhit_particle_outerSg_innerMD_lowerHit: " << simhit_particle_outerSg_innerMD_lowerHit <<  std::endl;
                    // std::cout <<  " simhit_particle_outerSg_innerMD_upperHit: " << simhit_particle_outerSg_innerMD_upperHit <<  std::endl;
                    // std::cout <<  " simhit_particle_outerSg_outerMD_lowerHit: " << simhit_particle_outerSg_outerMD_lowerHit <<  std::endl;
                    // std::cout <<  " simhit_particle_outerSg_outerMD_upperHit: " << simhit_particle_outerSg_outerMD_upperHit <<  std::endl;

                    // std::cout <<  " ==============simhit_simTrkIdx============" << std::endl;
                    // std::cout <<  " simhit_simTrkIdx_innerSg_innerMD_lowerHit: " << simhit_simTrkIdx_innerSg_innerMD_lowerHit <<  std::endl;
                    // std::cout <<  " simhit_simTrkIdx_innerSg_innerMD_upperHit: " << simhit_simTrkIdx_innerSg_innerMD_upperHit <<  std::endl;
                    // std::cout <<  " simhit_simTrkIdx_innerSg_outerMD_lowerHit: " << simhit_simTrkIdx_innerSg_outerMD_lowerHit <<  std::endl;
                    // std::cout <<  " simhit_simTrkIdx_innerSg_outerMD_upperHit: " << simhit_simTrkIdx_innerSg_outerMD_upperHit <<  std::endl;
                    // std::cout <<  " simhit_simTrkIdx_outerSg_innerMD_lowerHit: " << simhit_simTrkIdx_outerSg_innerMD_lowerHit <<  std::endl;
                    // std::cout <<  " simhit_simTrkIdx_outerSg_innerMD_upperHit: " << simhit_simTrkIdx_outerSg_innerMD_upperHit <<  std::endl;
                    // std::cout <<  " simhit_simTrkIdx_outerSg_outerMD_lowerHit: " << simhit_simTrkIdx_outerSg_outerMD_lowerHit <<  std::endl;
                    // std::cout <<  " simhit_simTrkIdx_outerSg_outerMD_upperHit: " << simhit_simTrkIdx_outerSg_outerMD_upperHit <<  std::endl;

                    // std::cout << std::endl;
                    // std::cout <<  "dbeta failed";
                    // std::cout <<  " : ";
                    // std::cout << std::setw(4) << simhit_particle_innerSg_innerMD_lowerHit <<  " : ";
                    // std::cout << std::setw(4) << simhit_particle_innerSg_innerMD_upperHit <<  " : ";
                    // std::cout << std::setw(4) << simhit_particle_innerSg_outerMD_lowerHit <<  " : ";
                    // std::cout << std::setw(4) << simhit_particle_innerSg_outerMD_upperHit <<  " : ";
                    // std::cout << std::setw(4) << simhit_particle_outerSg_innerMD_lowerHit <<  " : ";
                    // std::cout << std::setw(4) << simhit_particle_outerSg_innerMD_upperHit <<  " : ";
                    // std::cout << std::setw(4) << simhit_particle_outerSg_outerMD_lowerHit <<  " : ";
                    // std::cout << std::setw(4) << simhit_particle_outerSg_outerMD_upperHit;
                    // std::cout <<  " : ";
                    // std::cout << std::setw(4) << simhit_simTrkIdx_innerSg_innerMD_lowerHit <<  " : ";
                    // std::cout << std::setw(4) << simhit_simTrkIdx_innerSg_innerMD_upperHit <<  " : ";
                    // std::cout << std::setw(4) << simhit_simTrkIdx_innerSg_outerMD_lowerHit <<  " : ";
                    // std::cout << std::setw(4) << simhit_simTrkIdx_innerSg_outerMD_upperHit <<  " : ";
                    // std::cout << std::setw(4) << simhit_simTrkIdx_outerSg_innerMD_lowerHit <<  " : ";
                    // std::cout << std::setw(4) << simhit_simTrkIdx_outerSg_innerMD_upperHit <<  " : ";
                    // std::cout << std::setw(4) << simhit_simTrkIdx_outerSg_outerMD_lowerHit <<  " : ";
                    // std::cout << std::setw(4) << simhit_simTrkIdx_outerSg_outerMD_upperHit;
                    // std::cout <<  " : ";
                    // std::cout << std::setw(8) << (simhit_simTrkIdx_innerSg_innerMD_lowerHit ? trk.sim_pt()[simhit_simTrkIdx_innerSg_innerMD_lowerHit] : -99) << " : ";
                    // std::cout << std::setw(8) << (simhit_simTrkIdx_innerSg_innerMD_upperHit ? trk.sim_pt()[simhit_simTrkIdx_innerSg_innerMD_upperHit] : -99) << " : ";
                    // std::cout << std::setw(8) << (simhit_simTrkIdx_innerSg_outerMD_lowerHit ? trk.sim_pt()[simhit_simTrkIdx_innerSg_outerMD_lowerHit] : -99) << " : ";
                    // std::cout << std::setw(8) << (simhit_simTrkIdx_innerSg_outerMD_upperHit ? trk.sim_pt()[simhit_simTrkIdx_innerSg_outerMD_upperHit] : -99) << " : ";
                    // std::cout << std::setw(8) << (simhit_simTrkIdx_outerSg_innerMD_lowerHit ? trk.sim_pt()[simhit_simTrkIdx_outerSg_innerMD_lowerHit] : -99) << " : ";
                    // std::cout << std::setw(8) << (simhit_simTrkIdx_outerSg_innerMD_upperHit ? trk.sim_pt()[simhit_simTrkIdx_outerSg_innerMD_upperHit] : -99) << " : ";
                    // std::cout << std::setw(8) << (simhit_simTrkIdx_outerSg_outerMD_lowerHit ? trk.sim_pt()[simhit_simTrkIdx_outerSg_outerMD_lowerHit] : -99) << " : ";
                    // std::cout << std::setw(8) << (simhit_simTrkIdx_outerSg_outerMD_upperHit ? trk.sim_pt()[simhit_simTrkIdx_outerSg_outerMD_upperHit] : -99);
                    // std::cout <<  " : ";
                    // std::cout << std::setw(4) << (simhit_simTrkIdx_innerSg_innerMD_lowerHit ? trk.sim_pdgId()[simhit_simTrkIdx_innerSg_innerMD_lowerHit] : -99) << " : ";
                    // std::cout << std::setw(4) << (simhit_simTrkIdx_innerSg_innerMD_upperHit ? trk.sim_pdgId()[simhit_simTrkIdx_innerSg_innerMD_upperHit] : -99) << " : ";
                    // std::cout << std::setw(4) << (simhit_simTrkIdx_innerSg_outerMD_lowerHit ? trk.sim_pdgId()[simhit_simTrkIdx_innerSg_outerMD_lowerHit] : -99) << " : ";
                    // std::cout << std::setw(4) << (simhit_simTrkIdx_innerSg_outerMD_upperHit ? trk.sim_pdgId()[simhit_simTrkIdx_innerSg_outerMD_upperHit] : -99) << " : ";
                    // std::cout << std::setw(4) << (simhit_simTrkIdx_outerSg_innerMD_lowerHit ? trk.sim_pdgId()[simhit_simTrkIdx_outerSg_innerMD_lowerHit] : -99) << " : ";
                    // std::cout << std::setw(4) << (simhit_simTrkIdx_outerSg_innerMD_upperHit ? trk.sim_pdgId()[simhit_simTrkIdx_outerSg_innerMD_upperHit] : -99) << " : ";
                    // std::cout << std::setw(4) << (simhit_simTrkIdx_outerSg_outerMD_lowerHit ? trk.sim_pdgId()[simhit_simTrkIdx_outerSg_outerMD_lowerHit] : -99) << " : ";
                    // std::cout << std::setw(4) << (simhit_simTrkIdx_outerSg_outerMD_upperHit ? trk.sim_pdgId()[simhit_simTrkIdx_outerSg_outerMD_upperHit] : -99);
                    // std::cout << std::endl;


                }

                // ana.tx->setBranch<float>("sinAlphaMax", tl->getRecoVar("sinAlphaMax"));
                // ana.tx->setBranch<float>("betaIn", tl->getRecoVar("betaIn"));
                // ana.tx->setBranch<float>("betaInRHmax", tl->getRecoVar("betaInRHmax"));
                // ana.tx->setBranch<float>("betaInRHmin", tl->getRecoVar("betaInRHmin"));
                // ana.tx->setBranch<float>("betaOut", tl->getRecoVar("betaOut"));
                // ana.tx->setBranch<float>("betaOutRHmax", tl->getRecoVar("betaOutRHmax"));
                // ana.tx->setBranch<float>("betaOutRHmin", tl->getRecoVar("betaOutRHmin"));
                // ana.tx->setBranch<float>("dBeta", tl->getRecoVar("dBeta"));
                // ana.tx->setBranch<float>("dBetaCut2", tl->getRecoVar("dBetaCut2"));
                // ana.tx->setBranch<float>("dBetaLum2", tl->getRecoVar("dBetaLum2"));
                // ana.tx->setBranch<float>("dBetaMuls", tl->getRecoVar("dBetaMuls"));
                // ana.tx->setBranch<float>("dBetaRIn2", tl->getRecoVar("dBetaRIn2"));
                // ana.tx->setBranch<float>("dBetaROut2", tl->getRecoVar("dBetaROut2"));
                // ana.tx->setBranch<float>("dBetaRes", tl->getRecoVar("dBetaRes"));
                // ana.tx->setBranch<float>("deltaZLum", tl->getRecoVar("deltaZLum"));
                // ana.tx->setBranch<float>("dr", tl->getRecoVar("dr"));
                // ana.tx->setBranch<float>("dzDrtScale", tl->getRecoVar("dzDrtScale"));
                // ana.tx->setBranch<float>("innerSgInnerMdDetId", tl->getRecoVar("innerSgInnerMdDetId"));
                // ana.tx->setBranch<float>("innerSgOuterMdDetId", tl->getRecoVar("innerSgOuterMdDetId"));
                // ana.tx->setBranch<float>("k2Rinv1GeVf", tl->getRecoVar("k2Rinv1GeVf"));
                // ana.tx->setBranch<float>("kRinv1GeVf", tl->getRecoVar("kRinv1GeVf"));
                // ana.tx->setBranch<float>("outerSgInnerMdDetId", tl->getRecoVar("outerSgInnerMdDetId"));
                // ana.tx->setBranch<float>("outerSgOuterMdDetId", tl->getRecoVar("outerSgOuterMdDetId"));
                // ana.tx->setBranch<float>("pixelPSZpitch", tl->getRecoVar("pixelPSZpitch"));
                // ana.tx->setBranch<float>("ptCut", tl->getRecoVar("ptCut"));
                // ana.tx->setBranch<float>("pt_betaIn", tl->getRecoVar("pt_betaIn"));
                // ana.tx->setBranch<float>("pt_betaOut", tl->getRecoVar("pt_betaOut"));
                // ana.tx->setBranch<float>("rtIn", tl->getRecoVar("rtIn"));
                // ana.tx->setBranch<float>("rtOut", tl->getRecoVar("rtOut"));
                // ana.tx->setBranch<float>("rtOut_o_rtIn", tl->getRecoVar("rtOut_o_rtIn"));
                // ana.tx->setBranch<float>("sdIn_d", tl->getRecoVar("sdIn_d"));
                // ana.tx->setBranch<float>("sdOut_d", tl->getRecoVar("sdOut_d"));
                // ana.tx->setBranch<float>("sdlSlope", tl->getRecoVar("sdlSlope"));
                // ana.tx->setBranch<float>("strip2SZpitch", tl->getRecoVar("strip2SZpitch"));
                // ana.tx->setBranch<float>("zGeom", tl->getRecoVar("zGeom"));
                // ana.tx->setBranch<float>("zIn", tl->getRecoVar("zIn"));
                // ana.tx->setBranch<float>("zLo", tl->getRecoVar("zLo"));
                // ana.tx->setBranch<float>("zOut", tl->getRecoVar("zOut"));
                // ana.tx->setBranch<float>("betacormode", tl->getRecoVar("betacormode"));
                // ana.tx->setBranch<float>("sdIn_alpha", tl->getRecoVar("sdIn_alpha"));
                // ana.tx->setBranch<float>("sdOut_alphaOut", tl->getRecoVar("sdOut_alphaOut"));
                // ana.tx->setBranch<float>("rawBetaInCorrection", tl->getRecoVar("rawBetaInCorrection"));
                // ana.tx->setBranch<float>("rawBetaOutCorrection", tl->getRecoVar("rawBetaOutCorrection"));
                // ana.tx->setBranch<float>("rawBetaIn", tl->getRecoVar("rawBetaIn"));
                // ana.tx->setBranch<float>("rawBetaOut", tl->getRecoVar("rawBetaOut"));

                // ana.tx->fill();

            }

            // betaOut
            //------------------------
            if (passbit & (1 << SDL::Tracklet::TrackletSelection::dAlphaIn))
            {

                const float betaOut = tl->getBetaOut();
                const float betaOutCut = fabs(betaOut) - tl->getBetaOutCut();
                const float betaOutCutThresh = tl->getBetaOutCut();

                tl_betaOut.push_back(betaOut);
                tl_betaOut_dcut.push_back(betaOutCut);
                tl_betaOut_cutthresh.push_back(betaOutCutThresh);

                tl_betaOut_by_layer[layer_idx].push_back(betaOut);
                tl_betaOut_dcut_by_layer[layer_idx].push_back(betaOutCut);
                tl_betaOut_cutthresh_by_layer[layer_idx].push_back(betaOutCutThresh);
            }

            // betaIn
            //------------------------
            if (passbit & (1 << SDL::Tracklet::TrackletSelection::slope))
            {

                const float betaIn = tl->getBetaIn();
                const float betaInCut = fabs(betaIn) - tl->getBetaInCut();
                const float betaInCutThresh = tl->getBetaInCut();

                tl_betaIn.push_back(betaIn);
                tl_betaIn_dcut.push_back(betaInCut);
                tl_betaIn_cutthresh.push_back(betaInCutThresh);

                tl_betaIn_by_layer[layer_idx].push_back(betaIn);
                tl_betaIn_dcut_by_layer[layer_idx].push_back(betaInCut);
                tl_betaIn_cutthresh_by_layer[layer_idx].push_back(betaInCutThresh);
            }

        }

    }

}
