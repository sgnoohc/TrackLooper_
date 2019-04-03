#!/bin/env python

import plottery_wrapper as p

p.dump_plot(fnames=["debug.root"],
    dirname="plots/lin",
    extraoptions={},
    )

p.dump_plot(fnames=["debug.root"],
    dirname="plots/log",
    extraoptions={"yaxis_log":True, "legend_smart":False},
    )
