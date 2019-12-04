#ifndef StudySegmentCuts_h
#define StudySegmentCuts_h

# include "Study.h"
# include "SDL/Event.h"
# include "SDL/Segment.h"
# include <vector>
# include <tuple>

# include "TString.h"
# include "trktree.h"
# include "constants.h"

# include "AnalysisConfig.h"

class StudySegmentCuts : public Study
{
    public:
        const char * studyName;

        std::vector<float> dzValues;
        std::vector<float> dPhiValues;
        std::vector<float> dPhiChangeValues;
        std::vector<float> dAlphaInnerMDSegmentValues;
        std::vector<float> dAlphaOuterMDSegmentValues;
        std::vector<float> dAlphaInnerMDOuterMDValues;
        //one vector per layer
        std::vector<std::vector<float>> layerdzValues;
        std::vector<std::vector<float>> layerdPhiValues;
        std::vector<std::vector<float>> layerdPhiChangeValues;
        std::vector<std::vector<float>> layerdAlphaInnerMDSegmentValues;
        std::vector<std::vector<float>> layerdAlphaOuterMDSegmentValues;
        std::vector<std::vector<float>> layerdAlphaInnerMDOuterMDValues;

        std::vector<float> barreldzValues;
        std::vector<float> barreldPhiValues;
        std::vector<float> barreldPhiChangeValues;
        std::vector<float> barreldAlphaInnerMDSegmentValues;
        std::vector<float> barreldAlphaOuterMDSegmentValues;
        std::vector<float> barreldAlphaInnerMDOuterMDValues;
        //one vector per layer
        std::vector<std::vector<float>> layerBarreldzValues;
        std::vector<std::vector<float>> layerBarreldPhiValues;
        std::vector<std::vector<float>> layerBarreldPhiChangeValues;
        std::vector<std::vector<float>> layerBarreldAlphaInnerMDSegmentValues;
        std::vector<std::vector<float>> layerBarreldAlphaOuterMDSegmentValues;
        std::vector<std::vector<float>> layerBarreldAlphaInnerMDOuterMDValues;

        std::vector<float> endcapdrtValues;
        std::vector<float> endcapdPhiValues;
        std::vector<float> endcapdPhiChangeValues;
        std::vector<float> endcapdAlphaInnerMDSegmentValues;
        std::vector<float> endcapdAlphaOuterMDSegmentValues;
        std::vector<float> endcapdAlphaInnerMDOuterMDValues;
        //one vector per layer
        std::vector<std::vector<float>> layerEndcapdrtValues;
        std::vector<std::vector<float>> layerEndcapdPhiValues;
        std::vector<std::vector<float>> layerEndcapdPhiChangeValues;
        std::vector<std::vector<float>> layerEndcapdAlphaInnerMDSegmentValues;
        std::vector<std::vector<float>> layerEndcapdAlphaOuterMDSegmentValues;
        std::vector<std::vector<float>> layerEndcapdAlphaInnerMDOuterMDValues;
        //ring
        std::vector<std::vector<float>> ringEndcapdrtValues;
        std::vector<std::vector<float>> ringEndcapdPhiValues;
        std::vector<std::vector<float>> ringEndcapdPhiChangeValues;
        std::vector<std::vector<float>> ringEndcapdAlphaInnerMDSegmentValues;
        std::vector<std::vector<float>> ringEndcapdAlphaOuterMDSegmentValues;
        std::vector<std::vector<float>> ringEndcapdAlphaInnerMDOuterMDValues;
 
        

        StudySegmentCuts(const char * studyName);
        virtual void bookStudy();
        virtual void resetVariables();
        virtual void doStudy(SDL::Event &event, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents);

};

#endif
