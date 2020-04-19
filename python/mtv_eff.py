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

import sys
import os
import math
import trkcore

# Open the input data
t = r.TChain("trackingNtuple/tree")
t.Add("/home/users/phchang/public_html/analysis/sdl/trackingNtuple/CMSSW_10_4_0/src/trackingNtuple_100_pt0p5_2p0.root")

# Loop over events
for index, event in enumerate(t):

    # Loop over sim tracks
    for simtrk_idx, pt in enumerate(t.sim_pt):

        # Ask whether this is a good denominator
        if trkcore.goodBarrelTracks(t, simtrk_idx):

            continue


    # Create SDL Event
    sdlEvent = r.SDL.Event()

    # Loop over reco hits
    for hit_idx, (x, y, z, subdet, layer, detid) in enumerate(zip(t.ph2_x, t.ph2_y, t.ph2_z, t.ph2_subdet, t.ph2_layer, t.ph2_detId)):

        # Then it is in outer tracker
        if subdet == 5 or subdet == 4:

            sdlEvent.addHitToModule(r.SDL.Hit(x, y, z, hit_idx), t.ph2_detId[hit_idx])

    # Print hit information
    print("# of Hits : {}" .format( sdlEvent.getNumberOfHits()))
    print("# of Hits in layer 1: {}" .format( sdlEvent.getNumberOfHitsByLayerBarrel(0)))
    print("# of Hits in layer 2: {}" .format( sdlEvent.getNumberOfHitsByLayerBarrel(1)))
    print("# of Hits in layer 3: {}" .format( sdlEvent.getNumberOfHitsByLayerBarrel(2)))
    print("# of Hits in layer 4: {}" .format( sdlEvent.getNumberOfHitsByLayerBarrel(3)))
    print("# of Hits in layer 5: {}" .format( sdlEvent.getNumberOfHitsByLayerBarrel(4)))
    print("# of Hits in layer 6: {}" .format( sdlEvent.getNumberOfHitsByLayerBarrel(5)))
    print("# of Hits Upper Module in layer 1: {}" .format( sdlEvent.getNumberOfHitsByLayerBarrelUpperModule(0)))
    print("# of Hits Upper Module in layer 2: {}" .format( sdlEvent.getNumberOfHitsByLayerBarrelUpperModule(1)))
    print("# of Hits Upper Module in layer 3: {}" .format( sdlEvent.getNumberOfHitsByLayerBarrelUpperModule(2)))
    print("# of Hits Upper Module in layer 4: {}" .format( sdlEvent.getNumberOfHitsByLayerBarrelUpperModule(3)))
    print("# of Hits Upper Module in layer 5: {}" .format( sdlEvent.getNumberOfHitsByLayerBarrelUpperModule(4)))
    print("# of Hits Upper Module in layer 6: {}" .format( sdlEvent.getNumberOfHitsByLayerBarrelUpperModule(5)))

    # Run minidoublet
    sdlEvent.createMiniDoublets();
    print("# of Mini-doublets produced: {}" .format( sdlEvent.getNumberOfMiniDoublets()))
    print("# of Mini-doublets produced layer 1: {}" .format( sdlEvent.getNumberOfMiniDoubletsByLayerBarrel(0)))
    print("# of Mini-doublets produced layer 2: {}" .format( sdlEvent.getNumberOfMiniDoubletsByLayerBarrel(1)))
    print("# of Mini-doublets produced layer 3: {}" .format( sdlEvent.getNumberOfMiniDoubletsByLayerBarrel(2)))
    print("# of Mini-doublets produced layer 4: {}" .format( sdlEvent.getNumberOfMiniDoubletsByLayerBarrel(3)))
    print("# of Mini-doublets produced layer 5: {}" .format( sdlEvent.getNumberOfMiniDoubletsByLayerBarrel(4)))
    print("# of Mini-doublets produced layer 6: {}" .format( sdlEvent.getNumberOfMiniDoubletsByLayerBarrel(5)))
    print("# of Mini-doublets considered: {}" .format( sdlEvent.getNumberOfMiniDoubletCandidates()))
    print("# of Mini-doublets considered layer 1: {}" .format( sdlEvent.getNumberOfMiniDoubletCandidatesByLayerBarrel(0)))
    print("# of Mini-doublets considered layer 2: {}" .format( sdlEvent.getNumberOfMiniDoubletCandidatesByLayerBarrel(1)))
    print("# of Mini-doublets considered layer 3: {}" .format( sdlEvent.getNumberOfMiniDoubletCandidatesByLayerBarrel(2)))
    print("# of Mini-doublets considered layer 4: {}" .format( sdlEvent.getNumberOfMiniDoubletCandidatesByLayerBarrel(3)))
    print("# of Mini-doublets considered layer 5: {}" .format( sdlEvent.getNumberOfMiniDoubletCandidatesByLayerBarrel(4)))
    print("# of Mini-doublets considered layer 6: {}" .format( sdlEvent.getNumberOfMiniDoubletCandidatesByLayerBarrel(5)))

    # Run segment
    sdlEvent.createSegmentsWithModuleMap();
    # sdlEvent.createSegmentsWithModuleMap();
    print("# of Segments produced: {}" .format( sdlEvent.getNumberOfSegments()))
    print("# of Segments produced layer 1: {}" .format( sdlEvent.getNumberOfSegmentsByLayerBarrel(0)))
    print("# of Segments produced layer 2: {}" .format( sdlEvent.getNumberOfSegmentsByLayerBarrel(1)))
    print("# of Segments produced layer 3: {}" .format( sdlEvent.getNumberOfSegmentsByLayerBarrel(2)))
    print("# of Segments produced layer 4: {}" .format( sdlEvent.getNumberOfSegmentsByLayerBarrel(3)))
    print("# of Segments produced layer 5: {}" .format( sdlEvent.getNumberOfSegmentsByLayerBarrel(4)))
    print("# of Segments produced layer 6: {}" .format( sdlEvent.getNumberOfSegmentsByLayerBarrel(5)))
    print("# of Segments considered: {}" .format( sdlEvent.getNumberOfSegmentCandidates()))
    print("# of Segments considered layer 1: {}" .format( sdlEvent.getNumberOfSegmentCandidatesByLayerBarrel(0)))
    print("# of Segments considered layer 2: {}" .format( sdlEvent.getNumberOfSegmentCandidatesByLayerBarrel(1)))
    print("# of Segments considered layer 3: {}" .format( sdlEvent.getNumberOfSegmentCandidatesByLayerBarrel(2)))
    print("# of Segments considered layer 4: {}" .format( sdlEvent.getNumberOfSegmentCandidatesByLayerBarrel(3)))
    print("# of Segments considered layer 5: {}" .format( sdlEvent.getNumberOfSegmentCandidatesByLayerBarrel(4)))
    print("# of Segments considered layer 6: {}" .format( sdlEvent.getNumberOfSegmentCandidatesByLayerBarrel(5)))

    # Run tracklets
    sdlEvent.createTrackletsWithModuleMap();
    # sdlEvent.createTrackletsViaNavigation();
    print("# of Tracklets produced: {}" .format( sdlEvent.getNumberOfTracklets()))
    print("# of Tracklets produced layer 1: {}" .format( sdlEvent.getNumberOfTrackletsByLayerBarrel(0)))
    print("# of Tracklets produced layer 2: {}" .format( sdlEvent.getNumberOfTrackletsByLayerBarrel(1)))
    print("# of Tracklets produced layer 3: {}" .format( sdlEvent.getNumberOfTrackletsByLayerBarrel(2)))
    print("# of Tracklets produced layer 4: {}" .format( sdlEvent.getNumberOfTrackletsByLayerBarrel(3)))
    print("# of Tracklets produced layer 5: {}" .format( sdlEvent.getNumberOfTrackletsByLayerBarrel(4)))
    print("# of Tracklets produced layer 6: {}" .format( sdlEvent.getNumberOfTrackletsByLayerBarrel(5)))
    print("# of Tracklets considered: {}" .format( sdlEvent.getNumberOfTrackletCandidates()))
    print("# of Tracklets considered layer 1: {}" .format( sdlEvent.getNumberOfTrackletCandidatesByLayerBarrel(0)))
    print("# of Tracklets considered layer 2: {}" .format( sdlEvent.getNumberOfTrackletCandidatesByLayerBarrel(1)))
    print("# of Tracklets considered layer 3: {}" .format( sdlEvent.getNumberOfTrackletCandidatesByLayerBarrel(2)))
    print("# of Tracklets considered layer 4: {}" .format( sdlEvent.getNumberOfTrackletCandidatesByLayerBarrel(3)))
    print("# of Tracklets considered layer 5: {}" .format( sdlEvent.getNumberOfTrackletCandidatesByLayerBarrel(4)))
    print("# of Tracklets considered layer 6: {}" .format( sdlEvent.getNumberOfTrackletCandidatesByLayerBarrel(5)))

    # Run track candidates
    sdlEvent.createTrackCandidatesFromTracklets();
    print("# of TrackCandidates produced: {}" .format( sdlEvent.getNumberOfTrackCandidates()))
    print("# of TrackCandidates produced layer 1: {}" .format( sdlEvent.getNumberOfTrackCandidatesByLayerBarrel(0)))
    print("# of TrackCandidates produced layer 2: {}" .format( sdlEvent.getNumberOfTrackCandidatesByLayerBarrel(1)))
    print("# of TrackCandidates produced layer 3: {}" .format( sdlEvent.getNumberOfTrackCandidatesByLayerBarrel(2)))
    print("# of TrackCandidates produced layer 4: {}" .format( sdlEvent.getNumberOfTrackCandidatesByLayerBarrel(3)))
    print("# of TrackCandidates produced layer 5: {}" .format( sdlEvent.getNumberOfTrackCandidatesByLayerBarrel(4)))
    print("# of TrackCandidates produced layer 6: {}" .format( sdlEvent.getNumberOfTrackCandidatesByLayerBarrel(5)))
    print("# of TrackCandidates considered: {}" .format( sdlEvent.getNumberOfTrackCandidateCandidates()))
    print("# of TrackCandidates considered layer 1: {}" .format( sdlEvent.getNumberOfTrackCandidateCandidatesByLayerBarrel(0)))
    print("# of TrackCandidates considered layer 2: {}" .format( sdlEvent.getNumberOfTrackCandidateCandidatesByLayerBarrel(1)))
    print("# of TrackCandidates considered layer 3: {}" .format( sdlEvent.getNumberOfTrackCandidateCandidatesByLayerBarrel(2)))
    print("# of TrackCandidates considered layer 4: {}" .format( sdlEvent.getNumberOfTrackCandidateCandidatesByLayerBarrel(3)))
    print("# of TrackCandidates considered layer 5: {}" .format( sdlEvent.getNumberOfTrackCandidateCandidatesByLayerBarrel(4)))
    print("# of TrackCandidates considered layer 6: {}" .format( sdlEvent.getNumberOfTrackCandidateCandidatesByLayerBarrel(5)))

    break
