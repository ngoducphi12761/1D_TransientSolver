#include "initializationvalues.h"
// Definitions of the external variables (define them in one .cpp file)
std::vector<double> U(2,0.0);
std::vector<double> A(2,0.0);
std::vector<double> rho(2,1.227);
std::vector<double> p(2,0.0);
std::vector<double> T(2,0.0);
std::vector<double> h(2,0.0);
double Q = 0.0, q = 0.0, Uct = 0.0, k = 0.0, Ffr = 0.0, Cv = 0.0, R = 0.0, endTime =0.0;
double length = 0.0, deltaT = 0.0;
initializationValues::initializationValues()
{


}
void initializationValues::initialize() {
    Cv = 717.4; //J/(kg.K)
    R = 8.314/29*1000; //= 287 J/mol.K -> J/kg.K
    h[0] = 301426.8966; // J/kg
    U[0] = 20.0; // m/s
    T[0] = (h[0] -U[0]*U[0]/2)/(Cv+R);
    U[1] =U[0];
    T[1] = T[0];
    // for steel
    A[0]= 25.0 ;// m^2
    A[1]= 25.0 ;// m^2
 //   p[0] = rho[0]*R*T[0]; //Pa
    p[0] = 105550.7; //Pa
    p[1] = p[0]; //Pa
    rho[0] = p[0]/(R*T[0]);
    rho[1] = p[1]/(R*T[1]);

    k = 50.0; // W/mK
 //   Q = 5000.0; // W/m^2
     Q = 1000.0; // W/m^2
//   Ffr = 100.0; //N
    Ffr = 0.0; //N

    deltaT = 0.01;
    endTime =0.02;
    A.push_back(A[0]);
    length = 0.02;

}
