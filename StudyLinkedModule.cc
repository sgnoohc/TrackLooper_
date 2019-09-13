# include "StudyLinkedModule.h"

StudyLinkedModule::StudyLinkedModule(const char* studyName)
{
  studyname = studyName;
}

void StudyLinkedModule::bookStudy()
{

    ana.histograms.addVecHistogram(TString::Format("Linked_MD_occupancy_in_barrel"),100,0,100,[&](){return BarrelLinkedModuleOccupancy;});
    ana.histograms.addVecHistogram(TString::Format("Linked_MD_occupancy_in_endcap"),100,0,100,[&](){return EndcapLinkedModuleOccupancy;});

    ana.histograms.addHistogram(TString::Format("average_number_of_Linked_modules_in_barrel"),100,0,100,[&](){return nBarrelAverageLinkedModules;});
    ana.histograms.addVecHistogram(TString::Format("number_of_Linked_modules_in_barrel"),100,0,100,[&](){return nBarrelLinkedModules;});
    ana.histograms.addHistogram(TString::Format("average_number_of_Linked_modules_in_endcap"),100,0,100,[&](){return nEndcapAverageLinkedModules;});
    ana.histograms.addVecHistogram(TString::Format("number_of_Linked_modules_in_endcap"),100,0,100,[&](){return nEndcapLinkedModules;});

    ana.histograms.addHistogram(TString::Format("average_Linked_MD_occupancy_in_barrel"),1000,0,100,[&](){return averageBarrelLinkedModuleOccupancy;});
    ana.histograms.addHistogram(TString::Format("average_Linked_MD_occupancy_in_endcap"),1000,0,100,[&](){return averageEndcapLinkedModuleOccupancy;});

    for(int i = 0; i<6; i++)
    {
        
        ana.histograms.addVecHistogram(TString::Format("Linked_MD_occupancy_in_barrel_for_layer_%d",i+1),100,0,100,[&,i](){return LayerBarrelLinkedModuleOccupancy.at(i);});
        ana.histograms.addVecHistogram(TString::Format("Linked_MD_occupancy_in_endcap_for_layer_%d",i+1),1000,0,100,[&,i](){return LayerEndcapLinkedModuleOccupancy.at(i);});
  

        ana.histograms.addHistogram(TString::Format("average_Linked_MD_occupancy_in_endcap_for_layer_%d",i+1),1000,0,100,[&,i](){return averageLayerEndcapLinkedModuleOccupancy[i];});
        ana.histograms.addHistogram(TString::Format("average_Linked_MD_occupancy_in_barrel_for_layer_%d",i+1),1000,0,100,[&,i](){return averageLayerBarrelLinkedModuleOccupancy[i];});


      
        ana.histograms.addHistogram(TString::Format("average_number_of_Linked_modules_in_barrel_for_layer_%d",i+1),100,0,100,[&,i](){return nLayerBarrelAverageLinkedModules.at(i);});
        ana.histograms.addHistogram(TString::Format("average_number_of_Linked_modules_in_endcap_for_layer_%d",i+1),100,0,100,[&,i](){return nLayerEndcapAverageLinkedModules.at(i);});
        ana.histograms.addVecHistogram(TString::Format("number_of_Linked_modules_in_barrel_for_layer_%d",i+1),100,0,100,[&,i](){return nLayerBarrelLinkedModules.at(i);});
        ana.histograms.addVecHistogram(TString::Format("number_of_Linked_modules_in_endcap_for_layer_%d",i+1),100,0,100,[&,i](){return nLayerEndcapLinkedModules.at(i);});

    }


    for(int i=0;i<15;i++)
    {
        ana.histograms.addVecHistogram(TString::Format("Linked_MD_occupancy_in_endcap_for_ring_%d",i+1),100,0,100,[&,i](){return RingEndcapLinkedModuleOccupancy.at(i);});

        ana.histograms.addHistogram(TString::Format("average_number_of_Linked_Modules_in_endcap_for_ring_%d",i+1),100,0,100,[&,i](){return nRingEndcapAverageLinkedModules.at(i);});
        ana.histograms.addVecHistogram(TString::Format("number_of_Linked_modules_in_endcap_for_ring_%d",i+1),100,0,100,[&,i](){return nRingEndcapLinkedModules.at(i);});
        
        ana.histograms.addHistogram(TString::Format("average_Linked_MD_occupancy_in_endcap_for_ring_%d",i+1),1000,0,100,[&,i](){return averageEndcapRingLinkedModuleOccupancy[i];});

    }

    //2D layer-ring histogram of zero modules
    //
    ana.histograms.add2DVecHistogram("zero_connected_module_ring",15,0,15,"layer",6,0,6,[&](){return zeroConnectedModuleEndcapRing;},[&](){return zeroConnectedModuleEndcapLayer;});
}


void StudyLinkedModule::prepareStudy()
{

    nBarrelPrimaryModules = 0;
    nEndcapPrimaryModules = 0;

    averageBarrelLinkedModuleOccupancy = 0;
    averageEndcapLinkedModuleOccupancy = 0;
    nBarrelAverageLinkedModules = 0;
    nEndcapAverageLinkedModules = 0;

    BarrelLinkedModuleOccupancy.clear();
    EndcapLinkedModuleOccupancy.clear();
    nBarrelLinkedModules.clear();
    nEndcapLinkedModules.clear();


    averageLayerBarrelLinkedModuleOccupancy.clear();
    averageLayerBarrelLinkedModuleOccupancy = {0,0,0,0,0,0};    

    nBarrelLayerPrimaryModules.clear();
    nEndcapLayerPrimaryModules.clear();
    nBarrelLayerPrimaryModules = {0,0,0,0,0,0};
    nEndcapLayerPrimaryModules = {0,0,0,0,0,0};

    nLayerBarrelAverageLinkedModules.clear();
    nLayerBarrelAverageLinkedModules = {0,0,0,0,0,0};

    averageLayerEndcapLinkedModuleOccupancy.clear();
    averageLayerEndcapLinkedModuleOccupancy = {0,0,0,0,0,0};

    nLayerEndcapAverageLinkedModules.clear();
    nLayerEndcapAverageLinkedModules = {0,0,0,0,0,0};
    nEndcapRingPrimaryModules.clear();

    averageEndcapRingLinkedModuleOccupancy.clear();

    nRingEndcapAverageLinkedModules.clear();

    for(int i=0;i<15;i++)
    {
      averageEndcapRingLinkedModuleOccupancy.push_back(0);
      nRingEndcapAverageLinkedModules.push_back(0);
      nEndcapRingPrimaryModules.push_back(0);
    }

    
    LayerBarrelLinkedModuleOccupancy.clear();
    LayerEndcapLinkedModuleOccupancy.clear();
    RingEndcapLinkedModuleOccupancy.clear();

    nLayerBarrelLinkedModules.clear();
    nLayerEndcapLinkedModules.clear();
    nRingEndcapLinkedModules.clear();

    for(int i=0;i<6;i++)
    {
      LayerBarrelLinkedModuleOccupancy.push_back(std::vector<float>());
      LayerEndcapLinkedModuleOccupancy.push_back(std::vector<float>());

      nLayerBarrelLinkedModules.push_back(std::vector<float>());
      nLayerEndcapLinkedModules.push_back(std::vector<float>());
    }

    for(int i=0;i<15;i++)
    {
      RingEndcapLinkedModuleOccupancy.push_back(std::vector<float>());

      nRingEndcapLinkedModules.push_back(std::vector<float>());
    }

    zeroConnectedModuleEndcapLayer.clear();
    zeroConnectedModuleEndcapRing.clear();

}

void StudyLinkedModule::doStudy(SDL::Event &event,std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents)

{

//Separated the init here because there are lot of vectors to initialize
    prepareStudy();

    std::vector<SDL::Module*> moduleList = event.getModulePtrs();

    for(auto &module:moduleList)
    {
        std::vector<unsigned int> connectedModuleDetIds = SDL::moduleConnectionMap.getConnectedModuleDetIds(module->detId());
        int nConnectedModules = 0, connectedModuleOccupancy = 0;
        for(auto &connectedModuleId:connectedModuleDetIds)
        {
            SDL::Module& connectedModule = event.getModule(connectedModuleId);
            //Now start the occupancy thing
            connectedModuleOccupancy += connectedModule.getMiniDoubletPtrs().size();
            nConnectedModules ++;
        }

        if(module->subdet() == SDL::Module::Barrel)
        {
            if((module->getMiniDoubletPtrs()).size() != 0)
            {
                nBarrelAverageLinkedModules += nConnectedModules;
                nLayerBarrelAverageLinkedModules.at(module->layer()-1) += nConnectedModules;

                nBarrelLinkedModules.push_back(nConnectedModules);
                nLayerBarrelLinkedModules.at(module->layer()-1).push_back(nConnectedModules);

                BarrelLinkedModuleOccupancy.push_back(connectedModuleOccupancy);
                averageBarrelLinkedModuleOccupancy += connectedModuleOccupancy;
                nBarrelPrimaryModules++;

                LayerBarrelLinkedModuleOccupancy.at(module->layer() -1).push_back(connectedModuleOccupancy);
                averageLayerBarrelLinkedModuleOccupancy.at(module->layer()-1) += connectedModuleOccupancy;
                nBarrelLayerPrimaryModules.at(module->layer()-1)++;
            }
        }
        else if(module->subdet() == SDL::Module::Endcap)
        {
            if((module->getMiniDoubletPtrs()).size() != 0)
            {
                nEndcapAverageLinkedModules += nConnectedModules;
                nLayerEndcapAverageLinkedModules.at(module->layer()-1) += nConnectedModules;
                nRingEndcapAverageLinkedModules.at(module->ring()-1) += nConnectedModules;

                nEndcapLinkedModules.push_back(nConnectedModules);
                nLayerEndcapLinkedModules.at(module->layer()-1).push_back(nConnectedModules);
                nRingEndcapLinkedModules.at(module->ring()-1).push_back(nConnectedModules);

                EndcapLinkedModuleOccupancy.push_back(connectedModuleOccupancy);
                averageEndcapLinkedModuleOccupancy += connectedModuleOccupancy;
                nEndcapPrimaryModules++;

                LayerEndcapLinkedModuleOccupancy.at(module->layer()-1).push_back(connectedModuleOccupancy);
                averageLayerEndcapLinkedModuleOccupancy.at(module->layer()-1) += connectedModuleOccupancy;
                nEndcapLayerPrimaryModules.at(module->layer()-1)++;

                RingEndcapLinkedModuleOccupancy.at(module->ring()-1).push_back(connectedModuleOccupancy);
                averageEndcapRingLinkedModuleOccupancy.at(module->ring()-1) += connectedModuleOccupancy;
                nEndcapRingPrimaryModules.at(module->ring()-1) ++;

                //Zero connected modules
                if(nConnectedModules == 0)
                {
                    zeroConnectedModuleLayer.push_back(module->layer());
                    zeroConnectedModuleRing.push_back(module->ring());
                }
            }
        }

    }

    averageBarrelLinkedModuleOccupancy = (nBarrelPrimaryModules != 0) ? averageBarrelLinkedModuleOccupancy / nBarrelPrimaryModules : 0;
    averageEndcapLinkedModuleOccupancy = (nEndcapPrimaryModules != 0) ? averageEndcapLinkedModuleOccupancy / nEndcapPrimaryModules : 0;

    nBarrelAverageLinkedModules = (nBarrelPrimaryModules != 0) ? nBarrelAverageLinkedModules/nBarrelPrimaryModules : 0;
    nEndcapAverageLinkedModules = (nEndcapPrimaryModules != 0) ? nEndcapAverageLinkedModules/nEndcapPrimaryModules : 0;

    for(int i=0;i<6;i++)
    {
        averageLayerBarrelLinkedModuleOccupancy[i] = (nBarrelLayerPrimaryModules[i] != 0) ? averageLayerBarrelLinkedModuleOccupancy[i]/nBarrelLayerPrimaryModules[i] : 0;
    
        averageLayerEndcapLinkedModuleOccupancy[i] = (nEndcapLayerPrimaryModules[i] != 0) ? averageLayerEndcapLinkedModuleOccupancy[i]/nEndcapLayerPrimaryModules[i] : 0;

        nLayerBarrelAverageLinkedModules[i] = (nBarrelLayerPrimaryModules[i] != 0) ? nLayerBarrelAverageLinkedModules[i]/nBarrelLayerPrimaryModules[i] : 0;

        nLayerEndcapAverageLinkedModules[i] = (nEndcapLayerPrimaryModules[i] != 0) ? nLayerEndcapAverageLinkedModules[i]/nEndcapLayerPrimaryModules[i] : 0;

    }

    for(int i=0;i<15;i++)
    {
        averageEndcapRingLinkedModuleOccupancy.at(i) = (nEndcapRingPrimaryModules.at(i) !=0) ? averageEndcapRingLinkedModuleOccupancy.at(i)/nEndcapRingPrimaryModules.at(i) : 0;

        nRingEndcapAverageLinkedModules[i] = (nEndcapRingPrimaryModules.at(i) != 0) ? nRingEndcapAverageLinkedModules[i]/nEndcapRingPrimaryModules.at(i) : 0;
    }
}
