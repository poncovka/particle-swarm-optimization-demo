#ifndef TABPARTICLE_H
#define TABPARTICLE_H

#include <QWidget>
#include <string>
#include "particle.h"

class TabParticle : public QWidget
{
    Q_OBJECT
public:
    explicit TabParticle(QWidget *parent = 0);

signals:

public slots:
    void showParticle(Particle *particle);

protected:
    void updateLabel(const std::string& name, const std::string& text);


};

#endif // TABPARTICLE_H
