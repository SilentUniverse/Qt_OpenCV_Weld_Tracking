#include "opencvworker.h"
#include <opencv2/imgproc/imgproc.hpp>
#include "QDebug"
#include "qcvwidget.h"
#include <QTimer>
#include <QDateTime>
using namespace cv;
using namespace std;

OpenCvWorker::OpenCvWorker(QObject *parent) :
    QObject(parent),
    status(false),
    toggleStream(false),
    binaryThresholdEnable(false),
    binaryThreshold(127)
{
    //cv::VideoCapture cap(0);
    cap = new cv::VideoCapture();
}

OpenCvWorker::~OpenCvWorker()
{
    if(cap->isOpened()) cap->release();
    delete cap;
}

void OpenCvWorker::checkIfDeviceAlreadyOpened(const int device)
{
    if(cap->isOpened()) cap->release();
    cap->open(device);
}


double OpenCvWorker::process()
{

    cvtColor(_frameOriginal, _frameProcessed, COLOR_BGR2GRAY);
    GaussianBlur(_frameProcessed, _frameProcessed, Size(7, 7), 0, 0);
    std::vector<Point2f> corners;
    goodFeaturesToTrack(_frameProcessed, corners, 12, 0.04, 10, Mat());
    //亚像素
    Size winsize = Size(5, 5);
    Size zerozone = Size(-1, -1);// 拟合时使用 零区域
    TermCriteria tc = TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 40, 0.001);
    cornerSubPix(_frameProcessed, corners, winsize, zerozone, tc);
    for (int i = 0; i < int(corners.size()); i++)
    {
        std::vector<Point2f> max;
        if(corners[i].y < 260 & corners[i].y > 220)//视频流分辨率为640乘以480
        {
            max = corners;
            circle(_frameProcessed, max[i], 2, Scalar(0,0,0), 2);
            //qDebug() << i << ".point[x,y]=" << corners[i].x << "," << corners[i].y << endl;
            //return num = QString::number(corners[i].x);
            QCvWidget::position_x = corners[i].x;
            QCvWidget::position_y = corners[i].y;

            //qDebug() << num;
            //return QCvWidget::position_x;

        }

    }

    if(binaryThresholdEnable) {
        cv::threshold(_frameProcessed, _frameProcessed, binaryThreshold, 255, cv::THRESH_BINARY);

    }
}

void OpenCvWorker::receiveGrabFrame()
{
    if(!toggleStream) return;

    (*cap) >> _frameOriginal;
    if(_frameOriginal.empty()) return;

    process();

    QImage output((const unsigned char *)_frameProcessed.data, _frameProcessed.cols, _frameProcessed.rows, QImage::Format_Indexed8);
    emit sendFrame(output);
}

void OpenCvWorker::receiveSetup(const int device)
{
    checkIfDeviceAlreadyOpened(device);
    if(!cap->isOpened()) {
        status = false;
        return;
    }

    status = true;
}

void OpenCvWorker::receiveToggleStream() {
    toggleStream = !toggleStream;
}

void OpenCvWorker::receiveEnableBinaryThreshold() {
    binaryThresholdEnable = !binaryThresholdEnable;
}

void OpenCvWorker::receiveBinaryThreshold(int threshold) {
    binaryThreshold = threshold;
}

