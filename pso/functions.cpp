#include "functions.h"
#include <cmath>

namespace FitnessFunction {

    Function get(std::string name) {

        for (int i = 0; i < MAX; i++) {
            if (name == names[i]) {
                return functions[i];
            }
        }

        return NULL;
    }

    int getIndex(Function f) {

        for (int i = 0; i < MAX; i++) {
            if (f == functions[i]) {
                return i;
            }
        }

        return -1;
    }

    double sinx(Point& p) {
        return sin(p.x());
    }

    double absx(Point& p) {
        return (p.x() > 0) ? -p.x() : p.x();
    }
}



