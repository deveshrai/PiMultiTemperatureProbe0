#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->sensors = new ds18b20();
    if(sensors->getSensorCount()==2)
    {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MainWindow::onTimer);
        timer->setInterval(10000);
        timer->start();
        //ui->frame_2->hide();
        this->onTimer();
    }
    else if(sensors->getSensorCount()==1)
    {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MainWindow::onTimer);
        timer->setInterval(10000);
        timer->start();
        ui->frame_2->hide();
        this->onTimer();
    }
    else
    {
        ui->frame_2->hide();
        ui->label->setText("nope!");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::onTimer()
{
    this->temp1=sensors->readTemp(0);
    ui->label->setText(QString::number((double)(temp1))+"°C");
    if(this->sensors->getSensorCount()>=2)
    {
        this->temp2=sensors->readTemp(1);
        ui->label_2->setText(QString::number((double)(temp2))+"°C");
    }
    if(this->tDatCount<=8640)
    {
        this->tDat[this->tDatCount].temp1=temp1;
        this->tDat[this->tDatCount].temp2=temp2;
        this->tDat[this->tDatCount++].time=QDateTime::currentDateTime();
    }
    else
    {
        this->tDatCount=0;
        this->tDat[this->tDatCount].temp1=temp1;
        this->tDat[this->tDatCount].temp2=temp2;
        this->tDat[this->tDatCount++].time=QDateTime::currentDateTime();
    }

    TemperatureData tMax1=this->findMax1();
    TemperatureData tMax2=this->findMax2();
    TemperatureData tMin1=this->findMin1();
    TemperatureData tMin2=this->findMin2();
    QString Max1="Max: "+QString::number((double)tMax1.temp1)+"°C at\n"+tMax1.time.toString();
    QString Max2="Max: "+QString::number((double)tMax2.temp2)+"°C at \n"+tMax2.time.toString();
    QString Min1="Min: "+QString::number((double)tMin1.temp1)+"°C at\n"+tMin1.time.toString();
    QString Min2="Min: "+QString::number((double)tMin2.temp2)+"°C at \n"+tMin2.time.toString();
    ui->label_3->setText(Max1);
    ui->label_4->setText(Min1);
    ui->label_5->setText(Max2);
    ui->label_6->setText(Min2);


}
TemperatureData MainWindow::findMax1()
{
    float maxTemp=-1024.0f;
    QDateTime Max;
    for(int i=0;i<8641;i++)
    {
        if(this->tDat[i].temp1>maxTemp&&this->tDat[i].temp1!=1024)
        {
            maxTemp=this->tDat[i].temp1;
            Max=this->tDat[i].time;
        }
    }
    TemperatureData mT;
    mT.temp1=maxTemp;
    mT.time=Max;
    return mT;
}

TemperatureData MainWindow::findMax2()
{
    float maxTemp=-1024.0f;
    QDateTime Max;
    for(int i=0;i<8641;i++)
    {
        if(this->tDat[i].temp2>maxTemp&&this->tDat[i].temp2!=1024)
        {
            maxTemp=this->tDat[i].temp2;
            Max=this->tDat[i].time;
        }
    }
    TemperatureData mT;
    mT.temp2=maxTemp;
    mT.time=Max;
    return mT;
}

TemperatureData MainWindow::findMin1()
{
    float minTemp=1024.0f;
    QDateTime Min;
    for(int i=0;i<8641;i++)
    {
        if(this->tDat[i].temp1<minTemp&&this->tDat[i].temp1!=1024)
        {
            minTemp=this->tDat[i].temp1;
            Min=this->tDat[i].time;
        }
    }
    TemperatureData mT;
    mT.temp1=minTemp;
    mT.time=Min;
    return mT;
}
TemperatureData MainWindow::findMin2()
{
    float minTemp=1024.0f;
    QDateTime Min;
    for(int i=0;i<8641;i++)
    {
        if(this->tDat[i].temp2<minTemp&&this->tDat[i].temp2!=1024)
        {
            minTemp=this->tDat[i].temp2;
            Min=this->tDat[i].time;
        }
    }
    TemperatureData mT;
    mT.temp2=minTemp;
    mT.time=Min;
    return mT;
}

void MainWindow::createSaveFile(void)
{

}

void MainWindow::saveData()
{

}

void MainWindow::loadData()
{

}
