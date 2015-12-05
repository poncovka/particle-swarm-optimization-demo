#include "driver.h"
#include "functions.h"
#include "lib.h"

#include <QLocale>

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

void Driver::doInit() {

    // remove particles
    removeParticles();

    // init configuration
    optimization.init();

    // signals
    emit changedParticles();
    emit changedConfiguration();
}

void Driver::addParticle(const Point& p) {

    optimization.addParticle(p);
    emit changedParticles();

}

void Driver::generateParticles() {

    // generate particles
    for (int i = 0; i < 10; i++) {

        Point size = view.getPt(view.size);
        Point p(Lib::getRandomNumber(-size.x(), size.x()), 0);

        optimization.addParticle(p);
    }

     emit changedParticles();
}

void Driver::removeParticles() {

    // unselect particle
    view.setSelectedParticle(NULL);

    // remove particles
    optimization.removeParticles();

    // signal
    emit changedParticles();
    emit changedSelected(NULL);
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

void Driver::resizeView(int w, int h) {
    view.setSize(w, h);
    emit changedView();
}

void Driver::clickView(int x, int y) {

    // select particle or create new one
    if (!view.setSelectedParticle(view.currentParticle)) {

        // get position of future particle
        Point position(x, view.center.y());
        view.toPt(position);

        // create new particle
        addParticle(position);
    }

    emit changedView();
}

void Driver::mouseMoveView(int x, int y) {

    Particles* particles = getParticles();
    Particle* particle = view.findParticle(particles, x, y);

    if (view.setCurrentParticle(particle)) {
        emit changedSelected(particle);
        emit changedView();
    }
}

void Driver::wheelView(int orientation) {

    view.setZoom(orientation);
    emit changedView();
}

void Driver::drawView(QPainter& painter) {

    // axis
    view.drawAxis(painter);

    // function
    view.drawFunction(painter);

    // particles
    Particles* particles = getParticles();
    view.drawParticles(painter, particles);

    if (!particles->empty()) {
        view.drawBestPosition(painter, getBestPosition());
        view.drawSelectedParticle(painter);
    }
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

