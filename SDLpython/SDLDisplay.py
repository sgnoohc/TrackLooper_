#!/bin/env python

import numpy as np
import os

import math

import matplotlib
matplotlib.use('pdf')
import matplotlib.pyplot as plt
from matplotlib.patches import Polygon
from matplotlib.collections import PatchCollection

from DetectorGeometry import DetectorGeometry
from Module import Module

# Displayer

class SDLDisplay:

    def __init__(self, det_geom):
        self.det_geom = det_geom

    def display_detector_xy(self, ax, color=None):

        p = PatchCollection(self.patches_xy, cmap=matplotlib.cm.jet, alpha=0.4)

        if color:
            colors = np.ones(len(self.patches_xy)) * color
            p.set_array(np.array(colors))

        ax.add_collection(p)
        # ax.autoscale()
        ax.set_ylim(-150, 150)
        ax.set_xlim(-150, 150)

    def display_detector_rz(self, ax, color=None):

        p = PatchCollection(self.patches_rz, cmap=matplotlib.cm.jet, alpha=0.4)

        if color:
            colors = np.ones(len(self.patches_rz)) * color
            p.set_array(np.array(colors))

        ax.add_collection(p)
        # ax.autoscale()
        ax.set_ylim(0, 150)
        ax.set_xlim(-300, 300)

    def display_centroid_xy(self):

        f = open("data/centroid_2020_0421.txt")
        lines = f.readlines()

        # figure
        fig, ax = plt.subplots(figsize=(4,4))
        xs = []
        ys = []
        for line in lines:
            ls = line.split(",")
            if int(ls[5]) != 6:
                continue
            xs.append(ls[0])
            ys.append(ls[1])
        ax.scatter(xs, ys)

        ax.set_ylim(-150, 150)
        ax.set_xlim(-150, 150)

        fig.savefig("test.pdf")

    def get_six_faces(self, upper_module_points, lower_module_points):

        #    3----2
        #   /|   /|
        #  0----1 |
        #  | 3--|-2
        #  |/   |/
        #  0----1

        # One ordering should be correct

        min_uib = -1 # beginning index
        min_dist_sum = 999999999
        for i in range(4):
            temp_sum = 0
            for j in range(4):
                # print(j, i)
                # print(np.array(upper_module_points[j]))
                # print(np.array(lower_module_points[(j+i)%4]))
                # print(np.linalg.norm(np.array(upper_module_points[j]) - np.array(lower_module_points[(j+i)%4])))
                temp_sum += np.linalg.norm(np.array(upper_module_points[j]) - np.array(lower_module_points[(j+i)%4]))
            # print(temp_sum)
            if temp_sum < min_dist_sum:
                min_uib = i
                min_dist_sum = temp_sum
        # print(min_uib)
        # print(min_dist_sum)

        six_faces = [
            [upper_module_points[(0+min_uib)%4], lower_module_points[0], lower_module_points[1], upper_module_points[(1+min_uib)%4]],
            [upper_module_points[(1+min_uib)%4], lower_module_points[1], lower_module_points[2], upper_module_points[(2+min_uib)%4]],
            [upper_module_points[(2+min_uib)%4], lower_module_points[2], lower_module_points[3], upper_module_points[(3+min_uib)%4]],
            [upper_module_points[(3+min_uib)%4], lower_module_points[3], lower_module_points[0], upper_module_points[(0+min_uib)%4]],
            [upper_module_points[0], upper_module_points[1], upper_module_points[2], upper_module_points[3]],
            [lower_module_points[0], lower_module_points[1], lower_module_points[2], lower_module_points[3]],
            ]

        # print(six_faces)

        return six_faces

    def set_detector_xy_collection(self, list_of_detids):

        # Create detector patches
        self.patches_xy = []
        n_failed = 0
        for detid in list_of_detids:

            module = Module(detid) 
            partner_detid = Module(detid).partnerDetId()

            if partner_detid not in self.det_geom.getData().keys():
                # print("{} not found from {} (isLower = {}, isInverted = {})".format(partner_detid, detid, module.isLower(), module.isInverted()))
                n_failed += 1
                continue
            else:
                # print("{}     found from {} (isLower = {}, isInverted = {})".format(partner_detid, detid, module.isLower(), module.isInverted()))
                pass

            six_faces = self.get_six_faces(self.det_geom.getData()[detid], self.det_geom.getData()[partner_detid])

            for face in six_faces:
                points = [ [x[1], x[2]] for x in face ]
                polygon = Polygon(np.array(points), True)
                self.patches_xy.append(polygon)

        # print(len(list_of_detids))
        # print(n_failed)

    def set_detector_rz_collection(self, list_of_detids):

        # Create detector patches
        self.patches_rz = []
        n_failed = 0
        for detid in list_of_detids:

            module = Module(detid) 
            partner_detid = Module(detid).partnerDetId()

            if partner_detid not in self.det_geom.getData().keys():
                # print("{} not found from {} (isLower = {}, isInverted = {})".format(partner_detid, detid, module.isLower(), module.isInverted()))
                n_failed += 1
                continue
            else:
                # print("{}     found from {} (isLower = {}, isInverted = {})".format(partner_detid, detid, module.isLower(), module.isInverted()))
                pass

            six_faces = self.get_six_faces(self.det_geom.getData()[detid], self.det_geom.getData()[partner_detid])

            for face in six_faces:
                points = [ [x[0], math.sqrt(x[1]**2+x[2]**2)] for x in face ]
                polygon = Polygon(np.array(points), True)
                self.patches_rz.append(polygon)

        # print(len(list_of_detids))
        # print(n_failed)

def getDefaultSDLDisplay():
    dirpath = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    det_geom = DetectorGeometry("{}/data/phase2_2020_0428.txt".format(dirpath))
    sdlDisplay = SDLDisplay(det_geom)
    list_of_detids = det_geom.getDetIds(lambda x: Module(x[0]).subdet() == 5 and Module(x[0]).side() == 3 and Module(x[0]).module() <= 2)
    list_of_detids.sort()
    sdlDisplay.set_detector_xy_collection(list_of_detids)
    list_of_detids = det_geom.getDetIds(lambda x: (Module(x[0]).subdet() == 5 and Module(x[0]).side() == 3 and Module(x[0]).rod() <= 2) or (Module(x[0]).subdet() == 5 and Module(x[0]).side() != 3 and Module(x[0]).module() <= 2) or (Module(x[0]).subdet() == 4 and Module(x[0]).module() <= 2))
    list_of_detids.sort()
    sdlDisplay.set_detector_rz_collection(list_of_detids)
    return sdlDisplay

if __name__ == "__main__":

    # figure
    fig, ax = plt.subplots(figsize=(4,4))

    sdlDisplay.display_detector_xy(ax)

    fig.savefig("test.pdf")

