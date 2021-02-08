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



#ifndef MY_CLIENTS_H
#define MY_CLIENTS_H

#include <QWidget>
#include <QtNetwork>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>


class My_Clients : public QWidget
{
    Q_OBJECT
public:
    My_Clients(QTcpSocket *soc_client);
    QHBoxLayout* get_V_layout();
    QTcpSocket *My_socket;
    void set_Client_layout(QHBoxLayout* My_layout);
    void set_Client_button(QPushButton* Cl_button);

    virtual ~My_Clients() {};

private slots:
    void diconnect_Cl();

private:
    QString My_address;
    quint16 My_port;
    QLabel *label_address;
    QLabel *label_port;
    QHBoxLayout *V_layout;
    QPushButton *My_button;
};

#endif // MY_CLIENTS_H
