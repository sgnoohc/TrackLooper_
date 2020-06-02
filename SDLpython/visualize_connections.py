#!/bin/env python

import SDLDisplay
import matplotlib
matplotlib.use('pdf')
import matplotlib.pyplot as plt
from matplotlib.collections import LineCollection
from Centroid import Centroid
import math

# Centroid database
centroidDB = Centroid("data/centroid_2020_0428.txt")

f = open("data/module_connection_2020_0429.txt")

lines = f.readlines()

sdlDisplay = SDLDisplay.getDefaultSDLDisplay()
fullSDLDisplay = SDLDisplay.getDefaultSDLDisplay()

detids = []
segments_rz = []
segments_xy = []
for line in lines:
    ls = line.split()
    ref_detid = int(ls[0])
    nconn = int(ls[1])
    target_detids = [ int(x) for x in ls[2:] ]

    if nconn > 22:
        detids += target_detids
        detids.append(ref_detid)
        centroid_ref = centroidDB.getCentroid(ref_detid)
        ref_x = centroid_ref[0]
        ref_y = centroid_ref[1]
        ref_z = centroid_ref[2]
        ref_rt = math.sqrt(ref_x**2 + ref_y**2)
        for target_detid in target_detids:
            centroid_target = centroidDB.getCentroid(target_detid)
            target_x = centroid_target[0]
            target_y = centroid_target[1]
            target_z = centroid_target[2]
            target_rt = math.sqrt(target_x**2 + target_y**2)
            segments_rz.append([(ref_z, ref_rt), (target_z, target_rt)])
            segments_xy.append([(ref_x, ref_y), (target_x, target_y)])

sdlDisplay.set_detector_rz_collection(detids)
sdlDisplay.set_detector_xy_collection(detids)

fig, ax = plt.subplots(figsize=(10,4))
fullSDLDisplay.display_detector_rz(ax)
sdlDisplay.display_detector_rz(ax, color=3)
lc = LineCollection(segments_rz, colors=(1,0,0), linewidth=0.5, alpha=0.4)
ax.add_collection(lc)
fig.savefig("detrz_outlier_conn26.pdf")

fig, ax = plt.subplots(figsize=(6,6))
fullSDLDisplay.display_detector_xy(ax)
sdlDisplay.display_detector_xy(ax, color=2)
lc = LineCollection(segments_xy, colors=(1,0,0), linewidth=0.5, alpha=0.4)
ax.add_collection(lc)
fig.savefig("detxy_outlier_conn26.pdf")
