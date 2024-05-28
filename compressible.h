#ifndef COMPRESSIBLE_H
#define COMPRESSIBLE_H
#include <sstream>
#include <fstream>
#include <chrono>
#include <iostream>
#include <iomanip>

#include "initializationvalues.h"

class Compressible
{
private:
   double time;
   double rhoP , rhoP0 , UP , UP0 , CFL;
   double volume , TP0 ,pP , pP0, Uct, TP ;
   std::stringstream ss;
   std::string generateFilename();
   void calculateMomentum();
   void calculateContinuity();
   void calculateEnergy();
   void updatePhysicalProperties();
   void logOutput();
   void writeResultsToFile();
   bool loop(double deltaT);
   void updateUnderRelaxation();
public:
    Compressible(int initTime);
    ~Compressible();
    int run();
};

#endif // COMPRESSIBLE_H
