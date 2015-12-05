#include "optimization.h"
#include "functions.h"
#include "lib.h"

Optimization::Optimization() {

    init();
}

Optimization::~Optimization() {
    removeParticles();
}

void Optimization::init() {

    dt = 1;
    cg = 2.05;
    cp = 2.05;
    omega = 0.7;

    bestValue = 0;
    bestPosition.set(0,0);

    fitness = FitnessFunction::absx;

    maxIteration = 10000;
    iteration = 0;

    velocity_min.set(-1,-1);
    velocity_max.set(1,1);

}

void Optimization::addParticle(const Point& position) {

    // generate velocity
    Point velocity = Lib::getRandomPoint(velocity_min, velocity_max, 1);

    // create particle
    Particle& particle = *(new Particle(position, velocity));

    particle.value = computeFitness(particle);
    particle.bestValue = particle.value;
    particle.bestPosition = particle.position;
    particle.nextPosition = computeNextPosition(particle);

    // check if firt particle
    bool first = particles.empty();

    // add new particle
    particles.push_back(&particle);

    // update best
    if (first) {
        bestValue = particle.value;
        bestPosition = particle.position;
    }
    else {
        updateGlobalBest(particle);
    }
}

void Optimization::moveParticle(Particle& particle) {

    // compute new values
    particle.position = computeNextPosition(particle);
    particle.velocity = computeNextVelocity(particle);
    particle.value = computeFitness(particle);

    // calculate next position
    particle.nextPosition = computeNextPosition(particle);
}

void Optimization::moveParticleSwarm() {

    // update best found solutions
    for(Particles::iterator i = particles.begin(); i != particles.end(); i++) {
        Particle* particle = (*i);

        if(updateLocalBest(*particle)) {
            updateGlobalBest(*particle);
        }
    }

    // move with every particle
    for(Particles::iterator i = particles.begin(); i != particles.end(); i++) {
        Particle* particle = (*i);

        moveParticle(*particle);
    }

    // update iteration counter
    iteration++;

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
    double rp = Lib::getRandomNumber(0,1);
    double rg = Lib::getRandomNumber(0,1);

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




