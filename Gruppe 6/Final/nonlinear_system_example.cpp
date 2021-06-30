#include<adolc/adouble.h>
#include<adolc/adolc.h>
#include<iostream>


double* Example::grad(double* xp, double* p, int n)                                             //Gradient berechnen mit ADOL-C
{
    double  yp = 0;
    adouble* x = new adouble[n];
    adouble  y = 0;
    adouble temp;
    trace_on(1);

    for(int i=0;i<n;i++) {
            x[i] <<= xp[i];
            temp += p[i]*x[i]*x[i];
    }
    y = -exp(temp);                                                    //<--Funktion definieren bitte hier
    y >>= yp;
    delete[] x;
    trace_off();
    double* g = new double[n];
    gradient(1,n,xp,g);

    return g;
}

double** Example::hess(double* xp, double* p, int n)                                            //Hesse berechnen mit ADOL-C
{
    double  yp = 0;
    adouble* x = new adouble[n];                                            //Ob das hier so nötig ist weiß ich ehrlich gesagt nicht
    adouble  y = 0;
    adouble temp;
    trace_on(1);

    for(int i=0;i<n;i++) {
            x[i] <<= xp[i];
            temp += p[i]*x[i]*x[i];
    }
    y = -exp(temp);                                                    //<--Funktion definieren bitte hier
    y >>= yp;
    delete[] x;
    trace_off();
    double** H=(double**)malloc(n*sizeof(double*));
    for(int i=0;i<n;i++)
    {
        H[i]=(double*)malloc((i+1)*sizeof(double));
    }
    hessian(1,n,xp,H);

    return H;
}

double Example::norm(double* array, int n)
{
    double alpha,temp = 0;
    for(int i = 0; i<n; i++){
        temp += array[i]*array[i];
    }
    alpha = sqrt(temp);
    return alpha;
}
