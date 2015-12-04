#include "driver.h"
#include "functions.h"

Driver::Driver() {}

Driver *Driver::getInstance() {
    static Driver instance;
    return &instance;
}

Function Driver::getFitnessFunction() {
    return optimization.fitness;
}

Particles* Driver::getParticles() {
    return &(optimization.particles);
}

Point Driver::getBestPosition() {
    return optimization.bestPosition;
}

void Driver::addParticle(const Point& p) {
    optimization.addParticle(p);
    emit changedParticles();
}

void Driver::generateParticles() {
    //TODO
}

void Driver::removeParticles() {
    optimization.removeParticles();
    emit changedParticles();
}

void Driver::selectParticle(Particle *particle) {
    emit changedSelected(particle);
}

void Driver::doStep() {
    optimization.moveParticleSwarm();
    emit changedParticles();
}

void Driver::runAnimation() {
    //TODO
}

void Driver::stopAnimation() {
    //TODO
}

void Driver::setDrawing(bool flag) {
    //TODO
}

void Driver::computeOptimum() {
    //TODO
}
