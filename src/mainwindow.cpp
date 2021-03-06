#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Driver* driver, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // setup
    ui->setupUi(this);
    ui->tab_config->init();

    // actions
    connect(ui->actionRandom, SIGNAL(triggered()), driver, SLOT(generateParticles()));
    connect(ui->actionClear, SIGNAL(triggered()), driver, SLOT(removeParticles()));
    connect(ui->actionStep, SIGNAL(triggered()), driver, SLOT(doStep()));
    connect(ui->actionRun, SIGNAL(triggered()), driver, SLOT(runAnimation()));
    connect(ui->actionStop, SIGNAL(triggered()), driver, SLOT(stopAnimation()));
    connect(ui->actionFinish, SIGNAL(triggered()), driver, SLOT(computeOptimum()));
    connect(ui->actionRestart, SIGNAL(triggered()), driver, SLOT(doRestart()));

    // buttons
    connect(ui->button_default, SIGNAL(clicked()), driver, SLOT(setDefault()));

    // canvas
    connect(driver, SIGNAL(changedView()), ui->widget, SLOT(update()));
    connect(driver, SIGNAL(changedParticles()), ui->widget, SLOT(update()));

    // status bar
    connect(driver, SIGNAL(changedMessage(QString)), ui->statusBar, SLOT(showMessage(QString)));

    // tab particle
    connect(driver, SIGNAL(changedSelected(Particle*)), ui->tab_particle, SLOT(setParticle(Particle*)));
    connect(driver, SIGNAL(changedParticles()), ui->tab_particle, SLOT(updateLabels()));

    // tab configuration
    connect(driver, SIGNAL(changedParticles()), ui->tab_config, SLOT(updateLabels()));
    connect(driver, SIGNAL(changedConfiguration()), ui->tab_config, SLOT(updateValues()));

    connect(ui->lineEdit_cp, SIGNAL(textChanged(QString)), driver, SLOT(updateCp(QString)));
    connect(ui->lineEdit_cg, SIGNAL(textChanged(QString)), driver, SLOT(updateCg(QString)));
    connect(ui->lineEdit_omega, SIGNAL(textChanged(QString)), driver, SLOT(updateOmega(QString)));
    connect(ui->lineEdit_maxVelocity, SIGNAL(textChanged(QString)),driver, SLOT(updateMaxVelocity(QString)));
    connect(ui->lineEdit_maxIterations, SIGNAL(textChanged(QString)), driver, SLOT(updateMaxIterations(QString)));

    connect(ui->lineEdit_cg, SIGNAL(editingFinished()), driver, SLOT(updateFinished()));

    connect(ui->comboBox_function, SIGNAL(currentIndexChanged(QString)), driver, SLOT(updateFitnessFunction(QString)));


}

MainWindow::~MainWindow()
{
    delete ui;
}
