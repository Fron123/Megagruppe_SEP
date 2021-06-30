#include<adolc/adouble.h>
#include<adolc/adolc.h>
#include <cassert>
#include<iostream>
#include<Eigen/Dense>
#include<random>
#include<iomanip>
#include<chrono>
#include<unistd.h>
#include<Example.hpp>
#include<string>

constexpr int MIN = -1;                                                     //Definitionsbereich der Funktion
constexpr int MAX = 1;                                                      //In diesem Fall D(-1,1)

int main(){

auto start = std::chrono::steady_clock::now();
Example ex;								    //Objekt der Klasse Example erstellen 
const int n = 100;                                                                  //Anzahl unabhängiger Variablen
std::cout << "ADOL-C Tiefpunkt finden \n";

std::srand(std::time(nullptr));                                             //Zufallsgenerator

ex.xp = new double[n];
ex.xp2 = new double[n];
ex.xp_temp = new double[n];
ex.p = new double[n];                                                  //Parameter
ex.alpha = new double[1];
ex.H=(double**)malloc(n*sizeof(double*));

ex.eps = 1e-6;                                                          //Epsilon zum anpassen für den Linesearch
ex.alpha[0] = 0.01;                                                            //Alpha zum anpassen für den Linesearch

for (int i=0; i<n; i++) {
    ex.xp[i] = MIN + (double)(rand()) / ((double)(RAND_MAX/(MAX - MIN)));      //Zuweisung der Zufallszahlen an die x-Werte
    ex.p[i] = -0.5;
}

Eigen::Vector<double,n> v;                                                  //Erstellen eines Eigen Vektors mit den X-Werten
for (int i=0; i<n; i++) {
    v(i) = ex.xp[i];
}

std::cout << "Das ist jetzt der VeKtor:" <<std::endl << v << std::endl;


ex.array1 = new double[n];                                             //Array erstellen für den Gradienten
ex.array2 = new double[n];
ex.array_temp = new double[n];

ex.array1 = ex.grad(ex.xp,ex.p,n);                                                        //Gradienten berechnen von den ersten X-Werten

Eigen::Vector<double,n> gra;                                                  //Erstellen eines Eigen Vektors mit den X-Werten
for (int i=0; i<n; i++) {
    gra(i) = ex.array1[i];
}


std::cout << "Das ist jetzt der Gradient:" <<std::endl << gra << std::endl;

int iteration = 1;

while(ex.norm(ex.array1,n)>=ex.eps){
    for(int j=0; j<n; j++){
        ex.xp2[j] = ex.xp[j]+ex.alpha[0]*(-1)*ex.array1[j];
        ex.array2 = ex.grad(ex.xp2,ex.p,n);
        ex.xp_temp[j] = ex.xp[j];
        ex.xp[j] = ex.xp2[j];
        ex.array_temp[j]=ex.array1[j];
        ex.array1[j]=ex.array2[j];
    }
    Eigen::Vector<double,n> grad_1;                                                  //Erstellen eines Eigen Vektors mit den X-Werten
    for (int i=0; i<n; i++) {
        grad_1(i) = ex.array_temp[i];
    }
    Eigen::Vector<double,n> grad_2;                                                  //Erstellen eines Eigen Vektors mit den X-Werten
    for (int i=0; i<n; i++) {
        grad_2(i) = ex.array1[i];
    }
    Eigen::Vector<double,n> x_1;                                                  //Erstellen eines Eigen Vektors mit den X-Werten
    for (int i=0; i<n; i++) {
        x_1(i) = ex.xp_temp[i];
    }
    Eigen::Vector<double,n> x_2;                                                  //Erstellen eines Eigen Vektors mit den X-Werten
    for (int i=0; i<n; i++) {
        x_2(i) = ex.xp2[i];
    }
    ex.alpha[0] = (((x_2 - x_1).transpose()) * (grad_2 - grad_1)).norm() / ((grad_2 - grad_1).squaredNorm());


    iteration = iteration+1;

}

ex.H = ex.hess(ex.xp,ex.p,n);                                                             //Hessematrix ausrechenen zum prüfen???????

Eigen::Matrix<double,n,n> h;                                                //Erstellen einer Eigen Matrix die der Hesse Matrix entspricht
for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++){
                h(i,j) = ex.H[i][j];
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
    std::cout<<"Minimun bei x"<<j<<":"<< ex.xp[j]<<std::endl;                                  //Ausgabe der numerisch berechneten Minimalstellen
}

std::cout<<"Bei Iteration: "<< iteration<<std::endl;

auto end = std::chrono::steady_clock::now();
auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

std::cout << "Elapsed time in milliseconds: " << elapsed.count()*1e-6;


return 0;
}
