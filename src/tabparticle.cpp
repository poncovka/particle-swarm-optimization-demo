#include "tabparticle.h"
#include "lib.h"

#include <QLabel>
#include <QString>
#include <sstream>

TabParticle::TabParticle(QWidget *parent) :
    QWidget(parent)
{
}


void TabParticle::setParticle(Particle *particle) {
    this->particle = particle;
    updateLabels();
}

void TabParticle::updateLabels() {

    // max labels
    static const int MAX = 9;

    // get labels
    static const QString labels [MAX] = {
        "label_particle_position",
        "label_particle_next_position",
        "label_particle_best_position",
        "label_particle_fitness",
        "label_particle_best_fitness",
        "label_particle_velocity",
        "label_particle_vi",
        "label_particle_vp",
        "label_particle_vg"
    };

    if (particle) {

        // init texts
        const std::string values [MAX] = {
            particle->position.str(),
            particle->nextPosition.str(),
            particle->bestPosition.str(),
            Lib::str(particle->value),
            Lib::str(particle->bestValue),
            particle->velocity.str(),
            particle->vw.str(),
            particle->vp.str(),
            particle->vg.str()
        };

        // set text in labels
        for (int i = 0; i < MAX; i++) {
            updateLabel(labels[i], values[i]);
        }
    }
    else {
        // set empty string in labels
        for (int i = 0; i < MAX; i++) {
            updateLabel(labels[i], "");
        }
    }
}

void TabParticle::updateLabel(const QString &name, const std::string &text) {

    QLabel* label = this->findChild<QLabel*>(name);

    if (label) {
        label->setText(text.c_str());
    }
}


