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


#ifndef CLIENT_WINDOW_H
#define CLIENT_WINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "camviewer.h"
#include <QtNetwork>
#include <QDebug>
#include <QImage>

namespace Ui {
class Client_Window;
}

class Client_Window : public QWidget
{
    Q_OBJECT

public:
    explicit Client_Window(QWidget *parent = nullptr);
    bool isCameraOn;
    ~Client_Window();

private slots:
    void on_pushButton_clicked();

    void data_received();
    void connected_to_server();
    void disconnected_from_server();
    void Socket_Error(QAbstractSocket::SocketError error);

private:
    Ui::Client_Window *ui;
    QGraphicsScene scene;

    QTcpSocket *socket; // server socket
    quint32 Data_size;

    void send_MSG(QString msg);

};

#endif // CLIENT_WINDOW_H
