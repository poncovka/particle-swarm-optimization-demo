#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lib.h"

MainWindow::MainWindow(Driver* driver, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // setup
    ui->setupUi(this);

    //ui->lineEdit_maxIterations = driver->getMaxIterations();
    ui->lineEdit_maxIterations->setText(Lib::str(driver->getMaxIterations()).c_str());
    ui->lineEdit_omega->setText(Lib::str(driver->getOmega()).c_str());
    ui->lineEdit_cp->setText(Lib::str(driver->getCp()).c_str());
    ui->lineEdit_cg->setText(Lib::str(driver->getCg()).c_str());

    // actions
    connect(ui->actionStep, SIGNAL(triggered()), driver, SLOT(doStep()));
    connect(ui->actionClear, SIGNAL(triggered()), driver, SLOT(removeParticles()));
    connect(ui->actionRandom, SIGNAL(triggered()), driver, SLOT(generateParticles()));

    // canvas
    connect(driver, SIGNAL(changedParticles()), ui->widget, SLOT(update()));

    // tab particle
    connect(driver, SIGNAL(changedSelected(Particle*)), ui->tab_particle, SLOT(setParticle(Particle*)));
    connect(driver, SIGNAL(changedParticles()), ui->tab_particle, SLOT(updateLabels()));

    // tab configuration
    connect(driver, SIGNAL(changedParticles()), ui->tab_config, SLOT(updateLabels()));
    connect(ui->lineEdit_maxIterations, SIGNAL(textChanged(QString)), driver, SLOT(updateMaxIterations(QString)));
    connect(ui->lineEdit_omega, SIGNAL(textChanged(QString)), driver, SLOT(updateOmega(QString)));
    connect(ui->lineEdit_cp, SIGNAL(textChanged(QString)), driver, SLOT(updateCp(QString)));
    connect(ui->lineEdit_cg, SIGNAL(textChanged(QString)), driver, SLOT(updateCg(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
