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


#include "my_clients.h"

My_Clients::My_Clients(QTcpSocket *soc_client)
{
    My_socket = soc_client;

    //Layout vertical : IP et Port
    My_address= soc_client->peerAddress().toString();
    My_port = soc_client->peerPort();

    QLabel *label_address = new QLabel();
    label_address->setText(My_address);
    QLabel *label_port = new QLabel();
    label_port->setNum(My_port);

    QVBoxLayout *V_layout =new QVBoxLayout();
    V_layout->addWidget(label_address);
    V_layout->addWidget(label_port);

}



QHBoxLayout* My_Clients::get_V_layout()
{
    return V_layout;
}


void My_Clients::set_Client_layout(QHBoxLayout* My_layout)
{
    V_layout=My_layout;
}

void My_Clients::set_Client_button(QPushButton* Cl_button)
{
    My_button= Cl_button;
    connect(My_button, SIGNAL(clicked()), this, SLOT(diconnect_Cl()));
}

void My_Clients::diconnect_Cl()
{
    My_socket->close();
}


