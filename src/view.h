#ifndef VIEW_H
#define VIEW_H

#include <QColor>
#include <QPolygonF>
#include <QPainter>
#include <QTimer>

#include "point.h"
#include "particle.h"

class View {

public:

    // scale pt/px
    double scale;

    // zoom
    double zoom;

    // width and height
    Point size;

    // center point
    Point center;

    // position
    Point position;

    // orientation of axis
    Point orientation;

    // particle width
    int particle_diameter;

    // particles
    Particle* currentParticle;
    Particle* selectedParticle;
    bool isSelectedPermanent;

    // polygon for fitness function
    QPolygonF funcPolygon;

    // timer
    QTimer *timer;

    // colors
    QColor color_axis;
    QColor color_additional_axis;
    QColor color_function;
    QColor color_particle;
    QColor color_particle_selected;
    QColor color_particle_best;
    QColor color_particle_next;
    QColor color_velocity;
    QColor color_inert;
    QColor color_social;
    QColor color_cognitive;

public:
    View();

    Point getPt(Point& px);
    Point getPx(Point& pt);

    void toPt(Point& px);
    void toPx(Point& pt);

    double toPt(double, int);
    double toPx(double, int);

    void setSize(int w, int h);
    void setZoom(int orientation);
    void setPosition(int x, int y);
    bool setSelectedParticle(Particle *particle);
    bool setCurrentParticle(Particle* particle);
    Particle* findParticle(Particles* particles, int x, int y);
    void calculateFunction();

    void drawPoint(QPainter& painter, Point p, double r);
    void drawSquare(QPainter& painter, Point p, double r);
    void drawAxis(QPainter& painter);
    void drawFunction(QPainter& painter);
    void drawParticles(QPainter& painter, Particles *particles);
    void drawBestPosition(QPainter& painter, Point position);
    void drawSelectedParticle(QPainter&  painter);
    void drawVectors(QPainter& painter);
};

#endif // VIEW_H
