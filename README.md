# TrackLooper

## Install

    git clone --recurse-submodules git@github.com:sgnoohc/TrackLooper.git
    cd TrackLooper
    source rooutil/thisrooutil.sh # set rooutil
    source rooutil/root.sh # set ROOT
    make clean;
    make -j all; # Make the main SDL binary
    cd efficiency/
    make -j # Make the efficiency code binary
    cd ../

## Obtaining detector geometry via the centroids

    ./bin/sdl -i "/nfs-7/userdata/phchang/trackingNtuple/trackingNtuple_*.root" -t trackingNtuple/tree -d -m 1 # creates data/all_sim_hits.root
    python scripts/module_bound_fit.py # creates data/phase2.txt

## Building map

Folloing command creates ```data/conn.txt```.  Afterwards, copy it to a ```conn.py``` format.

    ./bin/sdl -m 0 -i /nfs-7/userdata/phchang/trackingNtuple/trackingNtuple_400_pt_0p8_2p0.root,/nfs-7/userdata/phchang/trackingNtuple/trackingNtuple_10MuGun.root,/nfs-7/userdata/phchang/trackingNtuple/trackingNtuple_hundred_pt_0p8_2p0.root

Then run the following command. (Watch out for the import statements)

    python SDLpython/build_module_connection.py

## Running SDL and writing ""SDL tracking ntuple""

Following are list of available sample choices

    SAMPLEID = 1  : pt 0.5 to 2.0 hundred-mu-gun sample
               2  : e 0 to 200 ten-mu-gun sample
               3  : pu200 ttbar (252 events without sim info on pileup tracks) with sdl option --pdg_id == 13
               4  : pu200 ttbar (252 events without sim info on pileup tracks) with sdl option --pdg_id == 211
               5  : pu200 ttbar (252 events without sim info on pileup tracks) with sdl option --pdg_id == 11
               6  : DO NOT USE: displaced SUSY stuff (not sure what)
               7  : pu200 ctau100 of some SUSY? with sdl option --pdg_id == 13
               8  : pu200 ctau100 of some SUSY? with sdl option --pdg_id == 211
               9  : pu200 ctau100 of some SUSY? with sdl option --pdg_id == 11
               10 : pt 0.5 to 3.0 hundred-mu-gun sample
               11 : pt 0.5 to 5.0 ten-mu-gun sample
               12 : pu200 ttbar (500 evt) with sdl option --pdg_id == 13
               13 : pu200 ttbar (500 evt) with sdl option --pdg_id == 211
               14 : pu200 ttbar (500 evt) with sdl option --pdg_id == 11
               15 : pu200 ttbar (500 evt) with sdl option --pdg_id == 0 (0 means all charged particle)
               17 : 5 cm 'cube' with pt 0.5 to 50 ten-mu-gun
               18 : 50 cm 'cube' with pt 0.5 to 50 ten-mu-gun
               19 : ttbar (pu 200?)
               20 : 100 pion gun pt 0.5 to 50 GeV

To run the 100 mu gun 0.5 to 2.0 GeV sample setup

    sh shell/sdlv2.sh -s 1 -t MyTag -d "JobTag"  -w


