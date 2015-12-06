#include "view.h"
#include "driver.h"
//#include "optimization.h"
#include "lib.h"

#include <QtGui>

View::View() {

    // set parameters
    zoom = 1;
    scale = 1.0/100;
    orientation.set(1,-1);

    particle_diameter = 15;

    color_axis              .setRgb(200, 200, 200);
    color_additional_axis   .setRgb(130,130,130);
    color_function          .setRgb(0,170,212);
    color_particle          .setRgb(153,153,153);
    color_particle_selected .setRgb(77,77,77);
    color_particle_next     .setRgb(20,182,159);
    color_particle_best     .setRgb(44,90,255);
    color_velocity          .setRgb(212,0,85);
    color_inert             .setRgb(255,102,0);
    color_social            .setRgb(0,170,212);
    color_cognitive         .setRgb(44,90,255);

    // set the state
    currentParticle = NULL;
    selectedParticle = NULL;
    isSelectedPermanent = false;

    // compute center
    //updateCenter();

    // compute function polygon
    //updateFunction();

}

Point View::getPt(Point& px) {
    Point p(px);
    toPt(p);
    return p;
}

Point View::getPx(Point& pt) {
    Point p(pt);
    toPx(p);
    return p;
}

void View::toPt(Point& p) {

    for (int i = 0; i < Point::MAXDIM; i++) {
        p.coordinate(i) = toPt(p.coordinate(i), i);
    }
}

void View::toPx(Point& p) {

    for (int i = 0; i < Point::MAXDIM; i++) {
        p.coordinate(i) = toPx(p.coordinate(i), i);
    }
}

double View::toPt(double px_i, int i) {
    return (px_i - center.coordinate(i)) * scale * orientation.coordinate(i) / zoom ;
}

double View::toPx(double pt_i, int i) {
    return (pt_i / scale * orientation.coordinate(i) * zoom) + center.coordinate(i);
}

void View::setSize(int w, int h) {

    size.x() = w;
    size.y() = h;

    center.x() = w/2;
    center.y() = h/2;

    calculateFunction();
}

void View::setZoom(int orientation) {

    if (orientation > 0) {
        zoom /= 1.5;
    }
    else {
        zoom *= 1.5;
    }

    calculateFunction();
}

void View::setPosition(int x, int y) {

    position.set(x,y);
    toPt(position);

}

bool View::setSelectedParticle(Particle *particle) {

    if (particle) {

        // undo select permanent
        if (selectedParticle == particle && isSelectedPermanent) {
            selectedParticle = NULL;
            isSelectedPermanent = false;
        }
        // select permanent
        else {
            selectedParticle = currentParticle;
            isSelectedPermanent = true;
        }
    }
    // undo select
    else if (selectedParticle) {
        selectedParticle = NULL;
        isSelectedPermanent = false;
    }

    // was selected?
    return (selectedParticle != NULL);
}

bool View::setCurrentParticle(Particle* particle) {

    currentParticle = particle;

    if (!isSelectedPermanent) {
        selectedParticle = currentParticle;
        return true;
    }

    return false;
}

Particle* View::findParticle(Particles* particles, int x, int y) {

    // get position in px
    Point position(x, y);
    toPt(position);

    double r_pt = particle_diameter/2 * scale / zoom;

    // check y axis
    if (Lib::isNearby(position.y(), 0, r_pt)) {

        // find particle at given x axis
        for(Particles::iterator i = particles->begin(); i!= particles->end(); i++) {

            Particle* particle = (*i);

            if(Lib::isNearby(particle->position.x(), position.x(), r_pt)) {

                return particle;
            }
        }
    }

    return NULL;
}

void View::calculateFunction() {

    Function fitness = Driver::getInstance()->getFitnessFunction();

    // clear polygon
    funcPolygon.clear();

    // check if the fitness function is defined
    if (!fitness) return;

    // compute points
    for(int i = 0; i < size.x(); i++) {

        // calculate input point
        Point point(i);
        toPt(point);

        // calculate result point
        point.y() = fitness(point);
        toPx(point);

        // add point to polygon
        funcPolygon << QPointF(point.x(), point.y());
    }
}

void View::drawPoint(QPainter& painter, Point p, double r) {
    painter.drawEllipse(p.x() - r/2, p.y() - r/2, r, r);
}

void View::drawSquare(QPainter& painter, Point p, double r) {
    QRectF rectangle(p.x() - r/2, p.y() - r/2, r, r);
    painter.drawRect(rectangle);
}

void View::drawAxis(QPainter& painter) {

    // set pen
    QPen pen(color_axis, 1, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);

    // draw x axis
    painter.drawLine(0, center.y(), size.x(), center.y());

    // draw y axis
    painter.drawLine(center.x(), 0, center.x(), size.y());

    /*
    // draw rules
    painter.setPen(Qt::black);

    int d = 5;
    double unit_pt = Lib::getUnit(size.x() * scale / zoom / 3);
    double unit_px = unit_pt / scale * zoom ;

    Point p(center.x(), center.y());
    Point p_pt = getPt(p);

    for (int x = 0; x <= size.x(); x++) {
        painter.drawLine(p.x(), p.y() + d, p.x(), p.y() - d);
        p.x() += unit_px;
        p_pt.x() += unit_pt;
    }
    */
}

void View::drawFunction(QPainter& painter) {

    // set pen
    QPen pen(color_function, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);

    // draw function
    painter.drawPolyline(funcPolygon);
}


void View::drawParticles(QPainter& painter, Particles* particles) {

    // draw particles
    painter.setPen(Qt::NoPen);
    painter.setBrush(color_particle);

    for(Particles::iterator i = particles->begin(); i != particles->end(); i++) {

        // get particle
        Particle* particle = (*i);

        // draw particle
        drawPoint(painter, getPx(particle->position), particle_diameter);
    }
}

void View::drawBestPosition(QPainter& painter, Point position) {

    // draw particles
    painter.setPen(color_function);
    painter.setBrush(color_function);

    // conversion
    toPx(position);

    // draw particle
    drawSquare(painter, position, particle_diameter);
}

void View::drawSelectedParticle(QPainter&  painter) {

    Particle *selected = selectedParticle;

    if (!selected) return;

    // init
    Point p= getPx(selected->position);
    QPen pen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // draw vectors
    drawVectors(painter);

    // draw additional axis
    pen.setColor(color_additional_axis);
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);
    painter.drawLine(p.x(), 0, p.x(), size.y());

    // draw particle
    int padding = 50;
    int r = 100;

    painter.setBrush(color_particle_selected);
    painter.setPen(color_particle_selected);
    drawPoint(painter, p, particle_diameter);

    // draw next
    Point p2 = getPx(selected->nextPosition);
    painter.setBrush(color_particle_next);
    painter.setPen(color_particle_next);

    drawSquare(painter, p2, particle_diameter);
    painter.drawText(p2.x() - r/2, p2.y() - r/2 + padding, r, r, Qt::AlignCenter, "next");

    // draw best
    Point p3 = getPx(selected->bestPosition);
    painter.setBrush(color_particle_best);
    painter.setPen(color_particle_best);

    drawSquare(painter, p3, particle_diameter);
    painter.drawText(p3.x() - r/2, p3.y() - r/2 + padding, r, r, Qt::AlignCenter, "best");

}

void View::drawVectors(QPainter& painter) {

    Particle *selected = selectedParticle;

    // set arrow parameters
    int arrow_w = 15;
    int arrow_h = 8;

    // set y starting point and delta y
    Point y(0, -100);
    Point dy(0, -50);

    // set vectors
    const int MAX = 4;
    Point vectors [MAX] = {selected->velocity, selected->vw, selected->vp, selected->vg};
    QColor colors [MAX] = {color_velocity, color_inert, color_cognitive, color_social};
    QString texts [MAX] = {"velocity", "inert velocity", "cognitive velocity", "social velocity"};

    // set pen
    QPen pen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // draw velocity vectors
    for (int i = 0; i < MAX; i++) {

        Point position = selected->position;

        //DEBUG("CANVAS: number " <<  i);
        //DEBUG("CANVAS: position " << position.str());
        //DEBUG("CANVAS: vector " << vectors[i].str());

        // set pen
        pen.setColor(colors[i]);
        painter.setBrush(colors[i]);
        painter.setPen(pen);

        // get end point of vector
        vectors[i].plus(position);

        // get orientation of the vector
        double orientation = (position.x() < vectors[i].x()) ? 1 : -1;

        //DEBUG("CANVAS: recalculation: " + vectors[i].str());

        // conversion
        toPx(position);
        toPx(vectors[i]);

        //DEBUG("CANVAS: conversion " + vectors[i].str());

        // move vector in y axis
        position.plus(y);
        vectors[i].plus(y);
        y.plus(dy);

        // draw text
        painter.drawText(position.x() + 5, position.y() - 10, texts[i]);

        // draw line
        painter.drawLine(position.x(), position.y(), vectors[i].x(), vectors[i].y());

        // draw arrow
        QPoint arrow [3] = {
            QPoint(vectors[i].x(),                            vectors[i].y()),
            QPoint(vectors[i].x() - arrow_w * orientation,    vectors[i].y() - arrow_h/2),
            QPoint(vectors[i].x() - arrow_w * orientation,    vectors[i].y() + arrow_h/2)
        };

        painter.drawPolygon(arrow, 3);
    }
}

