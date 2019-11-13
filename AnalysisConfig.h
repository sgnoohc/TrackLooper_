#ifndef AnalysisConfig_h
#define AnalysisConfig_h

#include "TString.h"
#include "rooutil.h"
#include "trktree.h"

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

    // specific event_index to process
    int specific_event_index;

    // efficiency study level
    // -1 upto mini-doublet is all-comb
    // -2 upto segment is all-comb
    // -3 upto tracklet is all-comb NOTE: MEMORY WILL BLOW UP FOR HIGH PU
    // -4 upto trackcandidate is all-comb NOTE: MEMORY WILL BLOW UP FOR HIGH PU
    //  0 nothing
    //  1 upto mini-doublet is all-comb
    //  2 upto mini-doublet is default segment is all-comb
    //  3 upto segment is default tracklet is all-comb
    //  4 upto tracklet is default trackcandidate is all-comb
    int eff_level;

    // pt binning options
    int ptbound_mode;

    // pdg id of the particles to compute efficincies on
    int pdg_id;

    // to print module connection info
    bool print_conn;

    // to print centroid
    bool print_centroid;

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

    // TTree output for studies
    TTree* output_ttree;

    // TTreeX to facilitate writing output to ttree
    RooUtil::TTreeX* tx;

};

extern AnalysisConfig ana;

#endif
