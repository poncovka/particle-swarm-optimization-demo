#ifndef DRIVER_H
#define DRIVER_H

#include <QObject>
#include "optimization.h"
#include "view.h"

class Driver : public QObject
{
    Q_OBJECT

private:
    View view;
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

    void resizeView(int w, int h);
    void clickView(int x, int y);
    void mouseMoveView(int x, int y);
    void wheelView(int orientation);
    void drawView(QPainter& painter);


signals:
    void changedParticles();
    void changedConfiguration();
    void changedSelected(Particle *particle);
    void changedView();

public slots:

    void doInit();
    void addParticle(const Point &p);
    void generateParticles();
    void removeParticles();

    void doStep();
    void runAnimation();
    void stopAnimation();
    void setDrawing(bool flag);
    void computeOptimum();

    void updateMaxIterations(const QString& text);
    void updateOmega(const QString& text);
    void updateCp(const QString& text);
    void updateCg(const QString& text);

};

#endif // DRIVER_H
