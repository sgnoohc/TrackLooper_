#ifndef StudySimtrackMatchedMDCuts_h
#define StudySimtrackMatchedMDCuts_h

# include "Study.h"
# include "SDL/Event.h"
# include "SDL/MiniDoublet.h"
# include <vector>
# include <tuple>

# include "TString.h"
# include "trktree.h"
# include "constants.h"

# include "AnalysisConfig.h"

class StudySimtrackMatchedMDCuts : public Study
{
    public:
        const char * studyName;
        //both barrel and endcap

        //overall
        std::vector<float> dzValues;
        std::vector<float> dPhiValues;
        std::vector<float> dPhiChangeValues;
        //split by layer - one vector per layer
        std::vector<std::vector<float>> layerdzValues;
        std::vector<std::vector<float>> layerdPhiValues;
        std::vector<std::vector<float>> layerdPhiChangeValues;

        //barrel
        std::vector<float> barreldzValues;
        std::vector<float> barreldPhiValues;
        std::vector<float> barreldPhiChangeValues;
        //split by barrel layer - one vector per layer
        std::vector<std::vector<float>> layerBarreldzValues;
        std::vector<std::vector<float>> layerBarreldPhiValues;
        std::vector<std::vector<float>> layerBarreldPhiChangeValues;

        //endcap
        std::vector<float> endcapdzValues;
        std::vector<float> endcapdrtvalues;
        std::vector<float> endcapdPhiValues;
        std::vector<float> endcapdPhiChangeValues;
        //split by barrel layer - one vector per layer
        std::vector<std::vector<float>> layerEndcapdzValues;
        std::vector<std::vector<float>> layerEndcapdrtValues;
        std::vector<std::vector<float>> layerEndcapdPhiValues;
        std::vector<std::vector<float>> layerEndcapdPhiChangeValues;

        std::vector<std::vector<float>> layerBarrelCenterdPhiValues;
        std::vector<std::vector<float>> layerBarrelNormalTilteddPhiValues;
        std::vector<std::vector<float>> layerBarrelEndcapTilteddPhiValues;

        //additional splittings for dPhiChange
        std::vector<std::vector<float>> layerBarrelCenterdPhiChangeValues;
        std::vector<std::vector<float>> layerBarrelNormalTilteddPhiChangeValues;
        std::vector<std::vector<float>> layerBarrelEndcapTilteddPhiChangeValues;




        StudySimtrackMatchedMDCuts(const char * studyName);
        virtual void bookStudy();
        virtual void resetVariables();
        virtual void doStudy(SDL::Event &event, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents);

};

#endif
