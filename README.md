# TrackLooper

## Install

    git clone --recurse-submodules git@github.com:sgnoohc/TrackLooper.git
    cd TrackLooper
    source rooutil/thisrooutil.sh # set rooutil
    source rooutil/root.sh # set ROOT
    make clean;
    make -j;

## Running Executable ```doAnalysis```

    $ ./doAnalysis
    
             **********************
             *                    *
             *       Looper       *
             *                    *
             **********************
    
    Usage:
    
      $ doAnalysis [OPTION...]
    
      -i, --input arg    Comma separated input file list OR if just a directory
                         is provided it will glob all in the directory BUT must end
                         with '/' for the path
      -t, --tree arg     Name of the tree in the root file to open and loop over
      -o, --output arg   Output file name
      -n, --nevents arg  N events to loop over (default: -1)
      -d, --debug        Run debug job. i.e. overrides output option to
                         'debug.root' and 'recreate's the file.
      -h, --help         Print help

To Run a job

    ./doAnalysis -i <path/to/trackingNtuple.root> -t <path/to/TTree/in/trackingNtuple/root/file> -o <path/to/output.root> -n <nevents>

Or to run a test (debug) job (-o option will be ignored and will output to ```debug.root``` regardless of what you provide)

    ./doAnalysis -i <path/to/trackingNtuple.root> -t <path/to/TTree/in/trackingNtuple/root/file> (if provided will be ignored: -o <path/to/output.root>) -n <nevents> -d

Example:

    ./doAnalysis -i /hadoop/cms/store/user/slava77/CMSSW_10_4_0_patch1-tkNtuple/pass-e072c1a/27411.0_TenMuExtendedE_0_200/trackingNtuple.root -d -n -1 -t trackingNtuple/tree -n 1 # Running 1 event only

Example output running over the first event (the first event happens to have only 4 hits in the event)

    $ ./doAnalysis -i /hadoop/cms/store/user/slava77/CMSSW_10_4_0_patch1-tkNtuple/pass-e072c1a/27411.0_TenMuExtendedE_0_200/trackingNtuple.root -d -n -1 -t trackingNtuple/tree -n 1
    =========================================================
     Setting of the analysis job based on provided arguments
    ---------------------------------------------------------
     ana.input_file_list_tstring: /hadoop/cms/store/user/slava77/CMSSW_10_4_0_patch1-tkNtuple/pass-e072c1a/27411.0_TenMuExtendedE_0_200/trackingNtuple.root
     ana.output_tfile: debug.root
     ana.n_events: 1
    =========================================================
    RooUtil:: Adding /hadoop/cms/store/user/slava77/CMSSW_10_4_0_patch1-tkNtuple/pass-e072c1a/27411.0_TenMuExtendedE_0_200/trackingNtuple.root
    RooUtil:: Start EventLooping
    RooUtil:: System info:
    uaf-10.t2.ucsd.edu
    Linux uaf-10.t2.ucsd.edu 2.6.32-754.3.5.el6.x86_64 #1 SMP Tue Aug 14 20:46:41 UTC 2018 x86_64 x86_64 x86_64 GNU/Linux
    Wed Apr  3 11:52:27 PDT 2019
    phchang
    /home/users/phchang/public_html/analysis/sdl/TrackLooper
    RooUtil::  _
    RooUtil:: /\\
    RooUtil:: \ \\  \__/ \__/
    RooUtil::  \ \\ (oo) (oo)  Here we come!
    RooUtil::   \_\\/~~\_/~~\_
    RooUtil::  _.-~===========~-._
    RooUtil:: (___________________)
    RooUtil::       \_______/
    RooUtil::
    RooUtil::  Your friendly aliens
    RooUtil::      Surf & Turf
    RooUtil::
    Warning in <TClass::Init>: no dictionary for class ROOT::TIOFeatures is available
    RooUtil:: Total Events in this Chain to process = 1
    RooUtil:: Cut name                         |pass|weight|systs
    RooUtil:: ====================================================
    RooUtil:: Root                             | 0 | 0.000000|
    RooUtil:: TTreeCache enabled
    RooUtil:: Looping /hadoop/cms/store/user/slava77/CMSSW_10_4_0_patch1-tkNtuple/pass-e072c1a/27411.0_TenMuExtendedE_0_200/trackingNtuple.root/TTree:tree
    SDL::
    SDL::  ==============
    SDL::  Printing Event
    SDL::  ==============
    SDL::
    SDL::  ==============================
    SDL::  Module(detId=412361801, subdet=4, side=1, layer=5, rod=0, ring=2, module=18, isLower=1)
    SDL::  ==============================
    SDL::  Hit(x=-27.3033, y=-26.7023, z=-264.03, r3=266.778, rt=38.1901, phi=3.91586)
    SDL::
    SDL::  ==============================
    SDL::  Module(detId=412361802, subdet=4, side=1, layer=5, rod=0, ring=2, module=18, isLower=0)
    SDL::  ==============================
    SDL::  Hit(x=-27.1477, y=-26.5467, z=-264.43, r3=267.142, rt=37.9701, phi=3.9158)
    SDL::
    SDL::  ==============================
    SDL::  Module(detId=420746257, subdet=4, side=2, layer=5, rod=0, ring=1, module=4, isLower=1)
    SDL::  ==============================
    SDL::  Hit(x=27.8826, y=24.5097, z=265.97, r3=268.548, rt=37.1236, phi=0.721109)
    SDL::
    SDL::  ==============================
    SDL::  Module(detId=420746258, subdet=4, side=2, layer=5, rod=0, ring=1, module=4, isLower=0)
    SDL::  ==============================
    SDL::  Hit(x=27.4123, y=24.0464, z=265.57, r3=268.062, rt=36.4646, phi=0.720083)
    SDL::
    RooUtil:: Wrote output to debug.root
    RooUtil::
    RooUtil::    \__/    \__/
    RooUtil::  S (oo)    (oo)
    RooUtil:: (\//~~\\  //~~\\
    RooUtil::  \/\__//  \\__//\T
    RooUtil::    ||||    ||\\ Who cares!
    RooUtil:: __ |||| __ |||| ___
    RooUtil::   (_)(_)  (_)(_)
    RooUtil::
    
    ------------------------------
    CPU  Time:      0.2
    Real Time:      0.3


