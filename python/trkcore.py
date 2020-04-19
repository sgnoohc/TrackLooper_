#!/bin/env import

import ROOT as r

##############################################################
#
# Useful objects
#
##############################################################

#_____________________________________________________________
# Track object
class Track():
    def __init__(self, t, simtrk_idx):
        self.simtrk_idx = simtrk_idx
        self.pt = t.sim_pt[simtrk_idx]
        self.eta = t.sim_eta[simtrk_idx]
        self.phi = t.sim_phi[simtrk_idx]
        self.pdgId = t.sim_pdgId[simtrk_idx]
        self.q = t.sim_q[simtrk_idx]
        self.dz = t.sim_pca_dz[simtrk_idx]
        self.dxy = t.sim_pca_dxy[simtrk_idx]

##############################################################
#
# Steering SDL
#
##############################################################

#_____________________________________________________________
# Run the main SDL algorithm
def getSDLEvent(t, verbose=0):

    # Create SDL Event
    sdlEvent = r.SDL.Event()

    # Loop over reco hits
    for hit_idx, (x, y, z, subdet, layer, detid) in enumerate(zip(t.ph2_x, t.ph2_y, t.ph2_z, t.ph2_subdet, t.ph2_layer, t.ph2_detId)):

        # Then it is in outer tracker
        if subdet == 5 or subdet == 4:

            # Add the hit to the SDL::Event
            sdlEvent.addHitToModule(r.SDL.Hit(x, y, z, hit_idx), t.ph2_detId[hit_idx])

    if verbose:
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
    if verbose:
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
    if verbose:
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
    if verbose:
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
    if verbose:
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

    return sdlEvent


#_____________________________________________________________
# Checks whether a segment is from a true track or not
# Checks the associated simhit's simtrk idx
# and check whether there is a common trkidx associated
# with the anchor hits
# TODO if it is a 2S module, check if one of the two match
# For now, it will use lower one only
def isTrueSegment(sg, t):

    # Get inner anchorHit idx
    iMD_hitidx = sg.innerMiniDoubletPtr().anchorHitPtr().idx()

    # Get list of trk idx associated with the anchorHit
    innerMD_trk_idx = []
    for simhitidx in t.ph2_simHitIdx[iMD_hitidx]:
        t.simhit_particle
        innerMD_trk_idx.append(t.simhit_simTrkIdx[simhitidx])

    # Get list of trk idx associated with the anchorHit
    oMD_hitidx = sg.outerMiniDoubletPtr().anchorHitPtr().idx()
    outerMD_trk_idx = []
    for simhitidx in t.ph2_simHitIdx[oMD_hitidx]:
        outerMD_trk_idx.append(t.simhit_simTrkIdx[simhitidx])

    # Intersection of two list
    common_trk_idx = [value for value in innerMD_trk_idx if value in outerMD_trk_idx] 

    return len(common_trk_idx) > 0

#_____________________________________________________________
# Good barrel tracks is where at least one sim hit with correct pdgid land on each layer
# Does not require pair of hits land on each layer.
# Does not require that the paired hits land on module pairs.
# Does not care whether a single layer has 4 hits
# Only one sim hit with correct pdgid is needed per layer to pass the requirement
# Input: TTree event, and sim trk index
def goodBarrelTracks(t, simtrk_idx):

    # List of layer index with the simhit with correct pdgid
    # Check this later to get the list
    layer_idx_with_hits = []

    # Loop over the sim hit index
    for simhitidx in t.sim_simHitIdx[simtrk_idx]:

        # If not a correct sim hit skip
        if t.simhit_particle[simhitidx] != t.sim_pdgId[simtrk_idx]:
            continue

        # Check it is barrel
        if t.simhit_subdet[simhitidx] != 5:
            continue

        # Add the layer index
        layer_idx_with_hits.append(t.simhit_layer[simhitidx])

    if sorted(list(set(layer_idx_with_hits))) == [1, 2, 3, 4, 5, 6]:
        return True
    else:
        return False

#_____________________________________________________________
# Get list of goodBarrelTracks
def listOfGoodBarrelTracks(t):

    list_of_good_barrel_tracks = []

    # Loop over sim tracks
    for simtrk_idx, pt in enumerate(t.sim_pt):

        # Ask whether this is a good denominator
        if goodBarrelTracks(t, simtrk_idx):

            list_of_good_barrel_tracks.append(Track(t, simtrk_idx))

    return list_of_good_barrel_tracks


#_____________________________________________________________
def barrelTruthTracks(t, layer_requirement=[1,1,1,1,1,1]):

    # Return object
    rtn_obj = []

    # loop over tracks
    for index, (pt, eta, phi, q, dz, dxy, pdgid, bx) in enumerate(zip(t.sim_pt, t.sim_eta, t.sim_phi, t.sim_q, t.sim_pca_dz, t.sim_pca_dxy, t.sim_pdgId, t.sim_bunchCrossing)):

        # If not barrel eta continue
        if abs(eta) > 0.8:
            continue

        # Check simhit layers
        simhit_layers = []
        for simhitidx in t.sim_simHitIdx[index]:
            if t.simhit_subdet[simhitidx] == 5 and t.simhit_particle[simhitidx] == t.sim_pdgId[index]:
                simhit_layers.append(t.simhit_layer[simhitidx])

        # pass simhit_layer requirement
        is_good = True
        for index, req in enumerate(layer_requirement):
            if req:
                if index + 1 not in simhit_layers:
                    is_good = False

        if not is_good:
            continue

        hit_layers = []
        for simhitidx in t.sim_simHitIdx[index]:
            if t.simhit_subdet[simhitidx] == 5 and t.simhit_particle[simhitidx] == t.sim_pdgId[index]:
                for hitidx in t.simhit_hitIdx[simhitidx]:
                    if t.ph2_subdet[hitidx] == 5:
                        hit_layers.append(t.ph2_layer[hitidx])
        if len(list(set(hit_layers))) == 6:
            all_sim_in_0misshit.append((pt, eta, phi, q, dz, dxy, pdgid, index))

        # pass hit_layer requirement
        is_good = True
        for index, req in enumerate(layer_requirement):
            if req:
                if index + 1 not in hit_layers:
                    is_good = False

        if not is_good:
            continue

        rtn_obj.append((pt, eta, phi, q, dz, dxy, pdgid, index))

    return rtn_obj

