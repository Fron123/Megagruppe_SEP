#include<adolc/adouble.h>
#include<adolc/adolc.h>
#include<iostream>
#include<math.h>
#include<array>
#include<Eigen/Dense>


Eigen::Matrix<double,1,1> eig(double** H,int n)
{
    Eigen::Matrix<double,n,n> Ematrix;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            Ematrix(i)(j) = H[i][j];
    return Ematrix;
}

double* grad(double* xp, int n)
{
    double  yp = 1.0;
    adouble* x = new adouble[n];
    adouble  y = 1;
    adouble temp;
    trace_on(1);

    for(int i=0;i<n;i++) {
            x[i] <<= xp[i];
            temp += x[i]*x[i];
    }
    y = -exp(-0.5*temp);
    y >>= yp;
    delete[] x;
    trace_off();
    double* g = new double[n];
    gradient(1,n,xp,g);

    return g;
}

double** hess(double* xp, int n)
{
    double  yp = 1.0;
    adouble* x = new adouble[n];
    adouble  y = 1;
    adouble temp;
    trace_on(1);

    for(int i=0;i<n;i++) {
            x[i] <<= xp[i];
            temp += x[i]*x[i];
    }
    y = -exp(-0.5*temp);
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

double norm(double array)
{
    double alpha;
    alpha = sqrt(array*array);
    return alpha;
}

double norm(double array1, double array2)
{
    double alpha;
    alpha = array2-array1;
    alpha = sqrt(alpha*alpha);
    return alpha;
}



int main(){
int n=2,i,j,tape_stats[11];
std::cout << "SPEELPENNINGS PRODUCT (ADOL-C Documented Example) \n";
std::cout << "number of independent variables = ?  \n";

Eigen::Matrix<double,n,n> Ematrix;


double* xp = new double[n];
double* xp2 = new double[n];
double  yp = 0.0;
adouble* x = new adouble[n];
adouble  y = 1;
adouble temp;
double eps = 1e-8;
double* alpha = new double[0];
double** H=(double**)malloc(n*sizeof(double*));
double* Hessianlul = new double[0];


alpha[0] = 0.01;


xp[0] = 1;

xp[1] = 0.5;

double* array1 = new double[n];
double* array2 = new double[n];

array1 = grad(xp,n);

H = hess(xp,n);

Eigen::MatrixXd<double,n,n> h;
for (int i=0; i<n; i++) {
	for (int j=0; j<n; j++)
		h(i,j) = H[i][j];
	}
    
Ematrix = eig(H,n);

if (H > 0)
{
    std::cout<<"Hessematrix ist positiv definit"<<std::endl;
}
else
{
    return 1;
}



std::cout<<"Minimun: "<< xp[0]<<std::endl;
i = 1;

while(norm(array1[0])>=eps){
    xp2[0] = xp[0]-alpha[0]*array1[0];
    array2 = grad(xp2,n);
    //alpha[0] = (xp2[0]-xp[0])*(norm(array1[0],array2[0]))/((norm(array1[0],array2[0]))*(norm(array1[0],array2[0])));
    //std::cout<<"Alpha: "<< alpha[0]<<std::endl;
    xp[0] = xp2[0];
    array1[0]=array2[0];
    std::cout<<"Iteration: "<< i<<std::endl;
    i = i+1;

}

std::cout<<"Minimun: "<< xp[0]<<std::endl;

std::cout<<"Hessian: "<< H[0][0]<<std::endl;
}
