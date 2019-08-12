#ifndef StudyOccupancy_h
#define StudyOccupancy_h

# include "SDL/Event.h"
# include "Study.h"
# include <vector>
# include <tuple>

# include "TString.h"
# include "trktree.h"
# include "constants.h"

# include "AnalysisConfig.h"

class StudyOccupancy : public Study
{
public:
  const char * studyname;

  float averageOccupancyInBarrel;
  float averageOccupancyInEndcap;
  std::vector<float> averageLayerOccupancy;
  std::vector<float> averageBarrelLayerOccupancy;
  std::vector<float> averageEndcapLayerOccupancy;

  StudyOccupancy(const char * studyName);
  virtual void bookStudy();
  virtual void doStudy(SDL::Event& event, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents);
};

#endif
