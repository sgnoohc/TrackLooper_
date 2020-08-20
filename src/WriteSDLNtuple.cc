#include "WriteSDLNtuple.h"

//____________________________________________________________________________________________
WriteSDLNtuple::WriteSDLNtuple(const char* studyName)
{
    studyname = studyName;
}

//____________________________________________________________________________________________
void WriteSDLNtuple::bookStudy()
{
    createHitsSimHitsSimTracksBranches();
    createMiniDoubletBranches();
    createSegmentBranches();
    createTripletBranches();
    createTrackletBranches();
    createTrackCandidateBranches();
}

//____________________________________________________________________________________________
void WriteSDLNtuple::createHitsSimHitsSimTracksBranches()
{
    // Reco hits
    ana.tx->createBranch<vector<float>>("ph2_x");
    ana.tx->createBranch<vector<float>>("ph2_y");
    ana.tx->createBranch<vector<float>>("ph2_z");
    ana.tx->createBranch<vector<unsigned int>>("ph2_detId");
    ana.tx->createBranch<vector<vector<int>>>("ph2_simHitIdx");
    ana.tx->createBranch<vector<unsigned int>>("ph2_simType");
    ana.tx->createBranch<vector<int>>("ph2_anchorLayer");

    // Sim hits
    ana.tx->createBranch<vector<float>>("simhit_x");
    ana.tx->createBranch<vector<float>>("simhit_y");
    ana.tx->createBranch<vector<float>>("simhit_z");
    ana.tx->createBranch<vector<unsigned int>>("simhit_detId");
    ana.tx->createBranch<vector<unsigned int>>("simhit_partnerDetId");
    ana.tx->createBranch<vector<unsigned int>>("simhit_subdet");
    ana.tx->createBranch<vector<int>>("simhit_particle");
    ana.tx->createBranch<vector<vector<int>>>("simhit_hitIdx");
    ana.tx->createBranch<vector<int>>("simhit_simTrkIdx");

    // Sim tracks
    ana.tx->createBranch<vector<float>>("sim_pt");
    ana.tx->createBranch<vector<float>>("sim_eta");
    ana.tx->createBranch<vector<float>>("sim_phi");
    ana.tx->createBranch<vector<float>>("sim_pca_dxy");
    ana.tx->createBranch<vector<float>>("sim_pca_dz");
    ana.tx->createBranch<vector<int>>("sim_q");
    ana.tx->createBranch<vector<int>>("sim_event");
    ana.tx->createBranch<vector<int>>("sim_pdgId");
    ana.tx->createBranch<vector<int>>("sim_bunchCrossing");
    ana.tx->createBranch<vector<vector<int>>>("sim_simHitIdx");
    ana.tx->createBranch<vector<vector<int>>>("sim_simHitLayer");
    ana.tx->createBranch<vector<vector<int>>>("sim_simHitBoth");
    ana.tx->createBranch<vector<vector<float>>>("sim_simHitDrFracWithHelix");
    ana.tx->createBranch<vector<vector<float>>>("sim_simHitDistXyWithHelix");

    // Sim vertex
    ana.tx->createBranch<vector<float>>("simvtx_x");
    ana.tx->createBranch<vector<float>>("simvtx_y");
    ana.tx->createBranch<vector<float>>("simvtx_z");
}

//____________________________________________________________________________________________
void WriteSDLNtuple::createMiniDoubletBranches()
{
    // Tracklets
    ana.tx->createBranch<vector<vector<int>>>("md_hitIdx");
    ana.tx->createBranch<vector<vector<int>>>("md_simTrkIdx");
    ana.tx->createBranch<vector<vector<int>>>("md_layer");
    // ana.tx->createBranch<vector<int>>("md_simHitIdx");

    // Kinematic quantity
    ana.tx->createBranch<vector<float>>("md_pt");
    ana.tx->createBranch<vector<float>>("md_eta");
    ana.tx->createBranch<vector<float>>("md_phi");
    ana.tx->createBranch<vector<float>>("md_sim_pt");
    ana.tx->createBranch<vector<float>>("md_sim_eta");
    ana.tx->createBranch<vector<float>>("md_sim_phi");

    // Sim track to minidoublet matching
    ana.tx->createBranch<vector<vector<int>>>("sim_mdIdx");
    ana.tx->createBranch<vector<vector<int>>>("sim_mdIdx_isMTVmatch");

    // reco hit to minidoublet matching
    ana.tx->createBranch<vector<vector<int>>>("ph2_mdIdx");
}

//____________________________________________________________________________________________
void WriteSDLNtuple::createSegmentBranches()
{
    // Tracklets
    ana.tx->createBranch<vector<vector<int>>>("sg_hitIdx");
    ana.tx->createBranch<vector<vector<int>>>("sg_simTrkIdx");
    ana.tx->createBranch<vector<vector<int>>>("sg_simTrkIdx_anchorMatching");
    ana.tx->createBranch<vector<vector<int>>>("sg_layer");
    // ana.tx->createBranch<vector<int>>("sg_simHitIdx");

    // Kinematic quantity
    ana.tx->createBranch<vector<float>>("sg_pt");
    ana.tx->createBranch<vector<float>>("sg_eta");
    ana.tx->createBranch<vector<float>>("sg_phi");
    ana.tx->createBranch<vector<float>>("sg_sim_pt");
    ana.tx->createBranch<vector<float>>("sg_sim_eta");
    ana.tx->createBranch<vector<float>>("sg_sim_phi");

    // Sim track to Tracklets matching
    ana.tx->createBranch<vector<vector<int>>>("sim_sgIdx");
    ana.tx->createBranch<vector<vector<int>>>("sim_sgIdx_isMTVmatch");
}

//____________________________________________________________________________________________
void WriteSDLNtuple::createTripletBranches()
{
    // Tracklets
    ana.tx->createBranch<vector<vector<int>>>("tp_hitIdx");
    ana.tx->createBranch<vector<vector<int>>>("tp_simTrkIdx");
    ana.tx->createBranch<vector<vector<int>>>("tp_layer");
    // ana.tx->createBranch<vector<int>>("tp_simHitIdx");

    // Kinematic quantity
    ana.tx->createBranch<vector<float>>("tp_pt");
    ana.tx->createBranch<vector<float>>("tp_eta");
    ana.tx->createBranch<vector<float>>("tp_phi");
    ana.tx->createBranch<vector<float>>("tp_sim_pt");
    ana.tx->createBranch<vector<float>>("tp_sim_eta");
    ana.tx->createBranch<vector<float>>("tp_sim_phi");

    // Sim track to Tracklets matching
    ana.tx->createBranch<vector<vector<int>>>("sim_tpIdx");
    ana.tx->createBranch<vector<vector<int>>>("sim_tpIdx_isMTVmatch");
}

//____________________________________________________________________________________________
void WriteSDLNtuple::createTrackletBranches()
{
    // Tracklets
    ana.tx->createBranch<vector<vector<int>>>("tl_hitIdx");
    ana.tx->createBranch<vector<vector<int>>>("tl_simTrkIdx");
    ana.tx->createBranch<vector<vector<int>>>("tl_layer");
    // ana.tx->createBranch<vector<int>>("tl_simHitIdx");

    // Kinematic quantity
    ana.tx->createBranch<vector<float>>("tl_pt");
    ana.tx->createBranch<vector<float>>("tl_eta");
    ana.tx->createBranch<vector<float>>("tl_phi");
    ana.tx->createBranch<vector<float>>("tl_sim_pt");
    ana.tx->createBranch<vector<float>>("tl_sim_eta");
    ana.tx->createBranch<vector<float>>("tl_sim_phi");

    // Sim track to Tracklets matching
    ana.tx->createBranch<vector<vector<int>>>("sim_tlIdx");
    ana.tx->createBranch<vector<vector<int>>>("sim_tlIdx_isMTVmatch");
}

//____________________________________________________________________________________________
void WriteSDLNtuple::createTrackCandidateBranches()
{
    // Tracklets
    ana.tx->createBranch<vector<vector<int>>>("tc_hitIdx");
    ana.tx->createBranch<vector<vector<int>>>("tc_simTrkIdx");
    ana.tx->createBranch<vector<vector<int>>>("tc_layer");
    // ana.tx->createBranch<vector<int>>("tc_simHitIdx");

    // Kinematic quantity
    ana.tx->createBranch<vector<float>>("tc_pt");
    ana.tx->createBranch<vector<float>>("tc_eta");
    ana.tx->createBranch<vector<float>>("tc_phi");
    ana.tx->createBranch<vector<float>>("tc_sim_pt");
    ana.tx->createBranch<vector<float>>("tc_sim_eta");
    ana.tx->createBranch<vector<float>>("tc_sim_phi");

    // Sim track to Tracklets matching
    ana.tx->createBranch<vector<vector<int>>>("sim_tcIdx");
    ana.tx->createBranch<vector<vector<int>>>("sim_tcIdx_isMTVmatch");
}

//____________________________________________________________________________________________
void WriteSDLNtuple::doStudy(SDL::Event& event, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents)
{
    setHitsSimHitsSimTracksBranches();
    setMiniDoubletBranches(event);
    setSegmentBranches(event);
    setTripletBranches(event);
    setTrackletBranches(event);
    setTrackCandidateBranches(event);
    ana.tx->fill();
    ana.tx->clear();
}

//____________________________________________________________________________________________
void WriteSDLNtuple::setHitsSimHitsSimTracksBranches()
{

    // Reco hits
    ana.tx->setBranch<vector<float>>("ph2_x", trk.ph2_x());
    ana.tx->setBranch<vector<float>>("ph2_y", trk.ph2_y());
    ana.tx->setBranch<vector<float>>("ph2_z", trk.ph2_z());
    ana.tx->setBranch<vector<unsigned int>>("ph2_detId", trk.ph2_detId());
    ana.tx->setBranch<vector<vector<int>>>("ph2_simHitIdx", trk.ph2_simHitIdx());
    vector<unsigned int> ph2_simType(trk.ph2_simType().begin(), trk.ph2_simType().end());
    ana.tx->setBranch<vector<unsigned int>>("ph2_simType", ph2_simType);
    vector<int> anchorLayer;
    for (unsigned int ihit = 0; ihit < trk.ph2_detId().size(); ++ihit)
    {
        int thisHitanchorLayer = 0;
        SDL::Module module(trk.ph2_detId()[ihit]);
        if (module.moduleType() == SDL::Module::PS and module.moduleLayerType() == SDL::Module::Pixel)
            thisHitanchorLayer = 1;
        if (module.moduleType() == SDL::Module::TwoS and module.isLower())
            thisHitanchorLayer = 1;
        anchorLayer.push_back(thisHitanchorLayer);
    }
    ana.tx->setBranch<vector<int>>("ph2_anchorLayer", anchorLayer);

    // Sim hits
    ana.tx->setBranch<vector<float>>("simhit_x", trk.simhit_x());
    ana.tx->setBranch<vector<float>>("simhit_y", trk.simhit_y());
    ana.tx->setBranch<vector<float>>("simhit_z", trk.simhit_z());
    ana.tx->setBranch<vector<unsigned int>>("simhit_detId", trk.simhit_detId());
    vector<unsigned int> simhit_partnerDetId;
    for (unsigned int imod = 0; imod < trk.simhit_detId().size(); imod++)
    {
        if (trk.simhit_subdet()[imod] == 4 or trk.simhit_subdet()[imod] == 5)
            simhit_partnerDetId.push_back(SDL::Module(trk.simhit_detId()[imod]).partnerDetId());
        else
            simhit_partnerDetId.push_back(-1);
    }
    ana.tx->setBranch<vector<unsigned int>>("simhit_partnerDetId", simhit_partnerDetId);
    vector<unsigned int> simhit_subdet(trk.simhit_subdet().begin(), trk.simhit_subdet().end());
    ana.tx->setBranch<vector<unsigned int>>("simhit_subdet", simhit_subdet);
    ana.tx->setBranch<vector<int>>("simhit_particle", trk.simhit_particle());
    ana.tx->setBranch<vector<vector<int>>>("simhit_hitIdx", trk.simhit_hitIdx());
    ana.tx->setBranch<vector<int>>("simhit_simTrkIdx", trk.simhit_simTrkIdx());

    // Sim tracks
    ana.tx->setBranch<vector<float>>("sim_pt", trk.sim_pt());
    ana.tx->setBranch<vector<float>>("sim_eta", trk.sim_eta());
    ana.tx->setBranch<vector<float>>("sim_phi", trk.sim_phi());
    ana.tx->setBranch<vector<float>>("sim_pca_dxy", trk.sim_pca_dxy());
    ana.tx->setBranch<vector<float>>("sim_pca_dz", trk.sim_pca_dz());
    ana.tx->setBranch<vector<int>>("sim_q", trk.sim_q());
    ana.tx->setBranch<vector<int>>("sim_event", trk.sim_event());
    ana.tx->setBranch<vector<int>>("sim_pdgId", trk.sim_pdgId());
    ana.tx->setBranch<vector<int>>("sim_bunchCrossing", trk.sim_bunchCrossing());
    ana.tx->setBranch<vector<vector<int>>>("sim_simHitIdx", trk.sim_simHitIdx());

    // simvtx
    ana.tx->setBranch<vector<float>>("simvtx_x", trk.simvtx_x());
    ana.tx->setBranch<vector<float>>("simvtx_y", trk.simvtx_y());
    ana.tx->setBranch<vector<float>>("simvtx_z", trk.simvtx_z());

    //--------------------
    // Extra calculations 
    //--------------------

    // layer index with simhits
    for (auto&& [isimtrk, sim_simHitIdx] : iter::enumerate(trk.sim_simHitIdx()))
    {

        std::vector<int> sim_simHitLayer;
        std::vector<int> sim_simHitBoth; // Both side in the pt module
        std::vector<float> sim_simHitDrFracWithHelix;
        std::vector<float> sim_simHitDistXyWithHelix;
        for (auto& isimhitidx : sim_simHitIdx)
        {
            int subdet = trk.simhit_subdet()[isimhitidx];
            int islower = trk.simhit_isLower()[isimhitidx];
            int sign = islower == 1 ? -1 : 1;
            if (subdet != 4 and subdet != 5)
            {
                sim_simHitLayer.push_back(0);
                sim_simHitBoth.push_back(0);
            }
            else
            {
                sim_simHitLayer.push_back( sign * (trk.simhit_layer()[isimhitidx] + 6 * (subdet == 4)) );

                bool bothside = false;
                for (auto& jsimhitidx : sim_simHitIdx)
                {
                    if (SDL::Module(trk.simhit_detId()[isimhitidx]).partnerDetId() == trk.simhit_detId()[jsimhitidx])
                    {
                        bothside = true;
                    }
                }
                
                if (bothside)
                {
                    sim_simHitBoth.push_back(1);
                }
                else
                {
                    sim_simHitBoth.push_back(0);
                }
            }

            sim_simHitDrFracWithHelix.push_back(drfracSimHitConsistentWithHelix(isimtrk, isimhitidx));
            sim_simHitDistXyWithHelix.push_back(distxySimHitConsistentWithHelix(isimtrk, isimhitidx));

        }

        ana.tx->pushbackToBranch<vector<int>>("sim_simHitLayer", sim_simHitLayer);
        ana.tx->pushbackToBranch<vector<int>>("sim_simHitBoth", sim_simHitBoth);
        ana.tx->pushbackToBranch<vector<float>>("sim_simHitDrFracWithHelix", sim_simHitDrFracWithHelix);
        ana.tx->pushbackToBranch<vector<float>>("sim_simHitDistXyWithHelix", sim_simHitDistXyWithHelix);

    }

}

//____________________________________________________________________________________________
void WriteSDLNtuple::setMiniDoubletBranches(SDL::Event& event)
{

    // get layer ptrs
    const std::vector<SDL::Layer*> layerPtrs = event.getLayerPtrs();

    // sim track to minidoublet matching
    std::vector<vector<int>> sim_mdIdx(trk.sim_pt().size());
    std::vector<vector<int>> sim_mdIdx_isMTVmatch(trk.sim_pt().size());

    // reco hit to minidoublet matching
    std::vector<vector<int>> ph2_mdIdx(trk.ph2_detId().size());

    // Loop over layers and access minidoublets
    for (auto& layerPtr : layerPtrs)
    {

        // Tracklet ptrs
        const std::vector<SDL::MiniDoublet*>& minidoubletPtrs = layerPtr->getMiniDoubletPtrs();

        // Loop over minidoublet ptrs
        for (auto& minidoubletPtr : minidoubletPtrs)
        {

            // hit idx
            std::vector<int> hit_idx;
            hit_idx.push_back(minidoubletPtr->lowerHitPtr()->idx());
            hit_idx.push_back(minidoubletPtr->upperHitPtr()->idx());
            ana.tx->pushbackToBranch<vector<int>>("md_hitIdx", hit_idx);

            // sim track matched index
            std::vector<int> matched_sim_trk_idxs = matchedSimTrkIdxs(minidoubletPtr);
            ana.tx->pushbackToBranch<vector<int>>("md_simTrkIdx", matched_sim_trk_idxs);

            // tracklet layers
            std::vector<int> layers;
            layers.push_back(minidoubletPtr->lowerHitPtr()->getModule().layer() + 6 * (minidoubletPtr->lowerHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            layers.push_back(minidoubletPtr->upperHitPtr()->getModule().layer() + 6 * (minidoubletPtr->upperHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            ana.tx->pushbackToBranch<vector<int>>("md_layer", layers);

            // Sim track to mini-doublet matching
            int imd = ana.tx->getBranch<vector<vector<int>>>("md_hitIdx").size() - 1;

            // For matched sim track
            for (auto& matched_sim_trk_idx : matched_sim_trk_idxs)
            {
                sim_mdIdx[matched_sim_trk_idx].push_back(imd);
                std::vector<unsigned int> hit_idx_(hit_idx.begin(), hit_idx.end());
                if (isMTVMatch(matched_sim_trk_idx, hit_idx_))
                    sim_mdIdx_isMTVmatch[matched_sim_trk_idx].push_back(imd);
            }

            // Reco hit to mini-doublet matching
            // For matched sim track
            for (auto& ihit : hit_idx)
            {
                ph2_mdIdx[ihit].push_back(imd);
            }

            SDL::Hit hitA(trk.ph2_x()[hit_idx[0]], trk.ph2_y()[hit_idx[0]], trk.ph2_z()[hit_idx[0]]);
            SDL::Hit hitB(trk.ph2_x()[hit_idx[1]], trk.ph2_y()[hit_idx[1]], trk.ph2_z()[hit_idx[1]]);
            SDL::Hit hitC(0, 0, 0);
            SDL::Hit center = SDL::MathUtil::getCenterFromThreePoints(hitA, hitB, hitC);
            float radius = center.rt();
            float pt = SDL::MathUtil::ptEstimateFromRadius(radius);
            float eta = hitB.eta();
            float phi = hitA.phi();

            float maxsimpt = -999;
            float maxsimeta = 0;
            float maxsimphi = 0;
            for (auto& simtrkidx : matched_sim_trk_idxs)
            {
                float tmpsimpt = trk.sim_pt()[simtrkidx];
                float tmpsimeta = trk.sim_eta()[simtrkidx];
                float tmpsimphi = trk.sim_phi()[simtrkidx];
                if (maxsimpt < tmpsimpt)
                {
                    maxsimpt = tmpsimpt;
                    maxsimeta = tmpsimeta;
                    maxsimphi = tmpsimphi;
                }
            }

            // Kinematic quantity
            ana.tx->pushbackToBranch<float>("md_pt", pt);
            ana.tx->pushbackToBranch<float>("md_eta", eta);
            ana.tx->pushbackToBranch<float>("md_phi", phi);
            ana.tx->pushbackToBranch<float>("md_sim_pt", maxsimpt);
            ana.tx->pushbackToBranch<float>("md_sim_eta", maxsimeta);
            ana.tx->pushbackToBranch<float>("md_sim_phi", maxsimphi);

        }


    }

    ana.tx->setBranch<vector<vector<int>>>("sim_mdIdx", sim_mdIdx);
    ana.tx->setBranch<vector<vector<int>>>("sim_mdIdx_isMTVmatch", sim_mdIdx_isMTVmatch);
    ana.tx->setBranch<vector<vector<int>>>("ph2_mdIdx", ph2_mdIdx);

}

//____________________________________________________________________________________________
void WriteSDLNtuple::setSegmentBranches(SDL::Event& event)
{

    // get layer ptrs
    const std::vector<SDL::Layer*> layerPtrs = event.getLayerPtrs();

    // sim track to segment matching
    std::vector<vector<int>> sim_sgIdx(trk.sim_pt().size());
    std::vector<vector<int>> sim_sgIdx_isMTVmatch(trk.sim_pt().size());

    // Loop over layers and access segments
    for (auto& layerPtr : layerPtrs)
    {

        // Tracklet ptrs
        const std::vector<SDL::Segment*>& segmentPtrs = layerPtr->getSegmentPtrs();

        // Loop over segment ptrs
        for (auto& segmentPtr : segmentPtrs)
        {

            // hit idx
            std::vector<int> hit_idx;
            hit_idx.push_back(segmentPtr->innerMiniDoubletPtr()->lowerHitPtr()->idx());
            hit_idx.push_back(segmentPtr->innerMiniDoubletPtr()->upperHitPtr()->idx());
            hit_idx.push_back(segmentPtr->outerMiniDoubletPtr()->lowerHitPtr()->idx());
            hit_idx.push_back(segmentPtr->outerMiniDoubletPtr()->upperHitPtr()->idx());
            ana.tx->pushbackToBranch<vector<int>>("sg_hitIdx", hit_idx);

            // sim track matched index
            std::vector<int> matched_sim_trk_idxs = matchedSimTrkIdxs(segmentPtr);
            ana.tx->pushbackToBranch<vector<int>>("sg_simTrkIdx", matched_sim_trk_idxs);

            std::vector<int> matched_sim_trk_idxs_anchorMatching = matchedSimTrkIdxs(segmentPtr, true);
            ana.tx->pushbackToBranch<vector<int>>("sg_simTrkIdx_anchorMatching", matched_sim_trk_idxs_anchorMatching);

            // tracklet layers
            std::vector<int> layers;
            layers.push_back(segmentPtr->innerMiniDoubletPtr()->lowerHitPtr()->getModule().layer() + 6 * (segmentPtr->innerMiniDoubletPtr()->lowerHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            layers.push_back(segmentPtr->innerMiniDoubletPtr()->upperHitPtr()->getModule().layer() + 6 * (segmentPtr->innerMiniDoubletPtr()->upperHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            layers.push_back(segmentPtr->outerMiniDoubletPtr()->lowerHitPtr()->getModule().layer() + 6 * (segmentPtr->outerMiniDoubletPtr()->lowerHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            layers.push_back(segmentPtr->outerMiniDoubletPtr()->upperHitPtr()->getModule().layer() + 6 * (segmentPtr->outerMiniDoubletPtr()->upperHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            ana.tx->pushbackToBranch<vector<int>>("sg_layer", layers);

            // Sim track to Tracklet matching
            int isg = ana.tx->getBranch<vector<vector<int>>>("sg_hitIdx").size() - 1;

            // For matched sim track
            for (auto& matched_sim_trk_idx : matched_sim_trk_idxs)
            {
                sim_sgIdx[matched_sim_trk_idx].push_back(isg);
                std::vector<unsigned int> hit_idx_(hit_idx.begin(), hit_idx.end());
                if (isMTVMatch(matched_sim_trk_idx, hit_idx_))
                    sim_sgIdx_isMTVmatch[matched_sim_trk_idx].push_back(isg);
            }

            SDL::Hit hitA(trk.ph2_x()[hit_idx[0]], trk.ph2_y()[hit_idx[0]], trk.ph2_z()[hit_idx[0]]);
            SDL::Hit hitB(trk.ph2_x()[hit_idx[3]], trk.ph2_y()[hit_idx[3]], trk.ph2_z()[hit_idx[3]]);
            SDL::Hit hitC(0, 0, 0);
            SDL::Hit center = SDL::MathUtil::getCenterFromThreePoints(hitA, hitB, hitC);
            float radius = center.rt();
            float pt = SDL::MathUtil::ptEstimateFromRadius(radius);
            float eta = hitB.eta();
            float phi = hitA.phi();

            float maxsimpt = -999;
            float maxsimeta = 0;
            float maxsimphi = 0;
            for (auto& simtrkidx : matched_sim_trk_idxs)
            {
                float tmpsimpt = trk.sim_pt()[simtrkidx];
                float tmpsimeta = trk.sim_eta()[simtrkidx];
                float tmpsimphi = trk.sim_phi()[simtrkidx];
                if (maxsimpt < tmpsimpt)
                {
                    maxsimpt = tmpsimpt;
                    maxsimeta = tmpsimeta;
                    maxsimphi = tmpsimphi;
                }
            }

            // Kinematic quantity
            ana.tx->pushbackToBranch<float>("sg_pt", pt);
            ana.tx->pushbackToBranch<float>("sg_eta", eta);
            ana.tx->pushbackToBranch<float>("sg_phi", phi);
            ana.tx->pushbackToBranch<float>("sg_sim_pt", maxsimpt);
            ana.tx->pushbackToBranch<float>("sg_sim_eta", maxsimeta);
            ana.tx->pushbackToBranch<float>("sg_sim_phi", maxsimphi);

        }

    }

    ana.tx->setBranch<vector<vector<int>>>("sim_sgIdx", sim_sgIdx);
    ana.tx->setBranch<vector<vector<int>>>("sim_sgIdx_isMTVmatch", sim_sgIdx_isMTVmatch);

}

//____________________________________________________________________________________________
void WriteSDLNtuple::setTripletBranches(SDL::Event& event)
{

    // get layer ptrs
    const std::vector<SDL::Layer*> layerPtrs = event.getLayerPtrs();

    // sim track to triplet matching
    std::vector<vector<int>> sim_tpIdx(trk.sim_pt().size());
    std::vector<vector<int>> sim_tpIdx_isMTVmatch(trk.sim_pt().size());

    // Loop over layers and access triplets
    for (auto& layerPtr : layerPtrs)
    {

        // Tracklet ptrs
        const std::vector<SDL::Triplet*>& tripletPtrs = layerPtr->getTripletPtrs();

        // Loop over triplet ptrs
        for (auto& tripletPtr : tripletPtrs)
        {

            // hit idx
            std::vector<int> hit_idx;
            hit_idx.push_back(tripletPtr->innerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->idx());
            hit_idx.push_back(tripletPtr->innerSegmentPtr()->innerMiniDoubletPtr()->upperHitPtr()->idx());
            hit_idx.push_back(tripletPtr->innerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->idx());
            hit_idx.push_back(tripletPtr->innerSegmentPtr()->outerMiniDoubletPtr()->upperHitPtr()->idx());
            hit_idx.push_back(tripletPtr->outerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->idx());
            hit_idx.push_back(tripletPtr->outerSegmentPtr()->outerMiniDoubletPtr()->upperHitPtr()->idx());
            ana.tx->pushbackToBranch<vector<int>>("tp_hitIdx", hit_idx);

            // sim track matched index
            std::vector<int> matched_sim_trk_idxs = matchedSimTrkIdxs(tripletPtr);
            ana.tx->pushbackToBranch<vector<int>>("tp_simTrkIdx", matched_sim_trk_idxs);

            // tracklet layers
            std::vector<int> layers;
            layers.push_back(tripletPtr->innerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->getModule().layer() + 6 * (tripletPtr->innerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            layers.push_back(tripletPtr->innerSegmentPtr()->innerMiniDoubletPtr()->upperHitPtr()->getModule().layer() + 6 * (tripletPtr->innerSegmentPtr()->innerMiniDoubletPtr()->upperHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            layers.push_back(tripletPtr->innerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->getModule().layer() + 6 * (tripletPtr->innerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            layers.push_back(tripletPtr->innerSegmentPtr()->outerMiniDoubletPtr()->upperHitPtr()->getModule().layer() + 6 * (tripletPtr->innerSegmentPtr()->outerMiniDoubletPtr()->upperHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            layers.push_back(tripletPtr->outerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->getModule().layer() + 6 * (tripletPtr->outerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            layers.push_back(tripletPtr->outerSegmentPtr()->outerMiniDoubletPtr()->upperHitPtr()->getModule().layer() + 6 * (tripletPtr->outerSegmentPtr()->outerMiniDoubletPtr()->upperHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            ana.tx->pushbackToBranch<vector<int>>("tp_layer", layers);

            // Sim track to Tracklet matching
            int itp = ana.tx->getBranch<vector<vector<int>>>("tp_hitIdx").size() - 1;

            // For matched sim track
            for (auto& matched_sim_trk_idx : matched_sim_trk_idxs)
            {
                sim_tpIdx[matched_sim_trk_idx].push_back(itp);
                std::vector<unsigned int> hit_idx_(hit_idx.begin(), hit_idx.end());
                if (isMTVMatch(matched_sim_trk_idx, hit_idx_))
                    sim_tpIdx_isMTVmatch[matched_sim_trk_idx].push_back(itp);
            }

            SDL::Hit hitA(trk.ph2_x()[hit_idx[0]], trk.ph2_y()[hit_idx[0]], trk.ph2_z()[hit_idx[0]]);
            SDL::Hit hitB(trk.ph2_x()[hit_idx[5]], trk.ph2_y()[hit_idx[5]], trk.ph2_z()[hit_idx[5]]);
            SDL::Hit hitC(0, 0, 0);
            SDL::Hit center = SDL::MathUtil::getCenterFromThreePoints(hitA, hitB, hitC);
            float radius = center.rt();
            float pt = SDL::MathUtil::ptEstimateFromRadius(radius);
            float eta = hitB.eta();
            float phi = hitA.phi();

            float maxsimpt = -999;
            float maxsimeta = 0;
            float maxsimphi = 0;
            for (auto& simtrkidx : matched_sim_trk_idxs)
            {
                float tmpsimpt = trk.sim_pt()[simtrkidx];
                float tmpsimeta = trk.sim_eta()[simtrkidx];
                float tmpsimphi = trk.sim_phi()[simtrkidx];
                if (maxsimpt < tmpsimpt)
                {
                    maxsimpt = tmpsimpt;
                    maxsimeta = tmpsimeta;
                    maxsimphi = tmpsimphi;
                }
            }

            // Kinematic quantity
            ana.tx->pushbackToBranch<float>("tp_pt", pt);
            ana.tx->pushbackToBranch<float>("tp_eta", eta);
            ana.tx->pushbackToBranch<float>("tp_phi", phi);
            ana.tx->pushbackToBranch<float>("tp_sim_pt", maxsimpt);
            ana.tx->pushbackToBranch<float>("tp_sim_eta", maxsimeta);
            ana.tx->pushbackToBranch<float>("tp_sim_phi", maxsimphi);

        }

    }

    ana.tx->setBranch<vector<vector<int>>>("sim_tpIdx", sim_tpIdx);
    ana.tx->setBranch<vector<vector<int>>>("sim_tpIdx_isMTVmatch", sim_tpIdx_isMTVmatch);

}

//____________________________________________________________________________________________
void WriteSDLNtuple::setTrackletBranches(SDL::Event& event)
{

    // get layer ptrs
    const std::vector<SDL::Layer*> layerPtrs = event.getLayerPtrs();

    // sim track to tracklet matching
    std::vector<vector<int>> sim_tlIdx(trk.sim_pt().size());
    std::vector<vector<int>> sim_tlIdx_isMTVmatch(trk.sim_pt().size());

    // Loop over layers and access tracklets
    for (auto& layerPtr : layerPtrs)
    {

        // Tracklet ptrs
        const std::vector<SDL::Tracklet*>& trackletPtrs = layerPtr->getTrackletPtrs();

        // Loop over tracklet ptrs
        for (auto& trackletPtr : trackletPtrs)
        {

            // hit idx
            std::vector<int> hit_idx;
            hit_idx.push_back(trackletPtr->innerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->idx());
            hit_idx.push_back(trackletPtr->innerSegmentPtr()->innerMiniDoubletPtr()->upperHitPtr()->idx());
            hit_idx.push_back(trackletPtr->innerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->idx());
            hit_idx.push_back(trackletPtr->innerSegmentPtr()->outerMiniDoubletPtr()->upperHitPtr()->idx());
            hit_idx.push_back(trackletPtr->outerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->idx());
            hit_idx.push_back(trackletPtr->outerSegmentPtr()->innerMiniDoubletPtr()->upperHitPtr()->idx());
            hit_idx.push_back(trackletPtr->outerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->idx());
            hit_idx.push_back(trackletPtr->outerSegmentPtr()->outerMiniDoubletPtr()->upperHitPtr()->idx());
            ana.tx->pushbackToBranch<vector<int>>("tl_hitIdx", hit_idx);

            // sim track matched index
            std::vector<int> matched_sim_trk_idxs = matchedSimTrkIdxs(*trackletPtr);
            ana.tx->pushbackToBranch<vector<int>>("tl_simTrkIdx", matched_sim_trk_idxs);

            // tracklet layers
            std::vector<int> layers;
            layers.push_back(trackletPtr->innerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->getModule().layer() + 6 * (trackletPtr->innerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            layers.push_back(trackletPtr->innerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->getModule().layer() + 6 * (trackletPtr->innerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            layers.push_back(trackletPtr->outerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->getModule().layer() + 6 * (trackletPtr->outerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            layers.push_back(trackletPtr->outerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->getModule().layer() + 6 * (trackletPtr->outerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            ana.tx->pushbackToBranch<vector<int>>("tl_layer", layers);

            // Sim track to Tracklet matching
            int itl = ana.tx->getBranch<vector<vector<int>>>("tl_hitIdx").size() - 1;

            // For matched sim track
            for (auto& matched_sim_trk_idx : matched_sim_trk_idxs)
            {
                sim_tlIdx[matched_sim_trk_idx].push_back(itl);
                std::vector<unsigned int> hit_idx_(hit_idx.begin(), hit_idx.end());
                if (isMTVMatch(matched_sim_trk_idx, hit_idx_))
                    sim_tlIdx_isMTVmatch[matched_sim_trk_idx].push_back(itl);
            }

            SDL::Hit hitA(trk.ph2_x()[hit_idx[0]], trk.ph2_y()[hit_idx[0]], trk.ph2_z()[hit_idx[0]]);
            SDL::Hit hitB(trk.ph2_x()[hit_idx[7]], trk.ph2_y()[hit_idx[7]], trk.ph2_z()[hit_idx[7]]);
            SDL::Hit hitC(0, 0, 0);
            SDL::Hit center = SDL::MathUtil::getCenterFromThreePoints(hitA, hitB, hitC);
            float radius = center.rt();
            float pt = SDL::MathUtil::ptEstimateFromRadius(radius);
            float eta = hitB.eta();
            float phi = hitA.phi();

            float maxsimpt = -999;
            float maxsimeta = 0;
            float maxsimphi = 0;
            for (auto& simtrkidx : matched_sim_trk_idxs)
            {
                float tmpsimpt = trk.sim_pt()[simtrkidx];
                float tmpsimeta = trk.sim_eta()[simtrkidx];
                float tmpsimphi = trk.sim_phi()[simtrkidx];
                if (maxsimpt < tmpsimpt)
                {
                    maxsimpt = tmpsimpt;
                    maxsimeta = tmpsimeta;
                    maxsimphi = tmpsimphi;
                }
            }

            // Kinematic quantity
            ana.tx->pushbackToBranch<float>("tl_pt", pt);
            ana.tx->pushbackToBranch<float>("tl_eta", eta);
            ana.tx->pushbackToBranch<float>("tl_phi", phi);
            ana.tx->pushbackToBranch<float>("tl_sim_pt", maxsimpt);
            ana.tx->pushbackToBranch<float>("tl_sim_eta", maxsimeta);
            ana.tx->pushbackToBranch<float>("tl_sim_phi", maxsimphi);

        }

    }

    ana.tx->setBranch<vector<vector<int>>>("sim_tlIdx", sim_tlIdx);
    ana.tx->setBranch<vector<vector<int>>>("sim_tlIdx_isMTVmatch", sim_tlIdx_isMTVmatch);

    // // Tracklets
    // ana.tx->setBranch<vector<int>>("tl_hitIdx");
    // ana.tx->setBranch<vector<int>>("tl_simHitIdx");
    // ana.tx->setBranch<vector<int>>("tl_simTrkIdx");

}

//____________________________________________________________________________________________
void WriteSDLNtuple::setTrackCandidateBranches(SDL::Event& event)
{

    // get layer ptrs
    const std::vector<SDL::Layer*> layerPtrs = event.getLayerPtrs();

    // sim track to track candidate matching
    std::vector<vector<int>> sim_tcIdx(trk.sim_pt().size());
    std::vector<vector<int>> sim_tcIdx_isMTVmatch(trk.sim_pt().size());

    // Loop over layers and access track candidates
    for (auto& layerPtr : layerPtrs)
    {

        // Tracklet ptrs
        const std::vector<SDL::TrackCandidate*>& trackCandidatePtrs = layerPtr->getTrackCandidatePtrs();

        // Loop over trackCandidate ptrs
        for (auto& trackCandidatePtr : trackCandidatePtrs)
        {

            // hit idx
            std::vector<int> hit_idx;
            hit_idx.push_back(trackCandidatePtr->innerTrackletPtr()->innerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->idx());
            hit_idx.push_back(trackCandidatePtr->innerTrackletPtr()->innerSegmentPtr()->innerMiniDoubletPtr()->upperHitPtr()->idx());
            hit_idx.push_back(trackCandidatePtr->innerTrackletPtr()->innerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->idx());
            hit_idx.push_back(trackCandidatePtr->innerTrackletPtr()->innerSegmentPtr()->outerMiniDoubletPtr()->upperHitPtr()->idx());
            hit_idx.push_back(trackCandidatePtr->innerTrackletPtr()->outerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->idx());
            hit_idx.push_back(trackCandidatePtr->innerTrackletPtr()->outerSegmentPtr()->innerMiniDoubletPtr()->upperHitPtr()->idx());
            hit_idx.push_back(trackCandidatePtr->innerTrackletPtr()->outerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->idx());
            hit_idx.push_back(trackCandidatePtr->innerTrackletPtr()->outerSegmentPtr()->outerMiniDoubletPtr()->upperHitPtr()->idx());
            hit_idx.push_back(trackCandidatePtr->outerTrackletPtr()->outerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->idx());
            hit_idx.push_back(trackCandidatePtr->outerTrackletPtr()->outerSegmentPtr()->innerMiniDoubletPtr()->upperHitPtr()->idx());
            hit_idx.push_back(trackCandidatePtr->outerTrackletPtr()->outerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->idx());
            hit_idx.push_back(trackCandidatePtr->outerTrackletPtr()->outerSegmentPtr()->outerMiniDoubletPtr()->upperHitPtr()->idx());
            ana.tx->pushbackToBranch<vector<int>>("tc_hitIdx", hit_idx);

            // sim track matched index
            std::vector<int> matched_sim_trk_idxs = matchedSimTrkIdxs(trackCandidatePtr);
            ana.tx->pushbackToBranch<vector<int>>("tc_simTrkIdx", matched_sim_trk_idxs);

            // trackCandidate layers
            std::vector<int> layers;
            layers.push_back(trackCandidatePtr->innerTrackletPtr()->innerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->getModule().layer() + 6 * (trackCandidatePtr->innerTrackletPtr()->innerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            layers.push_back(trackCandidatePtr->innerTrackletPtr()->innerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->getModule().layer() + 6 * (trackCandidatePtr->innerTrackletPtr()->innerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            layers.push_back(trackCandidatePtr->innerTrackletPtr()->outerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->getModule().layer() + 6 * (trackCandidatePtr->innerTrackletPtr()->outerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            layers.push_back(trackCandidatePtr->innerTrackletPtr()->outerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->getModule().layer() + 6 * (trackCandidatePtr->innerTrackletPtr()->outerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            layers.push_back(trackCandidatePtr->outerTrackletPtr()->outerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->getModule().layer() + 6 * (trackCandidatePtr->outerTrackletPtr()->outerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            layers.push_back(trackCandidatePtr->outerTrackletPtr()->outerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->getModule().layer() + 6 * (trackCandidatePtr->outerTrackletPtr()->outerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->getModule().subdet() == SDL::Module::Endcap));
            ana.tx->pushbackToBranch<vector<int>>("tc_layer", layers);

            // Sim track to Tracklet matching
            int itc = ana.tx->getBranch<vector<vector<int>>>("tc_hitIdx").size() - 1;

            // For matched sim track
            for (auto& matched_sim_trk_idx : matched_sim_trk_idxs)
            {
                sim_tcIdx[matched_sim_trk_idx].push_back(itc);
                std::vector<unsigned int> hit_idx_(hit_idx.begin(), hit_idx.end());
                if (isMTVMatch(matched_sim_trk_idx, hit_idx_))
                    sim_tcIdx_isMTVmatch[matched_sim_trk_idx].push_back(itc);
            }

            SDL::Hit hitA(trk.ph2_x()[hit_idx[0]], trk.ph2_y()[hit_idx[0]], trk.ph2_z()[hit_idx[0]]);
            SDL::Hit hitB(trk.ph2_x()[hit_idx[11]], trk.ph2_y()[hit_idx[11]], trk.ph2_z()[hit_idx[11]]);
            SDL::Hit hitC(0, 0, 0);
            SDL::Hit center = SDL::MathUtil::getCenterFromThreePoints(hitA, hitB, hitC);
            float radius = center.rt();
            float pt = SDL::MathUtil::ptEstimateFromRadius(radius);
            float eta = hitB.eta();
            float phi = hitA.phi();

            float maxsimpt = -999;
            float maxsimeta = 0;
            float maxsimphi = 0;
            for (auto& simtrkidx : matched_sim_trk_idxs)
            {
                float tmpsimpt = trk.sim_pt()[simtrkidx];
                float tmpsimeta = trk.sim_eta()[simtrkidx];
                float tmpsimphi = trk.sim_phi()[simtrkidx];
                if (maxsimpt < tmpsimpt)
                {
                    maxsimpt = tmpsimpt;
                    maxsimeta = tmpsimeta;
                    maxsimphi = tmpsimphi;
                }
            }

            // Kinematic quantity
            ana.tx->pushbackToBranch<float>("tc_pt", pt);
            ana.tx->pushbackToBranch<float>("tc_eta", eta);
            ana.tx->pushbackToBranch<float>("tc_phi", phi);
            ana.tx->pushbackToBranch<float>("tc_sim_pt", maxsimpt);
            ana.tx->pushbackToBranch<float>("tc_sim_eta", maxsimeta);
            ana.tx->pushbackToBranch<float>("tc_sim_phi", maxsimphi);

        }

    }

    ana.tx->setBranch<vector<vector<int>>>("sim_tcIdx", sim_tcIdx);
    ana.tx->setBranch<vector<vector<int>>>("sim_tcIdx_isMTVmatch", sim_tcIdx_isMTVmatch);

}
