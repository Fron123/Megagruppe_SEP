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
)       
        {
        auto n = b.size;
        typename Linear::System<T,N>::VT g(n);
        using DCO_M=typename dco::ga1s<T>;
        using DCO_T=typename DCO_M::type;
        using DCO_TT=typename DCO_M::tape_t;
        typename Linear::System<DCO_T,N>::VT b_a(n);
        typename Linear::System<DCO_T,N>::MT A_a(n,n)
        
        //Theoretisch müssten wir doch am besten ab hier die Hesse
        //Matrix berechnen und die dann weiter benutzen oder?
        
        b_a(0) = dco::derivative(A(x));
        b_a(1) = dco::derivative(A(y));
        
        
        A_a(0,0) = dco::derviative(dco::derivative(A(x))(x));
        A_a(0,1) = dco::derviative(dco::derivative(A(x))(y));
        A_a(1,0) = dco::derviative(dco::derivative(A(y))(x));
        A_a(1,1) = dco::derviative(dco::derivative(A(y))(y));
        
        /*
        Es fehlt jetzt noch die Rechnung für das a_k und s_k.
        Müssen wir dann auch die Epsilon überprüfung machen bzw.
        was meinst du muss am Ende bei uns herraukommen? Ich lade 
        auch mal ein Schaubild hoch andem ich das Programm geschrieben habe
        
        */    
        
        return Sinndeslebens;
        
        }
