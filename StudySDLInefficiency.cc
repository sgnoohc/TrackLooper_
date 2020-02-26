#include "StudySDLInefficiency.h"

StudySDLInefficiency::StudySDLInefficiency(
        const char* studyName,
        StudySDLInefficiency::StudySDLMiniDoubletInefficiencyMode md_mode_,
        StudySDLInefficiency::StudySDLSegmentInefficiencyMode sg_mode_,
        StudySDLInefficiency::StudySDLTrackletInefficiencyMode tl_mode_,
        StudySDLInefficiency::StudySDLTrackCandidateInefficiencyMode tc_mode_,
        std::vector<float> ptbounds)
{

    studyname = studyName;

    md_mode = md_mode_;
    sg_mode = sg_mode_;
    tl_mode = tl_mode_;
    tc_mode = tc_mode_;

    pt_boundaries = ptbounds;

    switch (md_mode)
    {
        case kStudySDLMDEffAll: md_modename = "all"; break;
        case kStudySDLMDEffBarrel: md_modename = "barrel"; break;
        case kStudySDLMDEffBarrelFlat: md_modename = "barrelflat"; break;
        case kStudySDLMDEffBarrelTilt: md_modename = "barreltilt"; break;
        case kStudySDLMDEffEndcap: md_modename = "endcap"; break;
        case kStudySDLMDEffEndcapPS: md_modename = "endcapPS"; break;
        case kStudySDLMDEffEndcap2S: md_modename = "endcap2S"; break;
        default: md_modename = "UNDEFINED"; break;
    }

    switch (sg_mode)
    {
        case kStudySDLSGEffAll: sg_modename = "all"; break;
        case kStudySDLSGEffBB: sg_modename = "bb"; break;
        default: sg_modename = "UNDEFINED"; break;
    }

    switch (tl_mode)
    {
        case kStudySDLTLEffAll: tl_modename = "all"; break;
        case kStudySDLTLEffBBBB: tl_modename = "bbbb"; break;
        default: tl_modename = "UNDEFINED"; break;
    }

    switch (tc_mode)
    {
        case kStudySDLTCEffAll: tc_modename = "all"; break;
        case kStudySDLTCEffBBBBBB: tc_modename = "bbbbbb"; break;
        default: tc_modename = "UNDEFINED"; break;
    }

}

void StudySDLInefficiency::bookStudy()
{
    ana.tx->createBranch<float>("pt");
    ana.tx->createBranch<float>("eta");
    ana.tx->createBranch<float>("dxy");
    ana.tx->createBranch<float>("dz");
    ana.tx->createBranch<float>("pdgid");
    ana.tx->createBranch<float>("itrk");


    for (unsigned int ilayer = 1; ilayer <= 6; ++ilayer)
    {
        ana.tx->createBranch<vector<int  >>(TString::Format("md%d_ncand", ilayer));
        ana.tx->createBranch<vector<float>>(TString::Format("md%d_dz", ilayer));
        ana.tx->createBranch<vector<float>>(TString::Format("md%d_dphi", ilayer));
        ana.tx->createBranch<vector<float>>(TString::Format("md%d_dphichange", ilayer));
        ana.tx->createBranch<vector<float>>(TString::Format("md%d_minicut", ilayer));
        ana.tx->createBranch<vector<int  >>(TString::Format("md%d_pass", ilayer));
        ana.tx->createBranch<vector<float>>(TString::Format("md%d_lower_hit_x", ilayer));
        ana.tx->createBranch<vector<float>>(TString::Format("md%d_lower_hit_y", ilayer));
        ana.tx->createBranch<vector<float>>(TString::Format("md%d_lower_hit_z", ilayer));
        ana.tx->createBranch<vector<float>>(TString::Format("md%d_lower_hit_rt", ilayer));
        ana.tx->createBranch<vector<int  >>(TString::Format("md%d_lower_hit_side", ilayer));
        ana.tx->createBranch<vector<int  >>(TString::Format("md%d_lower_hit_rod", ilayer));
        ana.tx->createBranch<vector<int  >>(TString::Format("md%d_lower_hit_module", ilayer));
        ana.tx->createBranch<vector<int  >>(TString::Format("md%d_lower_hit_subdet", ilayer));
        ana.tx->createBranch<vector<float>>(TString::Format("md%d_upper_hit_x", ilayer));
        ana.tx->createBranch<vector<float>>(TString::Format("md%d_upper_hit_y", ilayer));
        ana.tx->createBranch<vector<float>>(TString::Format("md%d_upper_hit_z", ilayer));
        ana.tx->createBranch<vector<float>>(TString::Format("md%d_upper_hit_rt", ilayer));
        ana.tx->createBranch<vector<int  >>(TString::Format("md%d_upper_hit_side", ilayer));
        ana.tx->createBranch<vector<int  >>(TString::Format("md%d_upper_hit_rod", ilayer));
        ana.tx->createBranch<vector<int  >>(TString::Format("md%d_upper_hit_module", ilayer));
        ana.tx->createBranch<vector<int  >>(TString::Format("md%d_upper_hit_subdet", ilayer));
    }

}

void StudySDLInefficiency::doStudy(SDL::Event& event, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents)
{

    ana.tx->clear();

    // Loop over track events
    for (auto& simtrkevent : simtrkevents)
    {
        // Unpack the tuple (sim_track_index, SDL::Event containing reco hits only matched to the given sim track)
        unsigned int& isimtrk = std::get<0>(simtrkevent);
        SDL::Event& trackevent = *(std::get<1>(simtrkevent));

        ana.tx->setBranch<float>("pt", trk.sim_pt()[isimtrk]);
        ana.tx->setBranch<float>("eta", trk.sim_eta()[isimtrk]);
        ana.tx->setBranch<float>("dxy", trk.sim_pca_dxy()[isimtrk]);
        ana.tx->setBranch<float>("dz", trk.sim_pca_dz()[isimtrk]);
        ana.tx->setBranch<float>("pdgid", trk.sim_pdgId()[isimtrk]);
        ana.tx->setBranch<float>("itrk", isimtrk);

        for (unsigned int ilayer = 1; ilayer <= 6; ilayer++)
        {

            ana.tx->pushbackToBranch<int>(TString::Format("md%d_ncand", ilayer), trackevent.getLayer(ilayer, SDL::Layer::Barrel).getMiniDoubletPtrs().size() );

            for (auto& mdPtr : trackevent.getLayer(ilayer, SDL::Layer::Barrel).getMiniDoubletPtrs())
            {

                mdPtr->runMiniDoubletAlgo(SDL::Default_MDAlgo);
                ana.tx->pushbackToBranch<float>(TString::Format("md%d_dz"               , ilayer), mdPtr->getDz()                                   );
                ana.tx->pushbackToBranch<float>(TString::Format("md%d_dphi"             , ilayer), mdPtr->getDeltaPhi()                             );
                ana.tx->pushbackToBranch<float>(TString::Format("md%d_dphichange"       , ilayer), mdPtr->getDeltaPhiChange()                       );
                ana.tx->pushbackToBranch<float>(TString::Format("md%d_minicut"          , ilayer), mdPtr->getRecoVar("miniCut")                     );
                ana.tx->pushbackToBranch<int  >(TString::Format("md%d_pass"             , ilayer), mdPtr->passesMiniDoubletAlgo(SDL::Default_MDAlgo));
                ana.tx->pushbackToBranch<float>(TString::Format("md%d_lower_hit_x"      , ilayer), mdPtr->lowerHitPtr()->x()                        );
                ana.tx->pushbackToBranch<float>(TString::Format("md%d_lower_hit_y"      , ilayer), mdPtr->lowerHitPtr()->y()                        );
                ana.tx->pushbackToBranch<float>(TString::Format("md%d_lower_hit_z"      , ilayer), mdPtr->lowerHitPtr()->z()                        );
                ana.tx->pushbackToBranch<float>(TString::Format("md%d_lower_hit_rt"     , ilayer), mdPtr->lowerHitPtr()->rt()                       );
                ana.tx->pushbackToBranch<int  >(TString::Format("md%d_lower_hit_side"   , ilayer), mdPtr->lowerHitPtr()->getModule().side()         );
                ana.tx->pushbackToBranch<int  >(TString::Format("md%d_lower_hit_rod"    , ilayer), mdPtr->lowerHitPtr()->getModule().rod()          );
                ana.tx->pushbackToBranch<int  >(TString::Format("md%d_lower_hit_module" , ilayer), mdPtr->lowerHitPtr()->getModule().module()       );
                ana.tx->pushbackToBranch<int  >(TString::Format("md%d_lower_hit_subdet" , ilayer), mdPtr->lowerHitPtr()->getModule().subdet()       );
                ana.tx->pushbackToBranch<float>(TString::Format("md%d_upper_hit_x"      , ilayer), mdPtr->upperHitPtr()->x()                        );
                ana.tx->pushbackToBranch<float>(TString::Format("md%d_upper_hit_y"      , ilayer), mdPtr->upperHitPtr()->y()                        );
                ana.tx->pushbackToBranch<float>(TString::Format("md%d_upper_hit_z"      , ilayer), mdPtr->upperHitPtr()->z()                        );
                ana.tx->pushbackToBranch<float>(TString::Format("md%d_upper_hit_rt"     , ilayer), mdPtr->upperHitPtr()->rt()                       );
                ana.tx->pushbackToBranch<int  >(TString::Format("md%d_upper_hit_side"   , ilayer), mdPtr->upperHitPtr()->getModule().side()         );
                ana.tx->pushbackToBranch<int  >(TString::Format("md%d_upper_hit_rod"    , ilayer), mdPtr->upperHitPtr()->getModule().rod()          );
                ana.tx->pushbackToBranch<int  >(TString::Format("md%d_upper_hit_module" , ilayer), mdPtr->upperHitPtr()->getModule().module()       );
                ana.tx->pushbackToBranch<int  >(TString::Format("md%d_upper_hit_subdet" , ilayer), mdPtr->upperHitPtr()->getModule().subdet()       );

            }

        }

        ana.tx->fill();
        ana.tx->clear();

    }

}

