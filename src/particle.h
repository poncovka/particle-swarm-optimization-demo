#ifndef PARTICLE_H
#define PARTICLE_H

#include <string>
#include <list>

#include "point.h"

// declare class
class Particle;

// type for list of particles
typedef std::list<Particle*> Particles;

// define class
class Particle {

public:
    // current state
    Point position;
    Point velocity;
    double value;

    // best solution
    Point bestPosition;
    double bestValue;

    // future state
    Point nextPosition;

    // previous state
    Point vw, vp, vg;

public:
    Particle(const Point& p, const Point& v);
    std::string str();
};

#endif // PARTICLE_H
