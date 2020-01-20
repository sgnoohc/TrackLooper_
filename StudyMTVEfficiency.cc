#include "StudyMTVEfficiency.h"

StudyMTVEfficiency::StudyMTVEfficiency(
        const char* studyName,
        std::vector<float> ptbounds)
{

    studyname = studyName;

    pt_boundaries = ptbounds;

}

void StudyMTVEfficiency::bookStudy()
{
    // Book Histograms
    const int nlayers = NLAYERS;

    const float etamax = 2.5;

    const int eta_nbins = 50;

    int ii = 0;

    ana.histograms.addVecHistogram("tc_matched_track_pt_mtv" , pt_boundaries, [&, ii]()                { return tc_matched_track_pt_mtv;  } );
    ana.histograms.addVecHistogram("tc_all_track_pt_mtv"     , pt_boundaries, [&, ii]()                { return tc_all_track_pt_mtv;      } );
    ana.histograms.addVecHistogram("tc_matched_track_eta_mtv", eta_nbins, -1*etamax, etamax, [&, ii]() { return tc_matched_track_eta_mtv; } );
    ana.histograms.addVecHistogram("tc_all_track_eta_mtv"    , eta_nbins, -1*etamax, etamax, [&, ii]() { return tc_all_track_eta_mtv;     } );
    ana.histograms.addVecHistogram("tc_matched_track_dxy_mtv", 50, -10, 10, [&, ii]()                  { return tc_matched_track_dxy_mtv; } );
    ana.histograms.addVecHistogram("tc_all_track_dxy_mtv"    , 50, -10, 10, [&, ii]()                  { return tc_all_track_dxy_mtv;     } );

}

void StudyMTVEfficiency::doStudy(SDL::Event& event, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents)
{
    // Each do study is performed per event

    // First clear all the output variables that will be used to fill the histograms for this event

    tc_matched_track_pt_mtv .clear();
    tc_all_track_pt_mtv     .clear();
    tc_matched_track_eta_mtv.clear();
    tc_all_track_eta_mtv    .clear();
    tc_matched_track_dxy_mtv.clear();
    tc_all_track_dxy_mtv    .clear();

    //***********************
    // Efficiency calculation
    //***********************

    std::array<float, 6> etabounds = {2.2, 1.8, 1.45, 1.2, 1, 0.8};

    // Loop over track events
    for (auto& simtrkevent : simtrkevents)
    {

        // Unpack the tuple (sim_track_index, SDL::Event containing reco hits only matched to the given sim track)
        unsigned int& isimtrk = std::get<0>(simtrkevent);
        SDL::Event& trackevent = *(std::get<1>(simtrkevent));

        // Create list of booleans
        bool tc_trackmatch_mtv = false;;

        // Parse pt and eta of this track
        float pt = std::min((double) trk.sim_pt()[isimtrk], 49.999);
        float eta = trk.sim_eta()[isimtrk];
        float dxy = trk.sim_pca_dxy()[isimtrk];

        // Loop over the layers that contains tracklets and/or track candidates
        for (auto& layerPtr_Track : event.getLayerPtrs())
        {
            // Parse the layer index later to be used for indexing
            int layer_idx = layerPtr_Track->layerIdx() - 1;

            // Loop over the track candidates and ask whether the hits are matched with this track (MTV like)
            for (auto& tcCandPtr : layerPtr_Track->getTrackCandidatePtrs())
            {
                std::vector<unsigned int> hitidxs;
                hitidxs.push_back(tcCandPtr->innerTrackletPtr()->innerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->idx());
                hitidxs.push_back(tcCandPtr->innerTrackletPtr()->innerSegmentPtr()->innerMiniDoubletPtr()->upperHitPtr()->idx());
                hitidxs.push_back(tcCandPtr->innerTrackletPtr()->innerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->idx());
                hitidxs.push_back(tcCandPtr->innerTrackletPtr()->innerSegmentPtr()->outerMiniDoubletPtr()->upperHitPtr()->idx());
                hitidxs.push_back(tcCandPtr->innerTrackletPtr()->outerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->idx());
                hitidxs.push_back(tcCandPtr->innerTrackletPtr()->outerSegmentPtr()->innerMiniDoubletPtr()->upperHitPtr()->idx());
                hitidxs.push_back(tcCandPtr->innerTrackletPtr()->outerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->idx());
                hitidxs.push_back(tcCandPtr->innerTrackletPtr()->outerSegmentPtr()->outerMiniDoubletPtr()->upperHitPtr()->idx());
                hitidxs.push_back(tcCandPtr->outerTrackletPtr()->outerSegmentPtr()->innerMiniDoubletPtr()->lowerHitPtr()->idx());
                hitidxs.push_back(tcCandPtr->outerTrackletPtr()->outerSegmentPtr()->innerMiniDoubletPtr()->upperHitPtr()->idx());
                hitidxs.push_back(tcCandPtr->outerTrackletPtr()->outerSegmentPtr()->outerMiniDoubletPtr()->lowerHitPtr()->idx());
                hitidxs.push_back(tcCandPtr->outerTrackletPtr()->outerSegmentPtr()->outerMiniDoubletPtr()->upperHitPtr()->idx());
                if (isMTVMatch(isimtrk, hitidxs))
                {
                    tc_trackmatch_mtv = true;
                }
            }
        }

        // *****************
        // Track Candidate
        // *****************

        float etamaxbound = etabounds[5];

        if (abs(eta) < etamaxbound and abs(dxy) < 3.5)
        {

            tc_all_track_pt_mtv.push_back(pt);
            if (tc_trackmatch_mtv) tc_matched_track_pt_mtv.push_back(pt);
        }

        if (abs(pt) > 1.5 and abs(dxy) < 3.5 and abs(eta) < etamaxbound)
        {

            tc_all_track_eta_mtv.push_back(eta);
            if (tc_trackmatch_mtv) tc_matched_track_eta_mtv.push_back(eta);
        }

        if (abs(pt) > 1.5 and abs(eta) < etamaxbound)
        {

            tc_all_track_dxy_mtv.push_back(dxy);
            if (tc_trackmatch_mtv) tc_matched_track_dxy_mtv.push_back(dxy);
        }

    }

}

