#!/bin/env python

import plottery_wrapper as p
from plottery import plottery as plt
import ROOT as r

import sys

filename = "debug.root"
if len(sys.argv) > 1:
    filename = sys.argv[1]

p.dump_plot(fnames=["debug.root"],
    dirname="plots/log",
    dogrep=True,
    filter_pattern="deltaBeta",
    extraoptions={"yaxis_log":True, "legend_smart":False, "print_yield":True},
    )

# p.dump_plot(fnames=["debug.root"],
#     dirname="plots/log",
#     extraoptions={"yaxis_log":True, "legend_smart":False, "print_yield":True},
#     )

def plot_eff(num_name, den_name, output_name):
    f = r.TFile(filename)
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
    if "_eta" in output_name:
        title = "#eta"
    elif "phi" in output_name:
        title = "#phi"
    elif "_z" in output_name:
        title = "z [cm]"
    else:
        title = "p_{T} [GeV]"
    eff.GetXaxis().SetTitle(title)
    eff.GetXaxis().SetTitleSize(0.05)
    eff.GetXaxis().SetLabelSize(0.05)
    eff.GetYaxis().SetLabelSize(0.05)
    if "_eta" in output_name and "sg_" not in output_name:
        eff.GetYaxis().SetRangeUser(0.995, 1.005)
    if "_z" in output_name and "sg_" not in output_name:
        eff.GetYaxis().SetRangeUser(0.98, 1.02)
    if "barrelflat_eta" in output_name:
        eff.GetYaxis().SetRangeUser(0.97, 1.03)
    if "_eta" in output_name and "sg_" in output_name:
        eff.GetYaxis().SetRangeUser(0.995, 1.005)
    if "_z" in output_name and "sg_" in output_name:
        eff.GetYaxis().SetRangeUser(0.98, 1.02)
    if "_ptzoom" in output_name and "sg_" in output_name:
        eff.GetYaxis().SetRangeUser(0.999, 1.001)
    if "_ptzoom" in output_name and "md_" in output_name:
        eff.GetYaxis().SetRangeUser(0.999, 1.001)
    if "_ptzoom" in output_name and "tl_" in output_name:
        eff.GetYaxis().SetRangeUser(0.985, 1.015)
    if "_eta" in output_name and "tl_" in output_name:
        eff.GetYaxis().SetRangeUser(0.0, 2.0)
    # if "_pt" in output_name:
    #     eff.GetXaxis().SetRangeUser(0.8, 1.2)
    # if "endcap2S_pt" in output_name:
    #     eff.GetYaxis().SetRangeUser(0.90, 1.03)
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

drawMDplots = False
drawSGplots = False
drawTLplots = True

if drawMDplots:

    plot_eff("Root__md_all_matched_track_pt", "Root__md_all_all_track_pt", "md_eff_all_pt.pdf")
    plot_eff("Root__md_all_matched_track_pt", "Root__md_all_all_track_pt", "md_eff_all_ptzoom.pdf")
    plot_eff("Root__md_all_matched_track_eta", "Root__md_all_all_track_eta", "md_eff_all_eta.pdf")
    plot_eff("Root__md_all_matched_track_phi", "Root__md_all_all_track_phi", "md_eff_all_phi.pdf")
    plot_eff("Root__md_all_matched_track_z", "Root__md_all_all_track_z", "md_eff_all_z.pdf")
    for i in xrange(6):
        plot_eff("Root__md_all_matched_track_pt_by_layer{}".format(i), "Root__md_all_all_track_pt_by_layer{}".format(i), "md_eff_all_pt_by_layer{}.pdf".format(i))
        plot_eff("Root__md_all_matched_track_pt_by_layer{}".format(i), "Root__md_all_all_track_pt_by_layer{}".format(i), "md_eff_all_ptzoom_by_layer{}.pdf".format(i))
        plot_eff("Root__md_all_matched_track_eta_by_layer{}".format(i), "Root__md_all_all_track_eta_by_layer{}".format(i), "md_eff_all_eta_by_layer{}.pdf".format(i))
        plot_eff("Root__md_all_matched_track_phi_by_layer{}".format(i), "Root__md_all_all_track_phi_by_layer{}".format(i), "md_eff_all_phi_by_layer{}.pdf".format(i))
        plot_eff("Root__md_all_matched_track_z_by_layer{}".format(i), "Root__md_all_all_track_z_by_layer{}".format(i), "md_eff_all_z_by_layer{}.pdf".format(i))
        plot_eff("Root__md_all_matched_track_wrapphi_by_layer{}".format(i), "Root__md_all_all_track_wrapphi_by_layer{}".format(i), "md_eff_all_wrapphi_by_layer{}.pdf".format(i))

    plot_eff("Root__md_barrel_matched_track_pt", "Root__md_barrel_all_track_pt", "md_eff_barrel_pt.pdf")
    plot_eff("Root__md_barrel_matched_track_pt", "Root__md_barrel_all_track_pt", "md_eff_barrel_ptzoom.pdf")
    plot_eff("Root__md_barrel_matched_track_eta", "Root__md_barrel_all_track_eta", "md_eff_barrel_eta.pdf")
    plot_eff("Root__md_barrel_matched_track_phi", "Root__md_barrel_all_track_phi", "md_eff_barrel_phi.pdf")
    plot_eff("Root__md_barrel_matched_track_z", "Root__md_barrel_all_track_z", "md_eff_barrel_z.pdf")
    for i in xrange(6):
        plot_eff("Root__md_barrel_matched_track_pt_by_layer{}".format(i), "Root__md_barrel_all_track_pt_by_layer{}".format(i), "md_eff_barrel_pt_by_layer{}.pdf".format(i))
        plot_eff("Root__md_barrel_matched_track_pt_by_layer{}".format(i), "Root__md_barrel_all_track_pt_by_layer{}".format(i), "md_eff_barrel_ptzoom_by_layer{}.pdf".format(i))
        plot_eff("Root__md_barrel_matched_track_eta_by_layer{}".format(i), "Root__md_barrel_all_track_eta_by_layer{}".format(i), "md_eff_barrel_eta_by_layer{}.pdf".format(i))
        plot_eff("Root__md_barrel_matched_track_phi_by_layer{}".format(i), "Root__md_barrel_all_track_phi_by_layer{}".format(i), "md_eff_barrel_phi_by_layer{}.pdf".format(i))
        plot_eff("Root__md_barrel_matched_track_z_by_layer{}".format(i), "Root__md_barrel_all_track_z_by_layer{}".format(i), "md_eff_barrel_z_by_layer{}.pdf".format(i))
        plot_eff("Root__md_barrel_matched_track_wrapphi_by_layer{}".format(i), "Root__md_barrel_all_track_wrapphi_by_layer{}".format(i), "md_eff_barrel_wrapphi_by_layer{}.pdf".format(i))

    plot_eff("Root__md_barrelflat_matched_track_pt", "Root__md_barrelflat_all_track_pt", "md_eff_barrelflat_pt.pdf")
    plot_eff("Root__md_barrelflat_matched_track_pt", "Root__md_barrelflat_all_track_pt", "md_eff_barrelflat_ptzoom.pdf")
    plot_eff("Root__md_barrelflat_matched_track_eta", "Root__md_barrelflat_all_track_eta", "md_eff_barrelflat_eta.pdf")
    plot_eff("Root__md_barrelflat_matched_track_phi", "Root__md_barrelflat_all_track_phi", "md_eff_barrelflat_phi.pdf")
    plot_eff("Root__md_barrelflat_matched_track_z", "Root__md_barrelflat_all_track_z", "md_eff_barrelflat_z.pdf")
    for i in xrange(6):
        plot_eff("Root__md_barrelflat_matched_track_pt_by_layer{}".format(i), "Root__md_barrelflat_all_track_pt_by_layer{}".format(i), "md_eff_barrelflat_pt_by_layer{}.pdf".format(i))
        plot_eff("Root__md_barrelflat_matched_track_pt_by_layer{}".format(i), "Root__md_barrelflat_all_track_pt_by_layer{}".format(i), "md_eff_barrelflat_ptzoom_by_layer{}.pdf".format(i))
        plot_eff("Root__md_barrelflat_matched_track_eta_by_layer{}".format(i), "Root__md_barrelflat_all_track_eta_by_layer{}".format(i), "md_eff_barrelflat_eta_by_layer{}.pdf".format(i))
        plot_eff("Root__md_barrelflat_matched_track_phi_by_layer{}".format(i), "Root__md_barrelflat_all_track_phi_by_layer{}".format(i), "md_eff_barrelflat_phi_by_layer{}.pdf".format(i))
        plot_eff("Root__md_barrelflat_matched_track_z_by_layer{}".format(i), "Root__md_barrelflat_all_track_z_by_layer{}".format(i), "md_eff_barrelflat_z_by_layer{}.pdf".format(i))
        plot_eff("Root__md_barrelflat_matched_track_wrapphi_by_layer{}".format(i), "Root__md_barrelflat_all_track_wrapphi_by_layer{}".format(i), "md_eff_barrelflat_wrapphi_by_layer{}.pdf".format(i))

    plot_eff("Root__md_barreltilt_matched_track_pt", "Root__md_barreltilt_all_track_pt", "md_eff_barreltilt_pt.pdf")
    plot_eff("Root__md_barreltilt_matched_track_pt", "Root__md_barreltilt_all_track_pt", "md_eff_barreltilt_ptzoom.pdf")
    plot_eff("Root__md_barreltilt_matched_track_eta", "Root__md_barreltilt_all_track_eta", "md_eff_barreltilt_eta.pdf")
    plot_eff("Root__md_barreltilt_matched_track_phi", "Root__md_barreltilt_all_track_phi", "md_eff_barreltilt_phi.pdf")
    plot_eff("Root__md_barreltilt_matched_track_z", "Root__md_barreltilt_all_track_z", "md_eff_barreltilt_z.pdf")
    for i in xrange(3):
        plot_eff("Root__md_barreltilt_matched_track_pt_by_layer{}".format(i), "Root__md_barreltilt_all_track_pt_by_layer{}".format(i), "md_eff_barreltilt_pt_by_layer{}.pdf".format(i))
        plot_eff("Root__md_barreltilt_matched_track_pt_by_layer{}".format(i), "Root__md_barreltilt_all_track_pt_by_layer{}".format(i), "md_eff_barreltilt_ptzoom_by_layer{}.pdf".format(i))
        plot_eff("Root__md_barreltilt_matched_track_eta_by_layer{}".format(i), "Root__md_barreltilt_all_track_eta_by_layer{}".format(i), "md_eff_barreltilt_eta_by_layer{}.pdf".format(i))
        plot_eff("Root__md_barreltilt_matched_track_phi_by_layer{}".format(i), "Root__md_barreltilt_all_track_phi_by_layer{}".format(i), "md_eff_barreltilt_phi_by_layer{}.pdf".format(i))
        plot_eff("Root__md_barreltilt_matched_track_z_by_layer{}".format(i), "Root__md_barreltilt_all_track_z_by_layer{}".format(i), "md_eff_barreltilt_z_by_layer{}.pdf".format(i))
        plot_eff("Root__md_barreltilt_matched_track_wrapphi_by_layer{}".format(i), "Root__md_barreltilt_all_track_wrapphi_by_layer{}".format(i), "md_eff_barreltilt_wrapphi_by_layer{}.pdf".format(i))

    plot_eff("Root__md_barreltilthighz_matched_track_pt", "Root__md_barreltilthighz_all_track_pt", "md_eff_barreltilthighz_pt.pdf")
    plot_eff("Root__md_barreltilthighz_matched_track_pt", "Root__md_barreltilthighz_all_track_pt", "md_eff_barreltilthighz_ptzoom.pdf")
    plot_eff("Root__md_barreltilthighz_matched_track_eta", "Root__md_barreltilthighz_all_track_eta", "md_eff_barreltilthighz_eta.pdf")
    plot_eff("Root__md_barreltilthighz_matched_track_phi", "Root__md_barreltilthighz_all_track_phi", "md_eff_barreltilthighz_phi.pdf")
    plot_eff("Root__md_barreltilthighz_matched_track_z", "Root__md_barreltilthighz_all_track_z", "md_eff_barreltilthighz_z.pdf")
    for i in xrange(3):
        plot_eff("Root__md_barreltilthighz_matched_track_pt_by_layer{}".format(i), "Root__md_barreltilthighz_all_track_pt_by_layer{}".format(i), "md_eff_barreltilthighz_pt_by_layer{}.pdf".format(i))
        plot_eff("Root__md_barreltilthighz_matched_track_pt_by_layer{}".format(i), "Root__md_barreltilthighz_all_track_pt_by_layer{}".format(i), "md_eff_barreltilthighz_ptzoom_by_layer{}.pdf".format(i))
        plot_eff("Root__md_barreltilthighz_matched_track_eta_by_layer{}".format(i), "Root__md_barreltilthighz_all_track_eta_by_layer{}".format(i), "md_eff_barreltilthighz_eta_by_layer{}.pdf".format(i))
        plot_eff("Root__md_barreltilthighz_matched_track_phi_by_layer{}".format(i), "Root__md_barreltilthighz_all_track_phi_by_layer{}".format(i), "md_eff_barreltilthighz_phi_by_layer{}.pdf".format(i))
        plot_eff("Root__md_barreltilthighz_matched_track_z_by_layer{}".format(i), "Root__md_barreltilthighz_all_track_z_by_layer{}".format(i), "md_eff_barreltilthighz_z_by_layer{}.pdf".format(i))
        plot_eff("Root__md_barreltilthighz_matched_track_wrapphi_by_layer{}".format(i), "Root__md_barreltilthighz_all_track_wrapphi_by_layer{}".format(i), "md_eff_barreltilthighz_wrapphi_by_layer{}.pdf".format(i))

    plot_eff("Root__md_endcapPS_matched_track_pt", "Root__md_endcapPS_all_track_pt", "md_eff_endcapPS_pt.pdf")
    plot_eff("Root__md_endcapPS_matched_track_pt", "Root__md_endcapPS_all_track_pt", "md_eff_endcapPS_ptzoom.pdf")
    plot_eff("Root__md_endcapPS_matched_track_eta", "Root__md_endcapPS_all_track_eta", "md_eff_endcapPS_eta.pdf")
    plot_eff("Root__md_endcapPS_matched_track_phi", "Root__md_endcapPS_all_track_phi", "md_eff_endcapPS_phi.pdf")
    plot_eff("Root__md_endcapPS_matched_track_z", "Root__md_endcapPS_all_track_z", "md_eff_endcapPS_z.pdf")
    for i in xrange(5):
        plot_eff("Root__md_endcapPS_matched_track_pt_by_layer{}".format(i), "Root__md_endcapPS_all_track_pt_by_layer{}".format(i), "md_eff_endcapPS_pt_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcapPS_matched_track_pt_by_layer{}".format(i), "Root__md_endcapPS_all_track_pt_by_layer{}".format(i), "md_eff_endcapPS_ptzoom_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcapPS_matched_track_eta_by_layer{}".format(i), "Root__md_endcapPS_all_track_eta_by_layer{}".format(i), "md_eff_endcapPS_eta_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcapPS_matched_track_phi_by_layer{}".format(i), "Root__md_endcapPS_all_track_phi_by_layer{}".format(i), "md_eff_endcapPS_phi_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcapPS_matched_track_z_by_layer{}".format(i), "Root__md_endcapPS_all_track_z_by_layer{}".format(i), "md_eff_endcapPS_z_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcapPS_matched_track_wrapphi_by_layer{}".format(i), "Root__md_endcapPS_all_track_wrapphi_by_layer{}".format(i), "md_eff_endcapPS_wrapphi_by_layer{}.pdf".format(i))

    plot_eff("Root__md_endcap2S_matched_track_pt", "Root__md_endcap2S_all_track_pt", "md_eff_endcap2S_pt.pdf")
    plot_eff("Root__md_endcap2S_matched_track_pt", "Root__md_endcap2S_all_track_pt", "md_eff_endcap2S_ptzoom.pdf")
    plot_eff("Root__md_endcap2S_matched_track_eta", "Root__md_endcap2S_all_track_eta", "md_eff_endcap2S_eta.pdf")
    plot_eff("Root__md_endcap2S_matched_track_phi", "Root__md_endcap2S_all_track_phi", "md_eff_endcap2S_phi.pdf")
    plot_eff("Root__md_endcap2S_matched_track_z", "Root__md_endcap2S_all_track_z", "md_eff_endcap2S_z.pdf")
    for i in xrange(5):
        plot_eff("Root__md_endcap2S_matched_track_pt_by_layer{}".format(i), "Root__md_endcap2S_all_track_pt_by_layer{}".format(i), "md_eff_endcap2S_pt_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcap2S_matched_track_pt_by_layer{}".format(i), "Root__md_endcap2S_all_track_pt_by_layer{}".format(i), "md_eff_endcap2S_ptzoom_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcap2S_matched_track_eta_by_layer{}".format(i), "Root__md_endcap2S_all_track_eta_by_layer{}".format(i), "md_eff_endcap2S_eta_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcap2S_matched_track_phi_by_layer{}".format(i), "Root__md_endcap2S_all_track_phi_by_layer{}".format(i), "md_eff_endcap2S_phi_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcap2S_matched_track_z_by_layer{}".format(i), "Root__md_endcap2S_all_track_z_by_layer{}".format(i), "md_eff_endcap2S_z_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcap2S_matched_track_wrapphi_by_layer{}".format(i), "Root__md_endcap2S_all_track_wrapphi_by_layer{}".format(i), "md_eff_endcap2S_wrapphi_by_layer{}.pdf".format(i))

    plot_eff("Root__md_endcap_matched_track_pt", "Root__md_endcap_all_track_pt", "md_eff_endcap_pt.pdf")
    plot_eff("Root__md_endcap_matched_track_pt", "Root__md_endcap_all_track_pt", "md_eff_endcap_ptzoom.pdf")
    plot_eff("Root__md_endcap_matched_track_eta", "Root__md_endcap_all_track_eta", "md_eff_endcap_eta.pdf")
    plot_eff("Root__md_endcap_matched_track_phi", "Root__md_endcap_all_track_phi", "md_eff_endcap_phi.pdf")
    plot_eff("Root__md_endcap_matched_track_z", "Root__md_endcap_all_track_z", "md_eff_endcap_z.pdf")
    for i in xrange(5):
        plot_eff("Root__md_endcap_matched_track_pt_by_layer{}".format(i), "Root__md_endcap_all_track_pt_by_layer{}".format(i), "md_eff_endcap_pt_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcap_matched_track_pt_by_layer{}".format(i), "Root__md_endcap_all_track_pt_by_layer{}".format(i), "md_eff_endcap_ptzoom_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcap_matched_track_eta_by_layer{}".format(i), "Root__md_endcap_all_track_eta_by_layer{}".format(i), "md_eff_endcap_eta_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcap_matched_track_phi_by_layer{}".format(i), "Root__md_endcap_all_track_phi_by_layer{}".format(i), "md_eff_endcap_phi_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcap_matched_track_z_by_layer{}".format(i), "Root__md_endcap_all_track_z_by_layer{}".format(i), "md_eff_endcap_z_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcap_matched_track_wrapphi_by_layer{}".format(i), "Root__md_endcap_all_track_wrapphi_by_layer{}".format(i), "md_eff_endcap_wrapphi_by_layer{}.pdf".format(i))

    plot_eff("Root__md_endcapPSCloseRing_matched_track_pt", "Root__md_endcapPSCloseRing_all_track_pt", "md_eff_endcapPSCloseRing_pt.pdf")
    plot_eff("Root__md_endcapPSCloseRing_matched_track_pt", "Root__md_endcapPSCloseRing_all_track_pt", "md_eff_endcapPSCloseRing_ptzoom.pdf")
    plot_eff("Root__md_endcapPSCloseRing_matched_track_eta", "Root__md_endcapPSCloseRing_all_track_eta", "md_eff_endcapPSCloseRing_eta.pdf")
    plot_eff("Root__md_endcapPSCloseRing_matched_track_phi", "Root__md_endcapPSCloseRing_all_track_phi", "md_eff_endcapPSCloseRing_phi.pdf")
    plot_eff("Root__md_endcapPSCloseRing_matched_track_z", "Root__md_endcapPSCloseRing_all_track_z", "md_eff_endcapPSCloseRing_z.pdf")
    for i in xrange(5):
        plot_eff("Root__md_endcapPSCloseRing_matched_track_pt_by_layer{}".format(i), "Root__md_endcapPSCloseRing_all_track_pt_by_layer{}".format(i), "md_eff_endcapPSCloseRing_pt_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcapPSCloseRing_matched_track_pt_by_layer{}".format(i), "Root__md_endcapPSCloseRing_all_track_pt_by_layer{}".format(i), "md_eff_endcapPSCloseRing_ptzoom_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcapPSCloseRing_matched_track_eta_by_layer{}".format(i), "Root__md_endcapPSCloseRing_all_track_eta_by_layer{}".format(i), "md_eff_endcapPSCloseRing_eta_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcapPSCloseRing_matched_track_phi_by_layer{}".format(i), "Root__md_endcapPSCloseRing_all_track_phi_by_layer{}".format(i), "md_eff_endcapPSCloseRing_phi_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcapPSCloseRing_matched_track_z_by_layer{}".format(i), "Root__md_endcapPSCloseRing_all_track_z_by_layer{}".format(i), "md_eff_endcapPSCloseRing_z_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcapPSCloseRing_matched_track_wrapphi_by_layer{}".format(i), "Root__md_endcapPSCloseRing_all_track_wrapphi_by_layer{}".format(i), "md_eff_endcapPSCloseRing_wrapphi_by_layer{}.pdf".format(i))

    plot_eff("Root__md_endcapPSLowPt_matched_track_pt", "Root__md_endcapPSLowPt_all_track_pt", "md_eff_endcapPSLowPt_pt.pdf")
    plot_eff("Root__md_endcapPSLowPt_matched_track_pt", "Root__md_endcapPSLowPt_all_track_pt", "md_eff_endcapPSLowPt_ptzoom.pdf")
    plot_eff("Root__md_endcapPSLowPt_matched_track_eta", "Root__md_endcapPSLowPt_all_track_eta", "md_eff_endcapPSLowPt_eta.pdf")
    plot_eff("Root__md_endcapPSLowPt_matched_track_phi", "Root__md_endcapPSLowPt_all_track_phi", "md_eff_endcapPSLowPt_phi.pdf")
    plot_eff("Root__md_endcapPSLowPt_matched_track_z", "Root__md_endcapPSLowPt_all_track_z", "md_eff_endcapPSLowPt_z.pdf")
    for i in xrange(5):
        plot_eff("Root__md_endcapPSLowPt_matched_track_pt_by_layer{}".format(i), "Root__md_endcapPSLowPt_all_track_pt_by_layer{}".format(i), "md_eff_endcapPSLowPt_pt_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcapPSLowPt_matched_track_pt_by_layer{}".format(i), "Root__md_endcapPSLowPt_all_track_pt_by_layer{}".format(i), "md_eff_endcapPSLowPt_ptzoom_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcapPSLowPt_matched_track_eta_by_layer{}".format(i), "Root__md_endcapPSLowPt_all_track_eta_by_layer{}".format(i), "md_eff_endcapPSLowPt_eta_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcapPSLowPt_matched_track_phi_by_layer{}".format(i), "Root__md_endcapPSLowPt_all_track_phi_by_layer{}".format(i), "md_eff_endcapPSLowPt_phi_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcapPSLowPt_matched_track_z_by_layer{}".format(i), "Root__md_endcapPSLowPt_all_track_z_by_layer{}".format(i), "md_eff_endcapPSLowPt_z_by_layer{}.pdf".format(i))
        plot_eff("Root__md_endcapPSLowPt_matched_track_wrapphi_by_layer{}".format(i), "Root__md_endcapPSLowPt_all_track_wrapphi_by_layer{}".format(i), "md_eff_endcapPSLowPt_wrapphi_by_layer{}.pdf".format(i))

if drawSGplots:

    plot_eff("Root__sg_all_matched_track_pt", "Root__sg_all_all_track_pt", "sg_eff_all_pt.pdf")
    plot_eff("Root__sg_all_matched_track_pt", "Root__sg_all_all_track_pt", "sg_eff_all_ptzoom.pdf")
    plot_eff("Root__sg_all_matched_track_eta", "Root__sg_all_all_track_eta", "sg_eff_all_eta.pdf")
    plot_eff("Root__sg_all_matched_track_phi", "Root__sg_all_all_track_phi", "sg_eff_all_phi.pdf")
    plot_eff("Root__sg_all_matched_track_z", "Root__sg_all_all_track_z", "sg_eff_all_z.pdf")
    for i in xrange(5):
        plot_eff("Root__sg_all_matched_track_pt_by_layer{}".format(i), "Root__sg_all_all_track_pt_by_layer{}".format(i), "sg_eff_all_pt_by_layer{}.pdf".format(i))
        plot_eff("Root__sg_all_matched_track_eta_by_layer{}".format(i), "Root__sg_all_all_track_eta_by_layer{}".format(i), "sg_eff_all_eta_by_layer{}.pdf".format(i))
        plot_eff("Root__sg_all_matched_track_phi_by_layer{}".format(i), "Root__sg_all_all_track_phi_by_layer{}".format(i), "sg_eff_all_phi_by_layer{}.pdf".format(i))
        plot_eff("Root__sg_all_matched_track_z_by_layer{}".format(i), "Root__sg_all_all_track_z_by_layer{}".format(i), "sg_eff_all_z_by_layer{}.pdf".format(i))

    sgcombos = ["all", "barrelbarrel", "barrelflatbarrel", "barreltiltbarrel", "barrelflatbarrelflat", "barrelflatbarreltilt", "barreltiltbarrelflat", "barreltiltbarreltilt", "barrelendcap", "barreltiltendcap", "barrel", "endcap", "endcapPS", "endcapPSPS", "endcapPS2S", "endcap2S"]
    # sgcombos = ["endcap2S", "endcapPS", "endcap"]

    for sgcombo in sgcombos:
        plot_eff("Root__sg_{}_matched_track_pt".format(sgcombo), "Root__sg_{}_all_track_pt".format(sgcombo), "sg_eff_{}_pt_alllayer.pdf".format(sgcombo))
        plot_eff("Root__sg_{}_matched_track_pt".format(sgcombo), "Root__sg_{}_all_track_pt".format(sgcombo), "sg_eff_{}_ptzoom_alllayer.pdf".format(sgcombo))
        plot_eff("Root__sg_{}_matched_track_eta".format(sgcombo), "Root__sg_{}_all_track_eta".format(sgcombo), "sg_eff_{}_eta_alllayer.pdf".format(sgcombo))
        plot_eff("Root__sg_{}_matched_track_phi".format(sgcombo), "Root__sg_{}_all_track_phi".format(sgcombo), "sg_eff_{}_phi_alllayer.pdf".format(sgcombo))
        plot_eff("Root__sg_{}_matched_track_z".format(sgcombo), "Root__sg_{}_all_track_z".format(sgcombo), "sg_eff_{}_z_alllayer.pdf".format(sgcombo))
        for i in xrange(5):
            plot_eff("Root__sg_{}_matched_track_pt_by_layer{}".format(sgcombo, i), "Root__sg_{}_all_track_pt_by_layer{}".format(sgcombo, i), "sg_eff_{}_pt_by_layer{}.pdf".format(sgcombo, i))
            plot_eff("Root__sg_{}_matched_track_pt_by_layer{}".format(sgcombo, i), "Root__sg_{}_all_track_pt_by_layer{}".format(sgcombo, i), "sg_eff_{}_ptzoom_by_layer{}.pdf".format(sgcombo, i))
            plot_eff("Root__sg_{}_matched_track_eta_by_layer{}".format(sgcombo, i), "Root__sg_{}_all_track_eta_by_layer{}".format(sgcombo, i), "sg_eff_{}_eta_by_layer{}.pdf".format(sgcombo, i))
            plot_eff("Root__sg_{}_matched_track_phi_by_layer{}".format(sgcombo, i), "Root__sg_{}_all_track_phi_by_layer{}".format(sgcombo, i), "sg_eff_{}_phi_by_layer{}.pdf".format(sgcombo, i))
            plot_eff("Root__sg_{}_matched_track_z_by_layer{}".format(sgcombo, i), "Root__sg_{}_all_track_z_by_layer{}".format(sgcombo, i), "sg_eff_{}_z_by_layer{}.pdf".format(sgcombo, i))

if drawTLplots:

    tlcombos = ["barrel1barrel3", "barrel1flatbarrel3flat", "barrel1tiltbarrel3flat", "barrel1tiltbarrel3tilt", "barrel1tiltbarrel3tiltbarrel4", "barrel1tiltbarrel3tiltendcap1", "barrelbarrelbarrelbarrel"]
    tlcombos = ["barrelbarrelbarrelbarrel", "barrelbarrelendcapendcap"]

    for tlcombo in tlcombos:
        plot_eff("Root__tl_{}_matched_track_pt".format(tlcombo), "Root__tl_{}_all_track_pt".format(tlcombo), "tl_eff_{}_pt_alllayer.pdf".format(tlcombo))
        plot_eff("Root__tl_{}_matched_track_pt".format(tlcombo), "Root__tl_{}_all_track_pt".format(tlcombo), "tl_eff_{}_ptzoom_alllayer.pdf".format(tlcombo))
        plot_eff("Root__tl_{}_matched_track_eta".format(tlcombo), "Root__tl_{}_all_track_eta".format(tlcombo), "tl_eff_{}_eta_alllayer.pdf".format(tlcombo))
        plot_eff("Root__tl_{}_matched_track_phi".format(tlcombo), "Root__tl_{}_all_track_phi".format(tlcombo), "tl_eff_{}_phi_alllayer.pdf".format(tlcombo))
        plot_eff("Root__tl_{}_matched_track_z".format(tlcombo), "Root__tl_{}_all_track_z".format(tlcombo), "tl_eff_{}_z_alllayer.pdf".format(tlcombo))
        for i in xrange(5):
            plot_eff("Root__tl_{}_matched_track_pt_by_layer{}".format(tlcombo, i), "Root__tl_{}_all_track_pt_by_layer{}".format(tlcombo, i), "tl_eff_{}_pt_by_layer{}.pdf".format(tlcombo, i))
            plot_eff("Root__tl_{}_matched_track_pt_by_layer{}".format(tlcombo, i), "Root__tl_{}_all_track_pt_by_layer{}".format(tlcombo, i), "tl_eff_{}_ptzoom_by_layer{}.pdf".format(tlcombo, i))
            plot_eff("Root__tl_{}_matched_track_eta_by_layer{}".format(tlcombo, i), "Root__tl_{}_all_track_eta_by_layer{}".format(tlcombo, i), "tl_eff_{}_eta_by_layer{}.pdf".format(tlcombo, i))
            plot_eff("Root__tl_{}_matched_track_phi_by_layer{}".format(tlcombo, i), "Root__tl_{}_all_track_phi_by_layer{}".format(tlcombo, i), "tl_eff_{}_phi_by_layer{}.pdf".format(tlcombo, i))
            plot_eff("Root__tl_{}_matched_track_z_by_layer{}".format(tlcombo, i), "Root__tl_{}_all_track_z_by_layer{}".format(tlcombo, i), "tl_eff_{}_z_by_layer{}.pdf".format(tlcombo, i))
