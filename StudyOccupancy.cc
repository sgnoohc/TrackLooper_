# include "StudyOccupancy.h"

StudyOccupancy::StudyOccupancy(const char *studyName)
{
  studyname = studyName;
}

void StudyOccupancy::bookStudy()
{

    ana.histograms.addHistogram(TString::Format("occupancy_in_barrel"),100,0,100,[&](){return averageOccupancyInBarrel;});

    ana.histograms.addHistogram(TString::Format("occupancy_in_endcap"),100,0,100,[&](){return averageOccupancyInEndcap;});

}

void StudyOccupancy::doStudy(SDL::Event& event, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents)
{
    //Get a list of modules in the event
    std::vector<SDL::Module*> moduleList = event.getModulePtrs();
    averageOccupancyInBarrel = 0;
    averageOccupancyInEndcap = 0;
    int nBarrelModules = 0, nEndcapModules = 0;
    //To get the occupancy, iterate through the modules and get the length
    //of the vector of pointers containing the hits on that module
    for(auto &module:moduleList)
    {
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

    averageOccupancyInBarrel = (nBarrelModules != 0) ? averageOccupancyInBarrel / nBarrelModules : 0;
    averageOccupancyInEndcap = (nEndcapModules != 0) ? averageOccupancyInEndcap / nEndcapModules : 0;

    std::cout<<"average occupancy in barrel="<<averageOccupancyInBarrel<<std::endl;
    std::cout<<"average occupancy in endcap="<<averageOccupancyInEndcap<<std::endl;
}
