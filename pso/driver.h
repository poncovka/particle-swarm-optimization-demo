#ifndef DRIVER_H
#define DRIVER_H

#include <QObject>
#include "optimization.h"
#include "view.h"

class Driver : public QObject
{
    Q_OBJECT

protected:
    View view;
    Optimization optimization;

private:
    double time;

    Driver();
    ~Driver();

public:
    static Driver* getInstance();

signals:
    void changedMessage(const QString &message);
    void changedParticles();
    void changedConfiguration();
    void changedSelected(Particle *particle);
    void changedView();

public slots:
    void doRestart();
    void setDefault();
    void addParticle(const Point &p);
    void generateParticles();
    void removeParticles();

    void doStep();
    void animateStep();
    void runAnimation();
    void stopAnimation();
    void computeOptimum();

    void updateCp(const QString& text);
    void updateCg(const QString& text);
    void updateOmega(const QString& text);
    void updateMaxVelocity(const QString& text);
    void updateMaxIterations(const QString& text);
    void updateFitnessFunction(const QString& text);

public:
    void finishStep();
    void sendMessage();

    void resizeView(int w, int h);
    void clickView(int x, int y);
    void mouseMoveView(int x, int y);
    void wheelView(int orientation);
    void drawView(QPainter& painter);

    double getCp();
    double getCg();
    double getOmega();
    double getMaxVelocity();
    double getBestValue();
    int getCurrentIteration();
    int getMaxIterations();
    int getParticlesNumber();
    Particles* getParticles();
    Particle* getBestParticle();
    Point getBestPosition();
    Function getFitnessFunction();

};

#endif // DRIVER_H
