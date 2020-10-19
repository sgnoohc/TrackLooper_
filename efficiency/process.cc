#include "process.h"

// Global variable
AnalysisConfig ana;

#include "sdl_types.h"

// ./process INPUTFILEPATH OUTPUTFILE [NEVENTS]
int main(int argc, char** argv)
{

    // Parse arguments
    parseArguments(argc, argv);

    // Initialize input and output root files
    initializeInputsAndOutputs();

    // Create various bits important for each track
    createSDLVariables();

    // creating a set of efficiency plots
    std::vector<EfficiencySetDefinition> list_effSetDef;
    list_effSetDef.push_back(EfficiencySetDefinition("MD_B1", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_B1")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("MD_B2", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_B2")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("MD_B3", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_B3")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("MD_B4", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_B4")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("MD_B5", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_B5")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("MD_B6", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_B6")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("MD_E1", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_E1")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("MD_E2", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_E2")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("MD_E3", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_E3")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("MD_E4", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_E4")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("MD_E5", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_E5")[isim].size() > 0;}));

    list_effSetDef.push_back(EfficiencySetDefinition("LS_B1B2", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_LS_B1B2")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("LS_B2B3", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_LS_B2B3")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("LS_B3B4", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_LS_B3B4")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("LS_B4B5", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_LS_B4B5")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("LS_B5B6", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_LS_B5B6")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("LS_B1E1", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_LS_B1E1")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("LS_B2E1", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_LS_B2E1")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("LS_B3E1", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_LS_B3E1")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("LS_B4E1", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_LS_B4E1")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("LS_B5E1", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_LS_B5E1")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("LS_E1E2", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_LS_E1E2")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("LS_E2E3", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_LS_E2E3")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("LS_E3E4", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_LS_E3E4")[isim].size() > 0;}));
    list_effSetDef.push_back(EfficiencySetDefinition("LS_E4E5", 13, [&](int isim) {return ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_LS_E4E5")[isim].size() > 0;}));

    bookEfficiencySets(list_effSetDef);

    ana.cutflow.bookCutflows();

    // Book Histograms
    ana.cutflow.bookHistograms(ana.histograms); // if just want to book everywhere

    // Looping input file
    while (ana.looper.nextEvent())
    {

        // If splitting jobs are requested then determine whether to process the event or not based on remainder
        if (ana.job_index != -1 and ana.nsplit_jobs != -1)
        {
            if (ana.looper.getNEventsProcessed() % ana.nsplit_jobs != (unsigned int) ana.job_index)
                continue;
        }

        // Reset all variables
        ana.tx.clear();

        setSDLVariables();

        fillEfficiencySets(list_effSetDef);

        //Do what you need to do in for each event here
        //To save use the following function
        ana.cutflow.fill();
    }

    // Writing output file
    ana.cutflow.saveOutput();

    // The below can be sometimes crucial
    delete ana.output_tfile;
}

AnalysisConfig::AnalysisConfig() : tx("variable", "variable")
{
}

void parseArguments(int argc, char** argv)
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
        ("j,nsplit_jobs" , "Enable splitting jobs by N blocks (--job_index must be set)"                                         , cxxopts::value<int>())
        ("I,job_index"   , "job_index of split jobs (--nsplit_jobs must be set. index starts from 0. i.e. 0, 1, 2, 3, etc...)"   , cxxopts::value<int>())
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

    //_______________________________________________________________________________
    // --nsplit_jobs
    if (result.count("nsplit_jobs"))
    {
        ana.nsplit_jobs = result["nsplit_jobs"].as<int>();
        if (ana.nsplit_jobs <= 0)
        {
            std::cout << options.help() << std::endl;
            std::cout << "ERROR: option string --nsplit_jobs" << ana.nsplit_jobs << " has zero or negative value!" << std::endl;
            std::cout << "I am not sure what this means..." << std::endl;
            exit(1);
        }
    }
    else
    {
        ana.nsplit_jobs = -1;
    }

    //_______________________________________________________________________________
    // --nsplit_jobs
    if (result.count("job_index"))
    {
        ana.job_index = result["job_index"].as<int>();
        if (ana.job_index < 0)
        {
            std::cout << options.help() << std::endl;
            std::cout << "ERROR: option string --job_index" << ana.job_index << " has negative value!" << std::endl;
            std::cout << "I am not sure what this means..." << std::endl;
            exit(1);
        }
    }
    else
    {
        ana.job_index = -1;
    }


    // Sanity check for split jobs (if one is set the other must be set too)
    if (result.count("job_index") or result.count("nsplit_jobs"))
    {
        // If one is not provided then throw error
        if ( not (result.count("job_index") and result.count("nsplit_jobs")))
        {
            std::cout << options.help() << std::endl;
            std::cout << "ERROR: option string --job_index and --nsplit_jobs must be set at the same time!" << std::endl;
            exit(1);
        }
        // If it is set then check for sanity
        else
        {
            if (ana.job_index >= ana.nsplit_jobs)
            {
                std::cout << options.help() << std::endl;
                std::cout << "ERROR: --job_index >= --nsplit_jobs ! This does not make sense..." << std::endl;
                exit(1);
            }
        }
    }

    //
    // Printing out the option settings overview
    //
    std::cout <<  "=========================================================" << std::endl;
    std::cout <<  " Setting of the analysis job based on provided arguments " << std::endl;
    std::cout <<  "---------------------------------------------------------" << std::endl;
    std::cout <<  " ana.input_file_list_tstring: " << ana.input_file_list_tstring <<  std::endl;
    std::cout <<  " ana.output_tfile: " << ana.output_tfile->GetName() <<  std::endl;
    std::cout <<  " ana.n_events: " << ana.n_events <<  std::endl;
    std::cout <<  " ana.nsplit_jobs: " << ana.nsplit_jobs <<  std::endl;
    std::cout <<  " ana.job_index: " << ana.job_index <<  std::endl;
    std::cout <<  "=========================================================" << std::endl;
}

void initializeInputsAndOutputs()
{
    // Create the TChain that holds the TTree's of the baby ntuples
    ana.events_tchain = RooUtil::FileUtil::createTChain(ana.input_tree_name, ana.input_file_list_tstring);

    // This is a standard thing SNT does pretty much every looper we use
    ana.looper.init(ana.events_tchain, &sdl, ana.n_events);

    // Set the cutflow object output file
    ana.cutflow.setTFile(ana.output_tfile);
}

void createSDLVariables()
{

    // hasAll12Hits
    ana.tx.createBranch<vector<int>>("sim_hasAll12HitsInBarrel");

    // Mini-Doublets
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_MD_B1");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_MD_B2");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_MD_B3");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_MD_B4");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_MD_B5");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_MD_B6");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_MD_E1");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_MD_E2");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_MD_E3");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_MD_E4");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_MD_E5");

    // Line segments
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_LS_B1B2");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_LS_B2B3");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_LS_B3B4");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_LS_B4B5");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_LS_B5B6");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_LS_B1E1");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_LS_B2E1");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_LS_B3E1");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_LS_B4E1");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_LS_B5E1");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_LS_E1E2");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_LS_E2E3");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_LS_E3E4");
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_LS_E4E5");

    // Pixel Line segments
    ana.tx.createBranch<vector<vector<int>>>("mtv_match_idxs_pLS_P");

    // Tracklets with Pixel
    ana.tx.createBranch<vector<int>>("mtv_match_idxs_pT4_PB1B2");
    ana.tx.createBranch<vector<int>>("mtv_match_idxs_pT4_PB2B3");
    ana.tx.createBranch<vector<int>>("mtv_match_idxs_pT4_PB3B4");
    ana.tx.createBranch<vector<int>>("mtv_match_idxs_pT4_PB4B5");
    ana.tx.createBranch<vector<int>>("mtv_match_idxs_pT4_PB5B6");
}

void setSDLVariables()
{

    for (unsigned int isim = 0; isim < sdl.sim_pt().size(); ++isim)
    {

        // hasAll12Hits
        ana.tx.pushbackToBranch<int>("sim_hasAll12HitsInBarrel", sdl.sim_hasAll12HitsInBarrel()[isim]);

        // Mini-Doublets
        std::array<std::vector<int>, 11> MD_idxs;
        for (auto& mdIdx : sdl.sim_mdIdx()[isim])
        {
            const int& layer = sdl.md_layer()[mdIdx][0];
            MD_idxs[layer-1].push_back(mdIdx);
        }

        // Set the MD idxs variables
        for (unsigned int imd = 0; imd < MD_types.size(); ++imd)
        {
            ana.tx.pushbackToBranch<vector<int>>(TString::Format("mtv_match_idxs_MD_%s", MD_types.at(imd).Data()), MD_idxs.at(imd));
        }

        // Line Segments
        std::array<std::vector<int>, 14> LS_idxs;
        for (auto& sgIdx : sdl.sim_sgIdx()[isim])
        {
            const int& layerIn = sdl.sg_layer()[sgIdx][0];
            const int& layerOut = sdl.sg_layer()[sgIdx][2];
            LS_idxs[LS_types_map[std::make_pair(layerIn, layerOut)]].push_back(sgIdx);
        }

        // Set the LS idxs variables
        for (unsigned int ils = 0; ils < LS_types.size(); ++ils)
        {
            ana.tx.pushbackToBranch<vector<int>>(TString::Format("mtv_match_idxs_LS_%s", LS_types.at(ils).Data()), LS_idxs.at(ils));
        }

        // // Pixel Line segments
        // ana.tx.pushbackToBranch<int>("mtv_match_idxs_pLS_P");

        // // Tracklets with Pixel
        // ana.tx.pushbackToBranch<int>("mtv_match_idxs_pT4_PB1B2");
        // ana.tx.pushbackToBranch<int>("mtv_match_idxs_pT4_PB2B3");
        // ana.tx.pushbackToBranch<int>("mtv_match_idxs_pT4_PB3B4");
        // ana.tx.pushbackToBranch<int>("mtv_match_idxs_pT4_PB4B5");
        // ana.tx.pushbackToBranch<int>("mtv_match_idxs_pT4_PB5B6");

    }

}

void printSDLVariables()
{
    for (unsigned int isimtrk = 0; isimtrk < sdl.sim_pt().size(); ++isimtrk)
        printSDLVariablesForATrack(isimtrk);
}

void printSDLVariablesForATrack(int isimtrk)
{

    // hasAll12Hits
    const int& hasAll12Hits = ana.tx.getBranch<vector<int>>("sim_hasAll12HitsInBarrel")[isimtrk];

    // Mini-Doublets
    bool hasMD_B1 = ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_B1")[isimtrk].size() > 0;
    bool hasMD_B2 = ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_B2")[isimtrk].size() > 0;
    bool hasMD_B3 = ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_B3")[isimtrk].size() > 0;
    bool hasMD_B4 = ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_B4")[isimtrk].size() > 0;
    bool hasMD_B5 = ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_B5")[isimtrk].size() > 0;
    bool hasMD_B6 = ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_B6")[isimtrk].size() > 0;
    bool hasMD_E1 = ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_E1")[isimtrk].size() > 0;
    bool hasMD_E2 = ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_E2")[isimtrk].size() > 0;
    bool hasMD_E3 = ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_E3")[isimtrk].size() > 0;
    bool hasMD_E4 = ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_E4")[isimtrk].size() > 0;
    bool hasMD_E5 = ana.tx.getBranch<vector<vector<int>>>("mtv_match_idxs_MD_E5")[isimtrk].size() > 0;

    const float& pt = sdl.sim_pt()[isimtrk];
    const float& eta = sdl.sim_eta()[isimtrk];
    const float& dz = sdl.sim_pca_dz()[isimtrk];
    const float& dxy = sdl.sim_pca_dxy()[isimtrk];
    const float& phi = sdl.sim_phi()[isimtrk];
    // const int& bunch = sdl.sim_bunchCrossing()[isimtrk];
    const int& pdgid = sdl.sim_pdgId()[isimtrk];

    std::cout << "isimtrk : " << isimtrk << std::endl;
    std::cout <<  " pt: " << pt <<  " eta: " << eta <<  " pdgid: " << pdgid <<  " dz: " << dz <<  " dxy: " << dxy <<  " phi: " << phi <<  std::endl;
    std::cout << "hasAll12Hits : " << hasAll12Hits << std::endl;
    std::cout <<  " hasMD_B1: " << hasMD_B1 <<  " hasMD_B2: " << hasMD_B2 <<  " hasMD_B3: " << hasMD_B3 <<  " hasMD_B4: " << hasMD_B4 <<  " hasMD_B5: " << hasMD_B5 <<  " hasMD_B6: " << hasMD_B6 <<  " hasMD_E1: " << hasMD_E1 <<  " hasMD_E2: " << hasMD_E2 <<  " hasMD_E3: " << hasMD_E3 <<  " hasMD_E4: " << hasMD_E4 <<  " hasMD_E5: " << hasMD_E5 <<  std::endl;

}

EfficiencySetDefinition::EfficiencySetDefinition(TString set_name_, int pdgid_, std::function<bool(int)> pass_)
{
    set_name = set_name_;
    pdgid = pdgid_;
    pass = pass_;
}

void bookEfficiencySets(std::vector<EfficiencySetDefinition>& effsets)
{
    for (auto& effset : effsets)
        bookEfficiencySet(effset);
}

void bookEfficiencySet(EfficiencySetDefinition& effset)
{

    std::vector<float> pt_boundaries = {0.5, 0.52, 0.54, 0.56, 0.58, 0.6, 0.62, 0.64, 0.66, 0.68, 0.7, 0.72, 0.74, 0.76, 0.78, 0.8, 0.82, 0.84, 0.86, 0.88, 0.9, 0.92, 0.94, 0.96, 0.98, 1.0, 1.02, 1.04, 1.06, 1.08, 1.1, 1.12, 1.14, 1.16, 1.18, 1.2, 1.22, 1.24, 1.26, 1.28, 1.3, 1.32, 1.34, 1.36, 1.38, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0};

    TString category_name = effset.set_name;

    // Denominator tracks' quantities
    ana.tx.createBranch<vector<float>>(category_name + "_denom_pt");
    ana.tx.createBranch<vector<float>>(category_name + "_denom_eta");
    ana.tx.createBranch<vector<float>>(category_name + "_denom_dxy");
    ana.tx.createBranch<vector<float>>(category_name + "_denom_dz");
    ana.tx.createBranch<vector<float>>(category_name + "_denom_phi");

    // Numerator tracks' quantities
    ana.tx.createBranch<vector<float>>(category_name + "_numer_pt");
    ana.tx.createBranch<vector<float>>(category_name + "_numer_eta");
    ana.tx.createBranch<vector<float>>(category_name + "_numer_dxy");
    ana.tx.createBranch<vector<float>>(category_name + "_numer_dz");
    ana.tx.createBranch<vector<float>>(category_name + "_numer_phi");

    // Histogram utility object that is used to define the histograms
    ana.histograms.addVecHistogram(category_name + "_h_denom_pt"  , pt_boundaries     , [&, category_name]() { return ana.tx.getBranchLazy<vector<float>>(category_name + "_denom_pt"); } );
    ana.histograms.addVecHistogram(category_name + "_h_numer_pt"  , pt_boundaries     , [&, category_name]() { return ana.tx.getBranchLazy<vector<float>>(category_name + "_numer_pt"); } );
    ana.histograms.addVecHistogram(category_name + "_h_denom_eta" , 30 , -2.5  , 2.5  , [&, category_name]() { return ana.tx.getBranchLazy<vector<float>>(category_name + "_denom_eta"); } );
    ana.histograms.addVecHistogram(category_name + "_h_numer_eta" , 30 , -2.5  , 2.5  , [&, category_name]() { return ana.tx.getBranchLazy<vector<float>>(category_name + "_numer_eta"); } );
    ana.histograms.addVecHistogram(category_name + "_h_denom_dxy" , 30 , -10.  , 10.  , [&, category_name]() { return ana.tx.getBranchLazy<vector<float>>(category_name + "_denom_dxy"); } );
    ana.histograms.addVecHistogram(category_name + "_h_numer_dxy" , 30 , -10.  , 10.  , [&, category_name]() { return ana.tx.getBranchLazy<vector<float>>(category_name + "_numer_dxy"); } );
    ana.histograms.addVecHistogram(category_name + "_h_denom_dz"  , 30 , -30.  , 30.  , [&, category_name]() { return ana.tx.getBranchLazy<vector<float>>(category_name + "_denom_dz"); } );
    ana.histograms.addVecHistogram(category_name + "_h_numer_dz"  , 30 , -30.  , 30.  , [&, category_name]() { return ana.tx.getBranchLazy<vector<float>>(category_name + "_numer_dz"); } );
    ana.histograms.addVecHistogram(category_name + "_h_denom_phi" , 30 , -M_PI , M_PI , [&, category_name]() { return ana.tx.getBranchLazy<vector<float>>(category_name + "_denom_phi"); } );
    ana.histograms.addVecHistogram(category_name + "_h_numer_phi" , 30 , -M_PI , M_PI , [&, category_name]() { return ana.tx.getBranchLazy<vector<float>>(category_name + "_numer_phi"); } );

}

void fillEfficiencySets(std::vector<EfficiencySetDefinition>& effsets)
{
    for (unsigned int isimtrk = 0; isimtrk < sdl.sim_pt().size(); ++isimtrk)
    {
        for (auto& effset : effsets)
        {
            fillEfficiencySet(isimtrk, effset);
        }
    }
}

void fillEfficiencySet(int isimtrk, EfficiencySetDefinition& effset)
{
    const float& pt = sdl.sim_pt()[isimtrk];
    const float& eta = sdl.sim_eta()[isimtrk];
    const float& dz = sdl.sim_pca_dz()[isimtrk];
    const float& dxy = sdl.sim_pca_dxy()[isimtrk];
    const float& phi = sdl.sim_phi()[isimtrk];
    const int& bunch = sdl.sim_bunchCrossing()[isimtrk];
    const int& pdgid = sdl.sim_pdgId()[isimtrk];

    if (abs(dz) > 30 or abs(dxy) > 2.5 or bunch != 0 or abs(pdgid) != 13)
        return;

    TString category_name = effset.set_name;

    if (category_name.Contains("B6"))
    {
    }

    if (pt > 1.5)
        ana.tx.pushbackToBranch<float>(category_name + "_denom_eta", eta);
    if (abs(eta) < 2.5)
        ana.tx.pushbackToBranch<float>(category_name + "_denom_pt", pt);
    if (abs(eta) < 2.5 and pt > 1.5)
        ana.tx.pushbackToBranch<float>(category_name + "_denom_phi", phi);
    if (abs(eta) < 2.5 and pt > 1.5)
        ana.tx.pushbackToBranch<float>(category_name + "_denom_dxy", dxy);
    if (abs(eta) < 2.5 and pt > 1.5)
        ana.tx.pushbackToBranch<float>(category_name + "_denom_dz", dz);

    if (effset.pass(isimtrk))
    {
        if (pt > 1.5)
            ana.tx.pushbackToBranch<float>(category_name + "_numer_eta", eta);
        if (abs(eta) < 2.5)
            ana.tx.pushbackToBranch<float>(category_name + "_numer_pt", pt);
        if (abs(eta) < 2.5 and pt > 1.5)
            ana.tx.pushbackToBranch<float>(category_name + "_numer_phi", phi);
        if (abs(eta) < 2.5 and pt > 1.5)
            ana.tx.pushbackToBranch<float>(category_name + "_numer_dxy", dxy);
        if (abs(eta) < 2.5 and pt > 1.5)
            ana.tx.pushbackToBranch<float>(category_name + "_numer_dz", dz);
    }
}

