#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    countdown = new QTimer(); //Construct the timer
    countdown->setInterval(1000); //One second interval
    countdown->setSingleShot(false); //Multiple shot. This means that the signal timeout will be signed each second
    connect(countdown,SIGNAL(timeout()),this,SLOT(timeOut())); //Connects the timeout signal to my slot timeOut
}

MainWindow::~MainWindow()
{
    delete ui;
}

void  MainWindow::timeOut()
{
    int Hours;
    int Minutes;
    int Seconds;
    if (startMilliseconds - 1000 >= 0) //If not timeout
    {
    startMilliseconds = startMilliseconds - 1000; //Reduce the milliseconds with 1 second (1000)
    //Convert milliseconds to H:M:S
    Hours = startMilliseconds / (1000*60*60);
    Minutes = (startMilliseconds % (1000*60*60)) / (1000*60);
    Seconds = ((startMilliseconds % (1000*60*60)) % (1000*60)) / 1000;

        //Move the H:M:S to the labels
    ui->lcdH->display(QString::number(Hours));
    ui->lcdM->display(QString::number(Minutes));
    ui->lcdS->display(QString::number(Seconds));

        if (startMilliseconds <=0) //If timeout
        {
            countdown->stop(); //Stop the timer
        }
    }
    else
    {
        countdown->stop(); //Stop the timer
    }

    if (startMilliseconds ==0) //If countdown = 0
    {
        QProcess::execute("dbus-send --system --print-reply --dest=org.freedesktop.ConsoleKit /org/freedesktop/ConsoleKit/Manager org.freedesktop.ConsoleKit.Manager.Stop"); //Launch command
    }
}

void MainWindow::on_btStart_clicked()
{
    //Converts the start paramenters into milliseconds
    startMilliseconds = QString(ui->spinBoxH->text()).toInt() * 1000 * 60 * 60;
    startMilliseconds = startMilliseconds + QString(ui->spinBoxM->text()).toInt() * 1000 * 60;
    startMilliseconds = startMilliseconds + QString(ui->spinBoxS->text()).toInt() * 1000;
    countdown->start(); //Start the timer
}

void MainWindow::on_btStop_clicked()
{
    countdown->stop(); //Stop the timer
}
