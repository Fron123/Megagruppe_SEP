//Stepsize_control Gruppe 6 (My)
#pragma once
#include <limits>
#include "nonlinear_system.hpp"

namespace Nonlinear{

template<typename TS, typename TP, int NS, int NP>
class Stepsize_control{

public: 
	TS alpha_max = std::numeric_limit<TS>::max();
	TS shrinking_factor;
	TS c_1;
	TS c_2;
	
Stepsize_control(const TS& alpha_max, const TS& shrinking_factor, const TS c_1, const TS c_2, const int cond);

TS condition(System<TS,TP,NS,NP>&, Descent<TS,TP,NS,NP>&, Linesearch<TS,TP,NS,NP>&);

};
}
