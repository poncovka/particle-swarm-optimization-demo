#ifndef TABCONFIGURATION_H
#define TABCONFIGURATION_H

#include <QWidget>
#include "driver.h"

class TabConfiguration : public QWidget
{
    Q_OBJECT

protected:
    Driver* driver;

public:
    explicit TabConfiguration(QWidget *parent = 0);

signals:

public slots:
    void updateLabels();
    void updateLabel(const QString &name, const std::string &text);

};

#endif // TABCONFIGURATION_H
