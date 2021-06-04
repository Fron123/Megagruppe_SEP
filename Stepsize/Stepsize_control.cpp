//Stepsize_control Gruppe 6 (My)

//#include "linesearch.cpp"
#include "Stepsize_control.hpp"
//#include "system.cpp"
//#include "descent.cpp"

namespace Nonlinear{

template<typename TS, typename TP, int NS, int NP>	
Stepsize_control<TS, TP,NS,NP>::Stepsize_control(const TS& alpha_max, const TS& shrinking_factor, const TS c_1, const TS c_2, const int cond):_alpha_max(alpha_max), _shrinking_factor(shrinking_factor), _c_1(c_1), _c_2(c_2), _cond(cond){}

template<typename TS, typename TP, int NS, int NP>
TS Stepsize_control<TS,TP,NS,NP>::condition(System<TS,TP,NS,NP>& nlsys, Descent<TS,TP,NS,NP>& dc, Linesearch<TS,TP,NS,NP>& ls){

switch(_cond){
	//Armijo
	case 1: {
		
		TS alpha = _alpha_max;  
		while(nlsys.f(ls.x()+alpha*dc.descent_direction()) > nlsys.f(ls.x())+_c_1*nlsys.dfdx(ls.x())*dc.descent_direction()){
 			alpha = alpha*_shrinking_factor;
		}	
		return alpha;
	}

	//Curvature
	case 2:{ 
		TS alpha= _alpha_max;
		while (nlsys.dfdx(ls.x()+alpha*dc.descent_direction())*dc.d() < _c_2*nlsys.dfdx(ls.x())*dc.descent_direction()){
			alpha = alpha * _shrinking_factor;
		 }
		return alpha;
	}	

	//Wolfe
	case 3: {
		TS alpha = _alpha_max;
		while(nlsys.f(ls.x()+alpha*dc.descent_direction()) > nlsys.f(ls.x()) + _c_1*alpha*nlsys.dfdx(ls.x())*dc.descent_direction() && nlsys.dfdx(ls.x() + alpha*dc.descecnt_direction())*dc.descent_direction() < _c_2*nlsys.dfdx(ls.x())*dc.descent_direction()){
			alpha=alpha*_shrinking:factor;
		}
		return alpha;
		}
	}	


}

