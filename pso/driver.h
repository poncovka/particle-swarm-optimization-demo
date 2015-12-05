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
    double getBestValue();
    int getCurrentIteration();
    int getParticlesNumber();
    int getMaxIterations();
    double getOmega();
    double getCp();
    double getCg();


signals:
    void changedParticles();
    void changedSelected(Particle *particle);

public slots:

    void doStep();
    void runAnimation();
    void stopAnimation();
    void setDrawing(bool flag);
    void computeOptimum();

    void addParticle(const Point &p);
    void generateParticles();
    void removeParticles();
    void selectParticle(Particle *particle);

    void updateMaxIterations(const QString& text);
    void updateOmega(const QString& text);
    void updateCp(const QString& text);
    void updateCg(const QString& text);

};

#endif // DRIVER_H
