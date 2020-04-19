#!/bin/env import

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

    print(layer_idx_with_hits)

    if sorted(list(set(layer_idx_with_hits))) == [1, 2, 3, 4, 5, 6]:
        return True
    else:
        return False

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

