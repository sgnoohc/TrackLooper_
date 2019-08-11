# include "StudyOccupancy.h"

StudyOccupancy::StudyOccupancy(const char *studyName)
{
  studyname = studyName;
}

void StudyOccupancy::bookStudy()
{
    for(auto &occupancy:occupancyInEveryModule)
    {
      ana.histograms.addHistogram(TString::Format("occupancy_in_%u",occupancy.first),100,0,100,[&](){return (float)occupancy.second;});
    }

    ana.histograms.addHistogram(TString::Format("occupancy_in_barrel"),100,0,100,[&](){return averageOccupancyInBarrel;});

    ana.histograms.addHistogram(TString::Format("occupancy_in_endcap"),100,0,100,[&](){return averageOccupancyInEndcap;});

}

void StudyOccupancy::doStudy(SDL::Event& event, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents)
{
    //Get a list of modules in the event
    occupancyInEveryModule.clear();
    std::vector<SDL::Module*> moduleList = event.getModulePtrs();
    averageOccupancyInBarrel = 0;
    int nBarrelModules = 0, nEndcapModules = 0;
    //To get the occupancy, iterate through the modules and get the length
    //of the vector of pointers containing the hits on that module
    for(auto &module:moduleList)
    {
      occupancyInEveryModule[module->detId()] = (module->getHitPtrs()).size();
      if(module->subdet() == 4) //barrel module
      {
        averageOccupancyInBarrel += (module->getHitPtrs()).size();
        nBarrelModules ++;
      }
      else if(module->subdet() == 5) //endcap module
      {
        averageOccupancyInEndcap += (module->getHitPtrs()).size();
        nEndcapModules ++;
      }
    }
    averageOccupancyInBarrel /= nBarrelModules;
    averageOccupancyInEndcap /= nEndcapModules;
}
