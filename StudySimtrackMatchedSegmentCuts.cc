# include "StudySimtrackMatchedSegmentCuts.h"

StudySimtrackMatchedSegmentCuts::StudySimtrackMatchedSegmentCuts(const char * studyName)
{
    studyName = studyName;
}

void StudySimtrackMatchedSegmentCuts::bookStudy()
{
    ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_dz"),400,-20,20,[&](){return dzValues;});
    ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_dPhi"),200,-6.28,6.28,[&](){return dPhiValues;});
    ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_dPhiChange"),200,-6.28,6.28,[&](){return dPhiChangeValues;});
    ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_dAlphaInnerMDSegment"),200,-6.28,6.28,[&](){return dAlphaInnerMDSegmentValues;});
    ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_dAlphaOuterMDSegment"),200,-6.28,6.28,[&](){return dAlphaOuterMDSegmentValues;});
    ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_dAlphaInnerMDOuterMD"),200,-6.28,6.28,[&](){return dAlphaInnerMDOuterMDValues;});



    ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_barrel_dz"),400,-20,20,[&](){return barreldzValues;});
    ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_barrel_dPhi"),200,-6.28,6.28,[&](){return barreldPhiValues;});
    ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_barrel_dPhiChange"),200,-6.28,6.28,[&](){return barreldPhiChangeValues;});
    ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_barrel_dAlphaInnerMDSegment"),200,-6.28,6.28,[&](){return barreldAlphaInnerMDSegmentValues;});
    ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_barrel_dAlphaOuterMDSegment"),200,-6.28,6.28,[&](){return barreldAlphaOuterMDSegmentValues;});
    ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_barrel_dAlphaInnerMDOuterMD"),200,-6.28,6.28,[&](){return barreldAlphaInnerMDOuterMDValues;});



    ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_endcap_drt"),400,-20,20,[&](){return endcapdrtValues;});
    ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_endcap_dPhi"),200,-6.28,6.28,[&](){return endcapdPhiValues;});
    ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_endcap_dPhiChange"),200,-6.28,6.28,[&](){return endcapdPhiChangeValues;});
     ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_endcap_dAlphaInnerMDSegment"),200,-6.28,6.28,[&](){return endcapdAlphaInnerMDSegmentValues;});
    ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_endcap_dAlphaOuterMDSegment"),200,-6.28,6.28,[&](){return endcapdAlphaOuterMDSegmentValues;});
    ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_endcap_dAlphaInnerMDOuterMD"),200,-6.28,6.28,[&](){return endcapdAlphaInnerMDOuterMDValues;});



    //one per layer
    for(size_t i = 0; i < 6; i++)
    {
        ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_dz_layer_%ld",i+1),400,-20,20,[&,i](){return layerdzValues[i];});
        ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_dPhi_layer_%ld",i+1),200,-6.28,6.28,[&,i](){return layerdPhiValues[i];});
        ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_dPhiChange_layer_%ld",i+1),200,-6.28,6.28,[&,i](){return layerdPhiChangeValues[i];});
        ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_dAlphaInnerMDSegment_layer%ld",i+1),200,-6.28,6.28,[&,i](){return layerdAlphaInnerMDSegmentValues[i];});
        ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_dAlphaOuterMDSegment_layer%ld",i+1),200,-6.28,6.28,[&,i](){return layerdAlphaOuterMDSegmentValues[i];});
        ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_dAlphaInnerMDOuterMD_layer%ld",i+1),200,-6.28,6.28,[&,i](){return layerdAlphaInnerMDOuterMDValues[i];});



        ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_barrel_dz_layer_%ld",i+1),400,-20,20,[&,i](){return layerBarreldzValues[i];});
        ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_barrel_dPhi_layer_%ld",i+1),200,-6.28,6.28,[&,i](){return layerBarreldPhiValues[i];});
        ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_barrel_dPhiChange_layer_%ld",i+1),200,-6.28,6.28,[&,i](){return layerBarreldPhiChangeValues[i];});
        ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_barrel_dAlphaInnerMDSegment_layer%ld",i+1),200,-6.28,6.28,[&,i](){return layerBarreldAlphaInnerMDSegmentValues[i];});
        ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_barrel_dAlphaOuterMDSegment_layer%ld",i+1),200,-6.28,6.28,[&,i](){return layerBarreldAlphaOuterMDSegmentValues[i];});
        ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_barrel_dAlphaInnerMDOuterMD_layer%ld",i+1),200,-6.28,6.28,[&,i](){return layerBarreldAlphaInnerMDOuterMDValues[i];});




        if(i < 5)
        {
            ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_endcap_drt_layer_%ld",i+1),400,-20,20,[&,i](){return layerEndcapdrtValues[i];});
            ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_endcap_dPhi_layer_%ld",i+1),200,-6.28,6.28,[&,i](){return layerEndcapdPhiValues[i];});
            ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_endcap_dPhiChange_layer_%ld",i+1),200,-6.28,6.28,[&,i](){return layerEndcapdPhiChangeValues[i];});
            ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_endcap_dAlphaInnerMDSegment_layer%ld",i+1),200,-6.28,6.28,[&,i](){return layerEndcapdAlphaInnerMDSegmentValues[i];});
        ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_endcap_dAlphaOuterMDSegment_layer%ld",i+1),200,-6.28,6.28,[&,i](){return layerEndcapdAlphaOuterMDSegmentValues[i];});
        ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_endcap_dAlphaInnerMDOuterMD_layer%ld",i+1),200,-6.28,6.28,[&,i](){return layerEndcapdAlphaInnerMDOuterMDValues[i];});
        }
    }

    for(size_t i = 0; i < 15; i++)
    {
        ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_endcap_drt_ring_%ld",i+1),400,-20,20,[&,i](){return ringEndcapdrtValues[i];});
        ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_endcap_dPhi_ring%ld",i+1),200,-6.28,6.28,[&,i](){return ringEndcapdPhiValues[i];});
        ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_endcap_dPhiChange_ring%ld",i+1),200,-6.28,6.28,[&,i](){return ringEndcapdPhiChangeValues[i];});
        ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_endcap_dAlphaInnerMDSegment_ring%ld",i+1),200,-6.28,6.28,[&,i](){return ringEndcapdAlphaInnerMDSegmentValues[i];});
        ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_endcap_dAlphaOuterMDSegment_ring%ld",i+1),200,-6.28,6.28,[&,i](){return ringEndcapdAlphaOuterMDSegmentValues[i];});
        ana.histograms.addVecHistogram(TString::Format("sim_matched_Segment_endcap_dAlphaInnerMDOuterMD_ring%ld",i+1),200,-6.28,6.28,[&,i](){return ringEndcapdAlphaInnerMDOuterMDValues[i];});
    }
}

void StudySimtrackMatchedSegmentCuts::resetVariables()
{
    dzValues.clear();
    dPhiValues.clear();
    dPhiChangeValues.clear();
    dAlphaInnerMDSegmentValues.clear();
    dAlphaOuterMDSegmentValues.clear();
    dAlphaInnerMDOuterMDValues.clear();

    barreldzValues.clear();
    barreldPhiValues.clear();
    barreldPhiChangeValues.clear();
    barreldAlphaInnerMDSegmentValues.clear();
    barreldAlphaOuterMDSegmentValues.clear();
    barreldAlphaInnerMDOuterMDValues.clear();

    endcapdrtValues.clear();
    endcapdPhiValues.clear();
    endcapdPhiChangeValues.clear();
    endcapdAlphaInnerMDSegmentValues.clear();
    endcapdAlphaOuterMDSegmentValues.clear();
    endcapdAlphaInnerMDOuterMDValues.clear();

    layerdzValues.clear();
    layerdPhiValues.clear();
    layerdPhiChangeValues.clear();
    layerdAlphaInnerMDSegmentValues.clear();
    layerdAlphaOuterMDSegmentValues.clear();
    layerdAlphaInnerMDOuterMDValues.clear();

    layerBarreldzValues.clear();
    layerBarreldPhiValues.clear();
    layerBarreldPhiChangeValues.clear();
    layerBarreldAlphaInnerMDSegmentValues.clear();
    layerBarreldAlphaOuterMDSegmentValues.clear();
    layerBarreldAlphaInnerMDOuterMDValues.clear();

    layerEndcapdrtValues.clear();
    layerEndcapdPhiValues.clear();
    layerEndcapdPhiChangeValues.clear();
    layerEndcapdAlphaInnerMDSegmentValues.clear();
    layerEndcapdAlphaOuterMDSegmentValues.clear();
    layerEndcapdAlphaInnerMDOuterMDValues.clear();

    ringEndcapdrtValues.clear();
    ringEndcapdPhiValues.clear();
    ringEndcapdPhiChangeValues.clear();
    ringEndcapdAlphaInnerMDSegmentValues.clear();
    ringEndcapdAlphaOuterMDSegmentValues.clear();
    ringEndcapdAlphaInnerMDOuterMDValues.clear();


    for(size_t i = 1; i <= 6; i++)
    {
        layerdzValues.push_back(std::vector<float>());
        layerdPhiValues.push_back(std::vector<float>());
        layerdPhiChangeValues.push_back(std::vector<float>());
        layerdAlphaInnerMDSegmentValues.push_back(std::vector<float>());
        layerdAlphaOuterMDSegmentValues.push_back(std::vector<float>());
        layerdAlphaInnerMDOuterMDValues.push_back(std::vector<float>());

        layerBarreldzValues.push_back(std::vector<float>());
        layerBarreldPhiValues.push_back(std::vector<float>());
        layerBarreldPhiChangeValues.push_back(std::vector<float>());
        layerBarreldAlphaInnerMDSegmentValues.push_back(std::vector<float>());
        layerBarreldAlphaOuterMDSegmentValues.push_back(std::vector<float>());
        layerBarreldAlphaInnerMDOuterMDValues.push_back(std::vector<float>());

        if(i < 6)
        {
            layerEndcapdrtValues.push_back(std::vector<float>());
            layerEndcapdPhiValues.push_back(std::vector<float>());
            layerEndcapdrtValues.push_back(std::vector<float>());
            layerEndcapdPhiChangeValues.push_back(std::vector<float>());
            layerEndcapdAlphaInnerMDSegmentValues.push_back(std::vector<float>());
            layerEndcapdAlphaOuterMDSegmentValues.push_back(std::vector<float>());
            layerEndcapdAlphaInnerMDOuterMDValues.push_back(std::vector<float>());
        }
      
    }

    for(size_t i = 0; i < 15; i++)
    {
        ringEndcapdrtValues.push_back(std::vector<float>());
        ringEndcapdPhiValues.push_back(std::vector<float>());
        ringEndcapdPhiChangeValues.push_back(std::vector<float>());
        ringEndcapdAlphaInnerMDSegmentValues.push_back(std::vector<float>());
        ringEndcapdAlphaOuterMDSegmentValues.push_back(std::vector<float>());
        ringEndcapdAlphaInnerMDOuterMDValues.push_back(std::vector<float>());
    }

} 


void StudySimtrackMatchedSegmentCuts::doStudy(SDL::Event &event, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents)
{
    resetVariables();

    for(auto &matchedTrack:simtrkevents)
    {
        std::vector<SDL::Module*> moduleList = std::get<1>(matchedTrack)->getLowerModulePtrs();
        for(auto &module:moduleList)
        {
            std::vector<SDL::Segment*> segments = module->getSegmentPtrs();
            for(auto &sg:segments)
            {
                dzValues.push_back(sg->getZOut());
                dPhiValues.push_back(sg->getRecoVars()["deltaPhi"]);
                dPhiChangeValues.push_back(sg->getDeltaPhiChange());

                layerdzValues.at(module->layer()-1).push_back(sg->getZOut());
                layerdPhiValues.at(module->layer()-1).push_back(sg->getRecoVars["deltaPhi"]);
                layerdPhiChangeValues.at(module->layer()-1).push_back(sg->getDeltaPhiChange());

                float dPhiChangeInnerMD = (sg->innerMiniDoubletPtr())->getDeltaPhiChange();
                float dPhiChangeOuterMD = (sg->outerMiniDoubletPtr())->getDeltaPhiChange();
                float dPhiChangeSegment = sg->getDeltaPhiChange();

                float dAlphaInnerMDSegment = dPhiChangeInnerMD - dPhiChangeSegment;
                float dAlphaOuterMDSegment = dPhiChangeOuterMD - dPhiChangeSegment;
                float dAlphaInnerMDOuterMD = dPhiChangeInnerMD - dPhiChangeOuterMD;

                dAlphaInnerMDSegmentValues.push_back(dAlphaInnerMDSegment);
                dAlphaOuterMDSegmentValues.push_back(dAlphaOuterMDSegment);
                dAlphaInnerMDOuterMDValues.push_back(dAlphaInnerMDOuterMD);
                layerdAlphaInnerMDSegmentValues.at(module->layer()-1).push_back(dAlphaInnerMDSegment);
                layerdAlphaOuterMDSegmentValues.at(module->layer()-1).push_back(dAlphaOuterMDSegment);
                layerdAlphaInnerMDOuterMDValues.at(module->layer()-1).push_back(dAlphaInnerMDOuterMD);

                if(module->subdet() == SDL::Module::Barrel)
                {
                    barreldzValues.push_back(sg->getZOut());
                    barreldPhiValues.push_back(sg->getRecoVars["deltaPhi"]);
                    barreldPhiChangeValues.push_back(sg->getDeltaPhiChange());
                    barreldAlphaInnerMDSegmentValues.push_back(dAlphaInnerMDSegment);
                    barreldAlphaOuterMDSegmentValues.push_back(dAlphaOuterMDSegment);
                    barreldAlphaInnerMDOuterMDValues.push_back(dAlphaInnerMDOuterMD);

                    layerBarreldzValues.at(module->layer()-1).push_back(sg->getZOut);
                    layerBarreldPhiValues.at(module->layer()-1).push_back(sg->getRecoVars["deltaPhi"]);
                    layerBarreldPhiChangeValues.at(module->layer()-1).push_back(sg->getDeltaPhiChange());
                    layerBarreldAlphaInnerMDSegmentValues.at(module->layer()-1).push_back(dAlphaInnerMDSegment);
                    layerBarreldAlphaOuterMDSegmentValues.at(module->layer()-1).push_back(dAlphaOuterMDSegment);
                    layerBarreldAlphaInnerMDOuterMDValues.at(module->layer()-1).push_back(dAlphaInnerMDOuterMD);
                }
                else if(module->subdet() == SDL::Module::Endcap)
                {
                    endcapdrtValues.push_back(sg->getRtOut());
                    endcapdPhiValues.push_back(sg->getRecoVars["deltaPhi"]);
                    endcapdPhiChangeValues.push_back(sg->getDeltaPhiChange());
                    endcapdAlphaInnerMDSegmentValues.push_back(dAlphaInnerMDSegment);
                    endcapdAlphaOuterMDSegmentValues.push_back(dAlphaOuterMDSegment);
                    endcapdAlphaInnerMDOuterMDValues.push_back(dAlphaInnerMDOuterMD);

                    layerEndcapdrtValues.at(module->layer()-1).push_back(sg->getRtOut());
                    layerEndcapdPhiValues.at(module->layer()-1).push_back(sg->getRecoVars()["deltaPhi"]);
                    layerEndcapdPhiChangeValues.at(module->layer()-1).push_back(sg->getDeltaPhiChange());
                    layerEndcapdAlphaInnerMDSegmentValues.at(module->layer()-1).push_back(dAlphaInnerMDSegment);
                    layerEndcapdAlphaOuterMDSegmentValues.at(module->layer()-1).push_back(dAlphaOuterMDSegment);
                    layerEndcapdAlphaInnerMDOuterMDValues.at(module->layer()-1).push_back(dAlphaInnerMDOuterMD);

                    ringEndcapdrtValues.at(module->ring()-1).push_back(sg->getRtOut());
                    ringEndcapdPhiValues.at(module->ring()-1).push_back(sg->getRecoVars["deltaPhi"]);
                    ringEndcapdPhiChangeValues.at(module->ring()-1).push_back(sg->getDeltaPhiChange());
                    ringEndcapdAlphaInnerMDSegmentValues.at(module->ring()-1).push_back(dAlphaInnerMDSegment);
                    ringEndcapdAlphaOuterMDSegmentValues.at(module->ring()-1).push_back(dAlphaOuterMDSegment);
                    ringEndcapdAlphaInnerMDOuterMDValues.at(module->ring()-1).push_back(dAlphaInnerMDOuterMD);
                }
            }
        }
    }
}
