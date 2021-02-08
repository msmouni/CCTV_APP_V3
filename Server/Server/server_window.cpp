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


#include "server_window.h"
#include "ui_server_window.h"



Server_Window::Server_Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server_Window)
{
    ui->setupUi(this);

    //the updateView() function is called every 30 millisec
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateView()));
    timer->start(30);

    ui->camViewer->setScene(&scene);

    //load Haar Cascade Classifier from file
    face_cascade.load(face_cascade_name);

    isServer_On=false;
}

Server_Window::~Server_Window()
{
    delete ui;
    if (video.isOpened())
    {
        video.release();
    }
}


void Server_Window::on_Button_connect_clicked()
{
    // Clear the display section
    ui->label->clear();

    // Create a video server
    My_server= new Vid_Server(this, ui->spin_port->value(), ui->Edit_pass->text());
    set_In_Text("Server connected !");


    // Connect the video server's Signals to the server window slots
    connect(My_server, SIGNAL(changeInput(QString)), this , SLOT(set_In_Text(QString)));
    connect(My_server, SIGNAL(new_client(My_Clients *)), this, SLOT(add_clients(My_Clients *)));
    connect(My_server, SIGNAL(remove_client(My_Clients *)), this, SLOT(delete_clients(My_Clients *)) );

    ui->Button_connect->setEnabled(false);
    ui->Button_disconnect->setEnabled(true);

    isServer_On=true;
}


void Server_Window::set_In_Text(QString input)
{
    ui->label->append(input);
}



void Server_Window::on_Button_disconnect_clicked()
{
    isServer_On=false;

    // Delete all clients from the client's tab
    My_server->delete_all_clients();

    delete My_server;

    ui->Button_connect->setEnabled(true);
    ui->Button_disconnect->setEnabled(false);


}


void Server_Window::on_Button_Start_clicked()
{
    if (video.isOpened())
    {
        video.release();
        // on the button
        ui->Button_Start->setText("Start Sending");
        // to display
        set_In_Text("Stop Sending");
    }
    else
    {
        video.open(CAM_ID);
        // on the button
        ui->Button_Start->setText("Stop Sending");
        // to display
        set_In_Text("Start Sending");
    }
}


void Server_Window::updateView()
{

    // If the video is not oppened we return
    if (!video.isOpened()) return;

    // If the video is oppened, we retrieve the frame
    cv::Mat frame;
    while(1)
    {
        video >> frame;
        if (!frame.empty())
        {
            break ;
        }
    }
    if (frame.empty()) return;

    // apply the changes to the image and then convert it to QImage
    QImage q_img=set_Image(frame, 200, 200);

    // display the result
    ui->camViewer->setImage(q_img);

    // if the server is connected, then we broadcast the image to all clients
    if (isServer_On)
    {
        My_server->send_to_all(q_img);
    }

}


QImage Server_Window::set_Image(cv::Mat frm, int h, int w)
{
    cv::Mat frame_gray;
    cv::Mat res_frm;

    cv::resize(frm, res_frm, cv::Size(w,h), 0, 0, cv::INTER_CUBIC);

    // transforming the colored image into gray image, in order to use it in the calssifier
    cv::cvtColor(res_frm, frame_gray, cv::COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    // using the classifier to detect faces, and saving them in a vector
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 4);

    // Drawing a rectangle around the detected faces
    for (std::size_t i=0; i< faces.size(); i++)
    {

        cv::Point pnt_1=cv::Point(faces[i].x, faces[i].y);
        cv::Point pnt_2=cv::Point(faces[i].x +faces[i].width, faces[i].y +faces[i].height);

        cv::rectangle(res_frm, pnt_1, pnt_2, cv::Scalar(0, 255, 0), 1);
    }

    //Convert cv::Mat to QImage
    QImage q_img=QImage((const unsigned char*)(res_frm.data),res_frm.cols,res_frm.rows,QImage::Format_RGB888);
    //Transform colors to RGB ~(diff between cv::Mat and QImage)
    q_img=q_img.rgbSwapped();


    return q_img;


}



// Add client to the connected clients Tab
void Server_Window::add_clients(My_Clients *client_to_add)
{

    QString client_addr=client_to_add->My_socket->peerAddress().toString();
    client_addr = "Ip adress :"+ client_addr +"   |";

    //quint16 to QString
    QString client_port = QString::number(client_to_add->My_socket->peerPort());
    client_port = " Port :" +client_port +"   |";

    QLabel *label_addr = new QLabel();
    label_addr->setText(client_addr);

    QLabel *label_port = new QLabel();
    label_port->setText(client_port);

    QPushButton *button_disconnect = new QPushButton("Disconnect");
    // saving a pointer to the button in order to use it for disconnecting the client
    client_to_add->set_Client_button(button_disconnect);


    QHBoxLayout *H_layout = new QHBoxLayout();
    H_layout->addWidget(label_addr);
    H_layout->addWidget(label_port);
    H_layout->addWidget(button_disconnect);

    // add H_layout the connected clients Tab
    ui->tab_2_layout->addLayout(H_layout);

    // saving a pointer to the layout in order to remove it later
    client_to_add->set_Client_layout(H_layout);


    ui->tab_2_layout->update();

}


// Delete client from to the connected clients Tab
void Server_Window::delete_clients(My_Clients *client_to_del)
{

    QHBoxLayout *V_layout =client_to_del->get_V_layout();


    // Remove all widgets within the layout so that they are no longer displayed
    // For more information please refer to the Qt documentation.
    // delete all
    QLayoutItem *child;
    while ((child = V_layout->takeAt(0)) !=0)
    {
        delete child->widget();
        delete child;
    }

    // then we delete the layout
    ui->tab_2_layout->removeItem(client_to_del->get_V_layout());
}
