#include "tabconfiguration.h"
#include "lib.h"

#include <QLabel>

TabConfiguration::TabConfiguration(QWidget *parent) :
    QWidget(parent)
{
    driver = Driver::getInstance();
}

void TabConfiguration::updateLabels() {

    updateLabel("label_particles_number", Lib::str(driver->getParticlesNumber()));
    updateLabel("label_iteration", Lib::str(driver->getCurrentIteration()));
    updateLabel("label_best_fitness", Lib::str(driver->getBestValue()));
    updateLabel("label_best_position", driver->getBestPosition().str());

}

void TabConfiguration::updateLabel(const QString &name, const std::string &text) {

    QLabel* label = this->findChild<QLabel*>(name);

    if (label) {
        label->setText(text.c_str());
    }
}
