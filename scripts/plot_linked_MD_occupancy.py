from __future__ import print_function
import plottery.plottery as ply
import ROOT as r
import numpy as np
import sys,os

filename = "../occupancy_studies/debug_all.root"
if len(sys.argv) > 1:
    filename = sys.argv[1]


def plot_occupancy(hist,prefix):
    filename_prefix = prefix.replace(" ","_")
    filename_prefix = "/home/users/bsathian/public_html/SDL/SDL_Occupancies_20200407/SDL_Linked_MD_Occupancies_20200407/"+filename_prefix
    #Fancy way to find xaxis range
    nonzero_flag = False
    ymax = 0
    xaxis_range = [0,100]
    for i in range(1,hist.GetNbinsX()-1):
        if hist.GetBinContent(i) != 0:
            if ymax < hist.GetBinContent(i):
                ymax = hist.GetBinContent(i)
            if i > 2 and nonzero_flag == False:
                xaxis_range[0] = hist.GetBinLowEdge(i-2)
            nonzero_flag = True
        if hist.GetBinContent(i) != 0 and hist.GetBinContent(i+1) == 0 and nonzero_flag == True:
            xaxis_range[1] = hist.GetBinLowEdge(i+2)
        #xaxis_range = [0,100]
    ply.plot_hist(
        bgs = [hist],
        legend_labels = [prefix],
        options = {
        "output_name":filename_prefix+".pdf",
        "xaxis_range":xaxis_range,
        "xaxis_label":prefix,
        "title":prefix,
        "yaxis_log":True,
        "yaxis_range":[0.1,ymax],
        "legend_percentageinbox":False,
        }
    )



f = r.TFile(filename)
layer_barrel_average_occupancy_hists = []
layer_barrel_occupancy_hists = []
layer_endcap_average_occupancy_hists = []
layer_endcap_occupancy_hists = []
ring_endcap_average_occupancy_hists = []
ring_endcap_occupancy_hists = []

for i in range(1,7):
    layer_barrel_average_occupancy_hists.append(f.Get("Root__average_Linked_MD_occupancy_in_barrel_for_layer_"+str(i)))
    layer_endcap_average_occupancy_hists.append(f.Get("Root__average_Linked_MD_occupancy_in_endcap_for_layer_"+str(i)))

    layer_barrel_occupancy_hists.append(f.Get("Root__Linked_MD_occupancy_in_barrel_for_layer_"+str(i)))
    layer_endcap_occupancy_hists.append(f.Get("Root__Linked_MD_occupancy_in_endcap_for_layer_"+str(i)))

for i in range(1,16):
    ring_endcap_average_occupancy_hists.append(f.Get("Root__average_Linked_MD_occupancy_in_endcap_for_ring_"+str(i)))
    ring_endcap_occupancy_hists.append(f.Get("Root__Linked_MD_occupancy_in_endcap_for_ring_"+str(i)))


barrel_occupancy_hist = f.Get("Root__Linked_MD_occupancy_in_barrel")
endcap_occupancy_hist = f.Get("Root__Linked_MD_occupancy_in_endcap")

barrel_average_occupancy_hist = f.Get("Root__average_Linked_MD_occupancy_in_barrel")
endcap_average_occupancy_hist = f.Get("Root__average_Linked_MD_occupancy_in_endcap")

plot_occupancy(barrel_occupancy_hist,"barrel Linked mini-doublet occupancy")
plot_occupancy(endcap_occupancy_hist,"endcap Linked mini-doublet occupancy")

plot_occupancy(barrel_average_occupancy_hist,"barrel average Linked mini-doublet occupancy")
plot_occupancy(endcap_average_occupancy_hist,"endcap average Linked mini-doublet occupancy")


for i in range(len(layer_barrel_occupancy_hists)):
    plot_occupancy(layer_barrel_occupancy_hists[i],"Barrel Linked Mini-doublet Occupancy for layer "+str(i+1))
    if i != 5:
        plot_occupancy(layer_endcap_occupancy_hists[i],"Endcap Linked mini-doublet Occupancy for layer "+str(i+1))



for i in range(len(layer_barrel_average_occupancy_hists)):
    plot_occupancy(layer_barrel_average_occupancy_hists[i],"Average barrel Linked mini-doublet occupancy for layer "+str(i+1))
    if i!= 5:
        plot_occupancy(layer_endcap_average_occupancy_hists[i],"Average endcap Linked mini-doublet occupancy for layer "+str(i+1))

for i in range(len(ring_endcap_average_occupancy_hists)):
    plot_occupancy(ring_endcap_average_occupancy_hists[i],"Average endcap Linked mini-doublet occupancy in ring "+str(i+1))
    plot_occupancy(ring_endcap_occupancy_hists[i],"Endcap Linked mini-doublet occupancy in ring "+str(i+1))


