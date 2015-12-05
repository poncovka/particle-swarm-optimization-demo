#ifndef OPTIMIZATION_H
#define OPTIMIZATION_H

#include <string>
#include "particle.h"
#include "functions.h"

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

    void init();
    void restart();

    void addParticle(const Point &position);
    void removeParticles();

    void moveParticle(Particle& particle);
    void moveParticleSwarm();

    double computeFitness(Particle &particle);
    Point computeNextPosition(Particle &particle, double dt);
    Point computeNextVelocity(Particle &particle);

    double getRandomNumber(double min, double max);
    Point getRandomPoint(Point &min, Point &max, int dim);

    bool updateLocalBest(Particle& particle);
    bool updateGlobalBest(Particle& particle);


    std::string str();
};

#endif // OPTIMIZATION_H
