#ifndef TABCONFIGURATION_H
#define TABCONFIGURATION_H

#include <QWidget>
#include "driver.h"

class TabConfig : public QWidget
{
    Q_OBJECT

protected:
    Driver* driver;

public:
    explicit TabConfig(QWidget *parent = 0);

signals:

public slots:
    void updateValues();
    void updateLabels();

public:
    void init();
    void updateValue(const QString &name, const std::string &text);
    void updateLabel(const QString &name, const std::string &text);

};

#endif // TABCONFIGURATION_H
