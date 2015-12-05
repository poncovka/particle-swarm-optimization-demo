#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "point.h"

// type for pointer to fitness function
typedef double (*Function)(Point& p);

namespace FitnessFunction {

    double sinx(Point &p);
    double absx(Point &p);

}

#endif // FUNCTIONS_H
