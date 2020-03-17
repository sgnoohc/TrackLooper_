#include "StudyMTVEfficiency.h"

StudyMTVEfficiency::StudyMTVEfficiency(
        const char* studyName,
        std::vector<float> ptbounds,
        int pdgid
        )
{

    studyname = studyName;

    pt_boundaries = ptbounds;

    pdgid_of_study = pdgid;

    dxy_thresh = 2.5;

    dz_thresh = 30;

    pt_thresh = 1.5;

}

void StudyMTVEfficiency::bookStudy()
{
    // Book Histograms
    const int nlayers = NLAYERS;

    const float etamax = 2.5;

    const int eta_nbins = 50;

    ana.histograms.addVecHistogram("tc_matched_track_pt_mtv" , pt_boundaries, [&]()                { return tc_matched_track_pt_mtv[0];  } );
    ana.histograms.addVecHistogram("tc_all_track_pt_mtv"     , pt_boundaries, [&]()                { return tc_all_track_pt_mtv[0];      } );
    ana.histograms.addVecHistogram("tc_matched_track_eta_mtv", eta_nbins, -1*etamax, etamax, [&]() { return tc_matched_track_eta_mtv[0]; } );
    ana.histograms.addVecHistogram("tc_all_track_eta_mtv"    , eta_nbins, -1*etamax, etamax, [&]() { return tc_all_track_eta_mtv[0];     } );
    ana.histograms.addVecHistogram("tc_matched_track_dxy_mtv", 50, -10, 10, [&]()                  { return tc_matched_track_dxy_mtv[0]; } );
    ana.histograms.addVecHistogram("tc_all_track_dxy_mtv"    , 50, -10, 10, [&]()                  { return tc_all_track_dxy_mtv[0];     } );

    ana.histograms.addVecHistogram("tc_matched_track_pt_mtv_eta0_0p4" , pt_boundaries, [&]()                { return tc_matched_track_pt_mtv[1];  } );
    ana.histograms.addVecHistogram("tc_all_track_pt_mtv_eta0_0p4"     , pt_boundaries, [&]()                { return tc_all_track_pt_mtv[1];      } );
    ana.histograms.addVecHistogram("tc_matched_track_eta_mtv_eta0_0p4", eta_nbins, -1*etamax, etamax, [&]() { return tc_matched_track_eta_mtv[1]; } );
    ana.histograms.addVecHistogram("tc_all_track_eta_mtv_eta0_0p4"    , eta_nbins, -1*etamax, etamax, [&]() { return tc_all_track_eta_mtv[1];     } );
    ana.histograms.addVecHistogram("tc_matched_track_dxy_mtv_eta0_0p4", 50, -10, 10, [&]()                  { return tc_matched_track_dxy_mtv[1]; } );
    ana.histograms.addVecHistogram("tc_all_track_dxy_mtv_eta0_0p4"    , 50, -10, 10, [&]()                  { return tc_all_track_dxy_mtv[1];     } );

    ana.histograms.addVecHistogram("tc_matched_track_pt_mtv_eta0p4_0p8" , pt_boundaries, [&]()                { return tc_matched_track_pt_mtv[2];  } );
    ana.histograms.addVecHistogram("tc_all_track_pt_mtv_eta0p4_0p8"     , pt_boundaries, [&]()                { return tc_all_track_pt_mtv[2];      } );
    ana.histograms.addVecHistogram("tc_matched_track_eta_mtv_eta0p4_0p8", eta_nbins, -1*etamax, etamax, [&]() { return tc_matched_track_eta_mtv[2]; } );
    ana.histograms.addVecHistogram("tc_all_track_eta_mtv_eta0p4_0p8"    , eta_nbins, -1*etamax, etamax, [&]() { return tc_all_track_eta_mtv[2];     } );
    ana.histograms.addVecHistogram("tc_matched_track_dxy_mtv_eta0p4_0p8", 50, -10, 10, [&]()                  { return tc_matched_track_dxy_mtv[2]; } );
    ana.histograms.addVecHistogram("tc_all_track_dxy_mtv_eta0p4_0p8"    , 50, -10, 10, [&]()                  { return tc_all_track_dxy_mtv[2];     } );

}

void StudyMTVEfficiency::doStudy(SDL::Event& event, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents)
{
    // Each do study is performed per event

    // First clear all the output variables that will be used to fill the histograms for this event

    for (unsigned int i = 0; i < 3; ++i)
    {
        tc_matched_track_pt_mtv [i].clear();
        tc_all_track_pt_mtv     [i].clear();
        tc_matched_track_eta_mtv[i].clear();
        tc_all_track_eta_mtv    [i].clear();
        tc_matched_track_dxy_mtv[i].clear();
        tc_all_track_dxy_mtv    [i].clear();
    }

    // Barrel layer layer 0
    SDL::Layer barrelLayer0 = event.getLayer(1, SDL::Layer::Barrel);

    //***************************************************************
    // Preselecting Reco Track Candidates that are worth looking into
    //***************************************************************

    // track candidates that match the particle of interest
    std::vector<unsigned int> good_track_candidates;

    // std::cout <<  " barrelLayer0.getTrackCandidatePtrs().size(): " << barrelLayer0.getTrackCandidatePtrs().size() <<  std::endl;

    // Loop over the track candidates and ask whether the hits are matched with this track (MTV like)
    for (unsigned int itc = 0; itc < barrelLayer0.getTrackCandidatePtrs().size(); ++itc)
    {

        SDL::TrackCandidate* tcCandPtr = barrelLayer0.getTrackCandidatePtrs()[itc];
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
        if (is75percentFromSimMatchedHits(hitidxs, pdgid_of_study))
        {
            good_track_candidates.push_back(itc);
        }
    }

    // std::cout <<  " good_track_candidates.size(): " << good_track_candidates.size() <<  std::endl;

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
        float dz = trk.sim_pca_dz()[isimtrk];

        if (abs(dz) > dz_thresh)
            continue;

        // Loop over the track candidates and ask whether the hits are matched with this track (MTV like)
        for (auto& igood_tc_idxs : good_track_candidates)
        {

            SDL::TrackCandidate* tcCandPtr = barrelLayer0.getTrackCandidatePtrs()[igood_tc_idxs];
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

        // *****************
        // Track Candidate
        // *****************

        float etamaxbound = etabounds[5];

        if (abs(eta) < etamaxbound and abs(dxy) < dxy_thresh)
        {

            tc_all_track_pt_mtv[0].push_back(pt);
            if (tc_trackmatch_mtv) tc_matched_track_pt_mtv[0].push_back(pt);

            if (abs(eta) < 0.4)
            {
                tc_all_track_pt_mtv[1].push_back(pt);
                if (tc_trackmatch_mtv) tc_matched_track_pt_mtv[1].push_back(pt);
            }
            if (abs(eta) > 0.4 and abs(eta) < 0.8)
            {
                tc_all_track_pt_mtv[2].push_back(pt);
                if (tc_trackmatch_mtv) tc_matched_track_pt_mtv[2].push_back(pt);
            }
        }

        if (pt > pt_thresh and abs(dxy) < dxy_thresh and abs(eta) < etamaxbound)
        {

            tc_all_track_eta_mtv[0].push_back(eta);
            if (tc_trackmatch_mtv) tc_matched_track_eta_mtv[0].push_back(eta);

            if (abs(eta) < 0.4)
            {
                tc_all_track_eta_mtv[1].push_back(eta);
                if (tc_trackmatch_mtv) tc_matched_track_eta_mtv[1].push_back(eta);
            }
            if (abs(eta) > 0.4 and abs(eta) < 0.8)
            {
                tc_all_track_eta_mtv[2].push_back(eta);
                if (tc_trackmatch_mtv) tc_matched_track_eta_mtv[2].push_back(eta);
            }
        }

        if (pt > pt_thresh and abs(eta) < etamaxbound)
        {

            tc_all_track_dxy_mtv[0].push_back(dxy);
            if (tc_trackmatch_mtv) tc_matched_track_dxy_mtv[0].push_back(dxy);

            if (abs(eta) < 0.4)
            {
                tc_all_track_dxy_mtv[1].push_back(dxy);
                if (tc_trackmatch_mtv) tc_matched_track_dxy_mtv[1].push_back(dxy);
            }
            if (abs(eta) > 0.4 and abs(eta) < 0.8)
            {
                tc_all_track_dxy_mtv[2].push_back(dxy);
                if (tc_trackmatch_mtv) tc_matched_track_dxy_mtv[2].push_back(dxy);
            }
        }

    }

}

