#include "driver.h"
#include "functions.h"
#include "lib.h"

#include <QLocale>

Driver::Driver() {}

Driver *Driver::getInstance() {
    static Driver instance;
    return &instance;
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

Function Driver::getFitnessFunction() {
    return optimization.fitness;
}

Particles* Driver::getParticles() {
    return &(optimization.particles);
}

Point Driver::getBestPosition() {
    return optimization.bestPosition;
}

double Driver::getBestValue() {
    return optimization.bestValue;
}

int Driver::getCurrentIteration() {
    return optimization.iteration;
}

int Driver::getParticlesNumber() {
    return optimization.particles.size();
}

int Driver::getMaxIterations() {
    return optimization.maxIteration;
}

double Driver::getOmega() {
    return optimization.omega;
}

double Driver::getCp() {
    return optimization.cp;
}

double Driver::getCg() {
    return optimization.cg;
}


void Driver::updateMaxIterations(const QString& text) {

    bool ok;
    int x = text.toInt(&ok);

    if (ok) {
        optimization.maxIteration = x;
        DEBUG("DRIVER : maxIteration = " << x)
    }

}

void Driver::updateOmega(const QString& text) {

    bool ok;
    double x = text.toDouble(&ok);

    if (ok) {
        optimization.omega = x;
        DEBUG("DRIVER : omega = " << x)
    }

}


void Driver::updateCp(const QString& text) {

    bool ok;
    double x = text.toDouble(&ok);

    if (ok) {
        optimization.cp = x;
        DEBUG("DRIVER : cp = " << x)
    }

}

void Driver::updateCg(const QString& text) {

    bool ok;
    double x = text.toDouble(&ok);

    if (ok) {
        optimization.cg = x;
        DEBUG("DRIVER : cg = " << x)
    }

}

