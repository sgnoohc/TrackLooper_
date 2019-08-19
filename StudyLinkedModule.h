# ifndef StudyMDOccupancy_h
#define StudyMDOccupancy_h

# include "Study.h"
# include "SDL/Event.h"
# include <vector>
# include <tuple>

# include "TString.h"
# include "trktree.h"
# include "constants.h"

# include "AnalysisConfig.h"

class StudyLinkedModule : public Study
{
  public:
    const char *studyname;
    std::vector<float> BarrelLinkedModuleOccupancy;
    std::vector<float> EndcapLinkedModuleOccupancy;
    float averageBarrelLinkedModuleOccupancy;
    float averageEndcapLinkedModuleOccupancy;

    std::vector<std::vector<float>> LayerBarrelLinkedModuleOccupancy;
    std::vector<float> averageLayerBarrelLinkedModuleOccupancy;
    std::vector<std::vector<float>> LayerEndcapLinkedModuleOccupancy;
    std::vector<float> averageLayerEndcapLinkedModuleOccupancy;
    std::vector<std::vector<float>> RingEndcapLinkedModuleOccupancy;
    std::vector<float> averageEndcapRingLinkedModuleOccupancy;

    StudyLinkedModule(const char* studyName);
    virtual void bookStudy();
    virtual void doStudy(SDL::Event &event,std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents);
};
