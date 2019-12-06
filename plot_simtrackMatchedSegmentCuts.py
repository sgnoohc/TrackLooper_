from __future__ import print_function
import plottery.plottery as ply
import ROOT as r
import numpy as np
import sys,os

filename_PU200 = "debug_ttbar_segments.root"
filename_muonGun = "debug_muonGun_segments.root"

#Normalize the track matched muon gun histograms with respect to complete muon gun histogrmas (i.e., not track matched). This is to ensure the track matched distribution (which is intended to be a subset of the larger distribution) has a smaller integral than the PU200 distribution

directory_prefix = "/home/users/bsathian/public_html/SDL/SDL_Segments/20191129-MuGunvTTBar/"

def normalize_histograms(hist_PU200,hist_muonGun_matched,hist_muonGun_unmatched):
    global directory_prefix
    hist_PU200.Scale(1.0/hist_PU200.Integral())
    hist_muonGun_matched.Scale(1.0/hist_muonGun_unmatched.Integral())
    hist_muonGun_unmatched.Scale(1.0/hist_muonGun_unmatched.Integral())

    return hist_PU200,hist_muonGun_matched,hist_muonGun_unmatched


def plot_md_params(PU200_hist,muonGun_matched_hist,muonGun_hist,prefix,additional_options = None):
    global directory_prefix
    PU200_normed_hist, muonGun_matched_normed_hist, muonGun_normed_hist = normalize_histograms(PU200_hist,muonGun_matched_hist,muonGun_hist)
    filename_prefix = prefix.replace(" ","_")
    filename_prefix = directory_prefix + filename_prefix

    default_options = {
        "output_name":filename_prefix+".pdf",
        "do_stack":False,
        "legend_smart":False,
        "xaxis_range":[-10,10],
        "yaxis_log":True,
        "yaxis_range":[1e-6,5],
#        "yaxis_range":[0.1,1e6],
        "xaxis_label":"",
        "title":prefix,
        "legend_percentageinbox":False,
        }
    if "dPhi" in prefix and "dPhiChange" not in prefix:
       default_options["xaxis_range"] = [-3.14,3.14]
    elif "dz" in prefix :
        default_options["xaxis_range"] = [-200,200]
    elif "drt" in prefix:
        default_options["xaxis_range"] = [0,200]
    options = default_options.copy()
    if type(additional_options) is dict:
        options.update(additional_options)

    ply.plot_hist(
        bgs = [PU200_normed_hist,muonGun_matched_normed_hist],
        legend_labels = ["High pile-up","Matched muon gun"],
#        legend_labels = ["Rec hits","Rec hits matched to sim hits"],
        colors = [r.kBlue,r.kRed],
        options = options)

f_PU200 = r.TFile(filename_PU200)
f_muonGun = r.TFile(filename_muonGun)

dzDiffLow_hist_PU200 = f_PU200.Get("Root__Segment_dzDiffLow")
dzDiffLow_hist_muonGun = f_muonGun.Get("Root__Segment_dzDiffLow")
dzDiffLow_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_dzDiffLow")

dzDiffHigh_hist_PU200 = f_PU200.Get("Root__Segment_dzDiffHigh")
dzDiffHigh_hist_muonGun = f_muonGun.Get("Root__Segment_dzDiffHigh")
dzDiffHigh_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_dzDiffHigh")

dzDiffLow_barrel_hist_PU200 = f_PU200.Get("Root__Segment_barrel_dzDiffLow")
dzDiffLow_barrel_hist_muonGun = f_muonGun.Get("Root__Segment_barrel_dzDiffLow")
dzDiffLow_barrel_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_barrel_dzDiffLow")

dzDiffHigh_barrel_hist_PU200 = f_PU200.Get("Root__Segment_barrel_dzDiffHigh")
dzDiffHigh_barrel_hist_muonGun = f_muonGun.Get("Root__Segment_barrel_dzDiffHigh")
dzDiffHigh_barrel_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_barrel_dzDiffHigh")

drtDiffLow_endcap_hist_PU200 = f_PU200.Get("Root__Segment_endcap_drtDiffLow")
drtDiffLow_endcap_hist_muonGun = f_muonGun.Get("Root__Segment_endcap_drtDiffLow")
drtDiffLow_endcap_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_endcap_drtDiffLow")

drtDiffHigh_endcap_hist_PU200 = f_PU200.Get("Root__Segment_endcap_drtDiffHigh")
drtDiffHigh_endcap_hist_muonGun = f_muonGun.Get("Root__Segment_endcap_drtDiffHigh")
drtDiffHigh_endcap_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_endcap_drtDiffHigh")

dPhi_hist_PU200 = f_PU200.Get("Root__Segment_dPhi")
dPhi_hist_muonGun = f_muonGun.Get("Root__Segment_dPhi")
dPhi_hist_matched_muonGun = f_muonGun.Get("Root__Segment_dPhi")

dPhi_barrel_hist_PU200 = f_PU200.Get("Root__Segment_barrel_dPhi")
dPhi_barrel_hist_muonGun = f_muonGun.Get("Root__Segment_barrel_dPhi")
dPhi_barrel_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_barrel_dPhi")

dPhi_endcap_hist_PU200 = f_PU200.Get("Root__Segment_endcap_dPhi")
dPhi_endcap_hist_muonGun = f_muonGun.Get("Root__Segment_endcap_dPhi")
dPhi_endcap_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_endcap_dPhi")

dPhiChange_hist_PU200 = f_PU200.Get("Root__Segment_dPhiChange")
dPhiChange_hist_muonGun = f_muonGun.Get("Root__Segment_dPhiChange")
dPhiChange_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_dPhiChange")

dPhiChange_barrel_hist_PU200 = f_PU200.Get("Root__Segment_barrel_dPhiChange")
dPhiChange_barrel_hist_muonGun = f_muonGun.Get("Root__Segment_barrel_dPhiChange")
dPhiChange_barrel_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_barrel_dPhiChange")

dPhiChange_endcap_hist_PU200 = f_PU200.Get("Root__Segment_endcap_dPhiChange")
dPhiChange_endcap_hist_muonGun = f_muonGun.Get("Root__Segment_endcap_dPhiChange")
dPhiChange_endcap_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_endcap_dPhiChange")

dAlphaInnerMDSegment_hist_PU200 = f_PU200.Get("Root__Segment_dAlphaInnerMDSegment")
dAlphaInnerMDSegment_hist_muonGun = f_muonGun.Get("Root__Segment_dAlphaInnerMDSegment")
dAlphaInnerMDSegment_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_dAlphaInnerMDSegment")

dAlphaInnerMDSegment_barrel_hist_PU200 = f_PU200.Get("Root__Segment_barrel_dAlphaInnerMDSegment")
dAlphaInnerMDSegment_barrel_hist_muonGun = f_muonGun.Get("Root__Segment_barrel_dAlphaInnerMDSegment")
dAlphaInnerMDSegment_barrel_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_barrel_dAlphaInnerMDSegment")

dAlphaInnerMDSegment_endcap_hist_PU200 = f_PU200.Get("Root__Segment_endcap_dAlphaInnerMDSegment")
dAlphaInnerMDSegment_endcap_hist_muonGun = f_muonGun.Get("Root__Segment_endcap_dAlphaInnerMDSegment")
dAlphaInnerMDSegment_endcap_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_endcap_dAlphaInnerMDSegment")

dAlphaOuterMDSegment_hist_PU200 = f_PU200.Get("Root__Segment_dAlphaOuterMDSegment")
dAlphaOuterMDSegment_hist_muonGun = f_muonGun.Get("Root__Segment_dAlphaOuterMDSegment")
dAlphaOuterMDSegment_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_dAlphaOuterMDSegment")

dAlphaOuterMDSegment_barrel_hist_PU200 = f_PU200.Get("Root__Segment_barrel_dAlphaOuterMDSegment")
dAlphaOuterMDSegment_barrel_hist_muonGun = f_muonGun.Get("Root__Segment_barrel_dAlphaOuterMDSegment")
dAlphaOuterMDSegment_barrel_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_barrel_dAlphaOuterMDSegment")

dAlphaOuterMDSegment_endcap_hist_PU200 = f_PU200.Get("Root__Segment_endcap_dAlphaOuterMDSegment")
dAlphaOuterMDSegment_endcap_hist_muonGun = f_muonGun.Get("Root__Segment_endcap_dAlphaOuterMDSegment")
dAlphaOuterMDSegment_endcap_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_endcap_dAlphaOuterMDSegment")

dAlphaInnerMDOuterMD_hist_PU200 = f_PU200.Get("Root__Segment_dAlphaInnerMDOuterMD")
dAlphaInnerMDOuterMD_hist_muonGun = f_muonGun.Get("Root__Segment_dAlphaInnerMDOuterMD")
dAlphaInnerMDOuterMD_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_dAlphaInnerMDOuterMD")

dAlphaInnerMDOuterMD_barrel_hist_PU200 = f_PU200.Get("Root__Segment_barrel_dAlphaInnerMDOuterMD")
dAlphaInnerMDOuterMD_barrel_hist_muonGun = f_muonGun.Get("Root__Segment_barrel_dAlphaInnerMDOuterMD")
dAlphaInnerMDOuterMD_barrel_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_barrel_dAlphaInnerMDOuterMD")

dAlphaInnerMDOuterMD_endcap_hist_PU200 = f_PU200.Get("Root__Segment_endcap_dAlphaInnerMDOuterMD")
dAlphaInnerMDOuterMD_endcap_hist_muonGun = f_muonGun.Get("Root__Segment_endcap_dAlphaInnerMDOuterMD")
dAlphaInnerMDOuterMD_endcap_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_endcap_dAlphaInnerMDOuterMD")


dzDiffLow_layer_hists_PU200 = []
dzDiffLow_layer_hists_muonGun = []
dzDiffLow_layer_hists_matched_muonGun = []

dzDiffHigh_layer_hists_PU200 = []
dzDiffHigh_layer_hists_muonGun = []
dzDiffHigh_layer_hists_matched_muonGun = []

dzDiffLow_barrel_layer_hists_PU200 = []
dzDiffLow_barrel_layer_hists_muonGun = []
dzDiffLow_barrel_layer_hists_matched_muonGun = []

dzDiffHigh_barrel_layer_hists_PU200 = []
dzDiffHigh_barrel_layer_hists_muonGun = []
dzDiffHigh_barrel_layer_hists_matched_muonGun = []

drtDiffLow_endcap_layer_hists_PU200 = []
drtDiffLow_endcap_layer_hists_muonGun = []
drtDiffLow_endcap_layer_hists_matched_muonGun = []

drtDiffHigh_endcap_layer_hists_PU200 = []
drtDiffHigh_endcap_layer_hists_muonGun = []
drtDiffHigh_endcap_layer_hists_matched_muonGun = []

drtDiffLow_endcap_ring_hists_PU200 = []
drtDiffLow_endcap_ring_hists_muonGun = []
drtDiffLow_endcap_ring_hists_matched_muonGun = []

drtDiffHigh_endcap_ring_hists_PU200 = []
drtDiffHigh_endcap_ring_hists_muonGun = []
drtDiffHigh_endcap_ring_hists_matched_muonGun = []

dPhi_layer_hists_PU200 = []
dPhi_layer_hists_muonGun = []
dPhi_layer_hists_matched_muonGun = []

dPhi_barrel_layer_hists_PU200 = []
dPhi_barrel_layer_hists_muonGun = []
dPhi_barrel_layer_hists_matched_muonGun = []

dPhi_endcap_layer_hists_PU200 = []
dPhi_endcap_layer_hists_muonGun = []
dPhi_endcap_layer_hists_matched_muonGun = []

dPhi_endcap_ring_hists_PU200 = []
dPhi_endcap_ring_hists_muonGun = []
dPhi_endcap_ring_hists_matched_muonGun = []

dPhiChange_layer_hists_PU200 = []
dPhiChange_layer_hists_muonGun = []
dPhiChange_layer_hists_matched_muonGun = []

dPhiChange_barrel_layer_hists_PU200 = []
dPhiChange_barrel_layer_hists_muonGun = []
dPhiChange_barrel_layer_hists_matched_muonGun = []

dPhiChange_endcap_layer_hists_PU200 = []
dPhiChange_endcap_layer_hists_muonGun = []
dPhiChange_endcap_layer_hists_matched_muonGun = []

dPhiChange_endcap_ring_hists_PU200 = []
dPhiChange_endcap_ring_hists_muonGun = []
dPhiChange_endcap_ring_hists_matched_muonGun = []

dAlphaInnerMDSegment_layer_hists_PU200 = []
dAlphaInnerMDSegment_layer_hists_muonGun = []
dAlphaInnerMDSegment_layer_hists_matched_muonGun = []

dAlphaInnerMDSegment_barrel_layer_hists_PU200 = []
dAlphaInnerMDSegment_barrel_layer_hists_muonGun = []
dAlphaInnerMDSegment_barrel_layer_hists_matched_muonGun = []

dAlphaInnerMDSegment_endcap_layer_hists_PU200 = []
dAlphaInnerMDSegment_endcap_layer_hists_muonGun = []
dAlphaInnerMDSegment_endcap_layer_hists_matched_muonGun = []

dAlphaInnerMDSegment_endcap_ring_hists_PU200 = []
dAlphaInnerMDSegment_endcap_ring_hists_muonGun = []
dAlphaInnerMDSegment_endcap_ring_hists_matched_muonGun = []

dAlphaOuterMDSegment_layer_hists_PU200 = []
dAlphaOuterMDSegment_layer_hists_muonGun = []
dAlphaOuterMDSegment_layer_hists_matched_muonGun = []

dAlphaOuterMDSegment_barrel_layer_hists_PU200 = []
dAlphaOuterMDSegment_barrel_layer_hists_muonGun = []
dAlphaOuterMDSegment_barrel_layer_hists_matched_muonGun = []

dAlphaOuterMDSegment_endcap_layer_hists_PU200 = []
dAlphaOuterMDSegment_endcap_layer_hists_muonGun = []
dAlphaOuterMDSegment_endcap_layer_hists_matched_muonGun = []

dAlphaOuterMDSegment_endcap_ring_hists_PU200 = []
dAlphaOuterMDSegment_endcap_ring_hists_muonGun = []
dAlphaOuterMDSegment_endcap_ring_hists_matched_muonGun = []

dAlphaInnerMDOuterMD_layer_hists_PU200 = []
dAlphaInnerMDOuterMD_layer_hists_muonGun = []
dAlphaInnerMDOuterMD_layer_hists_matched_muonGun = []

dAlphaInnerMDOuterMD_barrel_layer_hists_PU200 = []
dAlphaInnerMDOuterMD_barrel_layer_hists_muonGun = []
dAlphaInnerMDOuterMD_barrel_layer_hists_matched_muonGun = []

dAlphaInnerMDOuterMD_endcap_layer_hists_PU200 = []
dAlphaInnerMDOuterMD_endcap_layer_hists_muonGun = []
dAlphaInnerMDOuterMD_endcap_layer_hists_matched_muonGun = []

dAlphaInnerMDOuterMD_endcap_ring_hists_PU200 = []
dAlphaInnerMDOuterMD_endcap_ring_hists_muonGun = []
dAlphaInnerMDOuterMD_endcap_ring_hists_matched_muonGun = []

for layer in range(1,6):
    dzDiffLow_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dzDiffLow_layer_"+str(layer)))
    dzDiffLow_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dzDiffLow_layer_"+str(layer)))
    dzDiffLow_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dzDiffLow_layer_"+str(layer)))

    dzDiffHigh_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dzDiffHigh_layer_"+str(layer)))
    dzDiffHigh_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dzDiffHigh_layer_"+str(layer)))
    dzDiffHigh_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dzDiffHigh_layer_"+str(layer)))

    dzDiffLow_barrel_layer_hists_pu200.append(f_pu200.get("root__segment_barrel_dzDiffLow_layer_"+str(layer)))
    dzDiffLow_barrel_layer_hists_muongun.append(f_muongun.get("root__segment_barrel_dzDiffLow_layer_"+str(layer)))
    dzDiffLow_barrel_layer_hists_matched_muongun.append(f_muongun.get("root__sim_matched_segment_barrel_dzDiffLow_layer_"+str(layer)))

    dzDiffHigh_barrel_layer_hists_pu200.append(f_pu200.get("root__segment_barrel_dzDiffHigh_layer_"+str(layer)))
    dzDiffLow_barrel_layer_hists_muongun.append(f_muongun.get("root__segment_barrel_dzDiffHigh_layer_"+str(layer)))
    dzDiffLow_barrel_layer_hists_matched_muongun.append(f_muongun.get("root__sim_matched_segment_barrel_dzDiffHigh_layer_"+str(layer)))


    dPhi_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dPhi_layer_"+str(layer)))
    dPhi_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dPhi_layer_"+str(layer)))
    dPhi_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dPhi_layer_"+str(layer)))

    dPhi_barrel_layer_hists_PU200.append(f_PU200.Get("Root__Segment_barrel_dPhi_layer_"+str(layer)))
    dPhi_barrel_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_barrel_dPhi_layer_"+str(layer)))
    dPhi_barrel_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_barrel_dPhi_layer_"+str(layer)))

    dPhiChange_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dPhiChange_layer_"+str(layer)))
    dPhiChange_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dPhiChange_layer_"+str(layer)))
    dPhiChange_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dPhiChange_layer_"+str(layer)))

    dPhiChange_barrel_layer_hists_PU200.append(f_PU200.Get("Root__Segment_barrel_dPhiChange_layer_"+str(layer)))
    dPhiChange_barrel_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_barrel_dPhiChange_layer_"+str(layer)))
    dPhiChange_barrel_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_barrel_dPhiChange_layer_"+str(layer)))

    dAlphaInnerMDSegment_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dAlphaInnerMDSegment_layer"+str(layer)))
    dAlphaInnerMDSegment_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dAlphaInnerMDSegment_layer"+str(layer)))
    dAlphaInnerMDSegment_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dAlphaInnerMDSegment_layer"+str(layer)))

    dAlphaInnerMDSegment_barrel_layer_hists_PU200.append(f_PU200.Get("Root__Segment_barrel_dAlphaInnerMDSegment_layer"+str(layer)))
    dAlphaInnerMDSegment_barrel_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_barrel_dAlphaInnerMDSegment_layer"+str(layer)))
    dAlphaInnerMDSegment_barrel_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_barrel_dAlphaInnerMDSegment_layer"+str(layer)))

    dAlphaOuterMDSegment_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dAlphaOuterMDSegment_layer"+str(layer)))
    dAlphaOuterMDSegment_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dAlphaOuterMDSegment_layer"+str(layer)))
    dAlphaOuterMDSegment_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dAlphaOuterMDSegment_layer"+str(layer)))

    dAlphaOuterMDSegment_barrel_layer_hists_PU200.append(f_PU200.Get("Root__Segment_barrel_dAlphaOuterMDSegment_layer"+str(layer)))
    dAlphaOuterMDSegment_barrel_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_barrel_dAlphaOuterMDSegment_layer"+str(layer)))
    dAlphaOuterMDSegment_barrel_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_barrel_dAlphaOuterMDSegment_layer"+str(layer)))

    dAlphaInnerMDOuterMD_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dAlphaInnerMDOuterMD_layer"+str(layer)))
    dAlphaInnerMDOuterMD_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dAlphaInnerMDOuterMD_layer"+str(layer)))
    dAlphaInnerMDOuterMD_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dAlphaInnerMDOuterMD_layer"+str(layer)))

    dAlphaInnerMDOuterMD_barrel_layer_hists_PU200.append(f_PU200.Get("Root__Segment_barrel_dAlphaInnerMDOuterMD_layer"+str(layer)))
    dAlphaInnerMDOuterMD_barrel_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_barrel_dAlphaInnerMDOuterMD_layer"+str(layer)))
    dAlphaInnerMDOuterMD_barrel_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_barrel_dAlphaInnerMDOuterMD_layer"+str(layer)))

    if layer < 5:
        drtDiffLow_endcap_layer_hists_PU200.append(f_PU200.Get("Root__Segment_endcap_drtDiffLow_layer_"+str(layer)))
        drtDiffLow_endcap_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_endcap_drtDiffLow_layer_"+str(layer)))
        drtDiffLow_endcap_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_endcap_drtDiffLow_layer_"+str(layer)))

        drtDiffHigh_endcap_layer_hists_PU200.append(f_PU200.Get("Root__Segment_endcap_drtDiffHigh_layer_"+str(layer)))
        drtDiffHigh_endcap_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_endcap_drtDiffHigh_layer_"+str(layer)))
        drtDiffHigh_endcap_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_endcap_drtDiffHigh_layer_"+str(layer)))


        dPhi_endcap_layer_hists_PU200.append(f_PU200.Get("Root__Segment_endcap_dPhi_layer_"+str(layer)))
        dPhi_endcap_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_endcap_dPhi_layer_"+str(layer)))
        dPhi_endcap_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_endcap_dPhi_layer_"+str(layer)))

        dPhiChange_endcap_layer_hists_PU200.append(f_PU200.Get("Root__Segment_endcap_dPhiChange_layer_"+str(layer)))
        dPhiChange_endcap_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_endcap_dPhiChange_layer_"+str(layer)))
        dPhiChange_endcap_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_endcap_dPhiChange_layer_"+str(layer)))

        dAlphaInnerMDSegment_endcap_layer_hists_PU200.append(f_PU200.Get("Root__Segment_endcap_dAlphaInnerMDSegment_layer"+str(layer)))
        dAlphaInnerMDSegment_endcap_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_endcap_dAlphaInnerMDSegment_layer"+str(layer)))
        dAlphaInnerMDSegment_endcap_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_endcap_dAlphaInnerMDSegment_layer"+str(layer)))

        dAlphaOuterMDSegment_endcap_layer_hists_PU200.append(f_PU200.Get("Root__Segment_endcap_dAlphaOuterMDSegment_layer"+str(layer)))
        dAlphaOuterMDSegment_endcap_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_endcap_dAlphaOuterMDSegment_layer"+str(layer)))
        dAlphaOuterMDSegment_endcap_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_endcap_dAlphaOuterMDSegment_layer"+str(layer)))

        dAlphaInnerMDOuterMD_endcap_layer_hists_PU200.append(f_PU200.Get("Root__Segment_endcap_dAlphaInnerMDOuterMD_layer"+str(layer)))
        dAlphaInnerMDOuterMD_endcap_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_endcap_dAlphaInnerMDOuterMD_layer"+str(layer)))
        dAlphaInnerMDOuterMD_endcap_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_endcap_dAlphaInnerMDOuterMD_layer"+str(layer)))


for ring in range(1,16):
    drtDiffLow_endcap_ring_hists_PU200.append(f_PU200.Get("Root__Segment_endcap_drtDiffLow_ring_"+str(ring)))
    drtDiffLow_endcap_ring_hists_muonGun.append(f_muonGun.Get("Root__Segment_endcap_drtDiffLow_ring_"+str(ring)))
    drtDiffLow_endcap_ring_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_endcap_drtDiffLow_ring_"+str(ring)))

    drtDiffHigh_endcap_ring_hists_PU200.append(f_PU200.Get("Root__Segment_endcap_drtDiffHigh_ring_"+str(ring)))
    drtDiffHigh_endcap_ring_hists_muonGun.append(f_muonGun.Get("Root__Segment_endcap_drtDiffHigh_ring_"+str(ring)))
    drtDiffHigh_endcap_ring_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_endcap_drtDiffHigh_ring_"+str(ring)))


    dPhi_endcap_ring_hists_PU200.append(f_PU200.Get("Root__Segment_endcap_dPhi_ring"+str(ring)))
    dPhi_endcap_ring_hists_muonGun.append(f_muonGun.Get("Root__Segment_endcap_dPhi_ring"+str(ring)))
    dPhi_endcap_ring_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_endcap_dPhi_ring"+str(ring)))

    dPhiChange_endcap_ring_hists_PU200.append(f_PU200.Get("Root__Segment_endcap_dPhiChange_ring"+str(ring)))
    dPhiChange_endcap_ring_hists_muonGun.append(f_muonGun.Get("Root__Segment_endcap_dPhiChange_ring"+str(ring)))
    dPhiChange_endcap_ring_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_endcap_dPhiChange_ring"+str(ring)))

    dAlphaInnerMDSegment_endcap_ring_hists_PU200.append(f_PU200.Get("Root__Segment_endcap_dAlphaInnerMDSegment_ring"+str(ring)))
    dAlphaInnerMDSegment_endcap_ring_hists_muonGun.append(f_muonGun.Get("Root__Segment_endcap_dAlphaInnerMDSegment_ring"+str(ring)))
    dAlphaInnerMDSegment_endcap_ring_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_endcap_dAlphaInnerMDSegment_ring"+str(ring)))

    dAlphaOuterMDSegment_endcap_ring_hists_PU200.append(f_PU200.Get("Root__Segment_endcap_dAlphaOuterMDSegment_ring"+str(ring)))
    dAlphaOuterMDSegment_endcap_ring_hists_muonGun.append(f_muonGun.Get("Root__Segment_endcap_dAlphaOuterMDSegment_ring"+str(ring)))
    dAlphaOuterMDSegment_endcap_ring_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_endcap_dAlphaOuterMDSegment_ring"+str(ring)))

    dAlphaInnerMDOuterMD_endcap_ring_hists_PU200.append(f_PU200.Get("Root__Segment_endcap_dAlphaInnerMDOuterMD_ring"+str(ring)))
    dAlphaInnerMDOuterMD_endcap_ring_hists_muonGun.append(f_muonGun.Get("Root__Segment_endcap_dAlphaInnerMDOuterMD_ring"+str(ring)))
    dAlphaInnerMDOuterMD_endcap_ring_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_endcap_dAlphaInnerMDOuterMD_ring"+str(ring)))


plot_md_params(dzDiffLow_hist_PU200,dzDiffLow_hist_matched_muonGun,dzDiffLow_hist_muonGun,"Segment dzDiffLow histogram")

plot_md_params(dzDiffHigh_hist_PU200,dzDiffHigh_hist_matched_muonGun,dzDiffHigh_hist_muonGun,"Segment dzDiffHigh histogram")

plot_md_params(dzDiffLow_barrel_hist_PU200,dzDiffLow_barrel_hist_matched_muonGun,dzDiffLow_barrel_hist_muonGun,"Segment dzDiffLow histogram in barrel")

plot_md_params(dzDiffHigh_barrel_hist_PU200,dzDiffHigh_barrel_hist_matched_muonGun,dzDiffHigh_barrel_hist_muonGun,"Segment dzDiffHigh histogram in barrel")

plot_md_params(drtDiffLow_endcap_hist_PU200,drtDiffLow_endcap_hist_matched_muonGun,drtDiffLow_endcap_hist_muonGun,"Segment drtDiffLow histogram in endcap")

plot_md_params(drtDiffHigh_endcap_hist_PU200,drtDiffHigh_endcap_hist_matched_muonGun,drtDiffHigh_endcap_hist_muonGun,"Segment drtDiffHigh histogram in endcap")

plot_md_params(dPhi_hist_PU200,dPhi_hist_matched_muonGun,dPhi_hist_muonGun,"Segment dPhi histogram")
plot_md_params(dPhi_barrel_hist_PU200,dPhi_barrel_hist_matched_muonGun,dPhi_barrel_hist_muonGun,"Segment histogram in barrel")
plot_md_params(dPhi_endcap_hist_PU200,dPhi_endcap_hist_matched_muonGun,dPhi_barrel_hist_muonGun,"Segment dPhi histogram in endcap")

plot_md_params(dPhiChange_hist_PU200,dPhiChange_hist_matched_muonGun,dPhiChange_hist_muonGun,"Segment dPhiChange histogram")
plot_md_params(dPhiChange_barrel_hist_PU200,dPhiChange_barrel_hist_matched_muonGun,dPhiChange_barrel_hist_muonGun,"Segment dPhiChange histogram in barrel")
plot_md_params(dPhiChange_endcap_hist_PU200,dPhiChange_endcap_hist_matched_muonGun,dPhiChange_barrel_hist_muonGun,"Segment dPhiChange histogram in endcap")

plot_md_params(dAlphaInnerMDSegment_hist_PU200,dAlphaInnerMDSegment_hist_matched_muonGun,dAlphaInnerMDSegment_hist_muonGun,"Segment dAlphaInnerMDSegment histogram")
plot_md_params(dAlphaOuterMDSegment_hist_PU200,dAlphaOuterMDSegment_hist_matched_muonGun,dAlphaOuterMDSegment_hist_muonGun,"Segment dAlphaOuterMDSegment histogram")
plot_md_params(dAlphaInnerMDOuterMD_hist_PU200,dAlphaInnerMDOuterMD_hist_matched_muonGun,dAlphaInnerMDOuterMD_hist_muonGun,"Segment dAlphaInnerMDOuterMD histogram")



for layer in range(1,6):

    plot_md_params(dzDiffLow_layer_hists_PU200[layer-1],dzDiffLow_layer_hists_matched_muonGun[layer-1],dzDiffLow_layer_hists_muonGun[layer-1],"Segment dzDiffLow histogram for layer "+str(layer))

    plot_md_params(dzDiffHigh_layer_hists_PU200[layer-1],dzDiffHigh_layer_hists_matched_muonGun[layer-1],dzDiffHigh_layer_hists_muonGun[layer-1],"Segment dzDiffHigh histogram for layer "+str(layer))

    plot_md_params(dzDiffLow_barrel_layer_hists_PU200[layer-1],dzDiffLow_barrel_layer_hists_matched_muonGun[layer-1],dzDiffLow_barrel_layer_hists_muonGun[layer-1],"Segment dzDiffLow histogram in barrel for layer "+str(layer))

    plot_md_params(dzDiffLow_barrel_layer_hists_PU200[layer-1],dzDiffHigh_barrel_layer_hists_matched_muonGun[layer-1],dzDiffHigh_barrel_layer_hists_muonGun[layer-1],"Segment dzDiffHigh histogram in barrel for layer "+str(layer))

    plot_md_params(dPhi_layer_hists_PU200[layer-1],dPhi_layer_hists_matched_muonGun[layer-1],dPhi_layer_hists_muonGun[layer-1],"Segment dPhi histogram for layer "+str(layer))

    plot_md_params(dPhi_barrel_layer_hists_PU200[layer-1],dPhi_barrel_layer_hists_matched_muonGun[layer-1],dPhi_barrel_layer_hists_muonGun[layer-1],"Segment dPhi histogram in barrel for layer "+str(layer))

    plot_md_params(dPhiChange_layer_hists_PU200[layer-1],dPhiChange_layer_hists_matched_muonGun[layer-1],dPhiChange_layer_hists_muonGun[layer-1],"Segment dPhiChange histogram for layer "+str(layer))

    plot_md_params(dPhiChange_barrel_layer_hists_PU200[layer-1],dPhiChange_barrel_layer_hists_matched_muonGun[layer-1],dPhiChange_barrel_layer_hists_muonGun[layer-1],"Segment dPhiChange histogram in barrel for layer "+str(layer))

    plot_md_params(dAlphaInnerMDSegment_layer_hists_PU200[layer-1],dAlphaInnerMDSegment_layer_hists_matched_muonGun[layer-1],dAlphaInnerMDSegment_layer_hists_muonGun[layer-1],"Segment dAlphaInnerMDSegment histogram for layer "+str(layer))

    plot_md_params(dAlphaInnerMDSegment_barrel_layer_hists_PU200[layer-1],dAlphaInnerMDSegment_barrel_layer_hists_matched_muonGun[layer-1],dAlphaInnerMDSegment_barrel_layer_hists_muonGun[layer-1],"Segment dAlphaInnerMDSegment histogram in barrel for layer "+str(layer))

    plot_md_params(dAlphaOuterMDSegment_layer_hists_PU200[layer-1],dPhiChange_layer_hists_matched_muonGun[layer-1],dPhiChange_layer_hists_muonGun[layer-1],"Segment dAlphaOuterMDSegment histogram for layer "+str(layer))

    plot_md_params(dAlphaOuterMDSegment_barrel_layer_hists_PU200[layer-1],dAlphaOuterMDSegment_barrel_layer_hists_matched_muonGun[layer-1],dAlphaOuterMDSegment_barrel_layer_hists_muonGun[layer-1],"Segment dAlphaOuterMDSegment histogram in barrel for layer "+str(layer))

    plot_md_params(dAlphaInnerMDOuterMD_layer_hists_PU200[layer-1],dAlphaInnerMDOuterMD_layer_hists_matched_muonGun[layer-1],dAlphaInnerMDOuterMD_layer_hists_muonGun[layer-1],"Segment dAlphaInnerMDOuterMD histogram for layer "+str(layer))

    plot_md_params(dAlphaInnerMDOuterMD_barrel_layer_hists_PU200[layer-1],dAlphaInnerMDOuterMD_barrel_layer_hists_matched_muonGun[layer-1],dAlphaInnerMDOuterMD_barrel_layer_hists_muonGun[layer-1],"Segment dAlphaInnerMDOuterMD histogram in barrel for layer "+str(layer))


    if layer < 5:
        plot_md_params(drtDiffLow_endcap_layer_hists_PU200[layer-1],drtDiffLow_endcap_layer_hists_matched_muonGun[layer-1],drtDiffLow_endcap_layer_hists_muonGun[layer-1],"Segment drtDiffLow histogram in endcap for layer "+str(layer))

        plot_md_params(drtDiffHigh_endcap_layer_hists_PU200[layer-1],drtDiffHigh_endcap_layer_hists_matched_muonGun[layer-1],drtDiffHigh_endcap_layer_hists_muonGun[layer-1],"Segment drtDiffHigh histogram in endcap for layer "+str(layer))


        plot_md_params(dPhi_endcap_layer_hists_PU200[layer-1],dPhi_endcap_layer_hists_matched_muonGun[layer-1],dPhi_endcap_layer_hists_muonGun[layer-1],"Segment dPhi histogram in endcap for layer "+str(layer))

        plot_md_params(dPhiChange_endcap_layer_hists_PU200[layer-1],dPhiChange_endcap_layer_hists_matched_muonGun[layer-1],dPhiChange_endcap_layer_hists_muonGun[layer-1],"Segment dPhiChange histogram in endcap for layer "+str(layer))

        plot_md_params(dAlphaInnerMDSegment_endcap_layer_hists_PU200[layer-1],dAlphaInnerMDSegment_endcap_layer_hists_matched_muonGun[layer-1],dAlphaInnerMDSegment_endcap_layer_hists_muonGun[layer-1],"Segment dAlphaInnerMDSegment histogram in endcap for layer "+str(layer))

        plot_md_params(dAlphaOuterMDSegment_endcap_layer_hists_PU200[layer-1],dAlphaOuterMDSegment_endcap_layer_hists_matched_muonGun[layer-1],dAlphaOuterMDSegment_endcap_layer_hists_muonGun[layer-1],"Segment dAlphaOuterMDSegment histogram in endcap for layer "+str(layer))

        plot_md_params(dAlphaInnerMDOuterMD_endcap_layer_hists_PU200[layer-1],dAlphaInnerMDOuterMD_endcap_layer_hists_matched_muonGun[layer-1],dAlphaInnerMDOuterMD_endcap_layer_hists_muonGun[layer-1],"Segment dAlphaInnerMDOuterMD histogram in endcap for layer "+str(layer))



for ring in range(1,15):

    plot_md_params(drtDiffLow_endcap_ring_hists_PU200[ring-1],drtDiffLow_endcap_ring_hists_matched_muonGun[ring-1],drtDiffLow_endcap_ring_hists_muonGun[ring-1],"Segment drtDiffLow histogram in endcap for ring "+str(ring))

    plot_md_params(drtDiffHigh_endcap_ring_hists_PU200[ring-1],drtDiffHigh_endcap_ring_hists_matched_muonGun[ring-1],drtDiffHigh_endcap_ring_hists_muonGun[ring-1],"Segment drtDiffHigh histogram in endcap for ring "+str(ring))

    plot_md_params(dPhi_endcap_ring_hists_PU200[ring-1],dPhi_endcap_ring_hists_matched_muonGun[ring-1],dPhi_endcap_ring_hists_muonGun[ring-1],"Segment dPhi histogram in endcap for ring "+str(ring))

    plot_md_params(dPhiChange_endcap_ring_hists_PU200[ring-1],dPhiChange_endcap_ring_hists_matched_muonGun[ring-1],dPhiChange_endcap_ring_hists_muonGun[ring-1],"Segment dPhiChange histogram in endcap for ring "+str(ring))

    plot_md_params(dAlphaInnerMDSegment_endcap_ring_hists_PU200[ring-1],dAlphaInnerMDSegment_endcap_ring_hists_matched_muonGun[ring-1],dAlphaInnerMDSegment_endcap_ring_hists_muonGun[ring-1],"Segment dAlphaInnerMDSegment histogram in endcap for ring "+str(ring))

    plot_md_params(dAlphaOuterMDSegment_endcap_ring_hists_PU200[ring-1],dAlphaOuterMDSegment_endcap_ring_hists_matched_muonGun[ring-1],dAlphaOuterMDSegment_endcap_ring_hists_muonGun[ring-1],"Segment dAlphaOuterMDSegment histogram in endcap for ring "+str(ring))

    plot_md_params(dAlphaInnerMDOuterMD_endcap_ring_hists_PU200[ring-1],dAlphaInnerMDOuterMD_endcap_ring_hists_matched_muonGun[ring-1],dAlphaInnerMDOuterMD_endcap_ring_hists_muonGun[ring-1],"Segment dAlphaInnerMDOuterMD histogram in endcap for ring "+str(ring))


os.system("sh ~/niceplots/niceplots.sh "+directory_prefix)
os.system("chmod -R 755 "+directory_prefix)

