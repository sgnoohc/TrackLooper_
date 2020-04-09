from __future__ import print_function
import plottery.plottery as ply
import ROOT as r
import numpy as np
import sys,os

filename = "../occupancy_studies/debug_all.root"
if len(sys.argv) > 1:
    filename = sys.argv[1]

#xaxis_range = [0,50] #SUBJECT TO CHANGE

def plot_occupancy(hist,prefix):
    filename_prefix = prefix.replace(" ","_")
    filename_prefix = "/home/users/bsathian/public_html/SDL/SDL_Occupancies_20200407/SDL_Hit_Occupancies_20200407/"+filename_prefix
    #Fancy way to find xaxis range
    nonzero_flag = False
    xaxis_range = [0,100]
    for i in range(1,hist.GetNbinsX()-1):
        if hist.GetBinContent(i) != 0:
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
        "yaxis_log":True,
        "yaxis_range":[0.1,2e5],
        "title":prefix,
        "legend_percentageinbox":False,
        }
    )



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
    layer_average_occupancy_hists.append(f.Get("Root__Segment_occupancy_in_layer_"+str(i)))
    layer_barrel_average_occupancy_hists.append(f.Get("Root__average_Segment_occupancy_in_barrel_for_layer_"+str(i)))
    layer_endcap_average_occupancy_hists.append(f.Get("Root__average_Segment_occupancy_in_endcap_for_layer_"+str(i)))

    layer_occupancy_hists.append(f.Get("Root__Segment_occupancy_in_layer_"+str(i)))
    layer_barrel_occupancy_hists.append(f.Get("Root__Segment_occupancy_in_barrel_for_layer_"+str(i)))
    layer_endcap_occupancy_hists.append(f.Get("Root__Segment_occupancy_in_endcap_for_layer_"+str(i)))

for i in range(1,16):
    ring_endcap_average_occupancy_hists.append(f.Get("Root__average_Segment_occupancy_in_endcap_for_ring_"+str(i)))
    ring_endcap_occupancy_hists.append(f.Get("Root__Segment_occupancy_in_endcap_for_ring_"+str(i)))



barrel_occupancy_hist = f.Get("Root__Segment_occupancy_in_barrel")
endcap_occupancy_hist = f.Get("Root__Segment_occupancy_in_endcap")

barrel_average_occupancy_hist = f.Get("Root__average_Segment_occupancy_in_barrel")
endcap_average_occupancy_hist = f.Get("Root__average_Segment_occupancy_in_endcap")

plot_occupancy(barrel_occupancy_hist,"barrel Segment occupancy")
plot_occupancy(endcap_occupancy_hist,"endcap Segment occupancy")

plot_occupancy(barrel_average_occupancy_hist,"barrel average Segment occupancy")
plot_occupancy(endcap_average_occupancy_hist,"endcap average Segment occupancy")


for i in range(len(layer_occupancy_hists)):
    plot_occupancy(layer_occupancy_hists[i],"Segment occupancy for layer "+str(i+1))
    plot_occupancy(layer_barrel_occupancy_hists[i],"Barrel Segment occupancy for layer "+str(i+1))
    if i != 5:
        plot_occupancy(layer_endcap_occupancy_hists[i],"Endcap Segment occupancy for layer "+str(i+1))



for i in range(len(layer_average_occupancy_hists)):
    plot_occupancy(layer_average_occupancy_hists[i],"Average Segment occupancy for layer "+str(i+1))
    plot_occupancy(layer_barrel_average_occupancy_hists[i],"Average barrel Segment occupancy for layer "+str(i+1))
    if i!= 5:
        plot_occupancy(layer_endcap_average_occupancy_hists[i],"Average endcap Segment occupancy for layer "+str(i+1))

for i in range(len(ring_endcap_average_occupancy_hists)):
    plot_occupancy(ring_endcap_average_occupancy_hists[i],"Average endcap Segment occupancy in ring "+str(i+1))
    plot_occupancy(ring_endcap_occupancy_hists[i],"Endcap Segment occupancy in ring "+str(i+1))

