This code produces the results of the enzyme degradation dynamics (first part)
of the paper Guseva et al (2023), "Trade-offs faced by bacteria in the
decomposition of complex biopolymers".

The code implements population balance equations modeling the degradation of
polymer chains. Polymers are divided into size classes according to their size,
we model the flows from one size class to another during the degradation
process. All functions are written C++, they are run with the use of python
scripts. To run the code make sure to have installed Python 3 and Boost.Python.

# File list:
------------

1. **enz_dyn.hh** -- contains all functions modeling degradation dynamics

2. **mon_timeseries_PS.py** -- used to generate the time series of monomer concentration.

3. **numpy_bind.hh**, **demangle.hh**, **demangle.cc**: Functions for moving
   arrays between Numpy and C++, requires Boost.Python.

