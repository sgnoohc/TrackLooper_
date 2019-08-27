# ifndef StudyLinkedModule_h
#define StudyLinkedModule_h

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
    std::vector<int> nBarrelLinkedModules;
    std::vector<int> nEndcapLinkedModules;

    float averageBarrelLinkedModuleOccupancy;
    float averageEndcapLinkedModuleOccupancy;

    int nBarrelAverageLinkedModules,nEndcapAverageLinkedModules;

    std::vector<std::vector<float>> LayerBarrelLinkedModuleOccupancy;
    std::vector<std::vector<int>> nLayerBarrelLinkedModules;

    std::vector<int> nLayerBarrelAverageLinkedModules;
    std::vector<float> averageLayerBarrelLinkedModuleOccupancy;

    std::vector<std::vector<float>> LayerEndcapLinkedModuleOccupancy;
    std::vector<std::vector<int>> nLayerEndcapLinkedModules;

    std::vector<int> nLayerEndcapAverageLinkedModules;
    std::vector<float> averageLayerEndcapLinkedModuleOccupancy;

    std::vector<std::vector<float>> RingEndcapLinkedModuleOccupancy;
    std::vector<std::vector<int>> nRingEndcapLinkedModules;

    std::vector<int> nRingEndcapAverageLinkedModules;
    std::vector<float> averageEndcapRingLinkedModuleOccupancy;

    int nBarrelPrimaryModules, nEndcapPrimaryModules;
    std::vector<int> nBarrelLayerPrimaryModules;
    std::vector<int> nEndcapLayerPrimaryModules;
    std::vector<int> nEndcapRingPrimaryModules;



    StudyLinkedModule(const char* studyName);
    virtual void bookStudy();
    virtual void doStudy(SDL::Event &event,std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents);

    void prepareStudy();
};
#endif
