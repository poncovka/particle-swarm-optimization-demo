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
    connect(ui->widget, SIGNAL(changedSelectedParticle(Particle*)), ui->tab_particle, SLOT(showParticle(Particle*)));


    connect(driver, SIGNAL(updated()), ui->widget, SLOT(update()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
