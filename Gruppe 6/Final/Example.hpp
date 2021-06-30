#pragma once

class Example{
public:
//Variablen
double* xp;
double* xp2;
double* xp_temp;
double* p;                                 
double* alpha;
double** H;
double eps;
double* array1;                                             //Array erstellen für den Gradienten
double* array2;
double* array_temp;

//Methoden

double* grad(double* xp, double* p, int n);                                            //Gradient berechnen mit ADOL-C

double** hess(double* xp, double* p, int n) ;

double norm(double* array, int n);

};


#include "../src/nonlinear_system_example.cpp"
