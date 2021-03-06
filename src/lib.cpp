#include "lib.h"
#include <stdlib.h>

namespace Lib {

    double abs(double v) {
        return (v < 0) ? -v : v;
    }

    bool isNearby(double v1, double v2, double r) {
        return abs(v1 - v2) <= r;
    }

    double getRandomNumber(double min, double max) {
        return min + ((double)rand()/(double)RAND_MAX) * (max-min);
    }

    Point getRandomPoint(Point &min, Point &max, int dim) {

        Point point;

        for(int i = 0; i < dim; i++ ) {
            point.coordinate(i) = getRandomNumber(min.coordinate(i),max.coordinate(i));
        }

        return point;
    }

    double getUnit(double value) {

        double unit = 1;
        value = abs(value);

        if (value > 10) {

            while (value > 10) {
                value /=10;
                unit *= 10;
            }

        }
        else {
            while (value < 1) {
                value *=10;
                unit /= 10;
            }
        }

        //DEBUG(unit);
        return unit;
    }

}


