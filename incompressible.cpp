#include "incompressible.h"

Incompressible::Incompressible()
{

}
int Incompressible::run()
{

    /*
 (𝜌𝑢A)𝑒 − (𝜌𝑢A)𝑤 = 0
*/
    // continuity equationA
    U[1] = U[0]*A[0]/(A[1]);
    // momentum equation
    p[1] = (p[0]*A[0] + Ffr)/A[1];

    // energy equation
    Uct = (U[0] + U[1])/ 2.0;
    T[1] = (Ffr*Uct + Q + (rho[0]*Cv*T[0]*U[0]*A[0]))/(rho[1]*Cv*U[1]*A[1]);

    h[1] = T[1]*(Cv+R) + U[1]*U[1]/2.0;

    std::stringstream ss;
    ss <<"Velocity at outlet: "<< U[1] <<" m/s" << std::endl;
    ss <<"Static Pressure at outlet: "<< p[1] <<" Pa" << std::endl;
    ss <<"Temperature at outlet: "<< T[1] <<" K" << std::endl;
    ss <<"Total enthalpy at outlet: "<< h[1] <<" J/kg" << std::endl;
    std::cout << ss.str() << std::endl;
    return 0;
}
