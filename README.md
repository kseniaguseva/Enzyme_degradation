This code produces the first part of results of the paper Guseva et al (2024),
"Bacteria face trade-offs in the decomposition of complex biopolymers". 

The code implements population balance equations modeling the degradation of
polymer chains. Polymers are divided into size classes according to their size,
we model the flows from one size class to another during the degradation
process. All functions are written C++, they are run with the use of python
scripts. To run the code make sure to have installed Python 3 and Boost.Python.


# Installation:
---------------

For installation and use of Python and Boost.Python please check the
documentation:

https://www.python.org/downloads/

https://www.boost.org/doc/libs/1_84_0/more/getting_started/index.html

Please configure the Makefile file with for the appropriate location of your
libraries (first line of the file) and appropriate version of Python installed.
Run ==make== to compile all functions written in C++. 

After that you should be ready to tun the python code.


# File list:
------------

1. **enz_dyn.hh** -- contains all functions modeling degradation dynamics

2. **mon_timeseries_PS.py** -- used to generate the time series of monomer concentration.

3. **numpy_bind.hh**, **demangle.hh**, **demangle.cc**: Functions for moving
   arrays between Numpy and C++, requires Boost.Python.

