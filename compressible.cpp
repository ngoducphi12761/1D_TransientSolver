#include "compressible.h"

Compressible::Compressible(int initTime)
{
    this->time = initTime;

    rhoP =0.0, rhoP0 =0.0, UP =0.0, UP0 = 0.0, CFL = 0.0;
    volume = length*A[2], TP0 =0.0, TP = 0.0,pP =0.0, pP0 =0.0, Uct =0.0;
    TP0 = TPInit;
    Uct = (U[0] + U[1])/2.0;
    rhoP0 = (rho[0]+rho[1])/2.0;
    UP0 = (U[0]+U[1])/2.0;
    pP0 = (p[0]+p[1])/2.0;
}
Compressible::~Compressible(){

}
int Compressible::run()
{
    std::cout << "========calculating======" <<std::endl;
    while (loop(deltaT)) {
        // calculating Continuity equation
        calculateContinuity();
        // momentum equation
        calculateMomentum();
        // energy equation
        calculateEnergy();
        // updated values
        updatePhysicalProperties();
        // logOutput
        logOutput();
    }

    //write file
    writeResultsToFile();
    std::cout << "========calculation end======" <<std::endl;
    return 0;
}
bool Compressible::loop(double time){
    this->time +=time;

    return (this->time <= endTime)? true:false;
}
std::string Compressible::generateFilename() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d_%H-%M-%S");
    return "simulation_results_" + ss.str() + ".txt";
}
void Compressible::calculateContinuity() {
    //  rhoP0 = (rho[0]+rho[1])/2.0;
    // continuity equation
    rhoP = deltaT / volume * (rho[0] * U[0] * A[0] - rho[1] * U[1] * A[1]) + rhoP0;
}
void Compressible::calculateMomentum() {

    UP = deltaT / volume * (-A[0] * (p[1] - p[0]) - Ffr - ((rho[1] * U[1] * U[1] * A[1]) - (rho[0] * U[0] * U[0] * A[0]))) + rhoP0 * UP0;
    UP /= rhoP;
    /*
        UP = deltaT/volume*((-A[0]*(p[1]-p[0])-Ffr-((rho[1]*U[1]*U[1]*A[1])-(rho[0]*U[0]*U[0]*A[0]))))
                + rhoP0*UP0;
        UP = UP/rhoP;*/

}
void Compressible::calculateEnergy() {

    //    Uct = UP;

    TP = rhoP0 * Cv * TP0 * volume / deltaT - (rho[1] * Cv * T[1] * A[1] * U[1] - rho[0] * Cv * T[0] * A[0] * U[0])
            - pP0 * (U[1] * A[1] - U[0] * A[0]) + (k * A[1] * (T[1] - TP0) * 2 / length) - (k * A[0] * (TP0 - T[0]) * 2 / length)
            + Ffr * Uct;
    TP /= (rhoP * Cv) * volume /deltaT;
}

void Compressible::updatePhysicalProperties() {
    double Tcal = 0.0, rhoCal = 0.0, UCal =0.0, pCal=0.0;
    //   UP = (U[1] + U[0])/2.0*(1-relaxationFactor) + UP*relaxationFactor;
    Tcal =(Q*length)/(2*k) + TP;
    Tcal = Tcal + fixedGradientTemperatureValue*2/length;
    //  TP0 = (T[0] + T[1]) / 2.0;
    //  TP0 = TP;
    pP = rhoP * R * TP;

    //  pP = rhoP * R * TP;
    //  pCal = 2 * pP - p[0];
    pCal = pP + fixedGradientPressureValue*2/length;
    //    UCal = 2 * UP - U[0];
    UCal =  UP + fixedGradientVelocityValue*2/length;;
    //   TP0  = TP0*(1-relaxationFactor) + TP*relaxationFactor;
    T[1] = T[1]*(1-relaxationFactor) + Tcal*relaxationFactor;
    U[1] = U[1]*(1-relaxationFactor) + UCal*relaxationFactor;
    p[1] = p[1]*(1-relaxationFactor) + pCal*relaxationFactor;
    rho[1] = rho[1]*(1-relaxationFactor) + rhoP*relaxationFactor;
    h[1] = T[1] * (Cv + R) + U[1] * U[1] / 2.0;
 //   rho[1] = p[1] / (R * T[1]);
    rhoP0 = rhoP;
    //    Uct = (U[0] + U[1])/2.0;
    //   Uct = (U[1]+U[0])/2.0;
    Uct = (U[1] +U[0])/2.0;
    UP0 = U[1];
    pP0 =p[1];
    //   TP = (T[0] + T[1])/2.0;
    TP0 = T[1];
    CFL = Uct*deltaT/length;

}
void Compressible::logOutput() {
    CFL = Uct * deltaT / length;
    ss <<"time: "<< this->time <<"; CFL = "<< CFL <<"; density at outlet: "<< rho[1] <<" kg/m^3" << std::endl;
    ss <<"time: "<< this->time <<"; CFL = "<< CFL <<"; Velocity at center volume: "<< UP <<" m/s" << std::endl;
    ss <<"time: "<< this->time <<"; CFL = "<< CFL <<"; Velocity at outlet: "<< U[1] <<" m/s" << std::endl;
    ss <<"time: "<< this->time <<"; CFL = "<< CFL <<"; Static Pressure at outlet: "<< p[1] <<" Pa" << std::endl;
    ss <<"time: "<< this->time <<"; CFL = "<< CFL <<"; Temperature at inlet: "<< T[0] <<" K" << std::endl;
    ss <<"time: "<< this->time <<"; CFL = "<< CFL <<"; Temperature at outlet: "<< T[1] <<" K" << std::endl;
    ss <<"time: "<< this->time <<"; CFL = "<< CFL <<"; Total enthalpy at outlet: "<< h[1] <<" J/kg" << std::endl;
}
void Compressible::writeResultsToFile() {
    std::string filePath = "C:\\Users\\DELL\\Documents\\applicationTask\\" + generateFilename();
    std::ofstream file(filePath, std::ios::out | std::ios::app);
    if (file.is_open()) {
        std::cout << ss.str() << std::endl;
        file << ss.str();
        ss.clear();
        file.close();
    } else {
        std::cerr << "Failed to open file for writing." << std::endl;
    }
}
void Compressible::updateUnderRelaxation(){
    T[1] =(Q*length)/(2*k) + TP;
    //  TP0 = (T[0] + T[1]) / 2.0;
    TP0 = TP;
    pP = rhoP * R * TP0;
    p[1] = 2 * pP - p[0];
    rho[1] = p[1] / (R * T[1]);
    U[1] = 2 * UP - U[0];
    h[1] = T[1] * (Cv + R) + U[1] * U[1] / 2.0;
    CFL = Uct*deltaT/length;
}
