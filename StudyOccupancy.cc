# include "StudyOccupancy.h"

StudyOccupancy::studyOccupancy(const char *studyName)
{
  studyname = studyName;
  mode = mode_;
}

void StudyOccupancy::bookStudy()
{

}

void StudyOccupancy::doStudy(SDL::Event& event std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents)
{


    //Fetch the occupancies of all modules
    for(auto &module:Event.Modules())
    {
      occupancyInEveryModule[module.detId] = module.getOccupancy()[detId];
    }
}
