#include "point.h"
#include <iostream>
#include <stdexcept>


Point::Point(double x, double y, double z)
{
    set(x,y,z);
}

void Point::set(double x, double y, double z) {
    coordinates[0] = x;
    coordinates[1] = y;
    coordinates[2] = z;
}

void Point::plus(Point& p) {
    for (int i = 0; i < Point::MAXDIM; i++) {
        coordinates[i] += p.coordinate(i);
    }
}

double* Point::getCoordinates() {
    return coordinates;
}

double& Point::coordinate(int i) {

    if (i < 0 || i >= Point::MAXDIM) {
        throw std::out_of_range("The required dimension is out of boundaries.");
    }

    return (coordinates[i]);
}

double& Point::x() {
    return coordinates[0];
}

double& Point::y() {
    return coordinates[1];
}

double& Point::z() {
    return coordinates[2];
}

std::string Point::str()
{
    std::ostringstream stream;
    stream << "(" << x() << ", "<< y() << ", "<< z() << ")";
    return stream.str();
}
