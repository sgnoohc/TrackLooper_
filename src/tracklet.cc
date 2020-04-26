#include "tracklet.h"

void tracklet()
{
    // List of studies to perform
    std::vector<Study*> studies;

    // studies.push_back(new StudyTrackletSelection("studySelTlBB1BB3", StudyTrackletSelection::kStudySelBB1BB3));
    // studies.push_back(new StudyTrackletSelection("studySelTlBB1BE3", StudyTrackletSelection::kStudySelBB1BE3));
    // studies.push_back(new StudyTrackletSelection("studySelTlBB1EE3", StudyTrackletSelection::kStudySelBB1EE3));
    // studies.push_back(new StudyTrackletSelection("studySelTlBE1EE3", StudyTrackletSelection::kStudySelBE1EE3));
    // studies.push_back(new StudyTrackletSelection("studySelTlEE1EE3", StudyTrackletSelection::kStudySelEE1EE3));

    // studies.push_back(new StudyTrackletSelection("studySelTlBB2BB4", StudyTrackletSelection::kStudySelBB2BB4));
    // studies.push_back(new StudyTrackletSelection("studySelTlBB2BE4", StudyTrackletSelection::kStudySelBB2BE4));
    // studies.push_back(new StudyTrackletSelection("studySelTlBB2EE4", StudyTrackletSelection::kStudySelBB2EE4));
    // studies.push_back(new StudyTrackletSelection("studySelTlBE2EE4", StudyTrackletSelection::kStudySelBE2EE4));
    // studies.push_back(new StudyTrackletSelection("studySelTlEE2EE4", StudyTrackletSelection::kStudySelEE2EE4));

    // studies.push_back(new StudyTrackletSelection("studySelTlBB3BB5", StudyTrackletSelection::kStudySelBB3BB5));
    // studies.push_back(new StudyTrackletSelection("studySelTlBB3BE5", StudyTrackletSelection::kStudySelBB3BE5));
    // studies.push_back(new StudyTrackletSelection("studySelTlBB3EE5", StudyTrackletSelection::kStudySelBB3EE5));
    // studies.push_back(new StudyTrackletSelection("studySelTlBE3EE5", StudyTrackletSelection::kStudySelBE3EE5));

    // // EE3EE5 is impossible

    // // studies.push_back(new StudyTrackletSelection("studySelTlEE1EE3AllPS", StudyTrackletSelection::kStudySelEE1EE3AllPS));
    // // studies.push_back(new StudyTrackletSelection("studySelTlEE1EE3All2S", StudyTrackletSelection::kStudySelEE1EE3All2S));

    ana.tx->createBranch<int>("category");
    ana.tx->createBranch<int>("nPS");
    ana.tx->createBranch<float>("deltaBetaDefault");
    ana.tx->createBranch<float>("betaInDefault");
    ana.tx->createBranch<float>("betaOutDefault");
    ana.tx->createBranch<int>("betacormode");
    ana.tx->createBranch<int>("getPassBitsDefaultAlgo");
    ana.tx->createBranch<int>("passDeltaAlphaOut");
    ana.tx->createBranch<vector<float>>("betaIn");
    ana.tx->createBranch<vector<float>>("betaOut");
    ana.tx->createBranch<vector<float>>("betaAv");
    ana.tx->createBranch<vector<float>>("betaPt");
    ana.tx->createBranch<vector<float>>("dBeta");

    // book the studies
    for (auto& study : studies)
    {
        study->bookStudy();
    }

    // Book Histograms
    ana.cutflow.bookHistograms(ana.histograms); // if just want to book everywhere

    // Load various maps used in the SDL reconstruction
    loadMaps();

    // Looping input file
    while (ana.looper.nextEvent())
    {

        if (not goodEvent())
            continue;

        // Main instance that will hold modules, hits, minidoublets, etc. (i.e. main data structure)
        SDL::Event event;

        // Add hits to the event
        addOuterTrackerHits(event);

        printHitSummary(event);
        runMiniDoublet(event);
        printMiniDoubletSummary(event);
        runSegment(event);
        printSegmentSummary(event);

        TStopwatch my_timer;
        if (ana.verbose != 0) std::cout << "Reco Tracklet start" << std::endl;
        my_timer.Start(kFALSE);
        // event.createTrackletsWithModuleMap();
        // event.createTrackletsViaNavigation();
        event.createTrackletsWithModuleMap(SDL::DefaultNm1_TLAlgo);
        // event.createTrackletsViaNavigation(SDL::DefaultNm1_TLAlgo);
        float tl_elapsed = my_timer.RealTime();
        if (ana.verbose != 0) std::cout << "Reco Tracklet processing time: " << tl_elapsed << " secs" << std::endl;

        // std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents;

        // for (auto& study : studies)
        // {
        //     study->doStudy(event, simtrkevents);
        // }


        // Loop over tracklets in event
        for (auto& layerPtr : event.getLayerPtrs())
        {

            // Parse the layer index later to be used for indexing
            int layer_idx = layerPtr->layerIdx() - 1;

            for (auto& tl : layerPtr->getTrackletPtrs())
            {
                ana.tx->setBranch<int>("category", getTrackletCategory(*tl));
                ana.tx->setBranch<int>("nPS", getNPSModules(*tl));
                ana.tx->setBranch<float>("deltaBetaDefault", tl->getDeltaBeta());
                ana.tx->setBranch<float>("betaInDefault", tl->getRecoVar("betaIn"));
                ana.tx->setBranch<float>("betaOutDefault", tl->getRecoVar("betaOut"));
                ana.tx->setBranch<int>("betacormode", tl->getRecoVar("betacormode"));
                ana.tx->setBranch<int>("getPassBitsDefaultAlgo", tl->getPassBitsDefaultAlgo());
                ana.tx->setBranch<int>("passDeltaAlphaOut", tl->getPassBitsDefaultAlgo() & (1 << SDL::Tracklet::TrackletSelection::dBeta));
                ana.tx->pushbackToBranch<float>("betaIn", tl->getRecoVar("betaIn_0th"));
                ana.tx->pushbackToBranch<float>("betaOut", tl->getRecoVar("betaOut_0th"));
                ana.tx->pushbackToBranch<float>("betaAv", tl->getRecoVar("betaAv_0th"));
                ana.tx->pushbackToBranch<float>("betaPt", tl->getRecoVar("betaPt_0th"));
                ana.tx->pushbackToBranch<float>("dBeta", tl->getRecoVar("dBeta_0th"));
                ana.tx->pushbackToBranch<float>("betaIn", tl->getRecoVar("betaIn_1st"));
                ana.tx->pushbackToBranch<float>("betaOut", tl->getRecoVar("betaOut_1st"));
                ana.tx->pushbackToBranch<float>("betaAv", tl->getRecoVar("betaAv_1st"));
                ana.tx->pushbackToBranch<float>("betaPt", tl->getRecoVar("betaPt_1st"));
                ana.tx->pushbackToBranch<float>("dBeta", tl->getRecoVar("dBeta_1st"));
                ana.tx->pushbackToBranch<float>("betaIn", tl->getRecoVar("betaIn_2nd"));
                ana.tx->pushbackToBranch<float>("betaOut", tl->getRecoVar("betaOut_2nd"));
                ana.tx->pushbackToBranch<float>("betaAv", tl->getRecoVar("betaAv_2nd"));
                ana.tx->pushbackToBranch<float>("betaPt", tl->getRecoVar("betaPt_2nd"));
                ana.tx->pushbackToBranch<float>("dBeta", tl->getRecoVar("dBeta_2nd"));
                ana.tx->pushbackToBranch<float>("betaIn", tl->getRecoVar("betaIn_3rd"));
                ana.tx->pushbackToBranch<float>("betaOut", tl->getRecoVar("betaOut_3rd"));
                ana.tx->pushbackToBranch<float>("betaAv", tl->getRecoVar("betaAv_3rd"));
                ana.tx->pushbackToBranch<float>("betaPt", tl->getRecoVar("betaPt_3rd"));
                ana.tx->pushbackToBranch<float>("dBeta", tl->getRecoVar("dBeta_3rd"));
                ana.tx->pushbackToBranch<float>("betaIn", tl->getRecoVar("betaIn_4th"));
                ana.tx->pushbackToBranch<float>("betaOut", tl->getRecoVar("betaOut_4th"));
                ana.tx->pushbackToBranch<float>("betaAv", tl->getRecoVar("betaAv_4th"));
                ana.tx->pushbackToBranch<float>("betaPt", tl->getRecoVar("betaPt_4th"));
                ana.tx->pushbackToBranch<float>("dBeta", tl->getRecoVar("dBeta_4th"));
                ana.tx->fill();
                ana.tx->clear();
            }

        }


        // ************************************************
        // Now fill all the histograms booked by each study
        // ************************************************

        // Fill all the histograms
        ana.cutflow.fill();

        // <--------------------------
        // <--------------------------
        // <--------------------------
    }

    // Writing output file
    ana.cutflow.saveOutput();

    // Writing ttree output to file
    ana.output_ttree->Write();

    // The below can be sometimes crucial
    delete ana.output_tfile;

}
