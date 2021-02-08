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


#include "vid_server.h"



Vid_Server::Vid_Server( QObject *par, quint16 My_port, QString My_pass)
{

    server_port= My_port;
    server_password= My_pass;

    server = new QTcpServer(par);

    if (!server->listen(QHostAddress::Any, server_port)) // Starting the server on all available IP addresses and on port "server_port"
    {
        // If the server has not been started correctly
        qDebug() << " \n The server could not be started." ;
    }
    else
    {
        // If the server was successfully started
        qDebug() << " \n The server has been successfully started";

        connect(server, SIGNAL(newConnection()), this, SLOT(new_connection()));
    }

    data_size = 0;

    Host_pass=server_password;
    taille_ID=0;
    msg_recv="";


}

Vid_Server::~Vid_Server()
{
    server->close();
    delete server;

}


// This slot is called when a new client tries to connect to the server.
void Vid_Server::new_connection()
{
    emit changeInput(" \n NEW CLIENT");

    QTcpSocket *new_Client = server->nextPendingConnection();

    emit changeInput(" Ip Adress:" + new_Client->peerAddress().toString() );
    emit changeInput( " Port:" + QString::number(new_Client->peerPort()) );

    // client authentication

    // receive the password sent by the cient
    QByteArray array;

    // No waitForReadyRead may not get the data, because the network may be blocked
    while (new_Client->waitForReadyRead(500)) {

       array.append((QByteArray)new_Client->readAll());
    }

    QString pass= QString(array);

    //if the password sent by the client matches the server password, then it is added to the clients list
    if (pass == Host_pass)
    {
        My_Clients *My_nouveauClient= new My_Clients(new_Client);

        clients << My_nouveauClient;

        emit new_client(My_nouveauClient);
        connect(My_nouveauClient->My_socket, SIGNAL(disconnected()), this, SLOT(Client_disconnection()));
    }
    else
    {
        // Otherwise it is disconnected.
        new_Client->close();
    }


}



void Vid_Server::Client_disconnection()
{
    // We determine which client disconnects
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());

    if (socket == 0) // If we haven't found the client that emitted the signal, we stop this method.
        return;

    emit changeInput("Client disconnected ");
    emit changeInput(" Ip Adress:" + socket->peerAddress().toString() );
    emit changeInput( " Port:" + QString::number(socket->peerPort()) );

    for (int i = 0; i < clients.size(); i++)
    {
        if (clients[i]->My_socket == socket)
        {
            //remove the client from the connected clients tab
            emit remove_client(clients[i]);
            //remove the client from the clients list
            clients.removeOne(clients[i]);
        }
    }


    emit changeInput("Clients left : " + QString::number(clients.size()) +"\n");

    socket->deleteLater();

}



void Vid_Server::send_to_all(const QImage &frm)
{
    // Preparing the packet to be sent
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint32) 0; // Write 0 at the beginning of the packet to reserve the place for writing its size.
    out << frm; // add the data to be sent
    out.device()->seek(0); // We go back to the beginning of the packet
    out << (quint32) (paquet.size() - sizeof(quint32)); // We replace the 0 by the packet size

    // Sending the packet to all clients which are connected to the server
    for (int i = 0; i < clients.size(); i++)
    {
        clients[i]->My_socket->write(paquet);
    }

}




void Vid_Server::delete_all_clients()
{
    for (int i = 0; i < clients.size(); i++)
    {
        emit remove_client(clients[i]);

        clients.removeOne(clients[i]);
    }
}






