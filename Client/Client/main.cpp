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

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client_Window w;
    w.show();
    return a.exec();
}