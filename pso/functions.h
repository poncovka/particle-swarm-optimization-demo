#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "point.h"
#include <string>

// pointer to fitness function
typedef double (*Function)(Point& p);

// fitness functions
namespace FitnessFunction {

    Function get(std::string name);
    int getIndex(Function f);

    double sinx(Point &p);
    double absx(Point &p);

    const int MAX = 2;
    const std::string names [MAX]  = {"sin(x)", "abs(x)"};
    const Function functions [MAX] = {sinx, absx};

}

// select fitness function by name


#endif // FUNCTIONS_H
