#include "nonlinear_system.hpp"
#include "Linesearch.hpp"
#include <Eigen/Dense>
#include "adolc.h"
#include "Stepsize_control.cpp"

namespace Nonlinear{
  
  template<typename TS, typename TP, int NS, int NP>
  Linesearch<typename TS, typename TP, int NS, int NP>::checkpdHessian(){
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
  Linesearch<typename TS, typename TP, int NS, int NP>::getv0(){return v0}
  
  template<typename TS, typename TP, int NS, int NP>
  Linesearch<typename TS, typename TP, int NS, int NP>::iteration(){
    TS = TS + Stepsize_control<TS,TP,NS,NP>::condition(System<TS,TP,NS,NP>& nlsys, Descent<TS,TP,NS,NP>& dc, Linesearch<TS,TP,NS,NP>& ls);
    return TS;
  }
    
  template<typename TS, typename TP, int NS, int NP>
  Linesearch<typename TS, typename TP, int NS, int NP>::Linesearch(){
    TS = Linesearch<typename TS, typename TP, int NS, int NP>::iteration();
    if(Linesearch<typename TS, typename TP, int NS, int NP>::checkpdHessian()==true){  
    
    }
   
  }
  
  
  
  

  
            
    
