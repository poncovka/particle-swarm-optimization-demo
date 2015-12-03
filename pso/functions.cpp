#include "functions.h"
#include <cmath>

namespace FitnessFunction {

double sinx(Point& p) {
    return sin(p.x());
}

double absx(Point& p) {
    return (p.x() > 0) ? -p.x() : p.x();
}

}


