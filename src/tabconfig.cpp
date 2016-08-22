#include "tabconfig.h"
#include "functions.h"
#include "lib.h"

#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

TabConfig::TabConfig(QWidget *parent) :
    QWidget(parent)
{
    driver = Driver::getInstance();
}

void TabConfig::init() {

    // init combo box
    QComboBox* box = this->findChild<QComboBox*>("comboBox_function");

    if (box) {

        // add names of fitness functions
        for(int i = 0; i < FitnessFunction::MAX; i++) {
            box->addItem(FitnessFunction::names[i].c_str());
        }
    }

    // init text labels
    updateLabels();

    // init edit lines
    updateValues();
}

void TabConfig::updateValues() {

    // update edit lines
    updateValue("lineEdit_cp",              Lib::str(driver->getCp()));
    updateValue("lineEdit_cg",              Lib::str(driver->getCg()));
    updateValue("lineEdit_omega",           Lib::str(driver->getOmega()));
    updateValue("lineEdit_maxVelocity",     Lib::str(driver->getMaxVelocity()));
    updateValue("lineEdit_maxIterations",   Lib::str(driver->getMaxIterations()));

    // update combo box
    QComboBox* box = this->findChild<QComboBox*>("comboBox_function");
    if (box) {
        int i = FitnessFunction::getIndex(driver->getFitnessFunction());
        box->setCurrentIndex(i);
    }
}

void TabConfig::updateValue(const QString &name, const std::string &text) {

    QLineEdit* line = this->findChild<QLineEdit*>(name);

    if (line) {
        line->setText(text.c_str());
    }
}


void TabConfig::updateLabels() {

    // update labels
    updateLabel("label_particles_number",   Lib::str(driver->getParticlesNumber()));
    updateLabel("label_iteration",          Lib::str(driver->getCurrentIteration()));
    updateLabel("label_best_fitness",       Lib::str(driver->getBestValue()));
    updateLabel("label_best_position",      driver->getBestPosition().str());



}

void TabConfig::updateLabel(const QString &name, const std::string &text) {

    QLabel* label = this->findChild<QLabel*>(name);

    if (label) {
        label->setText(text.c_str());
    }
}
