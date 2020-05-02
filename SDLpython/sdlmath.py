#!/bin/env python

import matplotlib
matplotlib.use('pdf')
import matplotlib.pyplot as plt
from matplotlib.collections import LineCollection
import pickle
import numpy as np
import math

def get_track_points(pt, eta, phi, vx, vy, vz, charge):
    print(pt, eta, phi, vx, vy, vz, charge)

    # Reference point for sim track is based on simvtx_x,y,z (which I think is same as point of closest approach, but I am not 100% sure.)
    # N.B. Signs of the values are kind of disorganized... readers be aware
    radius = pt / (2.99792458e-3 * 3.8) * (charge) * -1 # signed radius of the helix (by charge)
    ref_vec = np.array([vx, vy, vz]) # reference point vector
    lam = math.copysign(math.pi/2.-2.*math.atan(math.exp(-abs(eta))), eta) # lambda
    print(lam, eta)

    # tangent_vec = np.array([math.cos(phi), math.sin(phi), math.sin(lam)]) # Tangential vector at reference point
    inward_radial_vec = radius * np.array([-math.sin(phi), math.cos(phi), 0]) # reference point to center vector
    center_vec = ref_vec + inward_radial_vec # center of the helix

    # print(lam, eta, radius)
    t = np.linspace(0, 2.*np.pi, 1000)
    xs = center_vec[0] + radius * np.sin(phi + t)
    ys = center_vec[1] - radius * np.cos(phi + t)
    zs = center_vec[2] - radius * charge * np.tan(lam) * t
    rs = np.sqrt(xs**2 + ys**2)
    return xs, ys, zs, rs

def get_track_point(pt, eta, phi, vx, vy, vz, charge,t):
    print(pt, eta, phi, vx, vy, vz, charge)

    # Reference point for sim track is based on simvtx_x,y,z (which I think is same as point of closest approach, but I am not 100% sure.)
    # N.B. Signs of the values are kind of disorganized... readers be aware
    radius = pt / (2.99792458e-3 * 3.8) * (charge) * -1 # signed radius of the helix (by charge)
    ref_vec = np.array([vx, vy, vz]) # reference point vector
    lam = math.copysign(math.pi/2.-2.*math.atan(math.exp(-abs(eta))), eta) # lambda
    print(lam, eta)

    # tangent_vec = np.array([math.cos(phi), math.sin(phi), math.sin(lam)]) # Tangential vector at reference point
    inward_radial_vec = radius * np.array([-math.sin(phi), math.cos(phi), 0]) # reference point to center vector
    center_vec = ref_vec + inward_radial_vec # center of the helix
    print("center at",center_vec)
    xs = center_vec[0] + radius * np.sin(phi + t)
    ys = center_vec[1] - radius * np.cos(phi + t)
    zs = center_vec[2] - radius * charge * np.tan(lam) * t
    rs = np.sqrt(xs**2 + ys**2)
    return xs, ys, zs, rs



def construct_helix_from_points(pt,vx,vy,vz,mx,my,mz,charge):
    '''Clarification : phi was derived assuming a negatively charged particle would start
    at the first quadrant. However the way signs are set up in the get_track_point function
    implies the particle actually starts out in the fourth quadrant, and phi is measured from
    the y axis as opposed to x axis in the expression provided in this function. Hence I tucked
    in an extra pi/2 to account for these effects'''

    radius = pt / (2.99792458e-3 * 3.8) * (charge) * -1 # signed radius of the helix (by charge)
    R = abs(radius) #For geometrical calculations

    t = 2 * np.arcsin(np.sqrt( (vx - mx) **2 + (vy - my) **2 )/(2*R))
    phi = np.pi/2 + np.arctan((vx - mx)/(my-vy)) - t/2
    cx = vx - radius * np.sin(phi)
    cy = vy + radius * np.cos(phi)
    cz = vz
    lam = np.arctan((vz - mz)/(radius * charge * t))

    return ([cx,cy,cz],phi,t,lam)



def draw_track_xy(ax, pt, eta, phi, vx, vy, vz, charge):
    xs, ys, zs, rs = get_track_points(pt, eta, phi, vx, vy, vz, charge)
    # ax.scatter(0, 0)
    # ax.scatter(vx, vy)
    # ax.plot([0, vx], [0, vy])
    # ax.plot([0, -dxy * math.sin(phi)], [0, dxy * math.cos(phi)])
    ax.plot(xs, ys, linewidth=0.2)

def draw_track_rz(ax, pt, eta, phi, vx, vy, vz, charge):
    xs, ys, zs, rs = get_track_points(pt, eta, phi, vx, vy, vz, charge)
    ax.plot(zs, rs, linewidth=0.2)

#_____________________________________________________________
# Good barrel tracks is where at least one sim hit with correct pdgid land on each layer
# Does not require pair of hits land on each layer.
# Does not require that the paired hits land on module pairs.
# Does not care whether a single layer has 4 hits
# Only one sim hit with correct pdgid is needed per layer to pass the requirement
# Input: TTree event, and sim trk index
def goodBarrelTracks(t, simtrk_idx, pdgid=0):

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

        # If pdgId condition is called require the pdgid
        if pdgid:
            if abs(t.sim_pdgId[simtrk_idx]) != abs(pdgid):
                continue

        # Add the layer index
        layer_idx_with_hits.append(t.simhit_layer[simhitidx])

    if sorted(list(set(layer_idx_with_hits))) == [1, 2, 3, 4, 5, 6]:
        return True
    else:
        return False


if __name__ == "__main__":

    # matched_trk_pt  = 1.85262
    # matched_trk_charge = 1
    # matched_trk_eta = -2.3464
    # matched_trk_phi = -0.777617
    # matched_trk_pca_pt = 1.85262
    # matched_trk_pca_dz = 2.5632
    # matched_trk_pca_dxy = 0.00028104
    # matched_trk_pca_phi = -0.777611
    # matched_trk_pca_eta = -2.3464
    # matched_trk_pca_cotTheta = -5.1761
    # matched_trk_pca_lambda = -1.37995
    # matched_trk_px  = 1.32015
    # matched_trk_py  = -1.29977
    # matched_trk_pz  = -9.58936
    # simvtx_x        = 0.000887035
    # simvtx_y        = -0.000470091
    # simvtx_z        = 2.57786

    import ROOT as r
    import sys

    # f = r.TFile("/home/users/phchang/public_html/analysis/sdl/trackingNtuple/CMSSW_10_4_0/src/trackingNtuple_100_pt0p5_2p0.root")
    f = r.TFile("/nfs-7/userdata/phchang/trackingNtuple/trackingNtuple_10_pt0p5_50_50cm_cube.root")
    tree = f.Get("trackingNtuple").Get("tree")

    ntrk = 0
    for index, event in enumerate(tree):
        for itrk, dxy in enumerate(event.sim_pca_dxy):

            if not (index == 0 and itrk == 1):
                continue

            ntrk += 1
            pt = event.sim_pt[itrk]
            eta = event.sim_eta[itrk]
            phi = event.sim_phi[itrk]
            dxy = event.sim_pca_dxy[itrk]
            dz = event.sim_pca_dz[itrk]
            charge = event.sim_q[itrk]
            vx = event.simvtx_x[0]
            vy = event.simvtx_y[0]
            vz = event.simvtx_z[0]
            xs = []
            ys = []
            zs = []
            for isimhit in event.sim_simHitIdx[itrk]:
                if event.simhit_subdet[isimhit] != 4 and event.simhit_subdet[isimhit] != 5:
                    continue
                if abs(event.simhit_particle[isimhit]) != 13:
                    continue
                xs.append(event.simhit_x[isimhit])
                ys.append(event.simhit_y[isimhit])
                zs.append(event.simhit_z[isimhit])

            print(vx, vy, vz)

            print("Track info read from the TTree:")
            print(index, itrk)
            print(xs)
            print(ys)
            print(zs)

            # xs, ys, zs, rs = get_track_points(pt, eta, phi, vx, vy, vz, charge)

            ax_rz = pickle.load(file('/nfs-7/userdata/phchang/detector_layout_matplotlib_pickle/detrz.pickle'))
            draw_track_rz(ax_rz, pt, eta, phi, vx, vy, vz, charge)
            plt.scatter(zs, np.sqrt(np.array(xs)**2 + np.array(ys)**2), s=0.1)
            plt.savefig("detrz.pdf")

            ax_xy = pickle.load(file('/nfs-7/userdata/phchang/detector_layout_matplotlib_pickle/detxy.pickle'))
            draw_track_xy(ax_xy, pt, eta, phi, vx, vy, vz, charge)
            # ax_xy.set_ylim(-0.01, 0.01)
            # ax_xy.set_xlim(-0.01, 0.01)
            plt.scatter(xs, ys, s=0.1)
            plt.savefig("detxy.pdf")

            if index == 0 and itrk == 1:
                sys.exit()

    # ax_rz = pickle.load(file('/nfs-7/userdata/phchang/detector_layout_matplotlib_pickle/detrz.pickle'))
    # draw_track_rz(ax_rz, 1.85262, -0.777617, -2.3464, 0.000887035, -0.000470091, 2.57786, 1)
    # plt.savefig("detrz.pdf")

