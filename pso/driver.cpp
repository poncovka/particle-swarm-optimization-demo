#include "driver.h"
#include "functions.h"
#include "lib.h"

#include <QLocale>

Driver::Driver() {

    // init timer
    view.timer = new QTimer(this);

    // call do step
    connect(view.timer, SIGNAL(timeout()), this, SLOT(animateStep()));

}

Driver *Driver::getInstance() {
    static Driver instance;
    return &instance;
}

double Driver::getCp() {
    return optimization.cp;
}

double Driver::getCg() {
    return optimization.cg;
}

double Driver::getOmega() {
    return optimization.omega;
}

double Driver::getMaxVelocity() {
    return optimization.maxVelocity;
}

double Driver::getBestValue() {
    return optimization.bestValue;
}

int Driver::getCurrentIteration() {
    return optimization.iteration;
}

int Driver::getMaxIterations() {
    return optimization.maxIteration;
}

int Driver::getParticlesNumber() {
    return optimization.particles.size();
}

Particles* Driver::getParticles() {
    return &(optimization.particles);
}

Point Driver::getBestPosition() {
    return optimization.bestPosition;
}

Function Driver::getFitnessFunction() {
    return optimization.fitness;
}

void Driver::doRestart() {
    // stop for sure
    stopAnimation();

    // restart optimization
    optimization.restart();

    // signals
    emit changedParticles();
    emit changedConfiguration();
}

void Driver::setDefault() {

    // init configuration
    optimization.init();

    // signals
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
    // stop for sure
    stopAnimation();

    // unselect particle
    view.setSelectedParticle(NULL);

    // remove particles
    optimization.removeParticles();

    // signal
    emit changedParticles();
    emit changedSelected(NULL);
}

void Driver::doStep() {    
    // stop for sure
    stopAnimation();

    // move particles
    optimization.moveParticleSwarm();

    // signal
    emit changedParticles();

    // stop timer
    if (optimization.iteration >= optimization.maxIteration) {
        view.timer->stop();
    }
}

void Driver::runAnimation() {

    // set time
    time = 0;

    // start timer
    view.timer->start(100);
}

void Driver::stopAnimation() {

    // stop timer
    view.timer->stop();

    // finish step
    finishStep();
}

void Driver::animateStep() {

    // set delta time
    double dt = 0.1;
    time += dt;

    // animate step
    if (time <= optimization.dt) {

        // get particles
        Particles* particles = &optimization.particles;

        // move particles
        for (Particles::iterator i = particles->begin(); i != particles->end(); i++) {
            Particle *particle = (*i);
            particle->position = optimization.computeNextPosition(*particle, dt);
        }

        // signal
        emit changedParticles();
     }
    // finish step
    else {
        finishStep();
    }

}

void Driver::finishStep() {

    if (time > 0) {

        // get particles
        Particles* particles = &optimization.particles;

        // calculate new values
        for (Particles::iterator i = particles->begin(); i != particles->end(); i++) {

            Particle *particle = (*i);
            particle->position = particle->nextPosition;

            particle->velocity = optimization.computeNextVelocity(*particle);
            particle->value = optimization.computeFitness(*particle);
            particle->nextPosition = optimization.computeNextPosition(*particle, optimization.dt);

            if (optimization.updateLocalBest(*particle)) {
                optimization.updateGlobalBest(*particle);
            }
        }

        // add iteration
        optimization.iteration++;

        // reset time
        time = 0;

        // signal
        emit changedParticles();
        emit changedView();
    }
}

void Driver::computeOptimum() {
    // stop for sure
    stopAnimation();

    for (int i = optimization.iteration; i < optimization.maxIteration; i++) {
        optimization.moveParticleSwarm();
    }

    emit changedParticles();
}

void Driver::resizeView(int w, int h) {
    view.setSize(w, h);
    emit changedView();
}

void Driver::clickView(int x, int) {

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


void Driver::updateCp(const QString& text) {
    bool ok;
    double x = text.toDouble(&ok);

    if (ok) {
        optimization.cp = x;
    }
}

void Driver::updateCg(const QString& text) {
    bool ok;
    double x = text.toDouble(&ok);

    if (ok) {
        optimization.cg = x;
    }
}

void Driver::updateOmega(const QString& text) {
    bool ok;
    double x = text.toDouble(&ok);

    if (ok) {
        optimization.omega = x;
    }
}

void Driver::updateMaxVelocity(const QString& text) {
    bool ok;
    double x = text.toDouble(&ok);

    if (ok) {
        optimization.maxVelocity = x;
    }
}

void Driver::updateMaxIterations(const QString& text) {
    bool ok;
    int x = text.toInt(&ok);

    if (ok) {
        optimization.maxIteration = x;
    }
}



