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


#include "client_window.h"
#include "ui_client_window.h"

Client_Window::Client_Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client_Window)
{
    ui->setupUi(this);
    ui->camViewer->setScene(&scene);

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(data_received()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected_to_server()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected_from_server()));
    //connect(socket, SIGNAL(errorOccured(QAbstractSocket::SocketError)), this, SLOT(Socket_Error(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(Socket_Error(QAbstractSocket::SocketError))); //Depending on Qt Version

    Data_size = 0;

}



Client_Window::~Client_Window()
{
    delete ui;
}


void Client_Window::on_pushButton_clicked()
{
    if (!socket->isOpen()){
        // If the client is not yet connected

        ui->pushButton->setEnabled(false);
        ui->pushButton->setText("Stop");

        ui->text_Info->clear();

        socket->abort(); // Previous connections are turned off
        socket->connectToHost(ui->host_ip->text(), ui->port->value()); // Connect to the specified server

        // Send password for authentication
        send_MSG(ui->password->text());

    }
    else {
        // If the client is already connected
        socket->close();
        ui->pushButton->setText("Start");
    }
}


// This slot is called when data are received from the server
void Client_Window::data_received()
{
    QDataStream in(socket);

    // For more informations refer to the sending method in the server : "send_to_all"
    // We first collect the packet size
    if (Data_size == 0)
    {
        if (socket->bytesAvailable() < (int)sizeof(quint32))
             return;

        in >> Data_size;
    }

    if (socket->bytesAvailable() < Data_size)
        return;


    // Then we retrieve the sent packet, in this case the image
    QImage imgRecu;
    in >> imgRecu;


    // Set image on the GUI
    ui->camViewer->setImage(imgRecu);


    // The message size is reset to 0 in order to be able to receive incoming packets
    Data_size = 0;
}


// This slot is called when the connection to the server succeeded
void Client_Window::connected_to_server()
{
    ui->pushButton->setEnabled(true);
    ui->text_Info->append("\n Connected to the server");
}

// This slot is called when disconnected from the server.
void Client_Window::disconnected_from_server()
{
    if (socket->isOpen())
    {
        socket->close();
        ui->pushButton->setText("Start");
    }

    ui->text_Info->append("\n Disconnected from the server");

}


// This function is used to send a text message to the server.
void Client_Window::send_MSG(QString msg)
{

    QByteArray paquet;

    //paquet.append(msg); //Depending on Qt Version

    // Changing QString into a char *
    QByteArray msg_array=msg.toLatin1();
    paquet.append(msg_array);

    socket->write(paquet);

    socket->waitForBytesWritten();

}


// This slot is called when an error occurs.
void Client_Window::Socket_Error(QAbstractSocket::SocketError erreur)
{
    if (socket->isOpen())
    {
        socket->close();
        ui->pushButton->setText("Start");
    }

    switch(erreur) // We display a different message depending on the error
    {
        case QAbstractSocket::HostNotFoundError:
            ui->text_Info->append("\n ERROR: the server could not be reached. Check IP and port.");
            break;

        case QAbstractSocket::ConnectionRefusedError:
            ui->text_Info->append("\n ERROR: the server refused the connection. Check if the server is connected. Check IP, port, and password.");
            break;

        case QAbstractSocket::RemoteHostClosedError:
            ui->text_Info->append("\n ERROR: Connection has been closed by the server.");
            break;

        default:
            ui->text_Info->append("\n ERREUR : " + socket->errorString());
    }

    ui->pushButton->setEnabled(true);
}

