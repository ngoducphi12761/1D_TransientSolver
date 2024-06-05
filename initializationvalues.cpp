#include "initializationvalues.h"
// Definitions of the external variables (define them in one .cpp file)
std::vector<double> U(2,0.0);
std::vector<double> A(2,0.0);
std::vector<double> rho(2,1.227);
std::vector<double> p(2,0.0);
std::vector<double> T(2,0.0);
std::vector<double> h(2,0.0);
double Q = 0.0, q = 0.0, Uct = 0.0, k = 0.0, Ffr = 0.0, Cv = 0.0, R = 0.0, endTime =0.0;
double length = 0.0, deltaT = 0.0, relaxationFactor = 0.0, gradientValue =0.0, TPInit =0.0;
double fixedGradientPressureValue = 0.0, fixedGradientTemperatureValue =0.0, fixedGradientVelocityValue =0.0;

initializationValues::initializationValues()
{


}
void initializationValues::initialize() {
    Cv = 717.4; //J/(kg.K)
    R = 8.314/29*1000; //= 287 J/mol.K -> J/kg.K
    h[0] = 301426.8966; // J/kg
    // Velocity
    U[0] = 20.0; // m/s
    U[1] =U[0];
    // Cross section
    A[0]= 25.0 ;// m^2
    A[1]= 25.0 ;// m^2
    A.push_back(A[0]);
    // Thermal conductivity
    k = 50.0; // W/mK
    // Heat Flow
     Q = 50.0; // W/m^2
    // Frictional force
    Ffr = 0.0; //N
    // Initialize calculated time
    deltaT = 0.01;
    endTime =0.1;
    // length of a unit control volume
    length = 1.0;
    // under relxation factor
    relaxationFactor = 1.0;
    //fixedGradient for outlet boundary condition
    fixedGradientPressureValue = .0;
    fixedGradientTemperatureValue =0.15;
    fixedGradientVelocityValue = 0.1;
    // initialize Temperature for inlet and outlet at time = 0;
    T[0] = (h[0] -U[0]*U[0]/2)/(Cv+R);
    TPInit =(Q*length)/(2*k) + T[0];
    T[1]=(Q*length)/(2*k) + TPInit;
    // initialize Pressure for inlet and outlet at time = 0;
    p[0] = 105550.7; //Pa
    p[1] = p[0]; //Pa
    // initialize Density for inlet and outlet at time = 0;
    rho[0] = p[0]/(R*T[0]);
    rho[1] = p[1]/(R*T[1]);

}
