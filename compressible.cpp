#include "compressible.h"

Compressible::Compressible(int initTime)
{
    this->time = initTime;

    rhoP =0.0, rhoP0 =0.0, UP =0.0, UP0 = 0.0, CFL = 0.0;
    volume = length*A[2],TP = 0.0, TP0 = 0.0,pP =0.0, pP0 =0.0, Uct =0.0;
    TP0 = (T[0] + T[1])/2.0;
    Uct = (U[0] + U[1])/2.0;
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
    rhoP0 = (rho[0]+rho[1])/2.0;
    // continuity equation
    rhoP = deltaT / volume * (rho[0] * U[0] * A[0] - rho[1] * U[1] * A[1]) + rhoP0;
}
void Compressible::calculateMomentum() {
    UP0 = (U[0]+U[1])/2.0;
    UP = deltaT / volume * (-A[0] * (p[1] - p[0]) - Ffr - ((rho[1] * U[1] * U[1] * A[1]) - (rho[0] * U[0] * U[0] * A[0]))) + rhoP0 * UP0;
    UP /= rhoP;
    /*
        UP = deltaT/volume*((-A[0]*(p[1]-p[0])-Ffr-((rho[1]*U[1]*U[1]*A[1])-(rho[0]*U[0]*U[0]*A[0]))))
                + rhoP0*UP0;
        UP = UP/rhoP;*/

}
void Compressible::calculateEnergy() {
    pP0 = (p[0]+p[1])/2.0;
    //    Uct = UP;

    TP = rhoP0 * Cv * TP0 * volume / deltaT - (rho[1] * Cv * T[1] * A[1] * U[1] - rho[0] * Cv * T[0] * A[0] * U[0])
            - pP0 * (U[1] * A[1] - U[0] * A[0]) + (k * A[1] * (T[1] - TP0) * 2 / length) - (k * A[0] * (TP0 - T[0]) * 2 / length)
            - Ffr * Uct;
    TP /= (rhoP * Cv) * deltaT / volume;
}

void Compressible::updatePhysicalProperties() {
    T[1] =(Q*length)/(2*k) + TP;
    TP0 = (T[0] + T[1]) / 2.0;
    pP = rhoP * R * TP0;
    p[1] = 2 * pP - p[0];
    rho[1] = p[1] / (R * T[1]);
    U[1] = 2 * UP - U[0];
    h[1] = T[1] * (Cv + R) + U[1] * U[1] / 2.0;
    CFL = Uct*deltaT/length;
    Uct = (U[0] + U[1])/2.0;
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
    std::cout << ss.str() << std::endl;
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
