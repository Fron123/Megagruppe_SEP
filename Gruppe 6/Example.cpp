#include<adolc/adouble.h>
#include<adolc/adolc.h>
#include<iostream>
#include<math.h>
#include<array>
#include<Eigen/Dense>
#include<random>
#include <iomanip>

double* grad(double* xp, double* p, int n)                                             //Gradient berechnen mit ADOL-C
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

double** hess(double* xp, double* p, int n)                                            //Hesse berechnen mit ADOL-C
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

double norm(double* array, int n)
{
    double alpha,temp = 0;
    for(int i = 0; i<n; i++){
        temp += array[i]*array[i];
    }
    alpha = sqrt(temp);
    return alpha;
}

constexpr int MIN = -1;                                                     //Definitionsbereich der Funktion
constexpr int MAX = 1;                                                      //In diesem Fall D(-1,1)

int main(){
const int n=3;
std::cout << "ADOL-C Tiefpunkt finden \n";

std::srand(std::time(nullptr));                                             //Zufallsgenerator

double* xp = new double[n];
double* xp2 = new double[n];
double* xp_temp = new double[n];
double* p = new double[n];                                                  //Parameter
double* alpha = new double[1];
double** H=(double**)malloc(n*sizeof(double*));

double eps = 1e-6;                                                          //Epsilon zum anpassen für den Linesearch
alpha[0] = 0.01;                                                            //Alpha zum anpassen für den Linesearch

for (int i=0; i<n; i++) {
    xp[i] = MIN + (double)(rand()) / ((double)(RAND_MAX/(MAX - MIN)));      //Zuweisung der Zufallszahlen an die x-Werte
    p[i] = -0.5;
}

Eigen::Vector<double,n> v;                                                  //Erstellen eines Eigen Vektors mit den X-Werten
for (int i=0; i<n; i++) {
    v(i) = xp[i];
}

std::cout << "Das ist jetzt der VeKtor:" <<std::endl << v << std::endl;


double* array1 = new double[n];                                             //Array erstellen für den Gradienten
double* array2 = new double[n];
double* array_temp = new double[n];

array1 = grad(xp,p,n);                                                        //Gradienten berechnen von den ersten X-Werten

Eigen::Vector<double,n> gra;                                                  //Erstellen eines Eigen Vektors mit den X-Werten
for (int i=0; i<n; i++) {
    gra(i) = array1[i];
}


std::cout << "Das ist jetzt der Gradient:" <<std::endl << gra << std::endl;

int iteration = 1;

while(norm(array1,n)>=eps){
    for(int j=0; j<n; j++){
        xp2[j] = xp[j]+alpha[0]*(-1)*array1[j];
        array2 = grad(xp2,p,n);
        xp_temp[j] = xp[j];
        xp[j] = xp2[j];
        array_temp[j]=array1[j];
        array1[j]=array2[j];
    }
    Eigen::Vector<double,n> grad_1;                                                  //Erstellen eines Eigen Vektors mit den X-Werten
    for (int i=0; i<n; i++) {
        grad_1(i) = array_temp[i];
    }
    Eigen::Vector<double,n> grad_2;                                                  //Erstellen eines Eigen Vektors mit den X-Werten
    for (int i=0; i<n; i++) {
        grad_2(i) = array1[i];
    }
    Eigen::Vector<double,n> x_1;                                                  //Erstellen eines Eigen Vektors mit den X-Werten
    for (int i=0; i<n; i++) {
        x_1(i) = xp_temp[i];
    }
    Eigen::Vector<double,n> x_2;                                                  //Erstellen eines Eigen Vektors mit den X-Werten
    for (int i=0; i<n; i++) {
        x_2(i) = xp2[i];
    }
    alpha[0] = (((x_2 - x_1).transpose()) * (grad_2 - grad_1)).norm() / ((grad_2 - grad_1).squaredNorm());


    iteration = iteration+1;

}

H = hess(xp,p,n);                                                             //Hessematrix ausrechenen zum prüfen???????

Eigen::Matrix<double,n,n> h;                                                //Erstellen einer Eigen Matrix die der Hesse Matrix entspricht
for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++){
                h(i,j) = H[i][j];
        }
}

std::cout << "Das ist jetzt die Hesse Matrix:" <<std::endl << h << std::endl;


Eigen::LLT<Eigen::MatrixXd> lltOfA(h);                                       //Prüfen ob positiv Definitheit durch Cholesky-Zerlegung
    if(lltOfA.info() == Eigen::NumericalIssue)
    {
        std::cout<<"Die Matrix ist nicht positiv definit"<<std::endl;
        return 1;
    }
    else
    {
        std::cout<<"Wie Sie sehen ist die Matrix Positiv Definit!"<<std::endl;
    }

for(int j=0; j<n; j++){
    std::cout<<"Minimun bei x"<<j<<":"<< xp[j]<<std::endl;                                  //Ausgabe der numerisch berechneten Minimalstellen
}

std::cout<<"Bei Iteration: "<< iteration<<std::endl;

return 0;
}
