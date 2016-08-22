#ifndef TABPARTICLE_H
#define TABPARTICLE_H

#include <QWidget>
#include <string>
#include "particle.h"

class TabParticle : public QWidget
{
    Q_OBJECT

protected:
    Particle *particle;

public:
    explicit TabParticle(QWidget *parent = 0);

signals:

public slots:
    void setParticle(Particle *particle);
    void updateLabels();

protected:
    void updateLabel(const QString &name, const std::string& text);


};

#endif // TABPARTICLE_H
