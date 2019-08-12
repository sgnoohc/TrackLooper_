from __future__ import print_function
import plottery.plottery as plt
import ROOT as r
import numpy as np
import sys,os

filename = "debug.root"
if len(sys.argv) > 1:
    filename = sys.argv[1]

xaxis_range = [0,5] #SUBJECT TO CHANGE

def plot_occupancy(hist,prefix):
    global xaxis_range
    filename_prefix = prefix.replace(" ","_")
    ply.plot_hist(
        bgs = [hist],
        legend_labels = [prefix],
        options = {
        "output_name":filename_prefix+".pdf",
        "xaxis_range":xaxis_range,
        "legend_percentageinbox":False,
        }
    )



f = r.TFile(filename)
layer_occupancy_hists = []
layer_barrel_occupancy_hists = []
layer_endcap_occupancy_hists = []
for i in range(1,6):
    layer_occupancy_hists.append(f.Get("Root__occupancy_in_layer_"+str(i)))
    layer_barrel_occupancy_hists.append(f.Get("Root__occupancy_in_barrel_for_layer_"+str(i)))
    layer_endcap_occupancy_hists.append(f.Get("Root__occupancy_in_endcap_for_layer_"+str(i)))

barrel_average_occupancy_hist = f.Get("Root__occupancy_in_barrel")
endcap_average_occupancy_hist = f.Get("Root__occupancy_in_endcap")

plot_occupancy(barrel_average_occupancy_hist,"barrel average occupancy")
plot_occupancy(endcap_average_occupancy_hist,"endcap average occupancy")

for i in range(1,6):
    plot_occupancy(layer_occupancy_hists[i],"Average occupancy for layer "+str(i))
    plot_occupancy(layer_barrel_occupancy_hists[i],"Average barrel occupancy for layer "+str(i))
    plot_occupancy(layer_endcap_occupancy_hists[i],"Average endcap occupancy for layer "+str(i))
