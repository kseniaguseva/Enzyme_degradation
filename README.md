This code produces the results ofthe enzyme degradation dynamics from the paper
Guseva et al (2023), "Trade-offs faced by bacteria in the decomposition of
complex biopolymers".

The code implements population balance equations modeling the degradation of
polymer chains. Polymers are divided into size classes according to their size,
we model the flows from one size class to another during the degradation
process. 

# File list:
1. enz_dyn.cc -- contains all functions modeling degradation dynamics

2. mon_timeseries_PS.py -- used to generate the time series of monomer concentration.

