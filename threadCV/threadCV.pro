QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    videoprocessorthread.cpp

HEADERS += \
    mainwindow.h \
    videoprocessorthread.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#opencv
INCLUDEPATH += /usr/include/opencv4\
               /usr/include/opencv4/opencv2\
               /usr/include/opencv4/opencv2/opencv_modules.hpp\
               /usr/include/opencv4/opencv2/opencv.hpp\


LIBS += /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.4.1.1\
        /usr/lib/x86_64-linux-gnu/libopencv_videoio.so \
        /usr/lib/x86_64-linux-gnu/libopencv_flann.so\
        /usr/lib/x86_64-linux-gnu/libopencv_ml.so\
        /usr/lib/x86_64-linux-gnu/libopencv_dnn.so.4.1\
        /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.4.1.1\
        /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so\
        /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so\
        /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.4.1.1\
        /usr/lib/x86_64-linux-gnu/libopencv_ml.so.4.1\
        /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.4.1\
        /usr/lib/x86_64-linux-gnu/libopencv_highgui.so\
        /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.4.1.1\
        /usr/lib/x86_64-linux-gnu/libopencv_video.so\
        /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.4.1\
        /usr/lib/x86_64-linux-gnu/libopencv_photo.so.4.1.1\
        /usr/lib/x86_64-linux-gnu/libopencv_photo.so\
        /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.4.1\
        /usr/lib/x86_64-linux-gnu/libopencv_gapi.so.4.1\
        /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so\
        /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.4.1.1\
        /usr/lib/x86_64-linux-gnu/libopencv_core.so\
        /usr/lib/x86_64-linux-gnu/libopencv_stitching.so\
        /usr/lib/x86_64-linux-gnu/libopencv_gapi.so\
        /usr/lib/x86_64-linux-gnu/libopencv_photo.so.4.1\
        /usr/lib/x86_64-linux-gnu/libopencv_video.so.4.1.1\
        /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.4.1\
        /usr/lib/x86_64-linux-gnu/libopencv_flann.so.4.1\
        /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.4.1\
        /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.4.1.1\
        /usr/lib/x86_64-linux-gnu/libopencv_core.so.4.1.1\
        /usr/lib/x86_64-linux-gnu/libopencv_features2d.so\
        /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.4.1\
        /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so\
        /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.4.1\
        /usr/lib/x86_64-linux-gnu/libopencv_dnn.so\
        /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.4.1.1\
        /usr/lib/x86_64-linux-gnu/libopencv_flann.so.4.1.1\
        /usr/lib/x86_64-linux-gnu/libopencv_gapi.so.4.1.1\
        /usr/lib/x86_64-linux-gnu/libopencv_core.so.4.1\
        /usr/lib/x86_64-linux-gnu/libopencv_ml.so.4.1.1\
        /usr/lib/x86_64-linux-gnu/libopencv_video.so.4.1\
        /usr/lib/x86_64-linux-gnu/libopencv_dnn.so.4.1.1\
        /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.4.1.1\
        /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.4.1\
