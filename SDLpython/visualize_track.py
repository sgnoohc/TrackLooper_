#!/bin/env python

import ROOT as r
import matplotlib
matplotlib.use('pdf')
import matplotlib.pyplot as plt
from matplotlib.collections import LineCollection
import pickle
import numpy as np
import math
import sdlmath
import SDLDisplay
from tqdm import tqdm

f = r.TFile("/home/users/phchang/public_html/analysis/sdl/trackingNtuple/CMSSW_10_4_0/src/trackingNtuple_100_pt0p5_3p0.root")
t = f.Get("trackingNtuple/tree")

pick_ievent = 15
pick_itrack = 7

t.GetEntry(pick_ievent)

for itrack, pt in enumerate(t.sim_pt):
    if itrack == pick_itrack:

        pt = t.sim_pt[itrack]
        eta = t.sim_eta[itrack]
        phi = t.sim_phi[itrack]
        charge = t.sim_q[itrack]
        vx = t.simvtx_x[0]
        vy = t.simvtx_y[0]
        vz = t.simvtx_z[0]

        print pt, eta, phi, charge, vx, vy, vz

        simhit_xs = []
        simhit_ys = []
        simhit_zs = []
        simhit_subdets = []
        simhit_pdgids  = []
        simhit_detids  = []
        for _, isimhit in  enumerate(t.sim_simHitIdx[itrack]):
            if t.simhit_subdet[isimhit] == 4 or t.simhit_subdet[isimhit] == 5:
                simhit_xs.append(t.simhit_x[isimhit])
                simhit_ys.append(t.simhit_y[isimhit])
                simhit_zs.append(t.simhit_z[isimhit])
                simhit_subdets.append(t.simhit_subdet[isimhit])
                simhit_pdgids.append(t.simhit_particle[isimhit])
                simhit_detids.append(int(t.simhit_detId[isimhit]))
        simhit_xs = np.array(simhit_xs)
        simhit_ys = np.array(simhit_ys)
        simhit_zs = np.array(simhit_zs)
        simhit_rs = np.sqrt(simhit_xs**2 + simhit_ys**2)

        print simhit_xs
        print simhit_ys
        print simhit_zs
        print simhit_rs
        print simhit_subdets
        print simhit_pdgids
        print simhit_detids

        break

detids = simhit_detids

sdlDisplay = SDLDisplay.getDefaultSDLDisplay()
fullSDLDisplay = SDLDisplay.getDefaultSDLDisplay()

sdlDisplay.set_detector_rz_collection(detids)
sdlDisplay.set_detector_xy_collection(detids)
sdlDisplay.set_detector_etaphi_collection(detids)

# ax = pickle.load(file('/nfs-7/userdata/phchang/detector_layout_matplotlib_pickle/detrz.pickle'))
ax = pickle.load(file('detrz.pickle'))
fullSDLDisplay.display_detector_rz(ax)
sdlDisplay.display_detector_rz(ax, color=(1,0,0))
sdlmath.draw_track_rz(ax, pt, eta, phi, vx, vy, vz, charge)
# lc = LineCollection(segments_rz, colors=(1,0,0), linewidth=0.5, alpha=0.4)
# ax.add_collection(lc)
plt.scatter(simhit_zs, simhit_rs, s=0.5)
plt.savefig("detrz_track_visualization.pdf")

# ax = pickle.load(file('/nfs-7/userdata/phchang/detector_layout_matplotlib_pickle/detxy.pickle'))
ax = pickle.load(file('detxy.pickle'))
fullSDLDisplay.display_detector_xy(ax)
sdlDisplay.display_detector_xy(ax, color=(0,0,1))
sdlmath.draw_track_xy(ax, pt, eta, phi, vx, vy, vz, charge)
# lc = LineCollection(segments_xy, colors=(1,0,0), linewidth=0.5, alpha=0.4)
# ax.add_collection(lc)
plt.scatter(simhit_xs, simhit_ys, s=0.5)
plt.savefig("detxy_track_visualization.pdf")

fig, ax = plt.subplots(figsize=(4. * 2,2.*math.pi))
sdlDisplay.display_detector_etaphi(ax, color=(0,0,1))
fig.savefig("detetaphi_track_visualization.pdf")

