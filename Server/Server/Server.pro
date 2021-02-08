# ***************************************************************
# ***************************************************************
# ***********                                         ***********
# ***********    CCTV Project with face detection     ***********
# ***********                                         ***********
# ***********      Developed by : SMOUNI Marwan       ***********
# ***********                                         ***********
# ***************************************************************
# ***************************************************************

QT += widgets core gui network

HEADERS += \
    camviewer.h \
    my_clients.h \
    server_window.h \
    vid_server.h

SOURCES += \
    camviewer.cpp \
    main.cpp \
    my_clients.cpp \
    server_window.cpp \
    vid_server.cpp

FORMS += \
    server_window.ui



# Please choose the paths associated with your OpenCV installation

# For more informations about how to setup Qt and openCV :
# https://wiki.qt.io/OpenCV_with_Qt
# https://wiki.qt.io/How_to_setup_Qt_and_openCV_on_Windows


INCLUDEPATH += D:\Programs\OpenCV\opencv\build\include

#INCLUDEPATH += D:\Programs\OpenCV\opencv\build\bin\

LIBS += D:\Programs\OpenCV\opencv\build\bin\libopencv_core451.dll
LIBS += D:\Programs\OpenCV\opencv\build\bin\libopencv_highgui451.dll
LIBS += D:\Programs\OpenCV\opencv\build\bin\libopencv_imgcodecs451.dll
LIBS += D:\Programs\OpenCV\opencv\build\bin\libopencv_imgproc451.dll
LIBS += D:\Programs\OpenCV\opencv\build\bin\libopencv_features2d451.dll
LIBS += D:\Programs\OpenCV\opencv\build\bin\libopencv_calib3d451.dll
LIBS += D:\Programs\OpenCV\opencv\build\bin\libopencv_video451.dll
LIBS += D:\Programs\OpenCV\opencv\build\bin\libopencv_videoio451.dll
LIBS += D:\Programs\OpenCV\opencv\build\bin\libopencv_objdetect451.dll


