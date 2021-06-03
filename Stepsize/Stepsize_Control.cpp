// Stepsize Control Florian

#pragma once 

#include<iostream>

#include<Eigen/Dense>
#include "dco.hpp"

template<typename T,int N>
typename Nonlinear::System<T,N>::VT Stepsize(
        const typename Nonlinear::System<T,N>::MT& A,
        const typename Nonlinear::System<T,N>::VT& b,
//        const int shrinking_factor,
//        const int alpha_max
//      const int c1;
//      const int c2;
)       
        {
        
        const typename Nonlinear::System<T,N>::MT t;
        const typename Nonlinear::System<T,N>::VT step;
        
        
        t = dco::derivative(A()(0))/dco::derivative(dco::derivative(A()(0)));
        step = b(0) + t;
       
        
        return step;
        
        }
