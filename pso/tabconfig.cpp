#include "tabconfig.h"
#include "lib.h"

#include <QLabel>
#include <QLineEdit>

TabConfig::TabConfig(QWidget *parent) :
    QWidget(parent)
{
    driver = Driver::getInstance();
}


void TabConfig::updateValues() {

    updateValue("lineEdit_cp",              Lib::str(driver->getCp()));
    updateValue("lineEdit_cg",              Lib::str(driver->getCg()));
    updateValue("lineEdit_omega",           Lib::str(driver->getOmega()));
    updateValue("lineEdit_maxIterations",   Lib::str(driver->getMaxIterations()));

}

void TabConfig::updateValue(const QString &name, const std::string &text) {

    QLineEdit* line = this->findChild<QLineEdit*>(name);

    if (line) {
        line->setText(text.c_str());
    }
}


void TabConfig::updateLabels() {

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
