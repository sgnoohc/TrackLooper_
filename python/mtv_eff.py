#!/bin/env python

# Tracking Ntuple MTV efficiency code
# Philip Chang

import ROOT as r
r.gROOT.SetBatch(True)
r.gROOT.ProcessLine(".L SDL/sdl.so")
r.gROOT.ProcessLine(".L SDL/Algo.h")
r.gROOT.ProcessLine(".L SDL/Constants.h")
r.gROOT.ProcessLine(".L SDL/EndcapGeometry.h")
r.gROOT.ProcessLine(".L SDL/Event.h")
r.gROOT.ProcessLine(".L SDL/GeometryUtil.h")
r.gROOT.ProcessLine(".L SDL/Hit.h")
r.gROOT.ProcessLine(".L SDL/Layer.h")
r.gROOT.ProcessLine(".L SDL/MathUtil.h")
r.gROOT.ProcessLine(".L SDL/MiniDoublet.h")
r.gROOT.ProcessLine(".L SDL/Module.h")
r.gROOT.ProcessLine(".L SDL/ModuleConnectionMap.h")
r.gROOT.ProcessLine(".L SDL/PrintUtil.h")
r.gROOT.ProcessLine(".L SDL/Segment.h")
r.gROOT.ProcessLine(".L SDL/TiltedGeometry.h")
r.gROOT.ProcessLine(".L SDL/TrackCandidate.h")
r.gROOT.ProcessLine(".L SDL/Tracklet.h")
r.gROOT.ProcessLine(".L SDL/TrackletBase.h")
r.gROOT.ProcessLine(".L SDL/Triplet.h")
r.SDL.endcapGeometry.load("/home/users/phchang/public_html/analysis/sdl/TrackLooper_/scripts/endcap_orientation_data_v2.txt");
r.SDL.tiltedGeometry.load("/home/users/phchang/public_html/analysis/sdl/TrackLooper_/scripts/tilted_orientation_data.txt");
r.SDL.moduleConnectionMap.load("/home/users/phchang/public_html/analysis/sdl/TrackLooper_/scripts/module_connection_map_data_10_e0_200_100_pt0p8_2p0_400_pt0p8_2p0_nolossers_dxy35cm_endcaplayer2.txt");

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
