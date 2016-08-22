#include "point.h"
#include <sstream>
#include <stdexcept>
#include <iomanip>

Point::Point(double x, double y)
{
    set(x,y);
}

void Point::set(double x, double y) {
    coordinates[0] = x;
    coordinates[1] = y;
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

std::string Point::str()
{
    std::ostringstream stream;
    stream << std::setprecision(2);
    stream << "(" << x() << ", "<< y() << ")";
    return stream.str();
}
