#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include "driver.h"

class Canvas : public QWidget
{
    Q_OBJECT    

protected:
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
