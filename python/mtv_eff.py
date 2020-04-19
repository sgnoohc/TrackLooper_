#!/bin/env python

# Tracking Ntuple MTV efficiency code
# Philip Chang

import ROOT as r
import sys
import os
import math
import trkcore

# Open the input data
t = r.TChain("trackingNtuple/tree")
t.Add("/home/users/phchang/public_html/analysis/sdl/trackingNtuple/CMSSW_10_4_0/src/trackingNtuple_100_pt0p5_2p0.root")

# Set verbose mode
verbose = 1

# Open the output root file
f = r.TFile("output.root", "recreate")
tt = r.TTree("tree", "tree")

# Set the RooUtil cutflow object
cutflow = r.RooUtil.Cutflow()
cutflow.setTFile(f)

# Create TTreeX variable for study
tx = r.RooUtil.TTreeX(tt)
tx.createBranch('float')("sim_pt")

tx.setBranch('float')("sim_pt", 3.)

print(tx.getBranch('float')("sim_pt"))

sys.exit()

# Loop over events
for index, event in enumerate(t):

    # Retrieve good barrel track
    list_of_good_barrel_tracks = trkcore.listOfGoodBarrelTracks(t)

    # Get an SDL event and run the reco on them
    sdlEvent = trkcore.getSDLEvent(t, verbose)
