#!/bin/env python

import ROOT as r
import json

class DetectorGeometry:

    def __init__(self, data):
        self.data = data
        self.datafile = open(self.data)
        self.geom_data_raw = json.load(self.datafile)
        self.geom_data = {}
        for key in self.geom_data_raw:
            detid = int(key)
            new_list = []
            for x in self.geom_data_raw[key]:
                new_x = [ float(y) for y in x ]
                new_list.append(new_x)
            self.geom_data[detid] = new_list

    def getData(self, filt=None):
        if filt:
            rtndict = dict(filter(filt, self.geom_data.items()))
            return rtndict
        else:
            return self.geom_data

    def getDetIds(self, filt=None):
        if filt:
            rtndict = dict(filter(filt, self.geom_data.items()))
            return rtndict.keys()
        else:
            return self.geom_data.keys()
