#!/bin/env python

import plottery_wrapper as p
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
    num.Divide(num, den, 1, 1, "B")
    p.plot_hist(
            bgs=[num],
            options=
                {
                    "output_name":"plots/lin/{}".format(output_name),
                    # "remove_underflow":True,
                    # "remove_overflow":True,
                    "yaxis_range": [0.95, 1.05] if "eta" in output_name else [],
                    #"yaxis_range": [0.95, 1.05],
                    "no_ratio":True,
                    "draw_points":True,
                    "do_stack":False,
                    "print_yield":True,
                    "yield_prec":4,
                },
            colors=[1],
            )

plot_eff("Root__md_matched_track_pt", "Root__md_all_track_pt", "eff_pt.pdf")
plot_eff("Root__md_matched_track_eta", "Root__md_all_track_eta", "eff_eta.pdf")
for i in xrange(6):
    plot_eff("Root__md_matched_track_pt_by_layer{}".format(i), "Root__md_all_track_pt_by_layer{}".format(i), "eff_pt_by_layer{}.pdf".format(i))
    plot_eff("Root__md_matched_track_eta_by_layer{}".format(i), "Root__md_all_track_eta_by_layer{}".format(i), "eff_eta_by_layer{}.pdf".format(i))
