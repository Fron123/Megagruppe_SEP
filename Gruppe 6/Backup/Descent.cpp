#include "nonlinear_system.hpp"
#include "Descent.hpp"
#include <adolc/adolc.h> 
#include "Linesearch.hpp"
#include <Eigen/Dense>

namespace Nonlinear{
	template<typename TS, typename TP, int NS, int NP>
	TS Descent< TS,  TP,  NS,  NP>::descent_direction(Linesearch<TS,TP,NS,NP>& ls){
		const typename Eigen::VectorXd gradient(NS);
		TS v = ls.get_v0();
		gradient = gradient(NS, System<TS, TP, NS, NP>::x(), gradient);
		return -gradient; 	
	}
}
