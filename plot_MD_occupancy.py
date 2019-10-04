from __future__ import print_function
import plottery.plottery as ply
import ROOT as r
import numpy as np
import sys,os

filename = "debug.root"
if len(sys.argv) > 1:
    filename = sys.argv[1]

xaxis_range = [0,25] #SUBJECT TO CHANGE


def plot_occupancy(hist,prefix,additional_options = None):
    global xaxis_range
    filename_prefix = prefix.replace(" ","_")
    filename_prefix = "/home/users/bsathian/public_html/SDL/SDL_20190918/MD_occupancies/"+filename_prefix
    xaxis_plot = xaxis_range

    default_options = {
        "output_name":filename_prefix+".pdf",
        "xaxis_range":xaxis_plot,
        "xaxis_label":prefix,
        "title":prefix,
        "legend_percentageinbox":False,
        }
    options = default_options.copy()
    if type(additional_options) is dict:
        options.update(additional_options)

    ply.plot_hist(
        bgs = [hist],
        legend_labels = [prefix],
        options = options)


f = r.TFile(filename)
layer_average_occupancy_hists = []
layer_occupancy_hists = []
layer_barrel_average_occupancy_hists = []
layer_barrel_occupancy_hists = []
layer_endcap_average_occupancy_hists = []
layer_endcap_occupancy_hists = []
ring_endcap_average_occupancy_hists = []
ring_endcap_occupancy_hists = []

for i in range(1,7):
    layer_average_occupancy_hists.append(f.Get("Root__average_MD_occupancy_in_layer_"+str(i)))
    layer_barrel_average_occupancy_hists.append(f.Get("Root__average_MD_occupancy_in_barrel_for_layer_"+str(i)))
    layer_endcap_average_occupancy_hists.append(f.Get("Root__average_MD_occupancy_in_endcap_for_layer_"+str(i)))

    layer_occupancy_hists.append(f.Get("Root__MD_occupancy_in_layer_"+str(i)))
    layer_barrel_occupancy_hists.append(f.Get("Root__MD_occupancy_in_barrel_for_layer_"+str(i)))
    layer_endcap_occupancy_hists.append(f.Get("Root__MD_occupancy_in_endcap_for_layer_"+str(i)))

for i in range(1,16):
    ring_endcap_average_occupancy_hists.append(f.Get("Root__average_MD_occupancy_in_endcap_for_ring_"+str(i)))
    ring_endcap_occupancy_hists.append(f.Get("Root__MD_occupancy_in_endcap_for_ring_"+str(i)))



barrel_occupancy_hist = f.Get("Root__MD_occupancy_in_barrel")
endcap_occupancy_hist = f.Get("Root__MD_occupancy_in_endcap")

barrel_average_occupancy_hist = f.Get("Root__average_MD_occupancy_in_barrel")
endcap_average_occupancy_hist = f.Get("Root__average_MD_occupancy_in_endcap")

plot_occupancy(barrel_occupancy_hist,"barrel mini-doublet occupancy",additional_options = {"yaxis_log":True,"xaxis_range":[0,100],"yaxis_range":[0.1,1e7]})
plot_occupancy(endcap_occupancy_hist,"endcap mini-doublet occupancy",additional_options = {"yaxis_log":True,"xaxis_range":[0,100],"yaxis_range":[0.1,1e6]})

plot_occupancy(barrel_average_occupancy_hist,"barrel average mini-doublet occupancy")
plot_occupancy(endcap_average_occupancy_hist,"endcap average mini-doublet occupancy")


for i in range(len(layer_occupancy_hists)):
    plot_occupancy(layer_occupancy_hists[i],"Mini-doublet Occupancy for layer "+str(i+1))
    plot_occupancy(layer_barrel_occupancy_hists[i],"Barrel Mini-doublet Occupancy for layer "+str(i+1),additional_options = {"yaxis_log":True,"xaxis_range":[0,200],"yaxis_range":[0.1,1e5]})
    if i != 5:
        plot_occupancy(layer_endcap_occupancy_hists[i],"Endcap mini-doublet Occupancy for layer "+str(i+1),additional_options = {"yaxis_log":True,"xaxis_range":[0,100],"yaxis_range":[0.1,1e5]})



for i in range(len(layer_average_occupancy_hists)):
    plot_occupancy(layer_average_occupancy_hists[i],"Average mini-doublet occupancy for layer "+str(i+1))
    plot_occupancy(layer_barrel_average_occupancy_hists[i],"Average barrel mini-doublet occupancy for layer "+str(i+1))
    if i!= 5:
        plot_occupancy(layer_endcap_average_occupancy_hists[i],"Average endcap mini-doublet occupancy for layer "+str(i+1))

for i in range(len(ring_endcap_average_occupancy_hists)):
    plot_occupancy(ring_endcap_average_occupancy_hists[i],"Average endcap mini-doublet occupancy in ring "+str(i+1))
    plot_occupancy(ring_endcap_occupancy_hists[i],"Endcap mini-doublet occupancy in ring "+str(i+1),additional_options = {"yaxis_log":True,"xaxis_range":[0,100],"yaxis_range":[0.1,1e5]})


