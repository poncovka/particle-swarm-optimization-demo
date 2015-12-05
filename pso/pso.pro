#-------------------------------------------------
#
# Project created by QtCreator 2015-11-30T20:51:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pso
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        canvas.cpp \
    particle.cpp \
    point.cpp \
    functions.cpp \
    optimization.cpp \
    driver.cpp \
    tabparticle.cpp \
    lib.cpp \
    tabconfig.cpp \
    view.cpp

HEADERS  += mainwindow.h \
        canvas.h \
    particle.h \
    point.h \
    functions.h \
    optimization.h \
    driver.h \
    tabparticle.h \
    lib.h \
    tabconfig.h \
    view.h

FORMS    += mainwindow.ui
