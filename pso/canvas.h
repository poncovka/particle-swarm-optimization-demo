#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPolygonF>

#include "driver.h"
#include "point.h"

class Canvas : public QWidget
{
    Q_OBJECT    

private:
    // driver
    Driver* driver;

    // center point
    Point center;

    // correct orientation of axis
    Point orientation;

    // particle
    Particle* currentParticle;
    Particle* selectedParticle;
    bool isSelectedPermanent;

    // polygon for fitness function
    QPolygonF funcPolygon;

    // scale 1:n pixels
    double scale;

    // zoom
    double zoom;

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

    // particle width
    int particle_diameter;
    int r2;

public:
    explicit Canvas(QWidget *parent = 0);

signals:

public slots:

protected:
    void updateCenter();
    void updateFunction();

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void resizeEvent(QResizeEvent *);

    double abs(double v);
    bool isNearby(double v1, double v2, double particle_diameter);

    Point getPt(Point& px);
    Point getPx(Point& pt);

    void toPt(Point& px);
    void toPx(Point& pt);

    double toPt(double, int);
    double toPx(double, int);

    void drawPoint(QPainter& painter, Point p, double r);
    void drawSquare(QPainter& painter, Point p, double r);
    void drawAxis(QPainter& painter);
    void drawFunction(QPainter& painter);
    void drawParticles(QPainter& painter, Particles *particles);
    void drawBestPosition(QPainter& painter, Point position);
    void drawSelectedParticle(QPainter&  painter, Particle *selected);
    void drawVectors(QPainter& painter, Particle *selected);

};

#endif // CANVAS_H
