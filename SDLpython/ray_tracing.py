#!/bin/env python

import matplotlib
matplotlib.use('pdf')
import matplotlib.pyplot as plt
from matplotlib.collections import LineCollection
import pickle
import numpy as np
import math

if __name__ == "__main__":

    ax_xy = pickle.load(file('/nfs-7/userdata/phchang/detector_layout_matplotlib_pickle/detxy.pickle'))

    rays = []
    nslice = 60
    for i in range(nslice):
        phi = i * (2. * math.pi/nslice)
        rays.append([(0, 0), (150. * math.cos(phi), 150. * math.sin(phi))])

    rays = LineCollection(rays, colors=(1,0,0), linewidth=0.5, alpha=0.4)

    circle1 = plt.Circle((0, 0), 20., color='r', fill=False, linewidth=1)

    ax_xy.add_artist(circle1)

    ax_xy.add_collection(rays)

    plt.savefig("detxy.pdf")
