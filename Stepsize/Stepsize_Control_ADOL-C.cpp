// Stepsize Control Florian

#pragma once 

#include<iostream>

#include<Eigen/Dense>
#include "adolc.h"

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
        
        const typename Nonlinear::System<T,N>::MT** Hessian;
        const typename Nonlinear::System<T,N>::VT** Gradient;
  
        hessian(1,N,A,Hessian);
        gradient(1,N,A,Gradient);
        
        t = Gradient/Hessian;
        step = b(0) + t;
       
        
        return step;
        
        }
