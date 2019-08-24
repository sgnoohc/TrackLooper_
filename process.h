#ifndef process_h
#define process_h

#include <vector>
#include <map>
#include <tuple>

#include "trktree.h"
#include "rooutil.h"
#include "cxxopts.h"

#include "SDL/Event.h" // SDL::Event
#include "SDL/Module.h" // SDL::Module
#include "SDL/PrintUtil.h" // SDL::out
#include "SDL/EndcapGeometry.h" // SDL::EndcapGeometry
#include "SDL/ModuleConnectionMap.h" // SDL::ModuleConnectionMap

// Efficiency study modules
#include "Study.h"
#include "StudyEfficiency.h"
#include "StudySegmentEfficiency.h"
#include "StudyEndcapInefficiency.h"
#include "StudyBarreldPhiChangeCutThresholdValidity.h"
#include "StudyTrackletEfficiency.h"

#include "constants.h"

#include "AnalysisConfig.h"


void printModuleConnectionInfo();

#endif
