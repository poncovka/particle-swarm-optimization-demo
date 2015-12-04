#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Driver* driver, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // setup
    ui->setupUi(this);

    // actions
    connect(ui->actionStep, SIGNAL(triggered()), driver, SLOT(doStep()));
    connect(ui->actionClear, SIGNAL(triggered()), driver, SLOT(removeParticles()));
    connect(ui->actionRandom, SIGNAL(triggered()), driver, SLOT(generateParticles()));

    // tab particle
    connect(driver, SIGNAL(changedSelected(Particle*)), ui->tab_particle, SLOT(setParticle(Particle*)));
    connect(driver, SIGNAL(changedParticles()), ui->tab_particle, SLOT(updateLabels()));
    connect(driver, SIGNAL(changedParticles()), ui->widget, SLOT(update()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
