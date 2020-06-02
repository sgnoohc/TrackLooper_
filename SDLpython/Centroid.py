#!/bin/env python

class Centroid:

    def __init__(self, filepath):
        self.filepath = filepath
        self.data = {}
        self.f = open(self.filepath)
        for line in self.f.readlines():
            ls = line.split(",")
            self.data[int(ls[0])] = [float(ls[1]), float(ls[2]), float(ls[3])]

    def getCentroid(self, detid):
        return self.data[detid]
