#include "nonlinear_system.hpp"
#include "Linesearch.hpp"
#include <Eigen/Dense>
#include "adolc.h"
#include "Stepsize_control.cpp"
#include "Descent.cpp"

namespace Nonlinear{
  
  template<typename TS, typename TP, int NS, int NP>
  bool Linesearch<TS, TP, NS, NP>::checkpdHessian(){
            const typename Eigen::MatrixXd Hessian(NS,NS);
            hessian(1,NS,System<TS,TP,NS,NP>::x(),Hessian);
            Eigen::LLT<Eigen::MatrixXd> lltOfA(Hessian); // compute the Cholesky decomposition of A
            if(lltOfA.info() == Eigen::NumericalIssue)
            {
              throw std::runtime_error("Possibly non semi-positive definitie matrix!");
              return false;
            }
            return true;    
  }

  template<typename TS, typename TP, int NS, int NP>
  TS Linesearch< TS,  TP,  NS,  NP>::getv0(){return v0;}
 
  template<typename TS, typename TP, int NS, int NP>
  TS Linesearch<TS, TP, NS, NP>::getx_prev(){return x_prev;}

 
  template<typename TS, typename TP, int NS, int NP>
  TS Linesearch< TS,  TP,  NS,  NP>::iteration(System<TS,TP,NS,NP>&nlsys){
  TS x_prev = nlsys.x();
  TS v0;    
  TS v_neu;
  TS tol = 1;
  TS grad_cur = tol;

  while(grad_cur.norm() >= tol){
    v_neu = x_prev + Stepsize_control<TS,TP,NS,NP>::condition()*Descent<TS,TP,NS,NP>::descent_direction();
    nlsys.x() = v_neu;
    x_prev = v0;
    grad_cur = dgdx(nlsys);
    v0 = v_neu;
  }   
  return v0;
  }
   
/* 
  template<typename TS, typename TP, int NS, int NP>
  Linesearch<typename TS, typename TP, int NS, int NP>::Linesearch(){
    TS = Linesearch<typename TS, typename TP, int NS, int NP>::iteration();
    if(Linesearch<typename TS, typename TP, int NS, int NP>::checkpdHessian()==true){  
    
    }
  */ 
  }
