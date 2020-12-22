#ifndef trkCore_h
#define trkCore_h

#include "trktree.h"
#include "SDL/Module.h" // SDL::Module
#include "TCanvas.h"
#include "TRandom3.h"
#include "TGraph.h"
#include "TMath.h"
#include "TArc.h"
#include "Math/Functor.h"
#include "Fit/Fitter.h"
#include "AnalysisConfig.h"
#include "SDL/ModuleConnectionMap.h"
#include "SDL/Event.h"
#include "SDL/TrackCandidate.h"
#include "SDL/Tracklet.h"
#include "SDLMath.h"
#include <cppitertools/itertools.hpp>

enum TrackletType {
    BB1BB3 = 0,
    BB2BB4,
    BB3BB5,
    BB1BE3,
    BB2BE4,
    BB3BE5,
    BB1EE3,
    BB2EE4,
    BB3EE5,
    BE1EE3,
    BE2EE4,
    BE3EE5,
    EE1EE3,
    EE2EE4,
};

float simhit_p(unsigned int simhitidx);
float hitAngle(unsigned int simhitidx);
bool isMuonCurlingHit(unsigned int isimtrk, unsigned int ith_hit);
std::tuple<bool, bool, int, int> getDenomSimTrackTypeForAlgoEff(float isimtrk);
bool goodBarrelTrack(unsigned int isimtrk, int pdgid=0);
bool hasAll12HitsInBarrel(unsigned int isimtrk);
bool hasAll12HitsWithNBarrel(unsigned int isimtrk, int nbarrel);
bool hasAll12HitsWithNBarrelUsingModuleMap(unsigned int isimtrk, int nbarrel, bool usesimhits=false);
bool isMTVMatch(unsigned int isimtrk, std::vector<unsigned int> hit_idxs, bool verbose=false);
bool hasAtLeastOneHitPairinEndcapLikeTiltedModule(unsigned short layer, unsigned int isimtrk);
bool is75percentFromSimMatchedHits(std::vector<unsigned int> hit_idxs, int pdgid);
TVector3 linePropagateR(const TVector3& r3, const TVector3& p3, double rDest, int& status, bool useClosest = true, bool verbose = false);
std::pair<TVector3,TVector3> helixPropagateApproxR(const TVector3& r3, const TVector3& p3, double rDest, int q, int& status, bool useClosest = true, bool verbose = false);

bool checkModuleConnectionsAreGood(std::array<std::vector<unsigned int>, 6>& layers_good_paired_modules);

void fitCircle(std::vector<float> x, std::vector<float> y);
void printMiniDoubletConnectionMultiplicitiesBarrel(SDL::Event& event, int layer, int depth, bool goinside=false);

std::vector<unsigned int> getHitIdxListTrackCandidate(SDL::TrackCandidate* tc);
std::vector<unsigned int> getModuleListTrackCandidate(SDL::TrackCandidate* tc);
int getNBarrelTrackCandidate(SDL::TrackCandidate* tc);
std::vector<unsigned int> allMatchedSimTrkIdxs(SDL::TrackCandidate* tc);
std::vector<int> matchedSimTrkIdxs(SDL::TrackCandidate* tc);
void perm(vector<int> intermediate, size_t n, vector<vector<int>>& va);

// Confiuration helper
std::vector<float> getPtBounds();

// Looper helper
bool goodEvent();

// MiniDoublet helper
std::vector<int> matchedSimTrkIdxs(SDL::MiniDoublet* md);

// Segment helper
std::vector<int> matchedSimTrkIdxs(SDL::Segment* sg, bool matchOnlyAnchor=false);

// Track helper
bool inTimeTrackWithPdgId(int isimtrk, int pdgid);

// Tracklet helper
TrackletType getTrackletCategory(SDL::Tracklet& tl);
int getNPSModules(SDL::Tracklet& tl);
std::vector<int> matchedSimTrkIdxs(SDL::Tracklet& tl);

// Triplet helper
std::vector<int> matchedSimTrkIdxs(SDL::Triplet* tp);

// Generic track matching function
std::vector<int> matchedSimTrkIdxs(std::vector<int> hitidxs, std::vector<int> hittypes);

// Steering SDL
void loadMaps();
TVector3 r3FromPCA(const TVector3& p3, const float dxy, const float dz);
void addPixelSegments(SDL::Event& event, int isimtrk = -1);
void addOuterTrackerHits(SDL::Event& event);
void addOuterTrackerHitsFromSimTrack(SDL::Event& event, int isimtrk);
void runSDL(SDL::Event& event);
void runSDLTest_v1(SDL::Event& event);
void runSDLTest_v2(SDL::Event& event);
void runSDLTest_PixelSegments(SDL::Event& event);

// Running pieces
void runMiniDoublet(SDL::Event& event);
void runSegment(SDL::Event& event);
void runTriplet(SDL::Event& event);
void runTracklet(SDL::Event& event);
void runTrackletWithAGap(SDL::Event& event);
void runTrackletTest_v1(SDL::Event& event);
void runTrackletTest_PixelSegment_v1(SDL::Event& event);
void runTrackCandidate(SDL::Event& event);
void runTrackCandidateTest_v1(SDL::Event& event);
void runTrackCandidateTest_v2(SDL::Event& event);
void runTrackCandidateTest_v3(SDL::Event& event);

// Printing SDL information
void printHitSummary(SDL::Event& event);
void printMiniDoubletSummary(SDL::Event& event);
void printSegmentSummary(SDL::Event& event);
void printTrackletSummary(SDL::Event& event);
void printTripletSummary(SDL::Event& event);
void printTrackCandidateSummary(SDL::Event& event);
void printMiniDoubletConnectionMultiplicitiesSummary(SDL::Event& event);

//
void printSimTrack(int isimtrk);

// Is good simhit
float drfracSimHitConsistentWithHelix(int isimtrk, int isimhitidx);
float drfracSimHitConsistentWithHelix(SDLMath::Helix& helix, int isimhitidx);
float distxySimHitConsistentWithHelix(int isimtrk, int isimhitidx);
float distxySimHitConsistentWithHelix(SDLMath::Helix& helix, int isimhitidx);

#endif
