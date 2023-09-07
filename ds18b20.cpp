#include "ds18b20.h"

ds18b20::ds18b20()
{
    QProcess process;
    process.start("sudo modprobe w1-gpio");
    process.waitForFinished(-1); // will wait forever until finished

    QString stdout = process.readAllStandardOutput();
    QString stderr = process.readAllStandardError();
    qDebug()<<stdout<<stderr;

    process.start("sudo modprobe w1-therm");
    process.waitForFinished(-1); // will wait forever until finished

    stdout = process.readAllStandardOutput();
    stderr = process.readAllStandardError();
    qDebug()<<stdout<<stderr;

    QDir directory("/sys/bus/w1/devices");
    if(directory.count()<2)
    {
        qDebug()<<"Files in DIR are less than 2, no sensor found!"<<directory.count();
    }
    else
    {
        foreach (QString sensorName, directory.entryList() )
        {
            if(sensorName.contains("28-"))
            {
                this->detected_sensors.append(sensorName);
                qDebug()<<"Sensor:"<<sensorName<<" detected and added!";
            }
        }
    }
}

bool ds18b20::ds18b20_init(int which)
{
    if(detected_sensors.count()>=which)
        return true;
    else
        return false;
}

float ds18b20::readTemp(int which)
{
    if(ds18b20_init(which))
    {
        QFile f("/sys/bus/w1/devices/"+this->detected_sensors[which]+"/w1_slave");
        f.open(QIODevice::ReadOnly|QIODevice::Text);
        QString val(f.readAll());
        QStringList vals=val.split("t=");
        qDebug()<<vals[1];
        int basicTemp=vals[1].toInt();
        float finalTemp=(double)basicTemp/(float)1000;
        return finalTemp;

    }
    return -1.0f;
}

int ds18b20::getSensorCount()
{
    return this->detected_sensors.count();
}
