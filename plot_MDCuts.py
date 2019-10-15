from __future__ import print_function
import plottery.plottery as ply
import ROOT as r
import numpy as np
import sys,os

filename = "debug.root"
if len(sys.argv) > 1:
    filename = sys.argv[1]

def plot_md_params(hist,prefix,additional_options = None):
    filename_prefix = prefix.replace(" ","_")
    filename_prefix = "/home/users/bsathian/public_html/SDL/SDL_Minidoublets/PU140_20191004/"+filename_prefix

    default_options = {
        "output_name":filename_prefix+".pdf",
        "legend_smart":False,
        "xaxis_range":[-10,10],
        "yaxis_log":True,
        "yaxis_range":[0.1,1e6],
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

dz_hist = f.Get("Root__MD_dz")
dz_barrel_hist = f.Get("Root__MD_barrel_dz")
dz_endcap_hist = f.Get("Root__MD_endcap_dz")
dz_layer_hists = []
dz_barrel_layer_hists = []
dz_endcap_layer_hists = []

dPhi_hist = f.Get("Root__MD_dPhi")
dPhi_barrel_hist = f.Get("Root__MD_barrel_dPhi")
dPhi_endcap_hist = f.Get("Root__MD_endcap_dPhi")
dPhi_layer_hists = []
dPhi_barrel_layer_hists = []
dPhi_endcap_layer_hists = []

dPhiChange_hist = f.Get("Root__MD_dPhiChange")
dPhiChange_barrel_hist = f.Get("Root__MD_barrel_dPhiChange")
dPhiChange_endcap_hist = f.Get("Root__MD_endcap_dPhiChange")
dPhiChange_layer_hists = []
dPhiChange_barrel_layer_hists = []
dPhiChange_endcap_layer_hists = []


for layer in range(1,7):
    dz_layer_hists.append(f.Get("Root__MD_barrel_dz_layer_"+str(layer)))
    dz_barrel_layer_hists.append(f.Get("Root__MD_barrel_dz_layer_"+str(layer)))
    if layer < 6 :
        dz_endcap_layer_hists.append(f.Get("Root__MD_endcap_dz_layer_"+str(layer)))

    dPhi_layer_hists.append(f.Get("Root__MD_barrel_dPhi_layer_"+str(layer)))
    dPhi_barrel_layer_hists.append(f.Get("Root__MD_barrel_dPhi_layer_"+str(layer)))
    if layer < 6 :
        dPhi_endcap_layer_hists.append(f.Get("Root__MD_endcap_dPhi_layer_"+str(layer)))
plot_md_params(dz_hist,"Mini-doublet dz histogram")
plot_md_params(dz_barrel_hist,"Mini-doublet dz histogram in barrel")
plot_md_params(dz_endcap_hist,"Mini-doublet dz histogram in endcap")

for layer in range(1,7):
    plot_md_params(dz_layer_hists[layer-1],"Mini-doublet dz histogram for layer "+str(layer))
    plot_md_params(dz_barrel_layer_hists[layer-1],"Mini-doublet dz histogram in barrel for layer "+str(layer))
    if layer < 6:
        plot_md_params(dz_endcap_layer_hists[layer-1],"Mini-doublet dz histogram in endcap for layer "+str(layer))





