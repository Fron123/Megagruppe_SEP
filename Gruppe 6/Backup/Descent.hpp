

namespace Nonlinear{
	
	template<typename TS, typename TP, int NS, int NP>
	public class Descent extends Linesearch{
	public:
		TS descent_direction(Linesearch<TS,TP,NS,NP>&);
	};
}
