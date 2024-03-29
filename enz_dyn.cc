// Copyright (C) 2022 Ksenia Guseva <ksenia@skewed.de>

#include "enz_dyn.hh"

void* do_import_array() {
    import_array1(NULL);
    return NULL;
}


BOOST_PYTHON_MODULE(enz_dyn)
{
    boost::python::numpy::initialize();
    do_import_array();
    using namespace boost::python;

    // chain size, concentration of n-mers, c_exo, c_endo, km_exo, km_endo 
    class_<Enzymes>("Enzymes", init<int, double,  double, double, double, double>())
           .def("exo_activity", &Enzymes::exo_activity)
           .def("endo_activity", &Enzymes::endo_activity)
           .def("evolve", &Enzymes::evolve)
           .def("get_tdeg", &Enzymes::get_tdeg);
    
    
};

