#ifndef VALUEINITIALIZATION_H
#define VALUEINITIALIZATION_H
#include<vector>
/*
double Ue: velocity at inlet m/s;
h01: total enthalpy at inlet
double tempInletT = 220 K;
h0e, h0w: enthalpy per unit mass at inlet and outlet J/Kg
pe,pw: static pressure at west face and east face
k: thermal conductivity W/m.k
T0e, T0w : temperature at inlet and outlet.
Ae: Area at the east face, Aw: Area at the east face
rhow]: density at the east and west face
Ffr: frictional force
Q: heat flow
T: temperature at the east and west face
Uct: velocity at center
*/

std::vector<double>U(2,0.0);
std::vector<double>A(2,0.0);
std::vector<double>rho(2,0.0);
std::vector<double>p(2,0.0) ;
std::vector<double>T(2,0.0) ;
std::vector<double>h(2,0.0) ;
double Q = 0.0, q = 0.0, Uct = 0.0;
double k = 0.0;

double Ffr = 0;
void initialize() {
    Uct = (U.at(0)+U.at(1))/2.0;
}


#endif // VALUEINITIALIZATION_H


