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


#ifndef CAMVIEWER_H
#define CAMVIEWER_H

#include <QGraphicsView>

/*Class used for displaying images and videos
 *Extends QGraphicsView >> Provides a widget to display QGraphics scene
*/
class CamViewer : public QGraphicsView
{

    public:
        CamViewer(QWidget* centralWidget) : QGraphicsView(centralWidget){}
        CamViewer(QGraphicsScene * scene, QWidget * parent =0) : QGraphicsView(scene, parent){}
        ~CamViewer(){}
        void setImage(QImage img);

    protected:
        void paintEvent(QPaintEvent* paintEventInfo);

    private:
        QImage image;

};

#endif // CAMVIEWER_H
