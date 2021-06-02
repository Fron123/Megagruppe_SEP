// Stepsize Control Florian

#pragma once 

#include<iostream>

#include<Eigen/Dense>
#include "dco.hpp"

template<typename T,int N>
typename Nonlinear::System<T,N>::VT Stepsize(
        const typename Nonlinear::System<T,N>::MT& A,
        const typename Nonlinear::System<T,N>::VT& b,
        const int shrinking_factor,
        const int alpha_max
//      const int c1;
//      const int c2;
){
        auto n = b.size;
        typename Linear::System<T,N>::VT g(n);
        using DCO_M=typename dco::ga1s<T>;
        using DCO_T=typename DCO_M::type;
        using DCO_TT=typename DCO_M::tape_t;
        typename Linear::System<DCO_T,N>::VT b_a(n);
        typename Linear::System<DCO_T,N>::MT A_a(n,n)
        b_a(0) = dco::derivative(A(x));
        b_a(1) = dco::derivative(A(y));

        for(i=0;i<n;i++){
                A_a(0,i) = dco::derivative(b_a(





~                                                                                                                                                                                                                                             
~                                          
