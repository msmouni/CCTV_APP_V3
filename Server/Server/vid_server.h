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



#ifndef VID_SERVER_H
#define VID_SERVER_H

#include <QWidget>
#include <QtNetwork>
#include <QDebug>

#include "my_clients.h"


/*
 *This class represents a server that manages the clients connected to it
 * and broadcasts the processed images to them.
*/

class Vid_Server : public QWidget
{
    Q_OBJECT

    public:
        Vid_Server(QObject *par, quint16 My_port, QString My_password);
        ~Vid_Server();

        void send_to_all(const QImage &frm);//envoyerATous(const QImage &frm);

        void delete_all_clients();


    private slots:
        void new_connection();//nouvelleConnexion();
        void Client_disconnection();//deconnexionClient();

    private:
        QTcpServer *server;
        QList<My_Clients *> clients;


        //use quint32 instead of quint16 : large image size
        quint32 data_size;

        QString Host_pass;
        quint16 taille_ID;
        QString msg_recv;

        quint16 server_port;
        QString server_password;


    signals:
        void changeInput(QString input);

        void pass_rcvd (QTcpSocket *sc_clt, QString pass_rcv);

        void new_client(My_Clients *client_to_add);
        void remove_client(My_Clients *client_to_remove);
};

#endif // VID_SERVER_H
