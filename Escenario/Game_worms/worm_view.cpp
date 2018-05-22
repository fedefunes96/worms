#include "worm_view.h"
#include <QKeyEvent>
#include <QMutex>
#include <QDebug>
#include <QList>
#include "girder_view.h"

#include <QGraphicsScene>
#include "bazooka.h"





Worm_View::Worm_View(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    currentFrame = 0;
    spriteImage = new QPixmap(":/images/wormwait.png"); // Load the sprite image QPixmap
    timer = new QTimer();   // Create a timer for sprite animation
    timer->start(25);   // Run the sprite on the signal generation with a frequency of 25 ms
    currentDir.first = 0;
    currentDir.second = 0;
    destDir = currentDir;
    setAngle(0,0);
    count=0;
    vida = new QLabel();
    vida->setText("100");
    vida->setAttribute(Qt::WA_TranslucentBackground);
    vida->setStyleSheet("QLabel {color : red; }");
}



void Worm_View::setDir(int x, int y)
{
    currentDir.first = x;
    currentDir.second = y;
}

std::pair<int, int>& Worm_View::getAngle()
{
    return angle;
}

void Worm_View::add_label(){
    scene()->addWidget(vida);
}



void Worm_View::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /* In the graphic renderer we draw the sprite
     * The first two arguments - is the X and Y coordinates of where to put QPixmap
     * The third argument - a pointer to QPixmap
     * 4 and 5 of the arguments - The coordinates in the image QPixmap, where the image is displayed
     * By setting the X coordinate with the variable currentFrame we would like to move the camera on the sprite
     * and the last two arguments - the width and height of the displayed area, that is, the frame
     * */
    painter->drawPixmap(0,0, *spriteImage, 0, currentFrame, 50,43);
    Q_UNUSED(option);
    Q_UNUSED(widget);
    vida->setGeometry(x()+15,y()-10,30,20);
}

QRectF Worm_View::boundingRect() const
{
    return QRectF(0,0,50,43);//tamaño del worm
}





void Worm_View::set_idWorm(int id)
{
    this->id_worm = id;
}





bool Worm_View::collidingGirder()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();

    QList<QGraphicsItem*>::iterator it;
    for (it=colliding_items.begin();it!=colliding_items.end();it++)
    {
        if((*it)->type()==Girder_View().type()){
            return true;
        }
    }
    //qDebug()<<"no encontre nada";
    return false;

}

std::pair<int, int> &Worm_View::getDir()
{
    return currentDir;
}












bool Worm_View::movingRight()
{
    return ( (currentDir.first<destDir.first) && (currentDir.second==destDir.second) );
}


bool Worm_View::movingLeft()
{
    return ( (currentDir.first>destDir.first) && (currentDir.second==destDir.second) );
}

void Worm_View::delete_bullet(QGraphicsItem *item)
{
    delete(item);
}

bool Worm_View::movingDUpLeft()
{
    return ( (currentDir.first>destDir.first) && (currentDir.second > destDir.second) );
}

void Worm_View::setAngle(int x, int y)
{
    angle.first = x;
    angle.second = y;
}

void Worm_View::nextFrame2_Right(){
    if(currentDir == destDir)
    {
        qDebug()<<"Llegue a destino";
        //Llegue al destino
        currentFrame=0;
        spriteImage = new QPixmap(":/images/wormwait.png");
        this->update(0,0,50,43);
        timer->disconnect();
        return;
    }
    currentFrame += 60;
    if(currentFrame >= spriteImage->height())
    {
        currentFrame=0;
    }
    this->setPos(x()+1,y());
    setAngle(1,0);
    setDir(x(),y());
    this->update(0,0,50,43);
}


void Worm_View::nextFrame2_Left(){
    if(currentDir == destDir)
    {
        qDebug()<<"Llegue a destino";
        //Llegue al destino
        currentFrame=0;
        spriteImage = new QPixmap(":/images/wormwait.png");   
        this->update(0,0,50,43);
        timer->disconnect();
        return;
    }
    currentFrame += 60;
    if(currentFrame >= spriteImage->height())
    {
        currentFrame=0;
    }
    setPos(x()-1,y());
    setAngle(-1,0);
    setDir(x(),y());
    this->update(0,0,50,43);
}


void Worm_View::nextFrame2_UpLeft(){
    if(currentDir == destDir)
    {
        qDebug()<<"Llegue a destino";
        //Llegue al destino
        currentFrame=0;
        spriteImage = new QPixmap(":/images/wormwait.png");
        this->update(0,0,50,43);
        timer->disconnect();
        return;
    }
    currentFrame += 60;
    if(currentFrame >= spriteImage->height())
    {
        currentFrame=0;
    }
    this->setPos(x()-1,y()-1);
    setAngle(-1,-1);
    setDir(x(),y());
    this->update(0,0,50,43);
}




void Worm_View::nextFrame2_UpLeft30(){
    if(currentDir == destDir)
    {
        qDebug()<<"Llegue a destino";
        //Llegue al destino
        currentFrame=0;
        spriteImage = new QPixmap(":/images/wormwait.png");
        this->update(0,0,50,43);
        timer->disconnect();
        return;
    }
    currentFrame += 60;
    if(currentFrame >= spriteImage->height())
    {
        currentFrame=0;
    }
    if(count == 2)
    {
        this->setPos(x()-1,y()-1);
        count =0;
    }else{
        qDebug()<<count;
        this->setPos(x()-1,y());
        count++;
    }

    setAngle(-1,-1);
    setDir(x(),y());
    this->update(0,0,50,43);
}


void Worm_View::moveToPos(int posx,int posy)
{

    currentFrame = 0;
    timer->disconnect();

    destDir.first = posx;
    destDir.second = posy;

    if(movingRight())
    {
        qDebug()<<"moviendo derecha";
        spriteImage = new QPixmap(":/images/wwalk_right.png");
        connect(timer, &QTimer::timeout, this, &Worm_View::nextFrame2_Right);
        return;
    }
    if(movingLeft())
    {
        qDebug()<<"moviendo izquierda";
        spriteImage = new QPixmap(":/images/wwalk_left.png");
        connect(timer, &QTimer::timeout, this, &Worm_View::nextFrame2_Left);
        return;
    }


    if(movingDUpLeft())
    {
        qDebug()<<"moviendo diagonal arriba izq";
        spriteImage = new QPixmap(":/images/wwalku_l.png");
        //connect(timer, &QTimer::timeout, this, &Worm_View::nextFrame2_UpLeft30);
        connect(timer, &QTimer::timeout, this, &Worm_View::nextFrame2_UpLeft);
        return;
    }



}


void Worm_View::throwProjectile()
{
    Bazooka* g= new Bazooka(this);
    g->setPos(x()-5,y()+30);
    g->setRotation(133);
    scene()->addItem(g);
    g->fire();
}














