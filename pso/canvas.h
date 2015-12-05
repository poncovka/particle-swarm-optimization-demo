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

public:
    explicit Canvas(QWidget *parent = 0);

signals:

public slots:

protected:

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void resizeEvent(QResizeEvent *);

};

#endif // CANVAS_H
