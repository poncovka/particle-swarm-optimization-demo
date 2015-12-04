#ifndef DRIVER_H
#define DRIVER_H

#include <QObject>
#include "optimization.h"

class Driver : public QObject
{
    Q_OBJECT

private:
    Optimization optimization;
    Driver();

public:
    static Driver* getInstance();

    Function getFitnessFunction();
    Particles* getParticles();
    Particle* getBestParticle();
    Point getBestPosition();

signals:
    void updated();

public slots:
    void addParticle(const Point &p);
    void generateParticles();
    void removeParticles();

    void setDrawing(bool flag);

    void doStep();
    void runAnimation();
    void stopAnimation();
    void computeOptimum();

};

#endif // DRIVER_H
