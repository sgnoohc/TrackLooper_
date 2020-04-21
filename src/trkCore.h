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

float simhit_p(unsigned int simhitidx);
float hitAngle(unsigned int simhitidx);
bool isMuonCurlingHit(unsigned int isimtrk, unsigned int ith_hit);
bool goodBarrelTrack(unsigned int isimtrk, int pdgid=0);
bool hasAll12HitsInBarrel(unsigned int isimtrk);
bool hasAll12HitsWithNBarrel(unsigned int isimtrk, int nbarrel);
bool hasAll12HitsWithNBarrelUsingModuleMap(unsigned int isimtrk, int nbarrel, bool usesimhits=false);
bool isMTVMatch(unsigned int isimtrk, std::vector<unsigned int> hit_idxs);
bool hasAtLeastOneHitPairinEndcapLikeTiltedModule(unsigned short layer, unsigned int isimtrk);
bool is75percentFromSimMatchedHits(std::vector<unsigned int> hit_idxs, int pdgid);
TVector3 linePropagateR(const TVector3& r3, const TVector3& p3, double rDest, int& status, bool useClosest = true, bool verbose = false);
std::pair<TVector3,TVector3> helixPropagateApproxR(const TVector3& r3, const TVector3& p3, double rDest, int q, int& status, bool useClosest = true, bool verbose = false);

bool checkModuleConnectionsAreGood(std::array<std::vector<unsigned int>, 6>& layers_good_paired_modules);

void fitCircle(std::vector<float> x, std::vector<float> y);
void printMiniDoubletConnectionMultiplicitiesBarrel(SDL::Event& event, int layer, int depth, bool goinside=false);

std::vector<int> matchedSimTrkIdxs(SDL::TrackCandidate* tc);
void perm(vector<int> intermediate, size_t n, vector<vector<int>>& va);

#endif
