from __future__ import print_function
import plottery.plottery as ply
import ROOT as r
import numpy as np
import sys,os

filename = "debug.root"
if len(sys.argv) > 1:
    filename = sys.argv[1]

xaxis_range = [0,50] #SUBJECT TO CHANGE

def plot_occupancy(hist,prefix,additional_options = None):
    global xaxis_range
    filename_prefix = prefix.replace(" ","_")
<<<<<<< HEAD
    filename_prefix = "/home/users/bsathian/public_html/SDL/SDL_20190918/hit_occupancies/"+filename_prefix
=======
    filename_prefix = "/home/users/bsathian/public_html/SDL/SDL_20190918/"+filename_prefix
>>>>>>> f06ab09736044651cc442ab94a96e707acc2b60d
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
    layer_average_occupancy_hists.append(f.Get("Root__occupancy_in_layer_"+str(i)))
    layer_barrel_average_occupancy_hists.append(f.Get("Root__average_occupancy_in_barrel_for_layer_"+str(i)))
    layer_endcap_average_occupancy_hists.append(f.Get("Root__average_occupancy_in_endcap_for_layer_"+str(i)))

    layer_occupancy_hists.append(f.Get("Root__occupancy_in_layer_"+str(i)))
    layer_barrel_occupancy_hists.append(f.Get("Root__occupancy_in_barrel_for_layer_"+str(i)))
    layer_endcap_occupancy_hists.append(f.Get("Root__occupancy_in_endcap_for_layer_"+str(i)))

for i in range(1,16):
    ring_endcap_average_occupancy_hists.append(f.Get("Root__average_occupancy_in_endcap_for_ring_"+str(i)))
    ring_endcap_occupancy_hists.append(f.Get("Root__occupancy_in_endcap_for_ring_"+str(i)))



barrel_occupancy_hist = f.Get("Root__occupancy_in_barrel")
endcap_occupancy_hist = f.Get("Root__occupancy_in_endcap")

barrel_average_occupancy_hist = f.Get("Root__average_occupancy_in_barrel")
endcap_average_occupancy_hist = f.Get("Root__average_occupancy_in_endcap")

<<<<<<< HEAD
plot_occupancy(barrel_occupancy_hist,"barrel occupancy",additional_options = {"yaxis_log":True,"xaxis_range":[0,100],"yaxis_range":[0.1,1e7]})
plot_occupancy(endcap_occupancy_hist,"endcap occupancy",additional_options = {"yaxis_log":True,"xaxis_range":[0,100],"yaxis_range":[0.1,1e7]})
=======
plot_occupancy(barrel_occupancy_hist,"barrel occupancy",additional_options = {"yaxis_log":True,"xaxis_range":[0,100],"yaxis_range":[0.1,1e4]})
plot_occupancy(endcap_occupancy_hist,"endcap occupancy",additional_options = {"yaxis_log":True,"xaxis_range":[0,100],"yaxis_range":[0.1,1e4])
>>>>>>> f06ab09736044651cc442ab94a96e707acc2b60d

plot_occupancy(barrel_average_occupancy_hist,"barrel average occupancy")
plot_occupancy(endcap_average_occupancy_hist,"endcap average occupancy")


for i in range(len(layer_occupancy_hists)):
    plot_occupancy(layer_occupancy_hists[i],"Occupancy for layer "+str(i+1))
<<<<<<< HEAD
    plot_occupancy(layer_barrel_occupancy_hists[i],"Barrel Occupancy for layer "+str(i+1),additional_options = {"yaxis_log":True,"xaxis_range":[0,100],"yaxis_range":[0.1,1e6]})
    if i != 5:
        plot_occupancy(layer_endcap_occupancy_hists[i],"Endcap Occupancy for layer "+str(i+1),additional_options = {"yaxis_log":True,"xaxis_range":[0,100],"yaxis_range":[0.1,1e6]})
=======
    plot_occupancy(layer_barrel_occupancy_hists[i],"Barrel Occupancy for layer "+str(i+1),additional_options = {"yaxis_log":True,"xaxis_range":[0,100],"yaxis_range":[0.1,1e4])
    if i != 5:
        plot_occupancy(layer_endcap_occupancy_hists[i],"Endcap Occupancy for layer "+str(i+1),additional_options = {"yaxis_log":True,"xaxis_range":[0,100],"yaxis_range":[0.1,1e4])
>>>>>>> f06ab09736044651cc442ab94a96e707acc2b60d



for i in range(len(layer_average_occupancy_hists)):
    plot_occupancy(layer_average_occupancy_hists[i],"Average occupancy for layer "+str(i+1))
    plot_occupancy(layer_barrel_average_occupancy_hists[i],"Average barrel occupancy for layer "+str(i+1))
    if i!= 5:
        plot_occupancy(layer_endcap_average_occupancy_hists[i],"Average endcap occupancy for layer "+str(i+1))

for i in range(len(ring_endcap_average_occupancy_hists)):
    plot_occupancy(ring_endcap_average_occupancy_hists[i],"Average endcap occupancy in ring "+str(i+1))
<<<<<<< HEAD
    plot_occupancy(ring_endcap_occupancy_hists[i],"Endcap occupancy in ring "+str(i+1),additional_options = {"yaxis_log":True,"xaxis_range":[0,100],"yaxis_range":[0.1,3e4]})
=======
    plot_occupancy(ring_endcap_occupancy_hists[i],"Endcap occupancy in ring "+str(i+1),additional_options = {"yaxis_log":True,"xaxis_range":[0,100],"yaxis_range":[0.1,1e4])
>>>>>>> f06ab09736044651cc442ab94a96e707acc2b60d


