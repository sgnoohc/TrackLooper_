#ifndef StudyMTVEfficiency_h
#define StudyMTVEfficiency_h

#include "SDL/Event.h"

#include "Study.h"

#include <vector>
#include <tuple>

#include "TString.h"
#include "trktree.h"
#include "constants.h"

#include "AnalysisConfig.h"

#include "trkCore.h"

class StudyMTVEfficiency : public Study
{

public:
    const char* studyname;

    std::vector<float> pt_boundaries;

    std::vector<float> tc_matched_track_pt;
    std::vector<float> tc_all_track_pt;
    std::vector<float> tc_matched_track_eta;
    std::vector<float> tc_all_track_eta;
    std::vector<float> tc_matched_track_dxy;
    std::vector<float> tc_all_track_dxy;
    std::vector<float> tc_matched_track_pt_mtv;
    std::vector<float> tc_all_track_pt_mtv;
    std::vector<float> tc_matched_track_eta_mtv;
    std::vector<float> tc_all_track_eta_mtv;
    std::vector<float> tc_matched_track_dxy_mtv;
    std::vector<float> tc_all_track_dxy_mtv;

    StudyMTVEfficiency(
        const char* studyName,
        std::vector<float> ptbounds);
    virtual void bookStudy();
    virtual void doStudy(SDL::Event& recoevent, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents);

};

#endif
