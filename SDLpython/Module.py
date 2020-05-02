#!/bin/env python

import ROOT as r

import os
dirpath = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

r.gROOT.ProcessLine(".L {}/SDL/extra/DetIdParser.cxx".format(dirpath))

class Module:

    def __init__(self, detid):
        self.detid = int(detid)
        self.moduleSDL = r.SDL.Module(self.detid)

    def detId(self): return int(self.detid)
    def partnerDetId(self): return int(self.moduleSDL.partnerDetId())
    def subdet(self): return int(self.moduleSDL.subdet())
    def side(self): return int(self.moduleSDL.side())
    def layer(self): return int(self.moduleSDL.layer())
    def logicalLayer(self): return int(self.moduleSDL.layer()) + (6 if self.subdet() == 4 else 0)
    def rod(self): return int(self.moduleSDL.rod())
    def ring(self): return int(self.moduleSDL.ring())
    def module(self): return int(self.moduleSDL.module())
    def isLower(self): return int(self.moduleSDL.isLower())
    def isInverted(self): return int(self.moduleSDL.isInverted())
    def moduleType(self): return int(self.moduleSDL.moduleType())
    def moduleLayerType(self): return int(self.moduleSDL.moduleLayerType())

    def __str__(self):
        return "detid={} logicalLayer={} side={} moduleType={} ring={}".format(self.detId(), self.logicalLayer(), self.side(), self.moduleType(), self.ring())

if __name__ == "__main__":

    module = Module(411309089)
    print(module.subdet())
    print(module.layer())
    print(module.isLower())
    print(module.ring())
    print(module.rod())
    print(module.moduleType())
    print(module.moduleLayerType())
