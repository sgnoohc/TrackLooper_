# include "StudyMDCuts.h"

StudyMDCuts::StudyMDCuts(const char * studyName)
{
    studyName = studyName;
}

void StudyMDCuts::bookStudy()
{
    ana.histograms.addVecHistogram(TString::Format("MD_dz"),400,-20,20,[&](){return dzValues;});
    ana.histograms.addVecHistogram(TString::Format("MD_dPhi"),200,-6.28,6.28,[&](){return dPhiValues;});
    ana.histograms.addVecHistogram(TString::Format("MD_dPhiChange"),200,-6.28,6.28,[&](){return dPhiChangeValues;});


    ana.histograms.addVecHistogram(TString::Format("MD_barrel_dz"),400,-20,20,[&](){return barreldzValues;});
    ana.histograms.addVecHistogram(TString::Format("MD_barrel_dPhi"),200,-6.28,6.28,[&](){return barreldPhiValues;});
    ana.histograms.addVecHistogram(TString::Format("MD_barrel_dPhiChange"),200,-6.28,6.28,[&](){return barreldPhiChangeValues;});


    ana.histograms.addVecHistogram(TString::Format("MD_endcap_dz"),400,-20,20,[&](){return endcapdzValues;});
    ana.histograms.addVecHistogram(TString::Format("MD_endcap_dPhi"),200,-6.28,6.28,[&](){return endcapdPhiValues;});
    ana.histograms.addVecHistogram(TString::Format("MD_endcap_dPhiChange"),200,-6.28,6.28,[&](){return endcapdPhiChangeValues;});

    //one per layer
    for(size_t i = 0; i < 6; i++)
    {
        ana.histograms.addVecHistogram(TString::Format("MD_dz_layer_%ld",i+1),400,-20,20,[&,i](){return layerdzValues[i];});
        ana.histograms.addVecHistogram(TString::Format("MD_dPhi_layer_%ld",i+1),200,-6.28,6.28,[&,i](){return layerdPhiValues[i];});
        ana.histograms.addVecHistogram(TString::Format("MD_dPhiChange_layer_%ld",i+1),200,-6.28,6.28,[&,i](){return layerdPhiChangeValues[i];});


        ana.histograms.addVecHistogram(TString::Format("MD_barrel_dz_layer_%ld",i+1),400,-20,20,[&,i](){return layerBarreldzValues[i];});
        ana.histograms.addVecHistogram(TString::Format("MD_barrel_dPhi_layer_%ld",i+1),200,-6.28,6.28,[&,i](){return layerBarreldPhiValues[i];});
        ana.histograms.addVecHistogram(TString::Format("MD_barrel_dPhiChange_layer_%ld",i+1),200,-6.28,6.28,[&,i](){return layerBarreldPhiChangeValues[i];});

        if(i < 5)
        {
            ana.histograms.addVecHistogram(TString::Format("MD_endcap_dz_layer_%ld",i+1),400,-20,20,[&,i](){return layerEndcapdzValues[i];});
            ana.histograms.addVecHistogram(TString::Format("MD_endcap_dPhi_layer_%ld",i+1),200,-6.28,6.28,[&,i](){return layerEndcapdPhiValues[i];});
            ana.histograms.addVecHistogram(TString::Format("MD_endcap_dPhiChange_layer_%ld",i),200,-6.28,6.28,[&,i](){return layerEndcapdPhiChangeValues[i];});
        }
    }
}

void StudyMDCuts::resetVariables()
{
    dzValues.clear();
    dPhiValues.clear();
    dPhiChangeValues.clear();

    barreldzValues.clear();
    barreldPhiValues.clear();
    barreldPhiChangeValues.clear();

    endcapdzValues.clear();
    endcapdPhiValues.clear();
    endcapdPhiChangeValues.clear();

    layerdzValues.clear();
    layerdPhiValues.clear();
    layerdPhiChangeValues.clear();

    layerBarreldzValues.clear();
    layerBarreldPhiValues.clear();
    layerBarreldPhiChangeValues.clear();

    layerEndcapdzValues.clear();
    layerEndcapdPhiValues.clear();
    layerEndcapdPhiChangeValues.clear();

    for(size_t i = 1; i <= 6; i++)
    {
      layerdzValues.push_back(std::vector<float>());
      layerdPhiValues.push_back(std::vector<float>());
      layerdPhiChangeValues.push_back(std::vector<float>());

      layerBarreldzValues.push_back(std::vector<float>());
      layerBarreldPhiValues.push_back(std::vector<float>());
      layerBarreldPhiChangeValues.push_back(std::vector<float>());

      if(i < 6)
      {
          layerEndcapdzValues.push_back(std::vector<float>());
          layerEndcapdPhiValues.push_back(std::vector<float>());
          layerEndcapdPhiChangeValues.push_back(std::vector<float>());
      }
    }
}

void StudyMDCuts::doStudy(SDL::Event &event,std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents)
{
    resetVariables();

    float dzCut = 10.0;
    std::vector<SDL::Module*> moduleList = event.getLowerModulePtrs();
    for(auto &module:moduleList)
    {
        std::vector<SDL::MiniDoublet*> miniDoublets = module->getMiniDoubletPtrs();
        for(auto &md:miniDoublets)
        {

            //Step 1 : Reproducing Philip's plots
            //md->runMiniDoubletAlgo(SDL::Default_MDAlgo);

            dzValues.push_back(md->getDz());
            dPhiValues.push_back(md->getDeltaPhi());
            dPhiChangeValues.push_back(md->getDeltaPhiChange());

            layerdzValues.at(module->layer()-1).push_back(md->getDz());
            layerdPhiValues.at(module->layer()-1).push_back(md->getDeltaPhi());
            layerdPhiChangeValues.at(module->layer()-1).push_back(md->getDeltaPhiChange());


            if(module->subdet() == SDL::Module::Barrel)
            {

                barreldzValues.push_back(md->getDz());
                barreldPhiValues.push_back(md->getDeltaPhi());
                barreldPhiChangeValues.push_back(md->getDeltaPhiChange());

                layerBarreldzValues.at(module->layer()-1).push_back(md->getDz());
                layerBarreldPhiValues.at(module->layer()-1).push_back(md->getDeltaPhi());
                layerBarreldPhiChangeValues.at(module->layer()-1).push_back(md->getDeltaPhiChange());
            }

            else if(module->subdet() == SDL::Module::Endcap)
            {

                endcapdzValues.push_back(md->getDz());
                endcapdPhiValues.push_back(md->getDeltaPhi());
                endcapdPhiChangeValues.push_back(md->getDeltaPhiChange());

                layerEndcapdzValues.at(module->layer()-1).push_back(md->getDz());
                layerEndcapdPhiValues.at(module->layer()-1).push_back(md->getDeltaPhi());
                layerEndcapdPhiChangeValues.at(module->layer()-1).push_back(md->getDeltaPhiChange());
            }
        }
    }
}
