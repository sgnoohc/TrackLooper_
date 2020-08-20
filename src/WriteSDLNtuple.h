#ifndef WriteSDLNtuple_h
#define WriteSDLNtuple_h

#include "SDL/Event.h"

#include "Study.h"

#include <vector>
#include <tuple>

#include "TString.h"
#include "trktree.h"
#include "constants.h"

#include "AnalysisConfig.h"

#include "trkCore.h"

#include "SDLMath.h"

#include "SDL/MathUtil.h"

#include <cppitertools/itertools.hpp>

class WriteSDLNtuple : public Study
{

public:
    const char* studyname;

    WriteSDLNtuple(const char* studyName);

    virtual void bookStudy();
    virtual void doStudy(SDL::Event& recoevent, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents);

    void createHitsSimHitsSimTracksBranches();
    void createMiniDoubletBranches();
    void createSegmentBranches();
    void createTripletBranches();
    void createTrackletBranches();
    void createTrackCandidateBranches();

    void setHitsSimHitsSimTracksBranches();
    void setMiniDoubletBranches(SDL::Event& recoevent);
    void setSegmentBranches(SDL::Event& recoevent);
    void setTripletBranches(SDL::Event& recoevent);
    void setTrackletBranches(SDL::Event& recoevent);
    void setTrackCandidateBranches(SDL::Event& recoevent);

};

#endif
