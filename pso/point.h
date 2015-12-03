#ifndef POINT_H
#define POINT_H

#include <QPoint>
#include <string>
#include <sstream>

class Point {

public:
    static const int MAXDIM = 3;

private:
    double coordinates[3];

public:
    Point(double x = 0, double y=0, double z=0);
    void set(double x = 0, double y=0, double z=0);
    void plus(Point& p);

    double* getCoordinates();
    double& coordinate(int i);
    double& x();
    double& y();
    double& z();

    std::string str();

};

#endif // POINT_H
