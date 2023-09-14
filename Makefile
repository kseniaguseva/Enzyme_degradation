CXXFLAGS=-Wall -O3 -g -std=c++17 -fPIC -lpython3.11  -lboost_python3 -lboost_numpy3 -I. -I/usr/include/python3.11 -I/usr/lib/python3.11/site-packages/numpy/core/include/ -shared -Wl,-soname,enz_dyn.so

enz_dyn.so: enz_dyn.hh enz_dyn.cc demangle.cc numpy_bind.hh
	g++ enz_dyn.cc demangle.cc -o enz_dyn.so ${CXXFLAGS}
