// von Gruppe5

#include "System.hpp"

namespace System {
template<typename TS, typename TP, int NS, int NP>
System<TS,TP,NS,NP>::System(int ns, int np) : _x(ns), _p(np) {}

template<typename TS, typename TP, int NS, int NP>
int
System<TS,TP,NS,NP>::ns() { return _x.size(); }

template<typename TS, typename TP, int NS, int NP>
int
System<TS,TP,NS,NP>::np() { return _p.size(); }

template<typename TS, typename TP, int NS, int NP>
typename System<TS,TP,NS,NP>::VTS&
System<TS,TP,NS,NP>::x() { return _x; }

template<typename TS, typename TP, int NS, int NP>
typename System<TS,TP,NS,NP>::VTP&
System<TS,TP,NS,NP>::p() { return _p; }

}
