#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&processor,
                SIGNAL(inDisplay(QPixmap)),
                ui->inVideo,
                SLOT(setPixmap(QPixmap)));

    connect(&processor,
                SIGNAL(outDisplay(QPixmap)),
                ui->outVideo,
                SLOT(setPixmap(QPixmap)));
    processor.start();
}

MainWindow::~MainWindow()
{
    processor.requestInterruption();
    processor.wait();
    delete ui;
}

