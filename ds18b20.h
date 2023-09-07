#ifndef DS18B20_H
#define DS18B20_H
#include <QThread>
#include <QProcess>
#include <QDebug>
#include <QDir>
#include <QFile>

class ds18b20
{
public:
    ds18b20();
    bool ds18b20_init(int which);
    float readTemp(int which);
    QStringList detected_sensors;
    int getSensorCount();
};

#endif // DS18B20_H
