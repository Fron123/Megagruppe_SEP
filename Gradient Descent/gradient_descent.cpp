#include "nonlinear_system.hpp"
#include "Gradient_Descent.hpp"
#include "adolc.h"
#include "Linesearch.cpp"
#include <Eigen/Dense>


	template<typename TS, typename TP, int NS, int NP>
	Gradient<typename TS, typename TP, int NS, int NP>::calcGradient(){
		const typename Eigen::VectorXd gradient(NS);
		gradient  = -gradient(NS, System<TS, TP, NS, NP>::x(), gradient);
		return gradient; 	
	}
