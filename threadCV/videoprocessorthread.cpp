#include "videoprocessorthread.h"

VideoProcessorThread::VideoProcessorThread(QObject *parent) : QThread(parent)
{

}
void VideoProcessorThread::run()
{
    using namespace cv;
    using namespace std;
    VideoCapture camera(0);
    Mat inFrame, outFrame;
    while(camera.isOpened() && !isInterruptionRequested())
    {
        camera >> inFrame;
        if(inFrame.empty())
            continue;
        cvtColor(inFrame, outFrame, COLOR_RGB2BGR);
        cvtColor(outFrame, outFrame, COLOR_BGR2GRAY);
        //bitwise_not(inFrame, outFrame);

        Mat mask =Mat::zeros(outFrame.size(), CV_32FC3);

        Mat img = outFrame.clone();
        //img.convertTo(img, CV_32FC1);
        GaussianBlur(img, img, Size(0, 0), 3, 3);
        //一阶偏导数
        Mat m1, m2;
        m1 = (Mat_<float>(1, 2) << 1, -1);
        m2 = (Mat_<float>(2, 1) << 1, -1);
        Mat dx, dy;
        filter2D(img, dx, CV_32FC1, m1);
        filter2D(img, dy, CV_32FC1, m2);

        //二阶偏导数
        Mat m3, m4, m5;
        m3 = (Mat_<float>(1, 3) << 1, -2, 1);
        m4 = (Mat_<float>(3, 1) << 1, -2, 1);
        m5 = (Mat_<float>(2, 2) << 1, -1, -1, 1);

        Mat dxx, dyy, dxy;
        filter2D(img, dxx, CV_32FC1, m3);
        filter2D(img, dyy, CV_32FC1, m4);
        filter2D(img, dxy, CV_32FC1, m5);

        //hessian矩阵
        int imgcol = img.cols;
        int imgrow = img.rows;
        vector<double> Pt;
        for (int i=0;i<imgcol;i++)
        {
            for (int j=0;j<imgrow;j++)
            {
                if (outFrame.at<uchar>(j,i)>200)
                {
                    Mat hessian(2, 2, CV_32FC1);
                    hessian.at<float>(0, 0) = dxx.at<float>(j, i);
                    hessian.at<float>(0, 1) = dxy.at<float>(j, i);
                    hessian.at<float>(1, 0) = dxy.at<float>(j, i);
                    hessian.at<float>(1, 1) = dyy.at<float>(j, i);

                    Mat eValue;
                    Mat eVectors;
                    eigen(hessian, eValue, eVectors);

                    double nx, ny;
                    double fmaxD = 0;
                    if (fabs(eValue.at<float>(0,0))>= fabs(eValue.at<float>(1,0)))  //求特征值最大时对应的特征向量
                    {
                        nx = eVectors.at<float>(0, 0);
                        ny = eVectors.at<float>(0, 1);
                        fmaxD = eValue.at<float>(0, 0);
                    }
                    else
                    {
                        nx = eVectors.at<float>(1, 0);
                        ny = eVectors.at<float>(1, 1);
                        fmaxD = eValue.at<float>(1, 0);
                    }

                    double t = -(nx*dx.at<float>(j, i) + ny*dy.at<float>(j, i)) / (nx*nx*dxx.at<float>(j,i)+2*nx*ny*dxy.at<float>(j,i)+ny*ny*dyy.at<float>(j,i));

                    if (fabs(t*nx)<=0.5 && fabs(t*ny)<=0.5)
                    {
                        Pt.push_back(i);
                        Pt.push_back(j);
                    }
                }
            }
        }
        //检测是否为空
        if(Pt.empty())
            continue;

        //cvtColor(img, outFrame, COLOR_GRAY2RGB);

        //保存找到的所有点
        vector<Point> max;
        for (int k = 0; k < int(Pt.size()/2); k++)
        {
            Point rpt;
            rpt.x = static_cast<int>(Pt[2 * k + 0]);
            rpt.y = static_cast<int>(Pt[2 * k + 1]);
            circle(img, rpt, 2, Scalar(0, 0, 0));
            if(rpt.x > 0||rpt.y > 0)
            {
                max.push_back(rpt);
            }else{
                continue;
            }
        }

        emit inDisplay(
                    QPixmap::fromImage(
                        QImage(
                            inFrame.data,
                            inFrame.cols,
                            inFrame.rows,
                            inFrame.step,
                            QImage::Format_RGB888)
                        .rgbSwapped()));

        emit outDisplay(
                    QPixmap::fromImage(
                        QImage(
                            img.data,
                            img.cols,
                            img.rows,
                            img.step,
                            QImage::Format_Indexed8)
                        .rgbSwapped()));
    }
}
