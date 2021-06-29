#pragma once


double* grad(double* xp, double* p, int n);                                            //Gradient berechnen mit ADOL-C

double** hess(double* xp, double* p, int n) ;

double norm(double* array, int n);




#include "../src/nonlinear_system_example.cpp"
