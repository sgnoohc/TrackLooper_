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

plot_eff("Root__md_matched_track_pt", "Root__md_all_track_pt", "eff_pt.pdf")
plot_eff("Root__md_matched_track_eta", "Root__md_all_track_eta", "eff_eta.pdf")
for i in xrange(6):
    plot_eff("Root__md_matched_track_pt_by_layer{}".format(i), "Root__md_all_track_pt_by_layer{}".format(i), "eff_pt_by_layer{}.pdf".format(i))
    plot_eff("Root__md_matched_track_eta_by_layer{}".format(i), "Root__md_all_track_eta_by_layer{}".format(i), "eff_eta_by_layer{}.pdf".format(i))
