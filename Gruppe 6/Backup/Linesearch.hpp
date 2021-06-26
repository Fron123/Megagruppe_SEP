#pragma once
#include<Eigen/Dense>
#include "nonlinear_system.hpp"

namespace Nonlinear{

template<typename TS, typename TP, int NS, int NP>
class Linesearch{
//  using VTS=Eigen::Matrix<TS,NS,1>;
public:
  using VTS=Eigen::Matrix<TS,NS,1>;

  TS v0;
  TS x_prev;
  TS eps;
  TS iteration(System<TS,TP,NS,NP>&nlsys);
 bool checkpdHessian();
  TS getv0();
  TS getx_prev();		
  Linesearch(TS a,TP b,int c,int d){
  TS TS = a;
  TP TP = b;
  int NS = c;
  int NP = d;
  }
  };
}  
