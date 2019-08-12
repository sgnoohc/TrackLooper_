# include "StudyOccupancy.h"

StudyOccupancy::StudyOccupancy(const char *studyName)
{
  studyname = studyName;
}

void StudyOccupancy::bookStudy()
{

    ana.histograms.addHistogram(TString::Format("occupancy_in_barrel"),1000,0,100,[&](){return averageOccupancyInBarrel;});

    ana.histograms.addHistogram(TString::Format("occupancy_in_endcap"),1000,0,100,[&](){return averageOccupancyInEndcap;});

    for(int i = 0; i<6; i++)
    {
      ana.histograms.addHistogram(TString::Format("occupancy_in_layer_%d",i+1),1000,0,100,[&,i](){return averageLayerOccupancy[i];});

      ana.histograms.addHistogram(TString::Format("occupancy_in_barrel_for_layer_%d",i+1),1000,0,100,[&,i](){return averageBarrelLayerOccupancy[i];});


      ana.histograms.addHistogram(TString::Format("occupancy_in_endcap_for_layer_%d",i+1),1000,0,100,[&,i](){return averageEndcapLayerOccupancy[i];});
    }

}

void StudyOccupancy::doStudy(SDL::Event& event, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents)
{
    //Get a list of modules in the event
    std::vector<SDL::Module*> moduleList = event.getModulePtrs();
    averageOccupancyInBarrel = 0;
    averageOccupancyInEndcap = 0;
    averageLayerOccupancy.clear();
    averageLayerOccupancy  = {0,0,0,0,0,0};
    std::vector<int> nLayerModules = {0,0,0,0,0,0};
    averageBarrelLayerOccupancy.clear();
    averageBarrelLayerOccupancy = {0,0,0,0,0,0};
    std::vector<int>nBarrelLayerModules = {0,0,0,0,0,0};
    averageEndcapLayerOccupancy.clear();
    averageEndcapLayerOccupancy = {0,0,0,0,0,0};
    std::vector<int> nEndcapLayerModules = {0,0,0,0,0,0};
    int nBarrelModules = 0, nEndcapModules = 0;
    //To get the occupancy, iterate through the modules and get the length
    //of the vector of pointers containing the hits on that module
    for(auto &module:moduleList)
    {
      averageLayerOccupancy.at(module->layer()-1) += (module->getHitPtrs()).size();
      nLayerModules.at(module->layer()-1)++;
      if(module->subdet() == SDL::Module::Barrel) //barrel module
      {
        averageOccupancyInBarrel += (module->getHitPtrs()).size();
        nBarrelModules ++;

        averageBarrelLayerOccupancy.at(module->layer()-1) += (module->getHitPtrs()).size();
        nBarrelLayerModules.at(module->layer()-1) ++;
      }
      else if(module->subdet() == SDL::Module::Endcap) //endcap module
      {
        averageOccupancyInEndcap += (module->getHitPtrs()).size();
        nEndcapModules ++;

        averageEndcapLayerOccupancy.at(module->layer()-1) += (module->getHitPtrs()).size();
        nEndcapLayerModules.at(module->layer()-1) ++;
      }
    }

    averageOccupancyInBarrel = (nBarrelModules != 0) ? averageOccupancyInBarrel / nBarrelModules : 0;
    averageOccupancyInEndcap = (nEndcapModules != 0) ? averageOccupancyInEndcap / nEndcapModules : 0;

    for(int i=0;i<6;i++)
    {

      averageBarrelLayerOccupancy[i] = (nBarrelLayerModules[i] != 0) ? averageBarrelLayerOccupancy[i]/nBarrelLayerModules[i] : 0;

      averageEndcapLayerOccupancy[i] = (nEndcapLayerModules[i] != 0) ? averageEndcapLayerOccupancy[i]/nEndcapLayerModules[i] : 0;

      averageLayerOccupancy[i] = (nLayerModules[i] != 0) ? averageLayerOccupancy[i]/nLayerModules[i] : 0;
    }
}
