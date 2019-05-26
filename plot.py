#!/bin/env python

import plottery_wrapper as p
from plottery import plottery as plt
import ROOT as r

p.dump_plot(fnames=["debug.root"],
    dirname="plots/lin",
    extraoptions={},
    )

p.dump_plot(fnames=["debug.root"],
    dirname="plots/log",
    extraoptions={"yaxis_log":True, "legend_smart":False, "print_yield":True},
    )

def plot_eff(num_name, den_name, output_name):
    f = r.TFile("debug.root")
    num = f.Get(num_name)
    den = f.Get(den_name)
    #num.Divide(num, den, 1, 1, "B")
    teff = r.TEfficiency(num, den)
    eff = teff.CreateGraph()
    #eff.Print("all")
    c1 = r.TCanvas()
    c1.SetBottomMargin(0.15)
    c1.SetLeftMargin(0.15)
    c1.SetTopMargin(0.15)
    c1.SetRightMargin(0.15)
    if "_pt" in output_name:
        c1.SetLogx()
    eff.Draw("epa")
    eff.SetMarkerStyle(19)
    eff.SetMarkerSize(1.2)
    eff.SetLineWidth(2)
    eff.GetXaxis().SetTitle("#eta" if "_eta" in output_name else "p_{T} [GeV]")
    eff.GetXaxis().SetTitleSize(0.05)
    eff.GetXaxis().SetLabelSize(0.05)
    eff.GetYaxis().SetLabelSize(0.05)
    if "_eta" in output_name:
        eff.GetYaxis().SetRangeUser(0.0, 1.05)
    c1.SaveAs("plots/lin/{}".format(output_name))
    c1.SaveAs("plots/lin/{}".format(output_name.replace("pdf", "png")))
    #p.plot_hist(
    #        bgs=[eff.Clone()],
    #        data=eff.Clone(),
    #        options=
    #            {
    #                "output_name":"plots/lin/{}".format(output_name),
    #                # "remove_underflow":True,
    #                # "remove_overflow":True,
    #                "yaxis_range": [0.95, 1.05] if "eta" in output_name else [],
    #                #"yaxis_range": [0.95, 1.05],
    #                "no_ratio":True,
    #                "draw_points":True,
    #                "do_stack":False,
    #                "print_yield":True,
    #                "yield_prec":4,
    #                "xaxis_log":False if "eta" in output_name else True,
    #                "hist_disable_xerrors": True if "eta" in output_name else False,
    #                "hist_black_line": True,
    #                "show_bkg_errors": True,
    #                "hist_line_black": True,
    #            },
    #        colors=[1],
    #        )

plot_eff("Root__md_all_matched_track_pt", "Root__md_all_all_track_pt", "eff_all_pt.pdf")
plot_eff("Root__md_all_matched_track_eta", "Root__md_all_all_track_eta", "eff_all_eta.pdf")
for i in xrange(6):
    plot_eff("Root__md_all_matched_track_pt_by_layer{}".format(i), "Root__md_all_all_track_pt_by_layer{}".format(i), "eff_all_pt_by_layer{}.pdf".format(i))
    plot_eff("Root__md_all_matched_track_eta_by_layer{}".format(i), "Root__md_all_all_track_eta_by_layer{}".format(i), "eff_all_eta_by_layer{}.pdf".format(i))

plot_eff("Root__md_barrel_matched_track_pt", "Root__md_barrel_all_track_pt", "eff_barrel_pt.pdf")
plot_eff("Root__md_barrel_matched_track_eta", "Root__md_barrel_all_track_eta", "eff_barrel_eta.pdf")
for i in xrange(6):
    plot_eff("Root__md_barrel_matched_track_pt_by_layer{}".format(i), "Root__md_barrel_all_track_pt_by_layer{}".format(i), "eff_barrel_pt_by_layer{}.pdf".format(i))
    plot_eff("Root__md_barrel_matched_track_eta_by_layer{}".format(i), "Root__md_barrel_all_track_eta_by_layer{}".format(i), "eff_barrel_eta_by_layer{}.pdf".format(i))

plot_eff("Root__md_barrelflat_matched_track_pt", "Root__md_barrelflat_all_track_pt", "eff_barrelflat_pt.pdf")
plot_eff("Root__md_barrelflat_matched_track_eta", "Root__md_barrelflat_all_track_eta", "eff_barrelflat_eta.pdf")
for i in xrange(6):
    plot_eff("Root__md_barrelflat_matched_track_pt_by_layer{}".format(i), "Root__md_barrelflat_all_track_pt_by_layer{}".format(i), "eff_barrelflat_pt_by_layer{}.pdf".format(i))
    plot_eff("Root__md_barrelflat_matched_track_eta_by_layer{}".format(i), "Root__md_barrelflat_all_track_eta_by_layer{}".format(i), "eff_barrelflat_eta_by_layer{}.pdf".format(i))

plot_eff("Root__md_barreltilt_matched_track_pt", "Root__md_barreltilt_all_track_pt", "eff_barreltilt_pt.pdf")
plot_eff("Root__md_barreltilt_matched_track_eta", "Root__md_barreltilt_all_track_eta", "eff_barreltilt_eta.pdf")
for i in xrange(6):
    plot_eff("Root__md_barreltilt_matched_track_pt_by_layer{}".format(i), "Root__md_barreltilt_all_track_pt_by_layer{}".format(i), "eff_barreltilt_pt_by_layer{}.pdf".format(i))
    plot_eff("Root__md_barreltilt_matched_track_eta_by_layer{}".format(i), "Root__md_barreltilt_all_track_eta_by_layer{}".format(i), "eff_barreltilt_eta_by_layer{}.pdf".format(i))

plot_eff("Root__md_endcapPS_matched_track_pt", "Root__md_endcapPS_all_track_pt", "eff_endcapPS_pt.pdf")
plot_eff("Root__md_endcapPS_matched_track_eta", "Root__md_endcapPS_all_track_eta", "eff_endcapPS_eta.pdf")
for i in xrange(5):
    plot_eff("Root__md_endcapPS_matched_track_pt_by_layer{}".format(i), "Root__md_endcapPS_all_track_pt_by_layer{}".format(i), "eff_endcapPS_pt_by_layer{}.pdf".format(i))
    plot_eff("Root__md_endcapPS_matched_track_eta_by_layer{}".format(i), "Root__md_endcapPS_all_track_eta_by_layer{}".format(i), "eff_endcapPS_eta_by_layer{}.pdf".format(i))

plot_eff("Root__md_endcap2S_matched_track_pt", "Root__md_endcap2S_all_track_pt", "eff_endcap2S_pt.pdf")
plot_eff("Root__md_endcap2S_matched_track_eta", "Root__md_endcap2S_all_track_eta", "eff_endcap2S_eta.pdf")
for i in xrange(5):
    plot_eff("Root__md_endcap2S_matched_track_pt_by_layer{}".format(i), "Root__md_endcap2S_all_track_pt_by_layer{}".format(i), "eff_endcap2S_pt_by_layer{}.pdf".format(i))
    plot_eff("Root__md_endcap2S_matched_track_eta_by_layer{}".format(i), "Root__md_endcap2S_all_track_eta_by_layer{}".format(i), "eff_endcap2S_eta_by_layer{}.pdf".format(i))

plot_eff("Root__md_endcap_matched_track_pt", "Root__md_endcap_all_track_pt", "eff_endcap_pt.pdf")
plot_eff("Root__md_endcap_matched_track_eta", "Root__md_endcap_all_track_eta", "eff_endcap_eta.pdf")
for i in xrange(5):
    plot_eff("Root__md_endcap_matched_track_pt_by_layer{}".format(i), "Root__md_endcap_all_track_pt_by_layer{}".format(i), "eff_endcap_pt_by_layer{}.pdf".format(i))
    plot_eff("Root__md_endcap_matched_track_eta_by_layer{}".format(i), "Root__md_endcap_all_track_eta_by_layer{}".format(i), "eff_endcap_eta_by_layer{}.pdf".format(i))

plot_eff("Root__md_endcapPSCloseRing_matched_track_pt", "Root__md_endcapPSCloseRing_all_track_pt", "eff_endcapPSCloseRing_pt.pdf")
plot_eff("Root__md_endcapPSCloseRing_matched_track_eta", "Root__md_endcapPSCloseRing_all_track_eta", "eff_endcapPSCloseRing_eta.pdf")
for i in xrange(5):
    plot_eff("Root__md_endcapPSCloseRing_matched_track_pt_by_layer{}".format(i), "Root__md_endcapPSCloseRing_all_track_pt_by_layer{}".format(i), "eff_endcapPSCloseRing_pt_by_layer{}.pdf".format(i))
    plot_eff("Root__md_endcapPSCloseRing_matched_track_eta_by_layer{}".format(i), "Root__md_endcapPSCloseRing_all_track_eta_by_layer{}".format(i), "eff_endcapPSCloseRing_eta_by_layer{}.pdf".format(i))

plot_eff("Root__md_endcapPSLowPt_matched_track_pt", "Root__md_endcapPSLowPt_all_track_pt", "eff_endcapPSLowPt_pt.pdf")
plot_eff("Root__md_endcapPSLowPt_matched_track_eta", "Root__md_endcapPSLowPt_all_track_eta", "eff_endcapPSLowPt_eta.pdf")
for i in xrange(5):
    plot_eff("Root__md_endcapPSLowPt_matched_track_pt_by_layer{}".format(i), "Root__md_endcapPSLowPt_all_track_pt_by_layer{}".format(i), "eff_endcapPSLowPt_pt_by_layer{}.pdf".format(i))
    plot_eff("Root__md_endcapPSLowPt_matched_track_eta_by_layer{}".format(i), "Root__md_endcapPSLowPt_all_track_eta_by_layer{}".format(i), "eff_endcapPSLowPt_eta_by_layer{}.pdf".format(i))

