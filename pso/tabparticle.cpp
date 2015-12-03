#include "tabparticle.h"
#include <QLabel>
#include <QString>
#include <sstream>

TabParticle::TabParticle(QWidget *parent) :
    QWidget(parent)
{
}

void TabParticle::showParticle(Particle *particle) {

    std::ostringstream s1, s2, s3, s4, s5, s6;

    if (particle) {
        s1 << particle->position.str();
        s2 << particle->velocity.str();
        s3 << particle->bestPosition.str();
        s4 << particle->bestValue;
        s5 << particle->nextPosition.str();
        s6 << particle->value;

    }

    updateLabel("label_particle_position", s1.str());
    updateLabel("label_particle_velocity", s2.str());
    updateLabel("label_particle_best_position", s3.str());
    updateLabel("label_particle_best_fitness", s4.str());
    updateLabel("label_particle_next_position", s5.str());
    updateLabel("label_particle_fitness", s6.str());

}

void TabParticle::updateLabel(const std::string &name, const std::string &text) {
    QLabel* label = this->findChild<QLabel*>(name.c_str());
    label->setText(text.c_str());
}
