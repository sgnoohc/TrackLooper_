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

    ./doAnalysis -i /hadoop/cms/store/user/slava77/CMSSW_10_4_0_patch1-tkNtuple/pass-e072c1a/27411.0_TenMuExtendedE_0_200/trackingNtuple.root -d -n -1 -t trackingNtuple/tree -n 10 # Running 10 events only
