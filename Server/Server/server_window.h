/***************************************************************
 ***************************************************************
 ***********                                         ***********
 ***********    CCTV Project with face detection     ***********
 ***********                                         ***********
 ***********      Developed by : SMOUNI Marwan       ***********
 ***********                                         ***********
 ***************************************************************
 ***************************************************************
*/


#ifndef SERVER_WINDOW_H
#define SERVER_WINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "camviewer.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include <QImage>
#include <QDebug>

#define CAM_ID 0

#include "vid_server.h"

#include "my_clients.h"

namespace Ui {
class Server_Window;
}

class Server_Window : public QWidget
{
    Q_OBJECT

public:
    explicit Server_Window(QWidget *parent = nullptr);
    bool isCameraOn;
    bool isServer_On;
    QImage set_Image(cv::Mat frm, int h, int w);

    ~Server_Window();

private slots:
    void on_Button_Start_clicked();
    void updateView(void); // connected to a timer
    void set_In_Text(QString input);

    void add_clients(My_Clients *client_to_add);
    void delete_clients(My_Clients *client_to_del);

    void on_Button_connect_clicked();
    void on_Button_disconnect_clicked();


private:
    Ui::Server_Window *ui;
    QGraphicsScene scene;
    cv::VideoCapture video; //WebCam capture
    cv::Mat frame; // to store the current frame

    Vid_Server *My_server;

    //HAAR CASCADE Classifier
    cv::CascadeClassifier face_cascade;
    cv::String face_cascade_name ="../haarcascade_frontalface.xml"; // Path to the classifier file
    cv::Mat frame_gray; // to convert the current frame to gray
};

#endif // SERVER_WINDOW_H
