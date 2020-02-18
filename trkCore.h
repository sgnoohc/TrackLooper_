#ifndef trkCore_h
#define trkCore_h

#include "trktree.h"
#include "SDL/Module.h" // SDL::Module

float simhit_p(unsigned int simhitidx);
float hitAngle(unsigned int simhitidx);
bool isMuonCurlingHit(unsigned int isimtrk, unsigned int ith_hit);
bool hasAll12HitsInBarrel(unsigned int isimtrk);
bool isMTVMatch(unsigned int isimtrk, std::vector<unsigned int> hit_idxs);
bool hasAtLeastOneHitPairinEndcapLikeTiltedModule(unsigned short layer, unsigned int isimtrk)

#endif
