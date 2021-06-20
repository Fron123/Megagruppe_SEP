

namespace Nonlinear{
	
	template<typename TS, typename TP, int NS, int NP>
	class Descent{
	public:
		TS descent_direction(Linesearch<TS,TP,NS,NP>&);
	};
}
