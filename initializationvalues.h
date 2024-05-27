#ifndef INITIALIZATIONVALUES_H
#define INITIALIZATIONVALUES_H
#include <vector>
extern std::vector<double> U;
extern std::vector<double> A;
extern std::vector<double> rho;
extern std::vector<double> p;
extern std::vector<double> T;
extern std::vector<double> h;
extern double Q, q, Uct, k, Ffr, Cv, R, endTime, length, deltaT;
class initializationValues
{

public:
    static void initialize();
    initializationValues();
};

#endif // INITIALIZATIONVALUES_H
