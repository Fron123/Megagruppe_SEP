#include "gradient_descent.hpp"
#include "adol-c.hpp"
#include "linesearch.hpp"


void gradien_descent(f, x0, alpha, kmax){

	d = -grad(f,x0);
	return line_search(f, x0, alpha, d, kmax)
	
}
