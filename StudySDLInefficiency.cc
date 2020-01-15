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
    ana.tx->createBranch<float>("pdgid");
    ana.tx->createBranch<float>("itrk");

    ana.tx->createBranch<vector<float>>("hit_x");
    ana.tx->createBranch<vector<float>>("hit_y");
    ana.tx->createBranch<vector<float>>("hit_z");
    ana.tx->createBranch<vector<int  >>("hit_side");
    ana.tx->createBranch<vector<int  >>("hit_rod");
    ana.tx->createBranch<vector<int  >>("hit_module");
    ana.tx->createBranch<vector<int  >>("hit_subdet");

    ana.tx->createBranch<vector<float>>("md_dz");
    ana.tx->createBranch<vector<float>>("md_dphi");
    ana.tx->createBranch<vector<float>>("md_dphichange");
    ana.tx->createBranch<vector<float>>("md_minicut");
    ana.tx->createBranch<vector<int  >>("md_pass");

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
        ana.tx->setBranch<float>("pdgid", trk.sim_pdgId()[isimtrk]);
        ana.tx->setBranch<float>("itrk", isimtrk);

        for (unsigned int ilayer = 1; ilayer <= 6; ilayer++)
        {

            float lower_hit_x      = -999;
            float lower_hit_y      = -999;
            float lower_hit_z      = -999;
            int   lower_hit_side   = -999;
            int   lower_hit_rod    = -999;
            int   lower_hit_module = -999;
            int   lower_hit_subdet = -999;

            float upper_hit_x      = -999;
            float upper_hit_y      = -999;
            float upper_hit_z      = -999;
            int   upper_hit_side   = -999;
            int   upper_hit_rod    = -999;
            int   upper_hit_module = -999;
            int   upper_hit_subdet = -999;

            float md_dz            = -999;
            float md_dphi          = -999;
            float md_dphichange    = -999;
            float md_minicut       = -999;
            int   md_pass          = -999;

            for (auto& mdPtr : trackevent.getLayer(ilayer, SDL::Layer::Barrel).getMiniDoubletPtrs())
            {

                mdPtr->runMiniDoubletAlgo(SDL::Default_MDAlgo);

                if ((md_dphichange == -999) or (md_dphichange > mdPtr->getDeltaPhiChange()))
                {

                    md_dz            = mdPtr->getDz();
                    md_dphi          = mdPtr->getDeltaPhi();
                    md_dphichange    = mdPtr->getDeltaPhiChange();
                    md_minicut       = mdPtr->getRecoVar("miniCut");
                    md_pass          = mdPtr->passesMiniDoubletAlgo(SDL::Default_MDAlgo);

                    lower_hit_x      = mdPtr->lowerHitPtr()->x();
                    lower_hit_y      = mdPtr->lowerHitPtr()->y();
                    lower_hit_z      = mdPtr->lowerHitPtr()->z();
                    lower_hit_side   = mdPtr->lowerHitPtr()->getModule().side();
                    lower_hit_rod    = mdPtr->lowerHitPtr()->getModule().rod();
                    lower_hit_module = mdPtr->lowerHitPtr()->getModule().module();
                    lower_hit_subdet = mdPtr->lowerHitPtr()->getModule().subdet();
                                                                                         
                    upper_hit_x      = mdPtr->upperHitPtr()->x();
                    upper_hit_y      = mdPtr->upperHitPtr()->y();
                    upper_hit_z      = mdPtr->upperHitPtr()->z();
                    upper_hit_side   = mdPtr->upperHitPtr()->getModule().side();
                    upper_hit_rod    = mdPtr->upperHitPtr()->getModule().rod();
                    upper_hit_module = mdPtr->upperHitPtr()->getModule().module();
                    upper_hit_subdet = mdPtr->upperHitPtr()->getModule().subdet();

                }

            }

            if (md_dphichange == -999)
            {
                std::cout <<  " ilayer: " << ilayer <<  std::endl;
                unsigned int size = trackevent.getLayer(ilayer, SDL::Layer::Barrel).getMiniDoubletPtrs().size();
                std::cout <<  " size: " << size <<  std::endl;
            }

            ana.tx->pushbackToBranch<float>("md_dz"         , md_dz        );
            ana.tx->pushbackToBranch<float>("md_dphi"       , md_dphi      );
            ana.tx->pushbackToBranch<float>("md_dphichange" , md_dphichange);
            ana.tx->pushbackToBranch<float>("md_minicut"    , md_minicut   );
            ana.tx->pushbackToBranch<int  >("md_pass"       , md_pass      );

            ana.tx->pushbackToBranch<float>("hit_x"      , lower_hit_x      );
            ana.tx->pushbackToBranch<float>("hit_y"      , lower_hit_y      );
            ana.tx->pushbackToBranch<float>("hit_z"      , lower_hit_z      );
            ana.tx->pushbackToBranch<int  >("hit_side"   , lower_hit_side   );
            ana.tx->pushbackToBranch<int  >("hit_rod"    , lower_hit_rod    );
            ana.tx->pushbackToBranch<int  >("hit_module" , lower_hit_module );
            ana.tx->pushbackToBranch<int  >("hit_subdet" , lower_hit_subdet );

            ana.tx->pushbackToBranch<float>("hit_x"      , upper_hit_x      );
            ana.tx->pushbackToBranch<float>("hit_y"      , upper_hit_y      );
            ana.tx->pushbackToBranch<float>("hit_z"      , upper_hit_z      );
            ana.tx->pushbackToBranch<int  >("hit_side"   , upper_hit_side   );
            ana.tx->pushbackToBranch<int  >("hit_rod"    , upper_hit_rod    );
            ana.tx->pushbackToBranch<int  >("hit_module" , upper_hit_module );
            ana.tx->pushbackToBranch<int  >("hit_subdet" , upper_hit_subdet );

        }

        ana.tx->fill();
        ana.tx->clear();

    }

}

