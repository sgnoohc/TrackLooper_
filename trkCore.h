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

float simhit_p(unsigned int simhitidx);
float hitAngle(unsigned int simhitidx);
bool isMuonCurlingHit(unsigned int isimtrk, unsigned int ith_hit);
bool hasAll12HitsInBarrel(unsigned int isimtrk);
bool isMTVMatch(unsigned int isimtrk, std::vector<unsigned int> hit_idxs);
bool hasAtLeastOneHitPairinEndcapLikeTiltedModule(unsigned short layer, unsigned int isimtrk);
bool is75percentFromSimMatchedHits(std::vector<unsigned int> hit_idxs, int pdgid);
TVector3 linePropagateR(const TVector3& r3, const TVector3& p3, double rDest, int& status, bool useClosest = true, bool verbose = false);
std::pair<TVector3,TVector3> helixPropagateApproxR(const TVector3& r3, const TVector3& p3, double rDest, int q, int& status, bool useClosest = true, bool verbose = false);

void fitCircle(std::vector<float> x, std::vector<float> y);

#endif
