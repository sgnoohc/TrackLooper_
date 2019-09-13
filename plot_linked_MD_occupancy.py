from __future__ import print_function
import plottery.plottery as ply
import ROOT as r
import numpy as np
import sys,os

filename = "debug.root"
if len(sys.argv) > 1:
    filename = sys.argv[1]

xaxis_range = [0,50] #SUBJECT TO CHANGE
xaxis_range_average = [0,25]

def plot_occupancy(hist,prefix,additional_options = None):
    global xaxis_range,xaxis_range_average
    filename_prefix = prefix.replace(" ","_")
    filename_prefix = "/home/users/bsathian/public_html/SDL/"+filename_prefix
    xaxis_plot = None
    if "average" not in prefix:
        xaxis_plot = xaxis_range
    else:
        xaxis_plot = xaxis_range_average

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
layer_barrel_average_occupancy_hists = []
layer_barrel_occupancy_hists = []
layer_endcap_average_occupancy_hists = []
layer_endcap_occupancy_hists = []
ring_endcap_average_occupancy_hists = []
ring_endcap_occupancy_hists = []

linked_average_modules_in_barrel_layer = []
linked_average_modules_in_endcap_layer = []
linked_average_modules_in_endcap_ring = []

linked_modules_in_barrel_layer = []
linked_modules_in_endcap_layer = []
linked_modules_in_endcap_ring = []

for i in range(1,7):
    layer_average_occupancy_hists.append(f.Get("Root__average_Linked_MD_occupancy_in_layer_"+str(i)))
    layer_barrel_average_occupancy_hists.append(f.Get("Root__average_Linked_MD_occupancy_in_barrel_for_layer_"+str(i)))
    layer_endcap_average_occupancy_hists.append(f.Get("Root__average_Linked_MD_occupancy_in_endcap_for_layer_"+str(i)))

    layer_barrel_occupancy_hists.append(f.Get("Root__Linked_MD_occupancy_in_barrel_for_layer_"+str(i)))
    layer_endcap_occupancy_hists.append(f.Get("Root__Linked_MD_occupancy_in_endcap_for_layer_"+str(i)))

    linked_average_modules_in_barrel_layer.append(f.Get("Root__average_number_of_Linked_modules_in_barrel_for_layer_"+str(i)))
    linked_average_modules_in_endcap_layer.append(f.Get("Root__average_number_of_Linked_modules_in_endcap_for_layer_"+str(i)))
    linked_modules_in_barrel_layer.append(f.Get("Root__number_of_Linked_modules_in_barrel_for_layer_"+str(i)))
    linked_modules_in_endcap_layer.append(f.Get("Root__number_of_Linked_modules_in_endcap_for_layer_"+str(i)))


for i in range(1,16):
    ring_endcap_average_occupancy_hists.append(f.Get("Root__average_Linked_MD_occupancy_in_endcap_for_ring_"+str(i)))
    ring_endcap_occupancy_hists.append(f.Get("Root__Linked_MD_occupancy_in_endcap_for_ring_"+str(i)))

    linked_average_modules_in_endcap_ring.append(f.Get("Root__average_number_of_Linked_modules_in_endcap_for_ring_"+str(i)))
    linked_modules_in_endcap_ring.append(f.Get("Root__number_of_Linked_modules_in_endcap_for_ring_"+str(i)))




barrel_occupancy_hist = f.Get("Root__Linked_MD_occupancy_in_barrel")
endcap_occupancy_hist = f.Get("Root__Linked_MD_occupancy_in_endcap")

barrel_average_occupancy_hist = f.Get("Root__average_Linked_MD_occupancy_in_barrel")
endcap_average_occupancy_hist = f.Get("Root__average_Linked_MD_occupancy_in_endcap")

barrel_average_linked_modules_hist = f.Get("Root__average_number_of_Linked_modules_in_barrel")
endcap_average_linked_modules_hist = f.Get("Root__average_number_of_Linked_modules_in_endcap")

barrel_linked_module_hist = f.Get("Root__number_of_Linked_modules_in_barrel")
endcap_linked_module_hist = f.Get("Root__number_of_Linked_modules_in_endcap")

plot_occupancy(barrel_occupancy_hist,"barrel mini-doublet occupancy")
plot_occupancy(endcap_occupancy_hist,"endcap mini-doublet occupancy")

plot_occupancy(barrel_average_occupancy_hist,"barrel average mini-doublet occupancy")
plot_occupancy(endcap_average_occupancy_hist,"endcap average mini-doublet occupancy")

plot_occupancy(barrel_average_linked_modules_hist,"average number of linked modules in barrel")
plot_occupancy(endcap_average_linked_modules_hist,"average number of linked modules in endcap")

plot_occupancy(barrel_linked_module_hist,"number of linked modules in barrel")
plot_occupancy(endcap_linked_module_hist,"number of linked modules in endcap")


zero_module_2d_hist = f.Get("Root__zero_connected_module_ring_v_layer")
ply.plot_hist_2d(
    hist = zero_module_2d_hist,
    options = {
            "xaxis_label":"Endcap ring number",
            "yaxis_label":"Endcap layer number",
            "title":"Endcap ring and layer numbers for zero connection modules",
            "output_name":"zero_connection_layer_ring.pdf",
        }
        )


for i in range(len(layer_barrel_occupancy_hists)):
    plot_occupancy(layer_barrel_occupancy_hists[i],"Barrel Linked Mini-doublet Occupancy for layer "+str(i+1))
    if i != 5:
        plot_occupancy(layer_endcap_occupancy_hists[i],"Endcap Linked mini-doublet Occupancy for layer "+str(i+1))




for i in range(len(layer_barrel_average_occupancy_hists)):
    plot_occupancy(layer_barrel_average_occupancy_hists[i],"Average barrel Linked mini-doublet occupancy for layer "+str(i+1))
    if i!=5 :
        plot_occupancy(linked_modules_in_barrel_layer[i],"number of linked modules in barrel layer "+str(i+1),additional_options = {"yaxis_log":True,"legend_smart":False})
        plot_occupancy(linked_average_modules_in_barrel_layer[i],"average number of linked modules in barrel layer "+str(i+1))
    if i!= 5:
        plot_occupancy(layer_endcap_average_occupancy_hists[i],"Average endcap Linked mini-doublet occupancy for layer "+str(i+1))
    if i<4:
        plot_occupancy(linked_average_modules_in_endcap_layer[i],"average number of linked modules in endcap layer "+str(i+1))
        plot_occupancy(linked_modules_in_endcap_layer[i],"number of linked modules in endcap layer "+str(i+1),additional_options = {"yaxis_log":True,"legend_smart":False})


for i in range(len(ring_endcap_average_occupancy_hists)):
    plot_occupancy(ring_endcap_average_occupancy_hists[i],"Average endcap mini-doublet occupancy in ring "+str(i+1))
    plot_occupancy(ring_endcap_occupancy_hists[i],"Endcap mini-doublet occupancy in ring "+str(i+1))
    if i< 14:
        plot_occupancy(linked_modules_in_endcap_ring[i],"number of linked modules in endcap ring "+str(i+1),additional_options = {"yaxis_log":True,"legend_smart":False})
        plot_occupancy(linked_average_modules_in_endcap_ring[i],"average number of linked modules in endcap ring "+str(i+1))




