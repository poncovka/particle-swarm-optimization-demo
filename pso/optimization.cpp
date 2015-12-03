#include "optimization.h"
#include "functions.h"

#include <iostream>
#include <stdlib.h>

Optimization::Optimization() {

    dt = 1;
    cg = 2.05;
    cp = 2.05;
    omega = 0.4;

    maxIteration = 10;
    iteration = 0;
    bestPosition = Point();

    fitness = FitnessFunction::absx;

    dimensions = 1;

    double V = 3;
    velocity_min = Point(-V,-V);
    velocity_max = Point(V,V);
}

Optimization::~Optimization() {
    removeParticles();
}

void Optimization::addParticle(const Point& position) {

    // generate velocity
    Point velocity = getRandomPoint(velocity_min, velocity_max, 1);

    // create particle
    Particle& particle = *(new Particle(position, velocity));

    particle.value = computeFitness(particle);
    particle.bestValue = particle.value;
    particle.bestPosition = particle.position;
    particle.nextPosition = computeNextPosition(particle);

    // check if this is the first particle
    bool first = particles.empty();

    // add new particle
    particles.push_back(&particle);

    // update best
    if (first) {
        bestPosition = particle.bestPosition;
        bestValue = particle.bestValue;
    }
    else {
        updateGlobalBest(particle);
    }
}

void Optimization::moveParticle(Particle& particle) {

    // compute new values
    Point nextPosition = computeNextPosition(particle);
    Point nextVelocity = computeNextVelocity(particle);

    // move
    particle.position = nextPosition;
    particle.velocity = nextVelocity;

    // calculate fitness
    particle.value = computeFitness(particle);

    // calculate next position
    particle.nextPosition = computeNextPosition(particle);


    // update best solution
    if(updateLocalBest(particle)) {
        updateGlobalBest(particle);
    }
}

void Optimization::moveParticleSwarm() {

    for(Particles::iterator i = particles.begin(); i != particles.end(); i++) {
        Particle* particle = (*i);
        moveParticle(*particle);
    }

}

void Optimization::removeParticles() {

    while(!particles.empty()) {
        Particle * p = particles.front();
        particles.pop_front();
        delete p;
    }
}


double Optimization::computeFitness(Particle &particle) {
    return (!fitness) ? (0.0/0.0) : fitness(particle.position);
}

Point Optimization::computeNextPosition(Particle &particle) {

    // get parameters
    double* x = particle.position.getCoordinates();
    double* v = particle.velocity.getCoordinates();

    // prepare new position vector
    Point point;
    double* new_x = point.getCoordinates();

    for(int i = 0; i < Point::MAXDIM; i++ ) {

        // compute new position
        new_x[i] = x[i] + v[i] * dt;
    }

    return point;
}

Point Optimization::computeNextVelocity(Particle &particle) {

    // generate random parameters
    double rp = getRandomNumber(0,1);
    double rg = getRandomNumber(0,1);

    // get parameters
    double* x             = particle.position.getCoordinates();
    double* v             = particle.velocity.getCoordinates();
    double* x_best        = particle.bestPosition.getCoordinates();
    double* x_global_best = bestPosition.getCoordinates();

    // prepare velocity vectors
    double* v_w            = particle.vw.getCoordinates();
    double* v_p            = particle.vp.getCoordinates();
    double* v_g            = particle.vg.getCoordinates();

    // prepare new velocity vector
    Point point;
    double* new_v         = point.getCoordinates();

    for(int i = 0; i < Point::MAXDIM; i++ ) {

        // compute velocity vectors
        v_w[i] = omega * v[i];
        v_p[i] = cp * rp * (x_best[i] - x[i]);
        v_g[i] = cg * rg * (x_global_best[i] - x[i]);

        // compute sum of the velocity vectors
        new_v[i] = v_w[i] + v_p[i] + v_g[i];
    }

    return point;
}

double Optimization::getRandomNumber(double min, double max) {
    return min + ((double)rand()/(double)RAND_MAX) * (max-min);
}

Point Optimization::getRandomPoint(Point &min, Point &max, int dim) {

    Point point;

    for(int i = 0; i < dim; i++ ) {

        point.coordinate(i) = getRandomNumber(min.coordinate(i),max.coordinate(i));
    }

    return point;
}


bool Optimization::updateLocalBest(Particle& particle) {

    if (particle.value > particle.bestValue) {
        particle.bestValue = particle.value;
        particle.bestPosition = particle.position;
        return true;
    }

    return false;
}

bool Optimization::updateGlobalBest(Particle& particle) {

    if (particle.bestValue > bestValue) {
        bestValue = particle.bestValue;
        bestPosition = particle.bestPosition;
        return true;
    }

    return false;
}

std::string Optimization::str()
{
    std::stringstream stream;
    stream << "Optimization";
    return stream.str();
}




