//#include "Linesearch.cpp"
#include "Stepsize_control.hpp"
#include <adolc/adolc.h>
#include <Eigen/Dense>

namespace Nonlinear{

template<typename TS, typename TP, int NS, int NP>	
Stepsize_control<TS, TP,NS,NP>::Stepsize_control(){}

template<typename TS, typename TP, int NS, int NP>
TS Stepsize_control<TS,TP,NS,NP>::condition(Linesearch<TS,TP,NS,NP>& ls){

	TS alpha;
	TS x_prev =ls.x_prev();
	TS v0 = ls.getv0();
	const typename Eigen::VectorXd grad_x_prev(NS);
	const typename Eigen::VectorXd grad_v0(NS);
	grad_x_prev = gradient(1,NS,x_prev,grad_x_prev);
	grad_v0 = gradient(1,NS,v0, grad_v0);

	alpha = (((v0 - x_prev).transpose()) * (grad_v0 - grad_x_prev)).norm() / ((grad_v0 - grad_x_prev).squaredNorm());
	return alpha;
}

}
