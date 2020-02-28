#include "qcvwidget.h"
#include "ui_qcvwidget.h"
#include "opencvworker.h"
#include "QDebug"

#include <QTimer>
#include <QDateTime>
#include <cstdlib>

double QCvWidget::position_x;
double QCvWidget::position_y;

QCvWidget::QCvWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QCvWidget)
{
    ui->setupUi(this);
    ui->labelView->setScaledContents(true);
    setup();
}

QCvWidget::~QCvWidget()
{
    thread->quit();
    while(!thread->isFinished());

    delete thread;
    delete ui;
}

void QCvWidget::setup()
{
    thread = new QThread();
    OpenCvWorker *worker = new OpenCvWorker();
    QTimer *workerTrigger = new QTimer();
    //QTimer *workerInterval = new QTimer();


    workerTrigger->setInterval(1);
    connect(workerTrigger, SIGNAL(timeout()), worker, SLOT(receiveGrabFrame()));
    connect(thread, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), workerTrigger, SLOT(deleteLater()));
    connect(this, SIGNAL(sendSetup(int)), worker, SLOT(receiveSetup(int)));
    connect(this, SIGNAL(sendToggleStream()), worker, SLOT(receiveToggleStream()));
    connect(ui->pushButtonPlay, SIGNAL(clicked(bool)), this, SLOT(receiveToggleStream()));
    connect(ui->checkBoxEnableBinaryThreshold, SIGNAL(toggled(bool)), worker, SLOT(receiveEnableBinaryThreshold()));
    connect(ui->spinBoxBinaryThreshold, SIGNAL(valueChanged(int)), worker, SLOT(receiveBinaryThreshold(int)));
    connect(worker, SIGNAL(sendFrame(QImage)), this, SLOT(receiveFrame(QImage)));
    connect(thread, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), workerTrigger, SLOT(deleteLater()));

    connect(worker, SIGNAL(sendFrame(QImage)), this, SLOT(showData()));

    //workerInterval->start(1000);

    workerTrigger->start();
    worker->moveToThread(thread);
//    worker->deleteLater();
    workerTrigger->moveToThread(thread);
//    workerTrigger->deleteLater();

    thread->start();

    emit sendSetup(0);
}

void QCvWidget::receiveFrame(QImage frame)
{
    ui->labelView->setPixmap(QPixmap::fromImage(frame));
}

void QCvWidget::receiveToggleStream()
{
    if(!ui->pushButtonPlay->text().compare(">"))
    {
        ui->pushButtonPlay->setText("||");
    }
    else
    {
        ui->pushButtonPlay->setText(">");
    }
    emit sendToggleStream();
}



void QCvWidget::showData()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
    //QString current_data = QString("%1 %2").arg(current_date).arg(QString::number(worker->num));
    QString x_position ="  x:";
    QString y_position ="  y:";
    QString unit ="mm";

    QString current_data = QString("%1 %2 %3 %4 %5 %6 %7").arg(current_date).arg(x_position).arg(QString::number(QCvWidget::position_x)).arg(unit).arg(y_position).arg(QString::number(QCvWidget::position_y)).arg(unit);
    if(position_x == 0 && position_y == 0)
    {

    }
    else
    {
        ui->textBrowser->append(current_data);
    }
}



