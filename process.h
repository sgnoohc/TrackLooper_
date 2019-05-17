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

#define NLAYERS 6

class AnalysisConfig
{

public:

    // TString that holds the input file list (comma separated)
    TString input_file_list_tstring;

    // TString that holds the name of the TTree to open for each input files
    TString input_tree_name;

    // Output TFile
    TFile* output_tfile;

    // Number of events to loop over
    int n_events;

    // Debug boolean
    bool debug;

    // TChain that holds the input TTree's
    TChain* events_tchain;

    // Custom Looper object to facilitate looping over many files
    RooUtil::Looper<trktree> looper;

    // Custom Cutflow framework
    RooUtil::Cutflow cutflow;

    // Custom Histograms object compatible with RooUtil::Cutflow framework
    RooUtil::Histograms histograms;

};

extern AnalysisConfig ana;

class Study
{

public:

    virtual void bookStudy();
    virtual void doStudy(SDL::Event& recoevent, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents);

};

class StudyBarreldPhiChangeCutThresholdValidity : public Study
{

public:

    std::vector<float> rt_v_phim__rt;
    std::vector<float> rt_v_phim__phim;
    std::array<std::vector<float>, NLAYERS> rt_v_phim__rt_by_layer;
    std::array<std::vector<float>, NLAYERS> rt_v_phim__phim_by_layer;
    std::vector<float> rt_v_dphi__rt;
    std::vector<float> rt_v_dphi__dphi;
    std::array<std::vector<float>, NLAYERS> rt_v_dphi__rt_by_layer;
    std::array<std::vector<float>, NLAYERS> rt_v_dphi__dphi_by_layer;

    virtual void bookStudy();
    virtual void doStudy(SDL::Event& recoevent, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents);

};

class StudyEfficiency : public Study
{

public:
    enum StudyEfficiencyMode
    {
        kStudyEffAll = 1,
        kStudyEffBarrel = 2,
        kStudyEffEndcap = 3,
        kStudyEffEndcapPS = 4,
        kStudyEffEndcap2S = 5,
    };

    const char* studyname;
    StudyEfficiencyMode mode;
    const char* modename;
    std::vector<float> pt_boundaries;
    std::vector<float> md_matched_track_pt;
    std::vector<float> md_all_track_pt;
    std::vector<float> md_matched_track_eta;
    std::vector<float> md_all_track_eta;
    std::array<std::vector<float>, NLAYERS> md_matched_track_pt_by_layer;
    std::array<std::vector<float>, NLAYERS> md_all_track_pt_by_layer;
    std::array<std::vector<float>, NLAYERS> md_matched_track_eta_by_layer;
    std::array<std::vector<float>, NLAYERS> md_all_track_eta_by_layer;
    std::vector<float> md_lower_hit_only_track_pt;
    std::vector<float> md_lower_hit_only_track_eta;

    StudyEfficiency(const char* studyName, StudyEfficiencyMode, std::vector<float> ptboundaries);
    virtual void bookStudy();
    virtual void doStudy(SDL::Event& recoevent, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents);

};

#endif
