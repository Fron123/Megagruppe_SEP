#include "nonlinear_system.hpp"
#include "Linesearch.hpp"
#include <Eigen/Dense>
#include <adolc/adolc.h>
#include "Stepsize_control.hpp"
#include "Descent.hpp"

#include "nonlinear_system_toy.hpp"
#include "nonlinear_solver.hpp"
#include "nonlinear_solver_newton.hpp"
#include "nonlinear_system.hpp"
#include "linear_solver_qr.hpp"
#include "linear_solver_lr.hpp"

namespace Nonlinear{
  
  template<typename TS, typename TP, int NS, int NP>
  bool Linesearch<TS, TP, NS, NP>::checkpdHessian(){
            const typename Eigen::MatrixXd Hessian(NS,NS);
            hessian(1,NS,System<TS,TP,NS,NP>::x(),Hessian);
            Eigen::LLT<Eigen::MatrixXd> lltOfA(Hessian); // compute the Cholesky decomposition of A
            if(lltOfA.info() == Eigen::NumericalIssue)
            {
              throw std::runtime_error("Possibly non semi-positive definitie matrix!");
              return false;
            }
            return true;    
  }

  template<typename TS, typename TP, int NS, int NP>
  TS Linesearch< TS,  TP,  NS,  NP>::getv0(){return v0;}
 
  template<typename TS, typename TP, int NS, int NP>
  TS Linesearch<TS, TP, NS, NP>::getx_prev(){return x_prev;}

 
  template<typename TS, typename TP, int NS, int NP>
  TS Linesearch< TS,  TP,  NS,  NP>::iteration(Toy::System<TS,TP> nlsys){
  TS x_prev = nlsys.x();
  TS v0;    
  TS v_neu;
  TS tol = 1;
  TS grad_cur = tol;
  TS alpha = 1;
	const typename Eigen::VectorXd grad_x_prev(NS);
	const typename Eigen::VectorXd grad_v0(NS);
  while(grad_cur.norm() >= tol){
	grad_x_prev = gradient(1,NS,x_prev,grad_x_prev);
	grad_v0 = gradient(1,NS,v0, grad_v0);

    alpha = (((v0 - x_prev).transpose()) * (grad_v0 - grad_x_prev)).norm() / ((grad_v0 - grad_x_prev).squaredNorm());

    v_neu = x_prev + alpha*Descent<TS,TP,NS,NP>::descent_direction();
    nlsys.x() = v_neu;
    x_prev = v0;
    grad_cur = dgdx(nlsys);
    v0 = v_neu;
  }
	return v0;
 }

  	template<typename TS, typename TP, int NS, int NP>
	TS Descent< TS,  TP,  NS,  NP>::descent_direction(Linesearch<TS,TP,NS,NP>& ls){
		const typename Eigen::VectorXd gradient(NS);
		TS v = ls.get_v0();
		gradient = gradient(NS, System<TS, TP, NS, NP>::x(), gradient);
		return -gradient; 	
	}

  template<typename TS, typename TP, int NS, int NP>	
Stepsize_control<TS, TP,NS,NP>::Stepsize_control(){}

/*template<typename TS, typename TP, int NS, int NP>
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
   
 */
  }


int main(){
	

	
  	using T=double; // definiere T mit dco adjoint mode
	
	
	Toy::System<T,T> nlsys;
  	Linear::Solver_LR<T,Toy::NS> lsol;
  	Nonlinear::Solver_Newton<T,T,Toy::NS,Toy::NP> nlsol(lsol,1e-7);
  	nlsys.x()(0)=10;
  	nlsys.p()(0)=2;

	typename Nonlinear::System<T,T,Toy::NS, Toy::NP>::VTS x_initial = nlsys.x();

	Nonlinear::Linesearch< TP,  TP,  Toy::NS,  Toy::NP>::iteration( Nonlinear::System<T,T,Toy::NS, Toy::NP>::VTS x_initial);
	

	return 0;
}
