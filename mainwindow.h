#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include "ds18b20.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct TemperatureData
{
    float temp1=1024;
    float temp2=1024;
    QDateTime time;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void onTimer();

private:
    Ui::MainWindow *ui;
    ds18b20 *sensors;
    QTimer *timer;
    float temp1, temp2=-1.0f;
    TemperatureData tDat[8641];
    int tDatCount=0;
    TemperatureData findMax1();
    TemperatureData findMax2();
    TemperatureData findMin1();
    TemperatureData findMin2();
};


#endif // MAINWINDOW_H
