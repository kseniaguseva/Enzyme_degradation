// Copyright (C) 2022 Ksenia Guseva <ksenia@skewed.de>

#ifndef ENZ_DYN_HH
#define ENZ_DYN_HH

#include <cmath>
#include <iostream>
#include <iomanip>
#include <tuple>
#include <ext/numeric>
using __gnu_cxx::power;
#include <vector>
#include <utility>

#include <boost/multi_array.hpp>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

#include "numpy_bind.hh"

using namespace std;
using namespace boost;

class Enzymes {

public:
    Enzymes(int shape, double c_init, double vmax_exo, double vmax_endo, double km_exo, double km_endo):
        _n(extents[shape]),
        _shape(100),
        _c_init(10.),
        _vmax_exo(0.82),             //   h^{-1}
        _km_exo(1.),                  //   nmolC
        _vmax_endo(0.82),             //   h^{-1}
        _km_endo(1.)                  //   nmolC
        
    {
        _shape = shape;
         _c_init = c_init;
        
        _km_exo = km_exo;
        _vmax_exo = vmax_exo;

        _km_endo = km_endo;
        _vmax_endo = vmax_endo;

        for (int i = 0; i < _shape; i++)
        {
            _n[i] = 0;
        }
        _n[_shape-1] = _c_init;
        
    }
    
    void exo_activity(double e, double *dn)
    {
        //double dn[shape];

        double sum_n = 0;
        // sums all, except monomers
        for (int k = 1; k < _shape; k++)
        {
            sum_n += _n[k];
        }
        
        double c_u = _vmax_exo * e/ (sum_n + _km_exo);  // same for all sizes
        // depends on the whole pool of particles in the system (except monomers)

        // 1. degradation into monomers
        double sum_n2 = 0;
        for (int k = 2; k < _shape; k++)
        {
            sum_n2 += _n[k];
        }
        // first term: from dimes, second term from all the rest
        dn[0] = (2 * _n[1] + sum_n2) * c_u;

        // 2. degradation into all other sizes, except the n-mer
        for (int k = 1; k < _shape - 1; k++)
        {
            dn[k] = c_u*(-_n[k]  + _n[k+1]);
        }

        // 3. degradation of n-mers (has only a negative term)
        dn[_shape-1] = (-_n[_shape-1] * c_u);
       
        
    }
    void endo_activity(double e, double *dn)
    {
        double sum_ni = 0;
        // sums all, except monomers
        for (int k = 1; k < _shape; k++)
        {
            sum_ni += _n[k]*k;
        }
         double c_u = _vmax_endo * e/ (sum_ni + _km_endo);  // same for all sizes
         for (int k = 0; k < _shape; k++)
        {
            if(k  > 0)
            {
                dn[k] -= c_u*_n[k]*k;
            
            }
            for (int j = k + 1; j < _shape; j++) //the smallest size produced are dimers
            {
                dn[k] += c_u*_n[j]*2;
            }
        } 
    }

    python::object evolve(double t_end, double dt, double fr_exo, double e)
    {
        double dn_exo[_shape];
        double dn_endo[_shape];
        int steps = int(t_end/dt);
        multi_array<double, 1> mon(extents[steps]);
        for(int t = 0; t < steps; t ++)
        {
            mon[t] = 0;
        }
        
        for(int t = 0; t < steps; t ++)
        {
            for (int k = 0; k < _shape; k++)
            {
                dn_exo[k] = 0;
                dn_endo[k] = 0;
            }
            if(fr_exo != 1)
            {
                endo_activity(e, dn_endo);
            }
            exo_activity(e, dn_exo);
            for (int k = 0; k < _shape; k++)
            {
                _n[k] += (fr_exo*dn_exo[k] + (1 - fr_exo)*dn_endo[k])*dt;
                if(_n[k] < 0)
                {
                    _n[k] = 0; 
                }
                
            }
            mon[t] = _n[0];
        }
        return wrap_multi_array_owned(mon);
    }

    double get_tdeg(double t_end, double dt, double fr_exo, double e)
    {
        double dn_exo[_shape];
        double dn_endo[_shape];
        int steps = int(t_end/dt);
        
        for(int t = 0; t < steps; t ++)
        {
            for (int k = 0; k < _shape; k++)
            {
                dn_exo[k] = 0;
                dn_endo[k] = 0;
            }
            if(fr_exo != 1)
            {
                endo_activity(e, dn_endo);
            }
            exo_activity(e, dn_exo);
            for (int k = 0; k < _shape; k++)
            {
                _n[k] += (fr_exo*dn_exo[k] + (1 - fr_exo)*dn_endo[k])*dt;
                
            }

            if(_n[0]/(_shape*_c_init) >= 0.99)
            {
                return t*dt;
            }
        }
        return steps*dt;
    }
    
    
    
    private:
    multi_array<double, 1> _n;
    int _shape;
    double _c_init;
    double _vmax_exo;
    double _km_exo;
    double _vmax_endo;
    double _km_endo;
    
};

    
#endif
