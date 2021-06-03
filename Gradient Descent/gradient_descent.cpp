#include "gradient_descent.hpp"
#include "adolc.h"
#include "linesearch.hpp"

class gradient_descent{

	void gradient_step(f, x0, alpha, kmax){

		d = -aldoc::grad(f,x0);
		return line_search(f, x0, alpha, d, kmax)
	}
}
