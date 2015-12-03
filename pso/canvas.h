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
    Particle* selectedParticle;

    // polygon for fitness function
    QPolygonF funcPolygon;

    // scale 1:n pixels
    double scale;

    // zoom
    double zoom;

    // particle width
    int r;
    int r2;

public:
    explicit Canvas(QWidget *parent = 0);

signals:
    void changedSelectedParticle(Particle *particle);

public slots:

protected:
    void updateCenter();
    void updateFunction();

    void paintEvent(QPaintEvent *);
    void drawPoint(QPainter& painter, Point &p, double r);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void resizeEvent(QResizeEvent *);

    double abs(double v);
    bool isNearby(double v1, double v2, double r);

    void toPt(Point& px);
    void toPx(Point& pt);

    double toPt(double, int);
    double toPx(double, int);
};

#endif // CANVAS_H
