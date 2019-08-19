# include "StudyLinkedModule.h"

StudyLinkedModule::StudyLinkedModule(const char* studyName)
{
  studyname = studyName;
}

void StudyLinkedModule::bookstudy()
{

  ana.histograms.addVecHistogram(TString::Format("Linked_MD_occupancy_in_barrel"),1000,0,100,[&](){return BarrelLinkedModuleOccupancy;});

    ana.histograms.addHistogram(TString::Format("average_Linked_MD_occupancy_in_barrel"),1000,0,100,[&](){return averageEndcapLinkedModuleOccupancy;});

    ana.histograms.addVecHistogram(TString::Format("Linked_MD_occupancy_in_endcap"),1000,0,100,[&](){return EndcapLinkedModuleOccupancy;});

    ana.histograms.addHistogram(TString::Format("average_Linked_MD_occupancy_in_endcap"),1000,0,100,[&](){return averageEndcapLinkedModuleOccupancy;});

    for(int i = 0; i<6; i++)
    {
      ana.histograms.addHistogram(TString::Format("average_Linked_MD_occupancy_in_barrel_for_layer_%d",i+1),1000,0,100,[&,i](){return averageLayerBarrelLinkedModuleOccupancy[i];});

      ana.histograms.addVecHistogram(TString::Format("Linked_MD_occupancy_in_barrel_for_layer_%d",i+1),1000,0,100,[&,i](){return BarrelLinkedModuleOccupancy.at(i);});

      ana.histograms.addHistogram(TString::Format("average_Linked_MD_occupancy_in_endcap_for_layer_%d",i+1),1000,0,100,[&,i](){return EndcapLinkedModuleOccupancy[i];});

      ana.histograms.addVecHistogram(TString::Format("Linked_MD_occupancy_in_endcap_for_layer_%d",i+1),1000,0,100,[&,i](){return EndcapLinkedModuleOccupancy.at(i);});
    }


    for(int i=0;i<15;i++)
    {
      ana.histograms.addHistogram(TString::Format("average_Linked_MD_occupancy_in_endcap_for_ring_%d",i+1),1000,0,100,[&,i](){return averageEndcapRingLinkedModuleOccupancy[i];});

      ana.histograms.addVecHistogram(TString::Format("Linked_MD_occupancy_in_endcap_for_ring_%d",i+1),1000,0,100,[&,i](){return RingEndcapLinkedModuleOccupancy.at(i);});
    }
}


void StudyLinkedModule::doStudy(SDL::Event &event,std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents)
{

    averageBarrelLinkedModuleOccupancy = 0;
    averageEndcapLinkedModuleOccupancy = 0;
    int nBarrelModules = 0,nEndcapModules = 0;
    LayerBarrelLinkedModuleOccupancy.clear();
    LayerEndcapLinkedModuleOccupancy.clear();

    averageLayerBarrelLinkedModuleOccupancy.clear();
    averageLayerBarrelLinkedModuleOccupancy = {0,0,0,0,0,0};
    std::vector<int> nBarrelLayerModules(6,0);
    std::vector<int> nEndcapLayerModules(6,0);
    averageLayerEndcapLinkedModuleOccupancy.clear();
    averageLayerEndcapLinkedModuleOccupancy = {0,0,0,0,0,0};
    averageEndcapRingLinkedModuleOccupancy.clear();
    for(int i=0;i<15;i++)
      averageEndcapRingLinkedModuleOccupancy.push_back(0);
    std::vector<int> nEndcapRingModules(15,0);

    LayerBarrelLinkedModuleOccupancy.clear();
    LayerEndcapLinkedModuleOccupancy.clear();
    RingEndcapLinkedModuleOccupancy.clear();

    for(int i=0;i<6;i++)
    {
      LayerBarrelLinkedModuleOccupancy.push_back(std::vector<float>());
      LayerEndcapLinkedModuleOccupancy.push_back(std::vector<float>());
    }

    for(int i=0;i<15;i++)
    {
      RingEndcapLinkedModuleOccupancy.push_back(std::vector<float>());
    }



    std::vector<SDL::Module*> moduleList = event.getModulePtrs();

    for(auto &module:moduleList)
    {
      std::vector<unsigned int> connectedModuleDetIds = moduleConnectionMap.getConnectedModuledetIds(module.detId());
      int nConnectedModules = 0, connectedModuleOccupancy = 0;
      for(auto &connectedModuleId:connectedModuledetIds)
      {
        SDL::Module connectedModule = getModule(connectedModuleId);
        //Now start the occupancy thing
        connectedModuleOccupancy += connectedModule->getMiniDoubletPtrs().size();
        nConnectedModules ++;
      }

      if(module->subdet() == SDL::Module::Barrel)
      {
        BarrelLinkedModuleOccupancy.push_back(connectedModuleOccupancy);
        averageBarrelLinkedModuleOccupancy += connectedModuleOccupancy;
        nBarrelModules++;

        LayerBarrelLinkedModuleOccupancy.at(module->layer() -1).push_back(connectedModuleOccupancy);
        averageLayerBarrelLinkedModuleOccupancy.at(module->layer()-1) += connectedModuleOccupancy;
        nBarrelLayerModules.at(module->layer()-1)++;
      }
      else if(module->subdet() = SDL::Module::Endcap)
      {
        EndcapLinkedModuleOccupancy.push_back(connectedModuleOccupancy);
        averageEndcapLinkedModuleOccupancy += connectedModuleOccupancy;
        nEndcapModules++;

        LayerEndcapLinkedModuleOccupancy.at(module->layer()-1).push_back(connectedModuleOccupancy);
        averageLayerEndcapLinkedModuleOccupancy.at(module->layer()-1) += connectedModuleOccupancy;
        nEndcapLayerModules.at(module->layer()-1)++;

        RingEndcapLinkedModuleOccupancy.at(module->ring()-1).push_back(connectedModuleOccupancy);
        averageEndcapRingLinkedModuleOccupancy.at(module->ring()-1) += connectedModuleOccupancy;
        nEndcapRingModules.at(module->ring()-1) ++;
      }
    }

    averageBarrelLinkedModuleOccupancy = (nBarrelModules != 0) ? averageBarrelLinkedModuleOccupancy / nBarrelModules : 0;
    averageEndcapLinkedModuleOccupancy = (nEndcapModules != 0) ? averageEndcapLinkedModuleOccupancy / nEndcapModules : 0;

    for(int i=0;i<6;i++)
    {
      averageLayerBarrelLinkedModuleOccupancy[i] = (nBarrelLayerModules[i] != 0) ? averageLayerBarrelLinkedModuleOccupancy[i]/nBarrelLayerModules[i] : 0;

      averageLayerEndcapLinkedModuleOccupancy[i] = (nEndcapLayerModules[i] != 0) ? averageLayerEndcapLinkedModuleOccupancy[i]/nEndcapLayerModules[i] : 0;

    }

    for(int i=0;i<15;i++)
    {
      averageEndcapRingLinkedModuleOccupancy.at(i) = (nEndcapRingModules.at(i) !=0) ? averageEndcapRingLinkedModuleOccupancy.at(i)/nEndcapRingModules.at(i) : 0;
    }
}
