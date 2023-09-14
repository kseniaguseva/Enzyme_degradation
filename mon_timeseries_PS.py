#!/usr/bin/env python
from math import *
from numpy import *
from pylab import *

import sys
#sys.path.append('../module_enzymes')
from enz_dyn import *


fig = figure(figsize=(7.5, 1.5))

## Parameters
################################################################################
t_end = 250   # time period in (h)
dt = 0.005    # time step
e  = 3.       # initial enzyme concnetration (nmol C/mm^3)
totmon_range = [100., 200, 300]   # initial concnetration of NAG (monomer units)
N = 200                           # size of chains in which the monomers above are trapped
time = arange(0, t_end, dt)       # timeline of the simulation
################################################################################

## Used for plots
# color used for the plots (orange for exo-enzymes, blue for endo-enzymes)
c = [(1,0.3961, 0.1529), 
     (0.2118, 0.2157, 0.6078)]
simb = ["--", "-.", "-"]
################################################################################

T_endo = []
aux = 0
subplot(133)
fr_exo = 0.   # fraction of exo-enzymes
for totmon in totmon_range:
    print(float(totmon/N))
    # starts the settings input: (chain_size, polymer concentration, kcat-exo,kcat-endo,km-exo, km-endo)
    enz = Enzymes(int(N), totmon/N, 0.82, 0.82, 0.5, 0.5)
    mon = enz.evolve(t_end, dt, fr_exo, e)   # degradation dynamics
    plot(time/24, mon, simb[aux], label = r"$N_n(t_0) = %.1f$" %(totmon/N), color = c[1])
    if(aux == 2):
        T_endo = mon
    aux += 1

title("Endo-enzymes", weight = "bold", fontsize = 10)
legend(loc = "best", fontsize = 6, frameon=False)
gca().set_xlabel(r"time (days)")
gca().set_yticks([])

text(-1.,  350, "C", fontsize=12, weight = "bold")

fr_exo = 1. # fraction of exo-enzymes
T_exo = []
aux = 0
subplot(132)
for totmon in totmon_range:
    print(float(totmon/N))
    enz = Enzymes(int(N), totmon/N, 0.82, 0.82, 0.5, 0.5)
    mon = enz.evolve(t_end, dt, fr_exo, e)       # see the paramters above
    plot(time/24, mon, simb[aux], label = r"$N_n(t_0) = %.1f$" %(totmon/N), color = c[0])
    if(aux == 2):
        T_exo = mon

    aux += 1

title("Exo-enzymes", weight = "bold", fontsize = 10)
legend(loc = "best", fontsize = 6, frameon=False)
gca().set_xlabel(r"time (days)")
gca().set_yticks([])


text(-1.,  350, "B", fontsize=12, weight = "bold")

subplot(131)
plot(5.2*ones(100), linspace(0, 300, 100) , "--", color = 'cornflowerblue')
plot(time/24, T_endo, "-", label = r"endo", color = c[1])

plot(8.5*ones(100), linspace(0, 300, 100) , "--", color = "orange")
plot(time/24, T_exo, "-", label = r"exo", color = c[0])

arrowprops = dict(arrowstyle = "<->", color = "cornflowerblue")
annotate(r'$T_{deg}$', xy =(0, 100), xytext =(5.3, 100), color = "cornflowerblue",
                arrowprops = arrowprops, )

arrowprops = dict(arrowstyle = "<->", color = "orange")
annotate(r'$T_{deg}$', xy =(0, 175), xytext =(8.6, 175), color = "orange",
                arrowprops = arrowprops, )

title("Comparison", weight = "bold", fontsize = 10)
legend(loc = "best", fontsize = 6, frameon=False)
gca().set_xlabel(r"time (days)")
gca().set_ylabel("monomers")
text(-3.2,  350, "A", fontsize=12, weight = "bold")

subplots_adjust(bottom=0.3, right=0.98, left=0.1, top = 0.85, wspace =0.05, hspace=0.05)
plt.savefig("PSmon_timeseries.pdf")
