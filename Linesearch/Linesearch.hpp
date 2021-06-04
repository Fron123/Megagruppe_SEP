#pragma once
#include <Eigen/Dense>
#include "nonlinear_system.hpp"

namespace Nonlinear{

template<typename TS, typename TP, int NS, int NP>
class Linesearch{

public:
  using VTS=Eigen::Matrix<TP,NP,1>;
  int _eps;
  
Linesearch()

Iteration(nlsys::System<TS,TP,NS,NP>)

checkpdHessian()

getv0()


};
}  
