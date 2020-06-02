#!/bin/env python

import matplotlib
matplotlib.use('pdf')
import matplotlib.pyplot as plt
from matplotlib.collections import LineCollection
import pickle
import numpy as np
import math
from scipy import optimize

class Helix:
    def __init__(self, center, radius, phi, lam, charge):
        self.center_ = center
        self.radius_ = radius
        self.phi_ = self.Phi_mpi_pi(phi)
        self.lam_ = lam
        self.charge_ = charge
    def center(self): return self.center_
    def radius(self): return self.radius_
    def phi(self): return self.phi_
    def lam(self): return self.lam_
    def charge(self): return self.charge_
    def __str__(self):
        rtnstr = [
        "Helix():",
        "  center = {}".format(self.center()),
        "  radius = {}".format(self.radius()),
        "  phi    = {}".format(self.phi()),
        "  lam    = {}".format(self.lam()),
        "  charge = {}".format(self.charge()),
        ]
        return "\n".join(rtnstr)
    def Phi_mpi_pi(self, phi):
        f = phi
        while f >= math.pi: f -= 2. * math.pi;
        while f < -math.pi: f += 2. * math.pi;
        return f

def get_helix_point(helix, t):
    x = helix.center()[0] - helix.charge() * helix.radius() * np.sin(helix.phi() - (helix.charge()) * t)
    y = helix.center()[1] + helix.charge() * helix.radius() * np.cos(helix.phi() - (helix.charge()) * t)
    z = helix.center()[2] +                  helix.radius() * np.tan(helix.lam()) * t
    r = np.sqrt(x**2 + y**2)
    return (x, y, z, r)

def get_helix_point_from_radius(helix, r):
    def h(t):
        x = helix.center()[0] - helix.charge() * helix.radius() * np.sin(helix.phi() - (helix.charge()) * t)
        y = helix.center()[1] + helix.charge() * helix.radius() * np.cos(helix.phi() - (helix.charge()) * t)
        return math.sqrt(x**2 + y**2)
    res = optimize.minimize_scalar(lambda t: abs(h(t) - r), bounds=(0, math.pi), method='bounded')
    t = res.x
    x = helix.center()[0] - helix.charge() * helix.radius() * np.sin(helix.phi() - (helix.charge()) * t)
    y = helix.center()[1] + helix.charge() * helix.radius() * np.cos(helix.phi() - (helix.charge()) * t)
    z = helix.center()[2] +                  helix.radius() * np.tan(helix.lam()) * t
    r = np.sqrt(x**2 + y**2)
    return (x, y, z, r)

def get_helix_points(helix):
    xs = []
    ys = []
    zs = []
    rs = []
    for t in np.linspace(0, 2.*np.pi, 1000):
        x, y, z, r = get_helix_point(helix, t)
        if r > 120:
            break
        xs.append(x)
        ys.append(y)
        zs.append(z)
        rs.append(r)
    xs = np.array(xs)
    ys = np.array(ys)
    zs = np.array(zs)
    rs = np.array(rs)
    return xs, ys, zs, rs

def get_square_point_at_radius_from_helices(helices, r, t1, t2):
    ''' t1 and t2 are the two parameters to define the point on square. Assumes
    helices are length 4 and also in order to create a square going from
    0->1->2->3->0'''
    point1 = get_helix_point_from_radius(helices[0], r)
    point2 = get_helix_point_from_radius(helices[1], r)
    point3 = get_helix_point_from_radius(helices[2], r)
    point4 = get_helix_point_from_radius(helices[3], r)


def construct_helix_from_kinematics(pt, eta, phi, vx, vy, vz, charge):

    print(pt, eta, phi, vx, vy, vz, charge)

    # Radius based on pt
    radius = pt / (2.99792458e-3 * 3.8)

    # reference point vector which for sim track is the vertex point
    ref_vec = np.array([vx, vy, vz]) # reference point vector

    # The reference to center vector
    inward_radial_vec = charge * radius * np.array([math.sin(phi), -math.cos(phi), 0]) # reference point to center vector

    # The center point
    center_vec = ref_vec + inward_radial_vec # center of the helix

    # The lambda
    lam = math.copysign(math.pi/2. - 2. * math.atan(math.exp(-abs(eta))), eta) # lambda

    return Helix(center_vec, radius, phi, lam, charge)

def construct_helix_from_points(pt, vx, vy, vz, mx, my, mz, charge):
    '''Clarification : phi was derived assuming a negatively charged particle would start
    at the first quadrant. However the way signs are set up in the get_track_point function
    implies the particle actually starts out in the fourth quadrant, and phi is measured from
    the y axis as opposed to x axis in the expression provided in this function. Hence I tucked
    in an extra pi/2 to account for these effects'''
    # print(pt,vx,vy,vz,mx,my,mz,charge)

    radius = pt / (2.99792458e-3 * 3.8)
    R = abs(radius) #For geometrical calculations

    t = 2 * np.arcsin(np.sqrt( (vx - mx) **2 + (vy - my) **2 )/(2*R))
    phi = np.pi/2 + np.arctan((vy-my)/(vx-mx)) + ((vy-my)/(vx-mx) < 0) * (np.pi) +charge *  t/2 + (my-vy < 0) * (np.pi/2) - (my-vy > 0) * (np.pi/2)
    cx = vx + charge *  radius * np.sin(phi)
    cy = vy - charge *  radius * np.cos(phi)
    cz = vz
    lam = np.arctan((mz - vz)/( radius * t))

    return Helix(np.array([cx,cy,cz]), radius, phi, lam, charge)

def draw_track_xy(ax, pt, eta, phi, vx, vy, vz, charge, verbose=False):
    if verbose:
        print("draw_track_xy: pt, eta, phi, vx, vy, vz, charge = ", pt, eta, phi, vx, vy, vz, charge)
    helix = construct_helix_from_kinematics(pt, eta, phi, vx, vy, vz, charge)
    print(helix)
    xs, ys, zs, rs = get_helix_points(helix)
    ax.scatter(helix.center()[0], helix.center()[1])
    ax.plot(xs, ys, linewidth=0.2, color=(1,0,0))

def draw_track_rz(ax, pt, eta, phi, vx, vy, vz, charge, verbose=False):
    if verbose:
        print("draw_track_rz: pt, eta, phi, vx, vy, vz, charge = ", pt, eta, phi, vx, vy, vz, charge)
    helix = construct_helix_from_kinematics(pt, eta, phi, vx, vy, vz, charge)
    print(helix)
    xs, ys, zs, rs = get_helix_points(helix)
    ax.plot(zs, rs, linewidth=0.2, color=(1,0,0))

def draw_track_xy_from_points(ax, pt, vx, vy, vz, mx, my, mz, charge, verbose=False):
    if verbose:
        print("draw_track_xy_from_points: pt, vx, vy, vz, mx, my, mz, charge = ", pt, vx, vy, vz, mx, my, mz, charge)
    helix = construct_helix_from_points(pt, vx, vy, vz, mx, my, mz, charge)
    print(helix)
    xs, ys, zs, rs = get_helix_points(helix)
    ax.scatter(helix.center()[0], helix.center()[1], s=0.4)
    ax.plot(xs, ys, linewidth=0.2, color=(1,0,0))

def draw_track_rz_from_points(ax, pt, vx, vy, vz, mx, my, mz, charge, verbose=False):
    if verbose:
        print("draw_track_rz_from_points: pt, vx, vy, vz, mx, my, mz, charge = ", pt, vx, vy, vz, mx, my, mz, charge)
    helix = construct_helix_from_points(pt, vx, vy, vz, mx, my, mz, charge)
    print(helix)
    xs, ys, zs, rs = get_helix_points(helix)
    ax.plot(zs, rs, linewidth=0.2, color=(1,0,0))

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

    import ROOT as r
    import sys

    f = r.TFile("/home/users/phchang/public_html/analysis/sdl/trackingNtuple/CMSSW_10_4_0/src/trackingNtuple_100_pt0p5_2p0.root")
    # f = r.TFile("/nfs-7/userdata/phchang/trackingNtuple/trackingNtuple_10_pt0p5_50_50cm_cube.root")
    tree = f.Get("trackingNtuple").Get("tree")

    ntrk = 0
    itrk_sel = int(sys.argv[1])
    for index, event in enumerate(tree):
        for itrk, dxy in enumerate(event.sim_pca_dxy):

            if not (index == 0 and itrk == itrk_sel):
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

            ax_xy = pickle.load(file('/nfs-7/userdata/phchang/detector_layout_matplotlib_pickle/detxy.pickle'))
            draw_track_xy(ax_xy, pt, eta, phi, vx, vy, vz, charge, verbose=True)
            draw_track_xy_from_points(ax_xy, pt, vx, vy, vz, xs[0], ys[0], zs[0], charge, verbose=True)
            plt.scatter(xs, ys, s=0.1)
            helix = construct_helix_from_kinematics(pt, eta, phi, vx, vy, vz, charge)
            for r in [20, 30, 50, 80]:
                point_on_radius = get_helix_point_from_radius(helix, r)
                plt.scatter(point_on_radius[0], point_on_radius[1])
            plt.savefig("detxy.pdf")

            # ax_rz = pickle.load(file('/nfs-7/userdata/phchang/detector_layout_matplotlib_pickle/detrz.pickle'))
            # draw_track_rz(ax_rz, pt, eta, phi, vx, vy, vz, charge, verbose=True)
            # # draw_track_rz_from_points(ax_rz, pt, vx, vy, vz, xs[0], ys[0], zs[0], charge, verbose=True)
            # plt.scatter(zs, np.sqrt(np.array(xs)**2+np.array(ys)**2), s=0.1)
            # plt.savefig("detrz.pdf")

            if index == 0 and itrk == itrk_sel:
                sys.exit()

