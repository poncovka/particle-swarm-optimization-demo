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
    double weierstrass(Point &p);
    double easom(Point &p);
    double ackley(Point& p);
    double holder(Point& p);

    const int MAX = 6;
    const std::string names [MAX]  = {"sin(x)", "-abs(x)", "Easom function", "Holder table function", "Ackley function", "Weierstrass function"};
    const Function functions [MAX] = {sinx, absx, easom, holder, ackley, weierstrass};

}

// select fitness function by name


#endif // FUNCTIONS_H
