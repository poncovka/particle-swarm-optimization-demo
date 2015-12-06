#include "functions.h"
#include "lib.h"
#include <cmath>

#define PI 3.1415926535897

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


    double easom(Point& p) {
        return -cos(p.x()) * exp(-pow(p.x() - PI,2));
    }

    double ackley(Point& p) {
        const double a = 20;
        const double b = 0.2;
        const double c = 2*PI;
        const int d = 1;

        return -(-a*exp(-b*sqrt(1/d*pow(p.x(), 2))) - exp(1/d*cos(c*p.x())) + a + exp(1));
    }

    double holder(Point& p) {
        double y = 9.66459;
        return -Lib::abs(sin(p.x())*cos(y)*exp(Lib::abs(1-(sqrt(pow(p.x(),2)+pow(y,2)))/PI)));
    }

    double weierstrass(Point& p) {

        const double a = 2;
        const int kmax = 10;

        double result = 0;

        for (int k = 1; k <= kmax; k++) {
            result += (sin(PI * pow(k,a) * p.x())) / (PI * pow(k,a));
        }

        DEBUG(result);
        return result;
    }
}



