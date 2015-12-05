#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "point.h"

// pointer to fitness function
typedef double (*Function)(Point& p);

// fitness functions
namespace FitnessFunction {

    double sinx(Point &p);
    double absx(Point &p);

}

#endif // FUNCTIONS_H
