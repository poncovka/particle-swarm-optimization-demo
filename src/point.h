#ifndef POINT_H
#define POINT_H

#include <string>

class Point {

public:
    static const int MAXDIM = 2;

private:
    double coordinates[MAXDIM];

public:
    Point(double x = 0, double y=0);
    void set(double x = 0, double y=0);
    void plus(Point& p);

    double* getCoordinates();
    double& coordinate(int i);
    double& x();
    double& y();

    std::string str();

};

#endif // POINT_H
