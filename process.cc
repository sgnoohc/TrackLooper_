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

    // Histogram utility object that is used to define the histograms
    ana.histograms.addVecHistogram("hit_res_z_pixel_center", 180, -1, 1, [&]()
            {
                std::vector<float> rtn;
                for (unsigned int ihit = 0; ihit < trk.ph2_side().size(); ++ihit)
                {
                    if (trk.ph2_side()[ihit] == 3)
                    {
                        SDL::Module module(trk.ph2_detId()[ihit]);
                        if (module.moduleLayerType() == SDL::Module::Pixel)
                        {
                            if (trk.ph2_simHitIdx()[ihit].size() == 0)
                                continue;
                            int simhit_idx = trk.ph2_simHitIdx()[ihit][0];
                            // trk.ph2_x()[ihit] - trk.simhit_x()[simhit_idx];
                            // trk.ph2_y()[ihit] - trk.simhit_y()[simhit_idx];
                            float dz = trk.ph2_z()[ihit] - trk.simhit_z()[simhit_idx];
                            rtn.push_back(dz);
                        }
                    }
                }
                return rtn;
            } );

    // Histogram utility object that is used to define the histograms
    ana.histograms.addVecHistogram("hit_res_r_pixel_center", 180, -1, 1, [&]()
            {
                std::vector<float> rtn;
                for (unsigned int ihit = 0; ihit < trk.ph2_side().size(); ++ihit)
                {
                    if (trk.ph2_side()[ihit] == 3)
                    {
                        SDL::Module module(trk.ph2_detId()[ihit]);
                        if (module.moduleLayerType() == SDL::Module::Pixel)
                        {
                            if (trk.ph2_simHitIdx()[ihit].size() == 0)
                                continue;
                            int simhit_idx = trk.ph2_simHitIdx()[ihit][0];
                            // trk.ph2_x()[ihit] - trk.simhit_x()[simhit_idx];
                            // trk.ph2_y()[ihit] - trk.simhit_y()[simhit_idx];
                            float dx = trk.ph2_x()[ihit] - trk.simhit_x()[simhit_idx];
                            float dy = trk.ph2_y()[ihit] - trk.simhit_y()[simhit_idx];
                            float dr = sqrt(pow(dx, 2) + pow(dy, 2));
                            rtn.push_back(dr);
                        }
                    }
                }
                return rtn;
            } );

    // Histogram utility object that is used to define the histograms
    ana.histograms.addVecHistogram("hit_res_z_strip_center", 180, -1, 1, [&]()
            {
                std::vector<float> rtn;
                for (unsigned int ihit = 0; ihit < trk.ph2_side().size(); ++ihit)
                {
                    if (trk.ph2_side()[ihit] == 3)
                    {
                        SDL::Module module(trk.ph2_detId()[ihit]);
                        if (module.moduleLayerType() == SDL::Module::Strip)
                        {
                            if (trk.ph2_simHitIdx()[ihit].size() == 0)
                                continue;
                            int simhit_idx = trk.ph2_simHitIdx()[ihit][0];
                            // trk.ph2_x()[ihit] - trk.simhit_x()[simhit_idx];
                            // trk.ph2_y()[ihit] - trk.simhit_y()[simhit_idx];
                            float dz = trk.ph2_z()[ihit] - trk.simhit_z()[simhit_idx];
                            rtn.push_back(dz);
                        }
                    }
                }
                return rtn;
            } );

    // Histogram utility object that is used to define the histograms
    ana.histograms.addVecHistogram("hit_res_r_strip_center", 180, -1, 1, [&]()
            {
                std::vector<float> rtn;
                for (unsigned int ihit = 0; ihit < trk.ph2_side().size(); ++ihit)
                {
                    if (trk.ph2_side()[ihit] == 3)
                    {
                        SDL::Module module(trk.ph2_detId()[ihit]);
                        if (module.moduleLayerType() == SDL::Module::Strip)
                        {
                            if (trk.ph2_simHitIdx()[ihit].size() == 0)
                                continue;
                            int simhit_idx = trk.ph2_simHitIdx()[ihit][0];
                            // trk.ph2_x()[ihit] - trk.simhit_x()[simhit_idx];
                            // trk.ph2_y()[ihit] - trk.simhit_y()[simhit_idx];
                            float dx = trk.ph2_x()[ihit] - trk.simhit_x()[simhit_idx];
                            float dy = trk.ph2_y()[ihit] - trk.simhit_y()[simhit_idx];
                            float dr = sqrt(pow(dx, 2) + pow(dy, 2));
                            rtn.push_back(dr);
                        }
                    }
                }
                return rtn;
            } );

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

        // Adding hits to modules
        for (unsigned int ihit = 0; ihit < trk.ph2_x().size(); ++ihit)
        {
            // Takes two arguments, SDL::Hit, and detId
            // SDL::Event internally will structure whether we already have the module instance or we need to create a new one.
            event.addHitToModule(
                    // a hit
                    SDL::Hit(trk.ph2_x()[ihit], trk.ph2_y()[ihit], trk.ph2_z()[ihit]),
                    // add to module with "detId"
                    trk.ph2_detId()[ihit]
                    );
        }

        // Loop over lower modules
        for (auto& lowerModulePtr : event.getLowerModulePtrs())
        {
            // Get reference to the lower Module
            SDL::Module& lowerModule = *lowerModulePtr;

            // Get reference to the upper Module
            SDL::Module& upperModule = event.getModule(lowerModule.partnerDetId());

            // Double nested loops
            // Loop over lower module hits
            for (auto& lowerHitPtr : lowerModule.getHitPtrs())
            {

                // Get reference to lower Hit
                SDL::Hit& lowerHit = *lowerHitPtr;

                // Loop over upper module hits
                for (auto& upperHitPtr : upperModule.getHitPtrs())
                {

                    // Get reference to upper Hit
                    SDL::Hit& upperHit = *upperHitPtr;

                    // <-------------------------------
                    // <-------------------------------
                    // <-------------------------------

                    // ********************************
                    // Mini Doublet Linking Logic
                    // ********************************

                    //
                    // Case 1: Working with barrel and flat PS modules only
                    //
                    // if (lowerModule.subdet() == SDL::Module::Barrel and lowerModule.side() == SDL::Module::Center and lowerModule.moduleType() == SDL::Module::PS)
                    if (lowerModule.subdet() == SDL::Module::Barrel and lowerModule.side() == SDL::Module::Center)
                    {
                        // The dphi change going from lower Hit to upper Hit
                        float dphi = lowerHit.deltaPhiChange(upperHit);

                        // =================================================================
                        // Various constants
                        // =================================================================
                        const float kRinv1GeVf = (2.99792458e-3 * 3.8);
                        const float k2Rinv1GeVf = kRinv1GeVf / 2.;
                        const float ptCut = 1.0;
                        const float sinAlphaMax = 0.95;
                        // p2Sim.directionT-r2Sim.directionT smearing around the mean computed with ptSim,rSim
                        // (1 sigma based on 95.45% = 2sigma at 2 GeV)
                        std::array<float, 6> miniMulsPtScaleBarrel {0.0052, 0.0038, 0.0034, 0.0034, 0.0032, 0.0034};
                        std::array<float, 5> miniMulsPtScaleEndcap {0.006, 0.006, 0.006, 0.006, 0.006}; //inter/extra-polated from L11 and L13 both roughly 0.006 [larger R have smaller value by ~50%]
                        //mean of the horizontal layer position in y; treat this as R below
                        std::array<float, 6> miniRminMeanBarrel {21.8, 34.6, 49.6, 67.4, 87.6, 106.8};
                        std::array<float, 5> miniRminMeanEndcap {131.4, 156.2, 185.6, 220.3, 261.5};// use z for endcaps

                        // =================================================================
                        // Computing cut threshold
                        // =================================================================
                        float rt = lowerHit.rt();
                        unsigned int iL = lowerModule.layer() - 1;
                        const float miniSlope = std::asin(std::min(rt * k2Rinv1GeVf / ptCut, sinAlphaMax));
                        const float rLayNominal = miniRminMeanBarrel[iL];
                        const float miniPVoff = 0.1 / rLayNominal;
                        const float miniMuls = miniMulsPtScaleBarrel[iL] * 3.f / ptCut;
                        const bool isTilted = false;
                        const bool tiltedOT123 = false;
                        const float pixelPSZpitch = 0.15;
                        const float miniTilt = isTilted && tiltedOT123 ? /*0.5f * pixelPSZpitch * drdz / sqrt(1.f + drdz * drdz) / miniDelta[iL]*/ : 0;
                        const float miniCut = miniSlope + sqrt(pow(miniMuls, 2) + pow(miniPVoff, 2) + pow(miniTilt * miniSlope, 2));

                        if (dphi < miniCut)
                        {
                            event.addMiniDoubletToLowerModule(SDL::MiniDoublet(lowerHitPtr, upperHitPtr), lowerModule.detId());
                        }

                    }

                    // the fabs(dphi) must be less than the curvature of min pt threshold

                    // <-------------------------------
                    // <-------------------------------
                    // <-------------------------------

                }

            }

        }

        // Print content in the event
        // (SDL::cout is a modified version of std::cout where each line is prefixed by SDL::)
        if (ana.looper.getCurrentEventIndex() < 10) // Print for the first 10 events only
            SDL::cout << event;

        // <--------------------------
        // <--------------------------
        // <--------------------------
    }

    // Writing output file
    ana.cutflow.saveOutput();

    // The below can be sometimes crucial
    delete ana.output_tfile;
}
