from __future__ import print_function
import plottery.plottery as ply
import ROOT as r
import numpy as np
import sys,os

filename_PU200 = "debug_ttbar_segments.root"
filename_muonGun = "debug_muonGun_segments.root"

#Normalize the track matched muon gun histograms with respect to complete muon gun histogrmas (i.e., not track matched). This is to ensure the track matched distribution (which is intended to be a subset of the larger distribution) has a smaller integral than the PU200 distribution

def normalize_histograms(hist_PU200,hist_muonGun_matched,hist_muonGun_unmatched):
    hist_PU200.Scale(1.0/hist_PU200.Integral())
    hist_muonGun_matched.Scale(1.0/hist_muonGun_unmatched.Integral())
    hist_muonGun_unmatched.Scale(1.0/hist_muonGun_unmatched.Integral())

    return hist_PU200,hist_muonGun_matched,hist_muonGun_unmatched


def plot_segment_params(PU200_hist,muonGun_matched_hist,muonGun_hist,prefix,additional_options = None):
    PU200_normed_hist, muonGun_matched_normed_hist, muonGun_normed_hist = normalize_histograms(PU200_hist,muonGun_matched_hist,muonGun_hist)
    filename_prefix = prefix.replace(" ","_")
    filename_prefix = "/home/users/bsathian/public_html/SDL/SDL_Minidoublets/20191110_lowPt_muGunvttbar/"+filename_prefix
#    filename_prefix = "/home/users/bsathian/public_html/SDL/SDL_Minidoublets/20191017_NuGun_tenMuon/"+filename_prefix

    default_options = {
        "output_name":filename_prefix+".pdf",
        "do_stack":False,
        "legend_smart":False,
        "xaxis_range":[-10,10],
        "yaxis_log":True,
        "yaxis_range":[1e-6,1],
#        "yaxis_range":[0.1,1e6],
        "xaxis_label":"",
        "title":prefix,
        "legend_percentageinbox":False,
        }
    if "dPhi" in prefix and "dPhiChange" not in prefix:
       default_options["xaxis_range"] = [-0.5,0.5]
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

dz_hist_PU200 = f_PU200.Get("Root__Segment_dz")
dz_hist_muonGun = f_muonGun.Get("Root__Segment_dz")
dz_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_dz")

dz_barrel_hist_PU200 = f_PU200.Get("Root__Segment_barrel_dz")
dz_barrel_hist_muonGun = f_muonGun.Get("Root__Segment_barrel_dz")
dz_barrel_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_barrel_dz")

drt_endcap_hist_PU200 = f_PU200.Get("Root__Segment_endcap_drt")
drt_endcap_hist_muonGun = f_muonGun.Get("Root__Segment_endcap_drt")
drt_endcap_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_endcap_drt")

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
dPhiChange_hist_muonGun = f_muonGun.Get("Roo__Segment_dPhiChange")
dPhiChange_hist_matched_muonGun = f_muonGun.Get("Root__sim_matched_Segment_dPhiChange")

dPhiChange_barrel_hist_PU200 = f_PU200.Get("Root__Segment_barrel_dPhiChange")
dPhiChange_barrel_hist_muonGun = f_muonGun.Get("Roo__Segment_barrel_dPhiChange")
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

dz_layer_hists_PU200 = []
dz_layer_hists_muonGun = []
dz_layer_hists_matched_muonGun = []

dz_barrel_layer_hists_PU200 = []
dz_barrel_layer_hists_muonGun = []
dz_barrel_layer_hists_matched_muonGun = []

drt_endcap_layer_hists_PU200 = []
drt_endcap_layer_hists_muonGun = []
drt_endcap_layer_hists_matched_muonGun = []

drt_endcap_ring_hists_PU200 = []
drt_endcap_ring_hists_muonGun = []
drt_endcap_rint_hists_matched_muonGun = []

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

for i in range(1,7):
    dz_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dz_layer_"+str(layer)))
    dz_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dz_layer_"+str(layer)))
    dz_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dz_layer_"+str(layer)))

    dz_barrel_layer_hists_PU200.append(f_PU200.Get("Root__Segment_barrel_dz_layer_"+str(layer)))
    dz_barrel_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_barrel_dz_layer_"+str(layer)))
    dz_barrel_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_barrel_dz_layer_"+str(layer)))

    dPhi_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dPhi_layer_"+str(layer)))
    dPhi_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dPhi_layer_"+str(layer)))
    dPhi_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dPhi_layer_"+str(layer)))

    dPhi_barrel_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dPhi_barrel_layer_"+str(layer)))
    dPhi_barrel_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dPhi_barrel_layer_"+str(layer)))
    dPhi_barrel_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dPhi_barrel_layer_"+str(layer)))

    dPhiChange_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dPhiChange_layer_"+str(layer)))
    dPhiChange_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dPhiChange_layer_"+str(layer)))
    dPhiChange_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dPhiChange_layer_"+str(layer)))

    dPhiChange_barrel_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dPhiChange_barrel_layer_"+str(layer)))
    dPhiChange_barrel_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dPhiChange_barrel_layer_"+str(layer)))
    dPhiChange_barrel_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dPhiChange_barrel_layer_"+str(layer)))

    dAlphaInnerMDSegment_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dAlphaInnerMDSegment_layer_"+str(layer)))
    dAlphaInnerMDSegment_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dAlphaInnerMDSegment_layer_"+str(layer)))
    dAlphaInnerMDSegment_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dAlphaInnerMDSegment_layer_"+str(layer)))

    dAlphaInnerMDSegment_barrel_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dAlphaInnerMDSegment_barrel_layer_"+str(layer)))
    dAlphaInnerMDSegment_barrel_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dAlphaInnerMDSegment_barrel_layer_"+str(layer)))
    dAlphaInnerMDSegment_barrel_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dAlphaInnerMDSegment_barrel_layer_"+str(layer)))

    dAlphaOuterMDSegment_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dAlphaOuterMDSegment_layer_"+str(layer)))
    dAlphaOuterMDSegment_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dAlphaOuterMDSegment_layer_"+str(layer)))
    dAlphaOuterMDSegment_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dAlphaOuterMDSegment_layer_"+str(layer)))

    dAlphaOuterMDSegment_barrel_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dAlphaOuterMDSegment_barrel_layer_"+str(layer)))
    dAlphaOuterMDSegment_barrel_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dAlphaOuterMDSegment_barrel_layer_"+str(layer)))
    dAlphaOuterMDSegment_barrel_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dAlphaOuterMDSegment_barrel_layer_"+str(layer)))

    dAlphaInnerMDOuterMD_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dAlphaInnerMDOuterMD_layer_"+str(layer)))
    dAlphaInnerMDOuterMD_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dAlphaInnerMDOuterMD_layer_"+str(layer)))
    dAlphaInnerMDOuterMD_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dAlphaInnerMDOuterMD_layer_"+str(layer)))

    dAlphaInnerMDOuterMD_barrel_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dAlphaInnerMDOuterMD_barrel_layer_"+str(layer)))
    dAlphaInnerMDOuterMD_barrel_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dAlphaInnerMDOuterMD_barrel_layer_"+str(layer)))
    dAlphaInnerMDOuterMD_barrel_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dAlphaInnerMDOuterMD_barrel_layer_"+str(layer)))

    if layer < 6:
        drt_endcap_layer_hists_PU200.append(f_PU200.Get("Root__Segment_endcap_dz_layer_"+str(layer)))
        drt_endcap_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_endcap_dz_layer_"+str(layer)))
        drt_endcap_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_endcap_dz_layer_"+str(layer)))

        dPhi_endcap_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dPhi_endcap_layer_"+str(layer)))
        dPhi_encap_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dPhi_endcap_layer_"+str(layer)))
        dPhi_encap_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dPhi_endcap_layer_"+str(layer)))

        dPhiChange_endcap_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dPhiChange_endcap_layer_"+str(layer)))
        dPhiChange_endcap_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dPhiChange_endcap_layer_"+str(layer)))
        dPhiChange_endcap_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dPhiChange_endcap_layer_"+str(layer)))

        dAlphaInnerMDSegment_endcap_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dAlphaInnerMDSegment_endcap_layer_"+str(layer)))
        dAlphaInnerMDSegment_endcap_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dAlphaInnerMDSegment_endcap_layer_"+str(layer)))
        dAlphaInnerMDSegment_endcap_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dAlphaInnerMDSegment_endcap_layer_"+str(layer)))

        dAlphaOuterMDSegment_endcap_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dAlphaOuterMDSegment_endcap_layer_"+str(layer)))
        dAlphaOuterMDSegment_endcap_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dAlphaOuterMDSegment_endcap_layer_"+str(layer)))
        dAlphaOuterMDSegment_endcap_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dAlphaOuterMdSegment_endcap_layer_"+str(layer)))

        dAlphaInnerMDOuterMD_endcap_layer_hists_PU200.append(f_PU200.Get("Root__Segment_dAlphaInnerMDOuterMD_endcap_layer_"+str(layer)))
        dAlphaInnerMDOuterMD_endcap_layer_hists_muonGun.append(f_muonGun.Get("Root__Segment_dAlphaInnerMDOuterMD_endcap_layer_"+str(layer)))
        dAlphaInnerMDOuterMD_endcap_layer_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dAlphaInnerMDOuterMD_endcap_layer_"+str(layer)))


for ring in range(1,16):
    drt_endcap_ring_hists_PU200.append(f_PU200.Get("Root__Segment_endcap_dz_ring_"+str(ring)))
    drt_endcap_ring_hists_muonGun.append(f_muonGun.Get("Root__Segment_endcap_dz_ring_"+str(ring)))
    drt_endcap_ring_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_endcap_dz_ring_"+str(ring)))

    dPhi_endcap_ring_hists_PU200.append(f_PU200.Get("Root__Segment_dPhi_endcap_ring_"+str(ring)))
    dPhi_encap_ring_hists_muonGun.append(f_muonGun.Get("Root__Segment_dPhi_endcap_ring_"+str(ring)))
    dPhi_encap_ring_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dPhi_endcap_ring_"+str(ring)))

    dPhiChange_endcap_ring_hists_PU200.append(f_PU200.Get("Root__Segment_dPhiChange_endcap_ring_"+str(ring)))
    dPhiChange_endcap_ring_hists_muonGun.append(f_muonGun.Get("Root__Segment_dPhiChange_endcap_ring_"+str(ring)))
    dPhiChange_endcap_ring_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dPhiChange_endcap_ring_"+str(ring)))

    dAlphaInnerMDSegment_endcap_ring_hists_PU200.append(f_PU200.Get("Root__Segment_dAlphaInnerMDSegment_endcap_ring_"+str(ring)))
    dAlphaInnerMDSegment_endcap_ring_hists_muonGun.append(f_muonGun.Get("Root__Segment_dAlphaInnerMDSegment_endcap_ring_"+str(ring)))
    dAlphaInnerMDSegment_endcap_ring_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dAlphaInnerMDSegment_endcap_ring_"+str(ring)))

    dAlphaOuterMDSegment_endcap_ring_hists_PU200.append(f_PU200.Get("Root__Segment_dAlphaOuterMDSegment_endcap_ring_"+str(ring)))
    dAlphaOuterMDSegment_endcap_ring_hists_muonGun.append(f_muonGun.Get("Root__Segment_dAlphaOuterMDSegment_endcap_ring_"+str(ring)))
    dAlphaOuterMDSegment_endcap_ring_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dAlphaOuterMdSegment_endcap_ring_"+str(ring)))

    dAlphaInnerMDOuterMD_endcap_ring_hists_PU200.append(f_PU200.Get("Root__Segment_dAlphaInnerMDOuterMD_endcap_ring_"+str(ring)))
    dAlphaInnerMDOuterMD_endcap_ring_hists_muonGun.append(f_muonGun.Get("Root__Segment_dAlphaInnerMDOuterMD_endcap_ring_"+str(ring)))
    dAlphaInnerMDOuterMD_endcap_ring_hists_matched_muonGun.append(f_muonGun.Get("Root__sim_matched_Segment_dAlphaInnerMDOuterMD_endcap_ring_"+str(ring)))


plot_md_params(dz_hist_PU200,dz_hist_matched_muonGun,dz_hist_muonGun,"Segment dz histogram")

plot_md_params(dz_barrel_hist_PU200,dz_barrel_hist_matched_muonGun,dz_barrel_hist_muonGun,"Segment dz histogram in barrel")
plot_md_params(drt_endcap_hist_PU200,drt_endcap_hist_matched_muonGun,drt_endcap_hist_muonGun,"Segment histogram in endcap")

plot_md_params(dPhi_hist_PU200,dPhi_hist_matched_muonGun,dPhi_hist_muonGun,"Segment dPhi histogram")
plot_md_params(dPhi_barrel_hist_PU200,dPhi_barrel_hist_matched_muonGun,dPhi_barrel_hist_muonGun,"Segment histogram in barrel")
plot_md_params(dPhi_endcap_hist_PU200,dPhi_endcap_hist_matched_muonGun,dPhi_barrel_hist_muonGun,"Segment dPhi histogram in endcap")

plot_md_params(dPhiChange_hist_PU200,dPhiChange_hist_matched_muonGun,dPhiChange_hist_muonGun,"Segment dPhiChange histogram")
plot_md_params(dPhiChange_barrel_hist_PU200,dPhiChange_barrel_hist_matched_muonGun,dPhiChange_barrel_hist_muonGun,"Segment dPhiChange histogram in barrel")
plot_md_params(dPhiChange_endcap_hist_PU200,dPhiChange_endcap_hist_matched_muonGun,dPhiChange_barrel_hist_muonGun,"Segment dPhiChange histogram in endcap")

plot_md_params(dAlphaInnerMDSegment_hist_PU200,dAlphaInnerMDSegment_hist_matched_muonGun,dAlphaInnerMDSegment_hist_muonGun,"Segment dAlphaInnerMDSegment histogram")
plot_md_params(dAlphaOuterMDSegment_hist_PU200,dAlphaOuterMDSegment_hist_matched_muonGun,dAlphaOuterMDSegment_hist_muonGun,"Segment dAlphaOuterMDSegment histogram")
plot_md_params(dAlphaInnerMDOuterMD_hist_PU200,dAlphaInnerMDOuterMD_hist_matched_muonGun,dAlphaInnerMDOuterMD_hist_muonGun,"Segment dAlphaInnerMDOuterMD histogram")



for layer in range(1,7):

    plot_md_params(dz_layer_hists_PU200[layer-1],dz_layer_hists_matched_muonGun[layer-1],dz_layer_hists_muonGun[layer-1],"Segment dz histogram for layer "+str(layer))

    plot_md_params(dz_barrel_layer_hists_PU200[layer-1],dz_barrel_layer_hists_matched_muonGun[layer-1],dz_barrel_layer_hists_muonGun[layer-1],"Segment dz histogram in barrel for layer "+str(layer))

    plot_md_params(dPhi_layer_hists_PU200[layer-1],dPhi_layer_hists_matched_muonGun[layer-1],dPhi_layer_hists_muonGun[layer-1],"Segment dPhi histogram for layer "+str(layer))

    plot_md_params(dPhi_barrel_layer_hists_PU200[layer-1],dPhi_barrel_layer_hists_matched_muonGun[layer-1],dPhi_barrel_layer_hists_muonGun[layer-1],"Segment dPhi histogram in barrel for layer "+str(layer))

    plot_md_params(dPhiChange_layer_hists_PU200[layer-1],dPhiChange_layer_hists_matched_muonGun[layer-1],dPhiChange_layer_hists_muonGun[layer-1],"Segment dPhiChange histogram for layer "+str(layer))

    plot_md_params(dPhiChange_barrel_layer_hists_PU200[layer-1],dPhiChange_barrel_layer_hists_matched_muonGun[layer-1],dPhiChange_barrel_layer_hists_muonGun[layer-1],"Segment dPhiChange histogram in barrel for layer "+str(layer))

    plot_md_params(dAlphaInnerMDSegment_layer_hists_PU200[layer-1],dAlphaInnerMDSegment_layer_hists_matched_muonGun[layer-1],dAlphaInnerMDSegment_layer_hists_muonGun[layer-1],"Segment dAlphaInnerMDSegment histogram for layer "+str(layer))

    plot_md_params(dAlphaInnerMDSegment_barrel_layer_hists_PU200[layer-1],dAlphaInnerMDSegment_barrel_layer_hists_matched_muonGun[layer-1],dAlphaInnerMDSegment_barrel_layer_hists_muonGun[layer-1],"Segment dAlphaInnerMDSegment histogram in barrel for layer "+str(layer))

    plot_md_params(dAlphaOuterMDSegment_layer_hists_PU200[layer-1],dPhiChange_layer_hists_matched_muonGun[layer-1],dPhiChange_layer_hists_muonGun[layer-1],"Segment dAlphaOuterMDSegment histogram for layer "+str(layer))

    plot_md_params(dAlphaOuterMDSegment_barrel_layer_hists_PU200[layer-1],dAlphaOuterMDSegment_barrel_layer_hists_matched_muonGun[layer-1],dAlphaOuterMDSegment_barrel_layer_hists_muonGun[layer-1],"Segment dAlphaOuterMDSegment histogram in barrel for layer "+str(layer))

    plot_md_params(dAlphaInnerMDOuterMD_layer_hists_PU200[layer-1],dAlphaInnerMDOuterMD_layer_hists_matched_muonGun[layer-1],dAlphaInnerMDOuterMD_layer_hists_muonGun[layer-1],"Segment dAlphaInnerMDOuterMD histogram for layer "+str(layer))

    plot_md_params(dAlphaInnerMDOuterMD_barrel_layer_hists_PU200[layer-1],dAlphaInnerMDOuterMD_barrel_layer_hists_matched_muonGun[layer-1],dAlphaInnerMDOuterMD_barrel_layer_hists_muonGun[layer-1],"Segment dAlphaInnerMDOuterMD histogram for layer "+str(layer))


    if layer < 6:
        plot_md_params(drt_endcap_layer_hists_PU200[layer-1],drt_endcap_layer_hists_matched_muonGun[layer-1],drt_endcap_layer_hists_muonGun[layer-1],"Segment drt histogram in endcap for layer "+str(layer))

        plot_md_params(dPhi_endcap_layer_hists_PU200[layer-1],dPhi_endcap_layer_hists_matched_muonGun[layer-1],dPhi_endcap_layer_hists_muonGun[layer-1],"Segment dPhi histogram in endcap for layer "+str(layer))

        plot_md_params(dPhiChange_endcap_layer_hists_PU200[layer-1],dPhiChange_endcap_layer_hists_matched_muonGun[layer-1],dPhiChange_endcap_layer_hists_muonGun[layer-1],"Segment dPhiChange histogram in endcap for layer "+str(layer))

        plot_md_params(dAlphaInnerMDSegment_endcap_layer_hists_PU200[layer-1],dAlphaInnerMDSegment_endcap_layer_hists_matched_muonGun[layer-1],dAlphaInnerMDSegment_endcap_layer_hists_muonGun[layer-1],"Segment dAlphaInnerMDSegment histogram in endcap for layer "+str(layer))

        plot_md_params(dAlphaOuterMDSegment_endcap_layer_hists_PU200[layer-1],dAlphaOuterMDSegment_endcap_layer_hists_matched_muonGun[layer-1],dAlphaOuterMDSegment_endcap_layer_hists_muonGun[layer-1],"Segment dAlphaOuterMDSegment histogram in endcap for layer "+str(layer))

        plot_md_params(dAlphaInnerMDOuterMD_endcap_layer_hists_PU200[layer-1],dAlphaInnerMDOuterMD_endcap_layer_hists_matched_muonGun[layer-1],dAlphaInnerMDOuterMD_endcap_layer_hists_muonGun[layer-1],"Segment dAlphaInnerMDOuterMD histogram in endcap for layer "+str(layer))



for ring in range(1,16):

    plot_md_params(drt_endcap_ring_hists_PU200[ring-1],drt_endcap_ring_hists_matched_muonGun[ring-1],drt_endcap_ring_hists_muonGun[ring-1],"Mini-doublet drt histogram in endcap for ring "+str(ring))

    plot_md_params(dPhi_endcap_ring_hists_PU200[ring-1],dPhi_endcap_ring_hists_matched_muonGun[ring-1],dPhi_endcap_ring_hists_muonGun[ring-1],"Segment dPhi histogram in endcap for ring "+str(ring))

    plot_md_params(dPhiChange_endcap_ring_hists_PU200[ring-1],dPhiChange_endcap_ring_hists_matched_muonGun[ring-1],dPhiChange_endcap_ring_hists_muonGun[ring-1],"Segment dPhiChange histogram in endcap for ring "+str(ring))

    plot_md_params(dAlphaInnerMDSegment_endcap_ring_hists_PU200[ring-1],dAlphaInnerMDSegment_endcap_ring_hists_matched_muonGun[ring-1],dAlphaInnerMDSegment_endcap_ring_hists_muonGun[ring-1],"Segment dAlphaInnerMDSegment histogram in endcap for ring "+str(ring))

    plot_md_params(dAlphaOuterMDSegment_endcap_ring_hists_PU200[ring-1],dAlphaOuterMDSegment_endcap_ring_hists_matched_muonGun[ring-1],dAlphaOuterMDSegment_endcap_ring_hists_muonGun[ring-1],"Segment dAlphaOuterMDSegment histogram in endcap for ring "+str(ring))

    plot_md_params(dAlphaInnerMDOuterMD_endcap_ring_hists_PU200[ring-1],dAlphaInnerMDOuterMD_endcap_ring_hists_matched_muonGun[ring-1],dAlphaInnerMDOuterMD_endcap_ring_hists_muonGun[ring-1],"Segment dAlphaInnerMDOuterMD histogram in endcap for ring "+str(ring))


