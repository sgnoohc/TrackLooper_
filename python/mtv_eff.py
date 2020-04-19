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

verbose = 1

# Loop over events
for index, event in enumerate(t):

    # Retrieve good barrel track
    list_of_good_barrel_tracks = trkcore.listOfGoodBarrelTracks(t)

    # Get an SDL event and run the reco on them
    sdlEvent = trkcore.getSDLEvent(t, verbose)
