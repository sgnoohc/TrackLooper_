#include "trktree.h"
#include "rooutil.h"
#include "cxxopts.h"

#include "SDL/Event.h" // SDL::Event
#include "SDL/Module.h" // SDL::Module
#include "SDL/PrintUtil.h" // SDL::out

class AnalysisConfig {

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

AnalysisConfig ana;

// ./process INPUTFILEPATH OUTPUTFILE [NEVENTS]
int main(int argc, char** argv)
{

//********************************************************************************
//
// 1. Parsing options
//
//********************************************************************************

    // cxxopts is just a tool to parse argc, and argv easily

    // Grand option setting
    cxxopts::Options options("\n  $ doAnalysis",  "\n         **********************\n         *                    *\n         *       Looper       *\n         *                    *\n         **********************\n");

    // Read the options
    options.add_options()
        ("i,input"       , "Comma separated input file list OR if just a directory is provided it will glob all in the directory BUT must end with '/' for the path", cxxopts::value<std::string>())
        ("t,tree"        , "Name of the tree in the root file to open and loop over"                                             , cxxopts::value<std::string>())
        ("o,output"      , "Output file name"                                                                                    , cxxopts::value<std::string>())
        ("n,nevents"     , "N events to loop over"                                                                               , cxxopts::value<int>()->default_value("-1"))
        ("d,debug"       , "Run debug job. i.e. overrides output option to 'debug.root' and 'recreate's the file.")
        ("h,help"        , "Print help")
        ;

    auto result = options.parse(argc, argv);

    // NOTE: When an option was provided (e.g. -i or --input), then the result.count("<option name>") is more than 0
    // Therefore, the option can be parsed easily by asking the condition if (result.count("<option name>");
    // That's how the several options are parsed below

    //_______________________________________________________________________________
    // --help
    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(1);
    }

    //_______________________________________________________________________________
    // --input
    if (result.count("input"))
    {
        ana.input_file_list_tstring = result["input"].as<std::string>();
    }
    else
    {
        std::cout << options.help() << std::endl;
        std::cout << "ERROR: Input list is not provided! Check your arguments" << std::endl;
        exit(1);
    }

    //_______________________________________________________________________________
    // --tree
    if (result.count("tree"))
    {
        ana.input_tree_name = result["tree"].as<std::string>();
    }
    else
    {
        std::cout << options.help() << std::endl;
        std::cout << "ERROR: Input tree name is not provided! Check your arguments" << std::endl;
        exit(1);
    }

    //_______________________________________________________________________________
    // --debug
    if (result.count("debug"))
    {
        ana.output_tfile = new TFile("debug.root", "recreate");
    }
    else
    {
        //_______________________________________________________________________________
        // --output
        if (result.count("output"))
        {
            ana.output_tfile = new TFile(result["output"].as<std::string>().c_str(), "create");
            if (not ana.output_tfile->IsOpen())
            {
                std::cout << options.help() << std::endl;
                std::cout << "ERROR: output already exists! provide new output name or delete old file. OUTPUTFILE=" << result["output"].as<std::string>() << std::endl;
                exit(1);
            }
        }
        else
        {
            std::cout << options.help() << std::endl;
            std::cout << "ERROR: Output file name is not provided! Check your arguments" << std::endl;
            exit(1);
        }
    }

    //_______________________________________________________________________________
    // --nevents
    ana.n_events = result["nevents"].as<int>();

    //
    // Printing out the option settings overview
    //
    std::cout <<  "=========================================================" << std::endl;
    std::cout <<  " Setting of the analysis job based on provided arguments " << std::endl;
    std::cout <<  "---------------------------------------------------------" << std::endl;
    std::cout <<  " ana.input_file_list_tstring: " << ana.input_file_list_tstring <<  std::endl;
    std::cout <<  " ana.output_tfile: " << ana.output_tfile->GetName() <<  std::endl;
    std::cout <<  " ana.n_events: " << ana.n_events <<  std::endl;
    std::cout <<  "=========================================================" << std::endl;

//********************************************************************************
//
// 2. Opening input baby files
//
//********************************************************************************

    // Create the TChain that holds the TTree's of the baby ntuples
    ana.events_tchain = RooUtil::FileUtil::createTChain(ana.input_tree_name, ana.input_file_list_tstring);

    // Create a Looper object to loop over input files
    // the "www" object is defined in the wwwtree.h/cc
    // This is an instance which helps read variables in the WWW baby TTree
    // It is a giant wrapper that facilitates reading TBranch values.
    // e.g. if there is a TBranch named "lep_pt" which is a std::vector<float> then, one can access the branch via
    //
    //    std::vector<float> lep_pt = www.lep_pt();
    //
    // and no need for "SetBranchAddress" and declaring variable shenanigans necessary
    // This is a standard thing SNT does pretty much every looper we use
    ana.looper.init(ana.events_tchain, &trk, ana.n_events);

//********************************************************************************
//
// Interlude... notes on RooUtil framework
//
//********************************************************************************

    // ~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
    // Quick tutorial on RooUtil::Cutflow object cut tree formation
    // ~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
    //
    // The RooUtil::Cutflow object facilitates creating a tree structure of cuts
    //
    // To add cuts to each node of the tree with cuts defined, use "addCut" or "addCutToLastActiveCut"
    // The "addCut" or "addCutToLastActiveCut" accepts three argument, <name>, and two lambda's that define the cut selection, and the weight to apply to that cut stage
    //
    // e.g. To create following cut-tree structure one does
    //
    //             (Root) <--- Always exists as soon as RooUtil::Cutflow object is created. But this is basically hidden underneath and users do not have to care
    //                |
    //            CutWeight
    //            |       |
    //     CutPreSel1    CutPreSel2
    //       |                  |
    //     CutSel1           CutSel2
    //
    //
    //   code:
    //
    //      // Create the object (Root node is created as soon as the instance is created)
    //      RooUtil::Cutflow cutflow;
    //
    //      cutflow.addCut("CutWeight"                 , <lambda> , <lambda>); // CutWeight is added below "Root"-node
    //      cutflow.addCutToLastActiveCut("CutPresel1" , <lambda> , <lambda>); // The last "active" cut is "CutWeight" since I just added that. So "CutPresel1" is added below "CutWeight"
    //      cutflow.addCutToLastActiveCut("CutSel1"    , <lambda> , <lambda>); // The last "active" cut is "CutPresel1" since I just added that. So "CutSel1" is added below "CutPresel1"
    //
    //      cutflow.getCut("CutWeight"); // By "getting" the cut object, this makes the "CutWeight" the last "active" cut.
    //      cutflow.addCutToLastActiveCut("CutPresel2" , <lambda> , <lambda>); // The last "active" cut is "CutWeight" since I "getCut" on it. So "CutPresel2" is added below "CutWeight"
    //      cutflow.addCutToLastActiveCut("CutSel2"    , <lambda> , <lambda>); // The last "active" cut is "CutPresel2" since I just added that. So "CutSel2" is added below "CutPresel1"
    //
    // (Side note: "UNITY" lambda is defined in the framework to just return 1. This so that use don't have to type [&]() {return 1;} so many times.)
    //
    // Once the cutflow is formed, create cutflow histograms can be created by calling RooUtil::Cutflow::bookCutflows())
    // This function looks through the terminating nodes of the tree structured cut tree. and creates a histogram that will fill the yields
    // For the example above, there are two terminationg nodes, "CutSel1", and "CutSel2"
    // So in this case Root::Cutflow::bookCutflows() will create two histograms. (Actually four histograms.)
    //
    //  - TH1F* type object :  CutSel1_cutflow (4 bins, with first bin labeled "Root", second bin labeled "CutWeight", third bin labeled "CutPreSel1", fourth bin labeled "CutSel1")
    //  - TH1F* type object :  CutSel2_cutflow (...)
    //  - TH1F* type object :  CutSel1_rawcutflow (...)
    //  - TH1F* type object :  CutSel2_rawcutflow (...)
    //                                ^
    //                                |
    // NOTE: There is only one underscore "_" between <CutName>_cutflow or <CutName>_rawcutflow
    //
    // And later in the loop when RooUtil::Cutflow::fill() function is called, the tree structure will be traversed through and the appropriate yields will be filled into the histograms
    //
    // After running the loop check for the histograms in the output root file

    // ~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
    // Quick tutorial on RooUtil::Histograms object
    // ~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
    //
    // The RooUtil::Histograms object facilitates book keeping histogram definitions
    // And in conjunction with RooUtil::Cutflow object, one can book same histograms across different cut stages easily without copy pasting codes many times by hand.
    //
    // The histogram addition happens in two steps.
    // 1. Defining histograms
    // 2. Booking histograms to cuts
    //
    // Histograms are defined via following functions
    //
    //      RooUtil::Histograms::addHistogram       : Typical 1D histogram (TH1F*) "Fill()" called once per event
    //      RooUtil::Histograms::addVecHistogram    : Typical 1D histogram (TH1F*) "Fill()" called multiple times per event
    //      RooUtil::Histograms::add2DHistogram     : Typical 2D histogram (TH2F*) "Fill()" called once per event
    //      RooUtil::Histograms::add2DVecHistogram  : Typical 2D histogram (TH2F*) "Fill()" called multiple times per event
    // e.g.
    //
    //    RooUtil::Histograms histograms;
    //    histograms.addHistogram   ("MllSS"    , 180 , 0. , 300. , [&]() { return www.MllSS()  ; }); // The lambda returns float
    //    histograms.addVecHistogram("AllLepPt" , 180 , 0. , 300. , [&]() { return www.lep_pt() ; }); // The lambda returns vector<float>
    //
    // The addVecHistogram will have lambda to return vector<float> and it will loop over the values and call TH1F::Fill() for each item
    //
    // To book histograms to cuts one uses
    //
    //      RooUtil::Cutflow::bookHistogramsForCut()
    //      RooUtil::Cutflow::bookHistogramsForCutAndBelow()
    //      RooUtil::Cutflow::bookHistogramsForCutAndAbove()
    //      RooUtil::Cutflow::bookHistogramsForEndCuts()
    //
    // e.g. Given a tree like the following, we can book histograms to various cuts as we want
    //
    //              Root
    //                |
    //            CutWeight
    //            |       |
    //     CutPreSel1    CutPreSel2
    //       |                  |
    //     CutSel1           CutSel2
    //
    // For example,
    //
    //    1. book a set of histograms to one cut:
    //
    //       cutflow.bookHistogramsForCut(histograms, "CutPreSel2")
    //
    //    2. book a set of histograms to a cut and below
    //
    //       cutflow.bookHistogramsForCutAndBelow(histograms, "CutWeight") // will book a set of histograms to CutWeight, CutPreSel1, CutPreSel2, CutSel1, and CutSel2
    //
    //    3. book a set of histograms to a cut and above (... useless...?)
    //
    //       cutflow.bookHistogramsForCutAndAbove(histograms, "CutPreSel2") // will book a set of histograms to CutPreSel2, CutWeight (nothing happens to Root node)
    //
    //    4. book a set of histograms to a terminating nodes
    //
    //       cutflow.bookHistogramsForEndCuts(histograms) // will book a set of histograms to CutSel1 and CutSel2
    //
    // The naming convention of the booked histograms are as follows
    //
    //   cutflow.bookHistogramsForCut(histograms, "CutSel1");
    //
    //  - TH1F* type object : CutSel1__MllSS;
    //  - TH1F* type object : CutSel1__AllLepPt;
    //                               ^^
    //                               ||
    // NOTE: There are two underscores "__" between <CutName>__<HistogramName>
    //
    // And later in the loop when RooUtil::CutName::fill() function is called, the tree structure will be traversed through and the appropriate histograms will be filled with appropriate variables
    // After running the loop check for the histograms in the output root file

    // Set the cutflow object output file
    ana.cutflow.setTFile(ana.output_tfile);
    // ana.cutflow.addCut("CutWeight", UNITY, UNITY);

    // Print cut structure
    ana.cutflow.printCuts();

    std::vector<float> pt_boundaries = {0, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.5, 2.0, 3.0, 5.0, 10, 15., 25, 50};
    std::vector<float> md_matched_track_pt;
    std::vector<float> md_all_track_pt;
    ana.histograms.addVecHistogram("md_matched_track_pt", pt_boundaries, [&]() { return md_matched_track_pt; } );
    ana.histograms.addVecHistogram("md_all_track_pt", pt_boundaries, [&]() { return md_all_track_pt; } );
    std::vector<float> md_matched_track_eta;
    std::vector<float> md_all_track_eta;
    ana.histograms.addVecHistogram("md_matched_track_eta", 50, -4, 4, [&]() { return md_matched_track_eta; } );
    ana.histograms.addVecHistogram("md_all_track_eta", 50, -4, 4, [&]() { return md_all_track_eta; } );

    const int nlayers = 6;
    std::array<std::vector<float>, nlayers> md_matched_track_pt_by_layer;
    std::array<std::vector<float>, nlayers> md_all_track_pt_by_layer;
    for (int ii = 0; ii < nlayers; ++ii)
    {
        ana.histograms.addVecHistogram(TString::Format("md_matched_track_pt_by_layer%d", ii), pt_boundaries, [&, ii]() { return md_matched_track_pt_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("md_all_track_pt_by_layer%d", ii), pt_boundaries, [&, ii]() { return md_all_track_pt_by_layer[ii]; } );
    }
    std::array<std::vector<float>, nlayers> md_matched_track_eta_by_layer;
    std::array<std::vector<float>, nlayers> md_all_track_eta_by_layer;
    for (int ii = 0; ii < nlayers; ++ii)
    {
        ana.histograms.addVecHistogram(TString::Format("md_matched_track_eta_by_layer%d", ii), 50, -4, 4, [&, ii]() { return md_matched_track_eta_by_layer[ii]; } );
        ana.histograms.addVecHistogram(TString::Format("md_all_track_eta_by_layer%d", ii), 50, -4, 4, [&, ii]() { return md_all_track_eta_by_layer[ii]; } );
    }

    std::vector<float> matched_dphi;
    ana.histograms.addVecHistogram("matched_dphi", 180, -3, 3, [&]() { return matched_dphi; } );
    std::vector<float> not_matched_dphi;
    ana.histograms.addVecHistogram("not_matched_dphi", 180, -3, 3, [&]() { return not_matched_dphi; } );
    std::vector<float> all_dphi;
    ana.histograms.addVecHistogram("all_dphi", 180, -3, 3, [&]() { return all_dphi; } );

    std::vector<float> rt_v_phim__rt;
    std::vector<float> rt_v_phim__phim;
    ana.histograms.add2DVecHistogram("rt", 50, 20, 120, "phim", 50, 0., 1., [&]() { return rt_v_phim__rt; }, [&]() { return rt_v_phim__phim; } );
    std::array<std::vector<float>, nlayers> rt_v_phim__rt_by_layer;
    std::array<std::vector<float>, nlayers> rt_v_phim__phim_by_layer;
    for (int ii = 0; ii < nlayers; ++ii)
    {
        ana.histograms.add2DVecHistogram("rt", 50, 20, 120, TString::Format("phim_by_layer%d", ii), 50, 0., 1., [&, ii]() { return rt_v_phim__rt_by_layer[ii]; }, [&, ii]() { return rt_v_phim__phim_by_layer[ii]; } );
    }

    std::vector<float> rt_v_dphi__rt;
    std::vector<float> rt_v_dphi__dphi;
    ana.histograms.add2DVecHistogram("rt", 50, 20, 120, "dphi", 50, 0., 1., [&]() { return rt_v_dphi__rt; }, [&]() { return rt_v_dphi__dphi; } );
    std::array<std::vector<float>, nlayers> rt_v_dphi__rt_by_layer;
    std::array<std::vector<float>, nlayers> rt_v_dphi__dphi_by_layer;
    for (int ii = 0; ii < nlayers; ++ii)
    {
        ana.histograms.add2DVecHistogram("rt", 50, 20, 120, TString::Format("dphi_by_layer%d", ii), 50, 0., 1., [&, ii]() { return rt_v_dphi__rt_by_layer[ii]; }, [&, ii]() { return rt_v_dphi__dphi_by_layer[ii]; } );
    }

    // Book cutflows
    // ana.cutflow.bookCutflows();

    // Book Histograms
    ana.cutflow.bookHistograms(ana.histograms); // if just want to book everywhere

    // Set extendable axes
    // ana.cutflow.setHistsAxesExtendable(); // Make histogram axes extendable

    // Looping input file
    while (ana.looper.nextEvent())
    {
        //Do what you need to do in for each event here
        //To save use the following function
        ana.cutflow.fill();

        // <--------------------------
        // <--------------------------
        // <--------------------------
        //
        // ***************************
        // Testing SDL Implementations
        // ***************************
        //

        // Main instance that will hold modules, hits, minidoublets, etc. (i.e. main data structure)
        SDL::Event event;
        SDL::Event simevent;

        // Adding hits to modules
        for (unsigned int ihit = 0; ihit < trk.ph2_x().size(); ++ihit)
        {
            // Takes two arguments, SDL::Hit, and detId
            // SDL::Event internally will structure whether we already have the module instance or we need to create a new one.
            event.addHitToModule(
                    // a hit
                    SDL::Hit(trk.ph2_x()[ihit], trk.ph2_y()[ihit], trk.ph2_z()[ihit], ihit),
                    // add to module with "detId"
                    trk.ph2_detId()[ihit]
                    );

            for (auto& simhitidx : trk.ph2_simHitIdx()[ihit])
            {
                SDL::Hit(trk.simhit_x()[simhitidx], trk.simhit_y()[simhitidx], trk.simhit_z()[simhitidx], simhitidx);
                simevent.addHitToModule(
                        // a hit
                        SDL::Hit(trk.simhit_x()[simhitidx], trk.simhit_y()[simhitidx], trk.simhit_z()[simhitidx], simhitidx),
                        // add to module with "detId"
                        trk.simhit_detId()[simhitidx]
                        );
            }

            // Access hits on the S side of the PS modules in the endcaps and get three numbers, (detId, x, y)
            SDL::Module module = SDL::Module(trk.ph2_detId()[ihit]);
            if (module.moduleType() == SDL::Module::PS and module.moduleLayerType() == SDL::Module::Strip and module.subdet() == SDL::Module::Endcap)
            {
                std::cout <<  " 'stripendcap': " << "stripendcap" <<  " trk.ph2_detId()[ihit]: " << trk.ph2_detId()[ihit] <<  " trk.ph2_x()[ihit]: " << trk.ph2_x()[ihit] <<  " trk.ph2_y()[ihit]: " << trk.ph2_y()[ihit] <<  std::endl;
            }

        }

        // Set log level
        event.setLogLevel(SDL::Log_Debug2);

        // Create mini doublets
        event.createMiniDoublets();

        rt_v_phim__rt.clear();
        rt_v_phim__phim.clear();
        for (int ii = 0; ii < nlayers; ++ii)
        {
            rt_v_phim__rt_by_layer[ii].clear();
            rt_v_phim__phim_by_layer[ii].clear();
        }

        rt_v_dphi__rt.clear();
        rt_v_dphi__dphi.clear();
        for (int ii = 0; ii < nlayers; ++ii)
        {
            rt_v_dphi__rt_by_layer[ii].clear();
            rt_v_dphi__dphi_by_layer[ii].clear();
        }

        // Efficiency measurement
        for (unsigned int isimtrk = 0; isimtrk < trk.sim_q().size(); ++isimtrk)
        {

            // Select only muon tracks
            if (abs(trk.sim_pdgId()[isimtrk]) != 13)
                continue;

            // if (trk.sim_pt()[isimtrk] < 1.)
            //     continue;

            // event just for this track
            SDL::Event trackevent;

            // loop over the simulated hits
            for (auto& simhitidx : trk.sim_simHitIdx()[isimtrk])
            {
                // float simhit_pt = sqrt(trk.simhit_px()[simhitidx] * trk.simhit_px()[simhitidx] + trk.simhit_py()[simhitidx] * trk.simhit_py()[simhitidx]);

                int simhit_particle = trk.simhit_particle()[simhitidx];

                // if (simhit_pt < 0.1 * trk.sim_pt()[isimtrk])
                if (abs(simhit_particle) != 13)
                    continue;
                    
                for (unsigned int irecohit = 0; irecohit < trk.simhit_hitIdx()[simhitidx].size(); ++irecohit) // list of reco hit matched to this sim hit
                {

                    // Get the recohit type
                    int recohittype = trk.simhit_hitType()[simhitidx][irecohit];

                    // Consider only ph2 hits
                    if (recohittype == 4)
                    {

                        int ihit = trk.simhit_hitIdx()[simhitidx][irecohit];

                        trackevent.addHitToModule(
                                // a hit
                                SDL::Hit(trk.ph2_x()[ihit], trk.ph2_y()[ihit], trk.ph2_z()[ihit], ihit),
                                // add to module with "detId"
                                trk.ph2_detId()[ihit]
                                );
                    }
                }

            }

            trackevent.createMiniDoublets(SDL::AllComb_MDAlgo);

            for (auto& lowerModulePtr_Track : trackevent.getLowerModulePtrs())
            {

                float pt = trk.sim_pt()[isimtrk];

                if (pt > 1.)
                    continue;

                if (lowerModulePtr_Track->subdet() == SDL::Module::Barrel and lowerModulePtr_Track->side() == SDL::Module::Center)
                {

                    for (auto& lowerHitPtr : lowerModulePtr_Track->getHitPtrs())
                    {
                        rt_v_phim__rt.push_back(lowerHitPtr->rt());
                        rt_v_phim__phim.push_back(SDL::MiniDoublet::dPhiThreshold(*lowerHitPtr, *lowerModulePtr_Track));
                        int layer_idx = lowerModulePtr_Track->layer() - 1;
                        rt_v_phim__rt_by_layer[layer_idx].push_back(lowerHitPtr->rt());
                        rt_v_phim__phim_by_layer[layer_idx].push_back(SDL::MiniDoublet::dPhiThreshold(*lowerHitPtr, *lowerModulePtr_Track));
                    }

                    for (auto& md_Track : lowerModulePtr_Track->getMiniDoubletPtrs())
                    {
                        SDL::Hit* lowerHitPtr = md_Track->lowerHitPtr();
                        float rt = lowerHitPtr->rt();
                        float dphi = lowerHitPtr->deltaPhiChange(*(md_Track->upperHitPtr()));
                        rt_v_dphi__rt.push_back(rt);
                        rt_v_dphi__dphi.push_back(dphi);
                        int layer_idx = lowerModulePtr_Track->layer() - 1;
                        rt_v_dphi__rt_by_layer[layer_idx].push_back(rt);
                        rt_v_dphi__dphi_by_layer[layer_idx].push_back(dphi);
                    }

                }

            }

            // Efficiency calculation
            md_matched_track_pt.clear();
            md_all_track_pt.clear();
            md_matched_track_eta.clear();
            md_all_track_eta.clear();
            for (int ii = 0; ii < nlayers; ++ii)
            {
                md_matched_track_pt_by_layer[ii].clear();
                md_all_track_pt_by_layer[ii].clear();
                md_matched_track_eta_by_layer[ii].clear();
                md_all_track_eta_by_layer[ii].clear();
            }
            matched_dphi.clear();
            not_matched_dphi.clear();
            all_dphi.clear();

            for (auto& lowerModulePtr_Track : trackevent.getLowerModulePtrs())
            {
                int layer_idx = lowerModulePtr_Track->layer() - 1;

                bool match = false;
                for (auto& md_Track : lowerModulePtr_Track->getMiniDoubletPtrs())
                {

                    // Compute "truth" MD's dphi
                    SDL::Hit* lowerHitPtr = md_Track->lowerHitPtr();
                    SDL::Hit* upperHitPtr = md_Track->upperHitPtr();
                    float dphi = lowerHitPtr->deltaPhiChange(*upperHitPtr);

                    all_dphi.push_back(dphi);

                    bool thismdmatched = false;
                    for (auto& md : event.getModule(lowerModulePtr_Track->detId()).getMiniDoubletPtrs())
                    {
                        if (md_Track->isIdxMatched(*md))
                        {
                            match = true;
                            thismdmatched = true;
                        }
                    }

                    if (thismdmatched)
                        matched_dphi.push_back(dphi);
                    else
                        not_matched_dphi.push_back(dphi);
                }

                float pt = std::min((double) trk.sim_pt()[isimtrk], 49.999);
                float eta = trk.sim_eta()[isimtrk];

                // Modules with true mini-doublets
                // if (lowerModulePtr_Track->subdet() == SDL::Module::Endcap and lowerModulePtr_Track->moduleType() == SDL::Module::TwoS and lowerModulePtr_Track->getMiniDoubletPtrs().size() > 0)
                // if (lowerModulePtr_Track->subdet() == SDL::Module::Endcap and lowerModulePtr_Track->moduleType() == SDL::Module::PS and lowerModulePtr_Track->getMiniDoubletPtrs().size() > 0)
                if (lowerModulePtr_Track->subdet() == SDL::Module::Barrel and lowerModulePtr_Track->side() == SDL::Module::Center and lowerModulePtr_Track->getMiniDoubletPtrs().size() > 0)
                {

                    md_all_track_pt.push_back(pt);
                    if (trk.sim_pt()[isimtrk] > 1.)
                        md_all_track_eta.push_back(eta);

                    if (match)
                    {
                        md_matched_track_pt.push_back(pt);
                        if (trk.sim_pt()[isimtrk] > 1.)
                            md_matched_track_eta.push_back(eta);
                    }

                    md_all_track_pt_by_layer[layer_idx].push_back(pt);
                    if (trk.sim_pt()[isimtrk] > 1.)
                        md_all_track_eta_by_layer[layer_idx].push_back(eta);

                    if (match)
                    {
                        md_matched_track_pt_by_layer[layer_idx].push_back(pt);
                        if (trk.sim_pt()[isimtrk] > 1.)
                            md_matched_track_eta_by_layer[layer_idx].push_back(eta);
                    }

                    // for (auto& md_Track : lowerModulePtr_Track->getMiniDoubletPtrs())
                    // {
                    //     const SDL::Hit& lowerHit = *md_Track->lowerHitPtr();
                    //     const SDL::Hit& upperHit = *md_Track->upperHitPtr();
                    //     if (not SDL::MiniDoublet::isMiniDoubletPair(lowerHit, upperHit, *lowerModulePtr_Track, SDL::Default_MDAlgo))
                    //         SDL::MiniDoublet::isMiniDoubletPair(lowerHit, upperHit, *lowerModulePtr_Track, SDL::Default_MDAlgo, SDL::Log_Debug2);
                    // }

                }

            }

        }

        // Print content in the event
        // (SDL::cout is a modified version of std::cout where each line is prefixed by SDL::)
        if (ana.looper.getCurrentEventIndex() < 3) // Print for the first 10 events only
        {
            SDL::cout << event;
            SDL::cout << simevent;
        }

        // <--------------------------
        // <--------------------------
        // <--------------------------
    }

    // Writing output file
    ana.cutflow.saveOutput();

    // The below can be sometimes crucial
    delete ana.output_tfile;
}
