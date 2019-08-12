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
      ana.histograms.addHistogram(TString::format("occupancy_in_layer_%d",i+1),1000,0,100,[&](){return averageLayerOccupancy[i]});

      ana.histograms.addHistogram(TString::format("occupancy_in_barrel_for_layer_%d",i+1),1000,0,100,[&](){return averageBarrelLayerOccupancy[i]});


      ana.histograms.addHistogram(TString::format("occupancy_in_endcap_for_layer_%d",i+1),1000,0,100,[&](){return averageEndcapLayerOccupancy[i]});
    }

}

void StudyOccupancy::doStudy(SDL::Event& event, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents)
{
    //Get a list of modules in the event
    std::vector<SDL::Module*> moduleList = event.getModulePtrs();
    averageOccupancyInBarrel = 0;
    averageOccupancyInEndcap = 0;
    averageLayerOccupancy  = {0,0,0,0,0,0};
    int nLayerModules[] = {0,0,0,0,0,0};
    averageBarrelLayerOccupancy = {0,0,0,0,0,0};
    int nBarrelLayerModules[] = {0,0,0,0,0,0};
    averageEndcapLayerOccupancy = {0,0,0,0,0,0};
    int nEndcapLayerModules[] = {0,0,0,0,0,0};
    int nBarrelModules = 0, nEndcapModules = 0;
    //To get the occupancy, iterate through the modules and get the length
    //of the vector of pointers containing the hits on that module
    for(auto &module:moduleList)
    {
      averageLayerOccupancy[module->layer()] += (module->getHitPtrs()).size();
      nLayerModules[module->layer()]++;
      if(module->subdet() == 4) //barrel module
      {
        averageOccupancyInBarrel += (module->getHitPtrs()).size();
        nBarrelModules ++;

        averageBarrelLayerOccupancy[model->layer()] += (module->getHitPtrs()).size();
        nBarrelLayerModules[model->layer()] ++;
      }
      else if(module->subdet() == 5) //endcap module
      {
        averageOccupancyInEndcap += (module->getHitPtrs()).size();
        nEndcapModules ++;

        averageEndcapLayerOccupancy[model->layer()] += (module->getHitPtrs()).size();
        nEndcapLayerModules[model->layer()] ++;
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
