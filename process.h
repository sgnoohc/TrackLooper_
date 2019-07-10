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
        kStudyEffBarrel,
        kStudyEffBarrelFlat,
        kStudyEffBarrelTilt,
        kStudyEffBarrelTiltHighZ,
        kStudyEffBarrelTiltLowZ,
        kStudyEffEndcap,
        kStudyEffEndcapPS,
        kStudyEffEndcap2S,
        kStudyEffEndcapPSCloseRing,
        kStudyEffEndcapPSLowPt,
    };

    const char* studyname;
    StudyEfficiencyMode mode;
    const char* modename;
    std::vector<float> pt_boundaries;
    std::vector<float> md_matched_track_pt;
    std::vector<float> md_all_track_pt;
    std::vector<float> md_matched_track_eta;
    std::vector<float> md_all_track_eta;
    std::vector<float> md_matched_track_phi;
    std::vector<float> md_all_track_phi;
    std::vector<float> md_matched_track_z;
    std::vector<float> md_all_track_z;
    std::array<std::vector<float>, NLAYERS> md_matched_track_pt_by_layer;
    std::array<std::vector<float>, NLAYERS> md_all_track_pt_by_layer;
    std::array<std::vector<float>, NLAYERS> md_matched_track_eta_by_layer;
    std::array<std::vector<float>, NLAYERS> md_all_track_eta_by_layer;
    std::array<std::vector<float>, NLAYERS> md_matched_track_phi_by_layer;
    std::array<std::vector<float>, NLAYERS> md_all_track_phi_by_layer;
    std::array<std::vector<float>, NLAYERS> md_matched_track_wrapphi_by_layer;
    std::array<std::vector<float>, NLAYERS> md_all_track_wrapphi_by_layer;
    std::array<std::vector<float>, NLAYERS> md_matched_track_z_by_layer;
    std::array<std::vector<float>, NLAYERS> md_all_track_z_by_layer;
    std::vector<float> md_lower_hit_only_track_pt;
    std::vector<float> md_lower_hit_only_track_eta;

    StudyEfficiency(const char* studyName, StudyEfficiencyMode, std::vector<float> ptboundaries);
    virtual void bookStudy();
    virtual void doStudy(SDL::Event& recoevent, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents);

};

class StudyEndcapInefficiency : public Study
{

public:
    enum StudyEndcapInefficiencyMode
    {
        kStudyEndcapIneffAll = 1,
        kStudyEndcapIneffPS = 2,
        kStudyEndcapIneff2S = 3,
        kStudyEndcapIneffPSLowP = 4,
        kStudyEndcapIneffPSLowS = 5,
    };

    const char* studyname;
    StudyEndcapInefficiencyMode mode;
    const char* modename;

    std::vector<float> dzs_passed;
    std::vector<float> drts_passed;
    std::vector<float> fabsdPhis_passed;
    std::vector<float> zs_passed;
    std::vector<float> dzfracs_passed;
    std::vector<float> fabsdPhiMods_passed;
    std::vector<float> fabsdPhiModDiffs_passed;

    std::vector<float> dzs_failed;
    std::vector<float> drts_failed;
    std::vector<float> fabsdPhis_failed;
    std::vector<float> zs_failed;
    std::vector<float> dzfracs_failed;
    std::vector<float> fabsdPhiMods_failed;
    std::vector<float> fabsdPhiModDiffs_failed;

    StudyEndcapInefficiency(const char* studyName, StudyEndcapInefficiencyMode);
    virtual void bookStudy();
    virtual void doStudy(SDL::Event& recoevent, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents);
};

class StudySegmentEfficiency : public Study
{

public:
    enum StudySegmentEfficiencyMode
    {
        kStudyEffAll = 1,
        kStudyEffBarrelBarrel,
        kStudyEffBarrelFlatBarrel,
        kStudyEffBarrelTiltBarrel,
        kStudyEffBarrelFlatBarrelFlat,
        kStudyEffBarrelFlatBarrelTilt,
        kStudyEffBarrelTiltBarrelFlat,
        kStudyEffBarrelTiltBarrelTilt,
    };

    const char* studyname;
    StudySegmentEfficiencyMode mode;
    const char* modename;
    std::vector<float> pt_boundaries;
    std::vector<float> sg_matched_track_pt;
    std::vector<float> sg_all_track_pt;
    std::vector<float> sg_matched_track_eta;
    std::vector<float> sg_all_track_eta;
    std::vector<float> sg_matched_track_phi;
    std::vector<float> sg_all_track_phi;
    std::vector<float> sg_matched_track_z;
    std::vector<float> sg_all_track_z;
    std::array<std::vector<float>, NLAYERS> sg_matched_track_pt_by_layer;
    std::array<std::vector<float>, NLAYERS> sg_all_track_pt_by_layer;
    std::array<std::vector<float>, NLAYERS> sg_matched_track_eta_by_layer;
    std::array<std::vector<float>, NLAYERS> sg_all_track_eta_by_layer;
    std::array<std::vector<float>, NLAYERS> sg_matched_track_phi_by_layer;
    std::array<std::vector<float>, NLAYERS> sg_all_track_phi_by_layer;
    std::array<std::vector<float>, NLAYERS> sg_matched_track_wrapphi_by_layer;
    std::array<std::vector<float>, NLAYERS> sg_all_track_wrapphi_by_layer;
    std::array<std::vector<float>, NLAYERS> sg_matched_track_z_by_layer;
    std::array<std::vector<float>, NLAYERS> sg_all_track_z_by_layer;

    StudySegmentEfficiency(const char* studyName, StudySegmentEfficiencyMode, std::vector<float> ptboundaries);
    virtual void bookStudy();
    virtual void doStudy(SDL::Event& recoevent, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents);

};

void printModuleConnectionInfo();

#endif
