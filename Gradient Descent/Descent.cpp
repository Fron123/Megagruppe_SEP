#include "nonlinear_system.hpp"
#include "Descent.hpp"
#include "adolc.h"
#include "Linesearch.cpp"
#include <Eigen/Dense>

namespace Nonlinear{
	template<typename TS, typename TP, int NS, int NP>
	Descent<typename TS, typename TP, int NS, int NP>::descent_direction(){
		const typename Eigen::VectorXd gradient(NS);
		v = Linesearch::get_v();
		gradient = gradient(1, NS, v, gradient);
		return -gradient; 	
	}
}
