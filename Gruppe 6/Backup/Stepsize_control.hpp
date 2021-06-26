#pragma once
#include <limits>
#include "nonlinear_system.hpp"

namespace Nonlinear{

template<typename TS, typename TP, int NS, int NP>
class Stepsize_control{

public: 

	Stepsize_control();

	TS condition(Linesearch<TS,TP,NS,NP>&);

};
}

