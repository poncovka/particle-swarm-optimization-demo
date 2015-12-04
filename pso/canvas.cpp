#include "canvas.h"
#include "optimization.h"
#include "debug.h"

#include <QtGui>

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    // get driver
    driver = Driver::getInstance();

    // set parameters
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

    // set state of canvas
    currentParticle = NULL;
    selectedParticle = NULL;
    isSelectedPermanent = false;

    orientation.set(1,1,-1);
    scale = 1.0/100;
    zoom = 1;

    // compute center
    updateCenter();

    // compute function polygon
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
        funcPolygon << QPointF(point.x(), point.z());
    }
}

void Canvas::paintEvent(QPaintEvent *) {

    // get painter
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing, true);

    // background
    painter.fillRect(0, 0, width(), height(), Qt::white);

    // axis
    drawAxis(painter);

    // function
    drawFunction(painter);

    // particles
    Particles* particles = driver->getParticles();
    drawParticles(painter, particles);

    if (!particles->empty()) {
        drawBestPosition(painter, driver->getBestPosition());
        drawSelectedParticle(painter, selectedParticle);
    }
}

void Canvas::mousePressEvent(QMouseEvent *event){

    // particle was selected
    if (currentParticle) {

        // undo select permanent
        if (selectedParticle == currentParticle && isSelectedPermanent) {
            selectedParticle = NULL;
            isSelectedPermanent = false;
        }
        // select permanent
        else {
            selectedParticle = currentParticle;
            isSelectedPermanent = true;
        }
    }
    // nothing selected
    else {
        selectedParticle = NULL;
        isSelectedPermanent = false;

        // get position of future particle
        Point position(event->x(), center.y(), center.z());
        toPt(position);

        // create new particle
        driver->addParticle(position);
    }

    update();
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {

    currentParticle = NULL;

    // get position of mouse
    Point position(event->x(), center.y(), event->y());
    toPt(position);

    double r_pt = particle_diameter/2 * scale / zoom;

    // check z axis
    if (isNearby(position.z(), 0, r_pt)) {

        // find particle at given x axis
        Particles* particles = driver->getParticles();
        for(Particles::iterator i = particles->begin(); i!= particles->end(); i++) {

            Particle* particle = (*i);
            if(isNearby(particle->position.x(), position.x(), r_pt)) {
                currentParticle = particle;
                break;
            }
        }
    }

    if (!isSelectedPermanent) {
        selectedParticle = currentParticle;
        emit changedSelectedParticle(selectedParticle);
    }

    update();
}

void Canvas::wheelEvent(QWheelEvent *event) {

    if (event->delta() > 0) {
        zoom = zoom / 1.5;
    }
    else {
        zoom = zoom * 1.5;
    }

    updateFunction();
    update();
}

void Canvas::resizeEvent(QResizeEvent *){
    updateCenter();
    updateFunction();
}

double Canvas::abs(double v) {
    return (v < 0) ? -v : v;
}

bool Canvas::isNearby(double v1, double v2, double r) {
    return abs(v1 - v2) <= r;
}


Point Canvas::getPt(Point& px) {
    Point p(px);
    toPt(p);
    return p;
}

Point Canvas::getPx(Point& pt) {
    Point p(pt);
    toPx(p);
    return p;
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

void Canvas::drawPoint(QPainter& painter, Point p, double r) {
    painter.drawEllipse(p.x() - r/2, p.z() - r/2, r, r);
}

void Canvas::drawSquare(QPainter& painter, Point p, double r) {
    QRectF rectangle(p.x() - r/2, p.z() - r/2, r, r);
    painter.drawRect(rectangle);
}

void Canvas::drawAxis(QPainter& painter) {

    // set pen
    QPen pen(color_axis, 1, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);

    // draw x axis
    painter.drawLine(0, center.z(), width(), center.z());

    // draw z axis
    painter.drawLine(center.x(), 0, center.x(), height());
}

void Canvas::drawFunction(QPainter& painter) {

    // set pen
    QPen pen(color_function, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);

    // draw function
    painter.drawPolyline(funcPolygon);
}


void Canvas::drawParticles(QPainter& painter, Particles* particles) {

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

void Canvas::drawBestPosition(QPainter& painter, Point position) {

    // draw particles
    painter.setPen(color_function);
    painter.setBrush(color_function);

    // conversion
    toPx(position);

    // draw particle
    drawPoint(painter, position, particle_diameter);
}

void Canvas::drawSelectedParticle(QPainter&  painter, Particle *selected) {

    if (!selected) return;

    // init
    Point p= getPx(selected->position);
    QPen pen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // draw vectors
    drawVectors(painter, selected);

    // draw additional axis
    pen.setColor(color_additional_axis);
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);
    painter.drawLine(p.x(), 0, p.x(), height());

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

void Canvas::drawVectors(QPainter& painter, Particle *selected) {

    // set arrow parameters
    int arrow_w = 15;
    int arrow_h = 8;

    // set z starting point and delta z
    Point z(0, 0, -100);
    Point dz(0, 0, -50);

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
        double orientation = (position.x() < vectors[i].x()) ? 1 : -1;

        DEBUG("TEST", vectors[i].str())
        //DEBUG("DRAWING VECTOR: ", vectors[i].str());

        // set pen
        pen.setColor(colors[i]);
        painter.setBrush(colors[i]);
        painter.setPen(pen);

        // get end point of vector
        vectors[i].plus(position);

        //DEBUG("RECALCULATION: ", vectors[i].str());

        // conversion
        toPx(position);
        toPx(vectors[i]);

        //DEBUG("CONVERSION: ", vectors[i].str());

        // move vector in z axis
        position.plus(z);
        vectors[i].plus(z);
        z.plus(dz);

        // draw text
        painter.drawText(position.x() + 5, position.z() - 10, texts[i]);

        // draw line
        painter.drawLine(position.x(), position.z(), vectors[i].x(), vectors[i].z());

        // draw arrow
        QPoint arrow [3] = {
            QPoint(vectors[i].x(),                            vectors[i].z()),
            QPoint(vectors[i].x() - arrow_w * orientation,    vectors[i].z() - arrow_h/2),
            QPoint(vectors[i].x() - arrow_w * orientation,    vectors[i].z() + arrow_h/2)
        };

        painter.drawPolygon(arrow, 3);
    }
}



