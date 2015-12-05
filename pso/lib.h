#ifndef LIB_H
#define LIB_H

#include <string>
#include <iostream>
#include "point.h"

#define DEBUG(str)      std::cerr << "DEBUG " << str << std::endl;
#define IFDEBUG(x)      x;

namespace Lib {

    double abs(double v);
    bool isNearby(double v1, double v2, double r);

    double getRandomNumber(double min, double max);
    Point getRandomPoint(Point &min, Point &max, int dim);

    template <typename T> std::string str(T item) {
        std::ostringstream stream;
        stream << item;
        return stream.str();
    }

}
#endif // LIB_H
