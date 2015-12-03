#include "canvas.h"
#include "optimization.h"

#include <QtGui>
#include <iostream>

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    driver = Driver::getInstance();

    r = 15;

    //scale = 1.0/100;
    scale = 1.0/100;
    zoom = 1;

    selectedParticle = NULL;
    orientation.set(1,1,-1);

    updateCenter();
    updateFunction();
}

void Canvas::updateCenter() {
    center.x() = width()/2;
    center.y() = height()/2;
    center.z() = height()/2;
}

void Canvas::updateFunction() {

    // get fitness function
    Function fitness = driver->getFitnessFunction();

    // clear polygon
    funcPolygon.clear();

    // check if the fitness function is defined
    if (!fitness) return;

    // compute points
    for(int i = 0; i < width(); i++) {

        // calculate input point
        Point point(i);
        toPt(point);

        // calculate result point
        point.z() = fitness(point);
        toPx(point);

        // add point to polygon
        funcPolygon << QPointF(i, point.z());
    }
}

void Canvas::paintEvent(QPaintEvent *event) {

    // get painter
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing, true);

    // paint background
    painter.fillRect(0, 0, width(), height(), Qt::white);

    // paint axes
    painter.setPen(Qt::gray);
    painter.drawLine(0, center.z(), width(), center.z());
    painter.drawLine(center.x(), 0, center.x(), height());

    // paint function
    painter.setPen(Qt::blue);
    painter.drawPolyline(funcPolygon);

    // get particles
    Particles* particles = driver->getParticles();

    // paint highlighted particle
    if (selectedParticle) {
        //int r = 12;
        int r2 = 10;
        int d = 80;

        QPen pen;
        pen.setWidth(2);

        Point p = selectedParticle->position;
        Point p2 = selectedParticle->nextPosition;
        Point v = selectedParticle->velocity;
        Point vw = selectedParticle->vw;
        Point vg = selectedParticle->vg;
        Point vp = selectedParticle->vp;

        v.plus(p);
        vw.plus(p);
        vg.plus(p);
        vp.plus(p);

        toPx(p);
        toPx(p2);
        toPx(v);
        toPx(vw);
        toPx(vg);
        toPx(vp);

        pen.setStyle(Qt::SolidLine);
        pen.setColor(Qt::gray);
        painter.setPen(pen);

        //drawPoint(painter, vw, r2);
        painter.drawLine(p.x(), p.z() - d, p2.x(), p2.z() - d);

        d += 30;

        pen.setStyle(Qt::SolidLine);
        pen.setColor(Qt::red);
        painter.setPen(pen);

        //drawPoint(painter, vw, r2);
        painter.drawLine(p.x(), p.z() - d, v.x(), v.z() - d);

        d += 30;

        pen.setStyle(Qt::DashLine);
        pen.setColor(Qt::red);
        painter.setPen(pen);
        //drawPoint(painter, vw, r2);
        painter.drawLine(p.x(), p.z() - d, vw.x(), vw.z() - d);

        d += 30;

        pen.setColor(Qt::darkYellow);
        painter.setPen(pen);
        //drawPoint(painter, vg, r2);
        painter.drawLine(p.x(), p.z() - d, vg.x(), vg.z() - d);

        d += 30;

        pen.setColor(Qt::darkBlue);
        painter.setPen(pen);
        //drawPoint(painter, vp, r2);
        painter.drawLine(p.x(), p.z() - d, vp.x(), vp.z() - d);

        painter.setBrush(Qt::black);
        painter.setPen(Qt::NoPen);
        drawPoint(painter, p, r);
    }
    // paint particles


        int r2 = 8;

        for(Particles::iterator i = particles->begin(); i!= particles->end(); i++) {

            Particle* particle = (*i);
            Point p(particle->position);

            toPx(p);

            painter.setBrush(Qt::black);
            painter.setPen(Qt::NoPen);

            drawPoint(painter, p, r);
        }

        // paint best particle
        if (!particles->empty()) {
            //int r = 12;

            Point p = driver->getBestPosition();
            toPx(p);

            painter.setBrush(Qt::blue);
            painter.setPen(Qt::NoPen);
            drawPoint(painter, p, r);
        }

}

void Canvas::drawPoint(QPainter& painter, Point &p, double r) {
    painter.drawEllipse(p.x() - r/2, p.z() - r/2, r, r);
}

void Canvas::mousePressEvent(QMouseEvent *event){

    // get position of future particle
    Point position(event->x(), center.y(), center.z());
    toPt(position);

    // create new particle
    driver->addParticle(position);
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {

    selectedParticle = NULL;

    // get position of mouse
    Point position(event->x(), center.y(), event->y());
    toPt(position);

    double r_pt = r/2 * scale / zoom;

    // check z axis
    if (isNearby(position.z(), 0, r_pt)) {

        // find particle at given x axis
        Particles* particles = driver->getParticles();
        for(Particles::iterator i = particles->begin(); i!= particles->end(); i++) {

            Particle* particle = (*i);
            if(isNearby(particle->position.x(), position.x(), r_pt)) {
                selectedParticle = particle;
                break;
            }
        }
    }

    update();
    emit changedSelectedParticle(selectedParticle);
}

void Canvas::wheelEvent(QWheelEvent *event) {

    if (event->delta() > 0) {
        zoom = zoom / 1.5;
    }
    else {
        zoom = zoom * 1.5;
    }

    update();
}

void Canvas::resizeEvent(QResizeEvent *event){
    updateCenter();
    updateFunction();
}

double Canvas::abs(double v) {
    return (v < 0) ? -v : v;
}

bool Canvas::isNearby(double v1, double v2, double r) {
    return abs(v1 - v2) <= r;
}


void Canvas::toPt(Point& p) {

    for (int i = 0; i < Point::MAXDIM; i++) {
        p.coordinate(i) = toPt(p.coordinate(i), i);
    }
}

void Canvas::toPx(Point& p) {

    for (int i = 0; i < Point::MAXDIM; i++) {
        p.coordinate(i) = toPx(p.coordinate(i), i);
    }
}

double Canvas::toPt(double px_i, int i) {
    return (px_i - center.coordinate(i)) * scale * orientation.coordinate(i) / zoom ;
}

double Canvas::toPx(double pt_i, int i) {
    return (pt_i / scale * orientation.coordinate(i) * zoom) + center.coordinate(i);
}


