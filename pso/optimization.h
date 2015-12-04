#ifndef OPTIMIZATION_H
#define OPTIMIZATION_H

#include <list>
#include <string>
#include "particle.h"

//---------------------------------------------

// type for pointer to fitness function
typedef double (*Function)(Point& p);

// type for list of particles
typedef std::list<Particle*> Particles;

//---------------------------------------------

class Optimization {

public:

    // fitness function
    Function fitness;

    // particles
    Particles particles;

    // kognitive factor
    double cp;

    // social factor
    double cg;

    // inertia factor
    double omega;

    // delta time
    double dt;

    // number of iterations
    int maxIteration;

    // current iteration
    int iteration;

    // best solution
    Point bestPosition;

    // best values
    double bestValue;

    // velicity boundaries
    Point velocity_max;
    Point velocity_min;

public:
    Optimization();
    ~Optimization();

    void addParticle(const Point &position);
    void moveParticle(Particle& particle);
    void removeParticles();

    void moveParticleSwarm();

    double computeFitness(Particle &particle);
    Point computeNextPosition(Particle &particle);
    Point computeNextVelocity(Particle &particle);

    double getRandomNumber(double min, double max);
    Point getRandomPoint(Point &min, Point &max, int dim);

    bool updateLocalBest(Particle& particle);
    bool updateGlobalBest(Particle& particle);


    std::string str();
};

#endif // OPTIMIZATION_H
