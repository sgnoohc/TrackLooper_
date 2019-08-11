# include "StudyOccupancy.h"

StudyOccupancy::studyOccupancy(const char *studyName)
{
  studyname = studyName;
}

void StudyOccupancy::bookStudy()
{
    for(auto &occupancy:occupancyInEveryModule)
    {
      ana.histograms.addHistogram(TString::format("occupancy_in_%u",occupany.first),100,0,100,[&](){return (float)occupancy.first;});
    }

    ana.histogram.addHistogram(TString::format("occupancy_in_barrel"),100,0,100[&](){return averageOccupancyInBarrel;});

    ana.histogram.addHistogram(TString::format("occupancy_in_endcap"),100,0,100[&](){return averageOccupancyInEndcap;});

}

void StudyOccupancy::doStudy(SDL::Event& event std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents)
{
    //Get a list of modules in the event
    occupancyInEveryModule.clear();
    std::vector<SDL::Module*> moduleList = Event.getModulePtrs();
    averageOccupancyInBarrel = 0;
    int nBarrelModules = 0, nEndcapModules = 0;
    //To get the occupancy, iterate through the modules and get the length
    //of the vector of pointers containing the hits on that module
    for(auto &module:moduleList)
    {
      occupancyInEveryModule[module->detId] = (module->getHitPtrs()).size()
      if(module->subdet() == 4) //barrel module
      {
        averageOccupancyInBarrel += (module->getHitPtrs()).size();
        nBarrelModules ++;
      }
      else if(module->subdet == 5) //endcap module
      {
        averageOccupancyInEndcap += (module->getHitPtrs()).size();
        nEndcapModules ++;
      }
    }
    averageOccupancyInBarrel /= nBarrelModules;
    averageOccupancyInEndcap /= nEndcapModules;
}
