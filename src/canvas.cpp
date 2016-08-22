#include "canvas.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QWheelEvent>
#include <QPainter>

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    // get driver
    driver = Driver::getInstance();
}

void Canvas::resizeEvent(QResizeEvent *){
    driver->resizeView(width(), height());
}

void Canvas::mousePressEvent(QMouseEvent *event){

    driver->clickView(event->x(), event->y());
    update();
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {

    driver->mouseMoveView(event->x(), event->y());
    update();
}

void Canvas::wheelEvent(QWheelEvent *event) {

    driver->wheelView((event->delta() > 0) ? 1 : -1);
    update();
}

void Canvas::paintEvent(QPaintEvent *) {

    // get painter
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing, true);

    // background
    painter.fillRect(0, 0, width(), height(), Qt::white);

    // draw view
    driver->drawView(painter);
}




