#include <iostream>
#include "incompressible.h"
#include "initializationvalues.h"
#include "compressible.h"
using namespace std;

int main()
{
    initializationValues::initialize();
    Compressible com(0);
    com.run();
 //   Incompressible::run();
    return 0;
}
