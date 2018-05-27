#include "worm_view.h"
#include <QKeyEvent>
#include <QMutex>
#include <QDebug>
#include <QList>
#include "girder_view.h"

#include <QGraphicsScene>
#include "bazooka.h"

#include <string>



Worm_View::Worm_View(QObject *parent) :
    QObject(parent), MovableItem()
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    currentFrame = 0;
    spriteImage = new QPixmap(":/images/wormwait.png"); // Load the sprite image QPixmap
    timer = new QTimer();   // Create a timer for sprite animation
    timer->start(25);   // Run the sprite on the signal generation with a frequency of 25 ms
    currentDir.first = 0;
    currentDir.second = 0;
    this->vida=0;
    destDir = currentDir;
    count=0;
    alive=true; // check this after recvDamage()

    this->labelset=false;
/* ---> VER TEMA CAMBIAR COLOR VIDA
    QString colour; // you can use also QColor
    QString text;
    // ...
    QString template = tr("<font color='%1'>%2</font>");
    somelabel->setText( template.arg( colour, text ) );

*/

}

bool Worm_View::isAlive()
{
    return this->alive;
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

void Worm_View::setVida(int vida)
{
    this->vida = vida;
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
    painter->drawPixmap(0,0, *spriteImage, 0, currentFrame, 60,60);
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(!labelset){
        labelVida = new QLabel();
        labelVida->setAttribute(Qt::WA_TranslucentBackground);
        labelVida->setStyleSheet("QLabel {color : red; }");
        labelset=true;
        scene()->addWidget(labelVida);
    }
    QString aux;
    aux.setNum(this->vida);
    labelVida->setText(aux);
    labelVida->setGeometry(x()+15,y()-10,30,20);
}

QRectF Worm_View::boundingRect() const
{
    return QRectF(0,0,60,60);//tamaño del worm
}





void Worm_View::set_idWorm(int id)
{
    this->id = id;
}

int Worm_View::getId()
{
    return this->id;
}

bool Worm_View::isMovable()
{
    return true;
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



//tendria que guardarme el angulo ... no cordenadas? o no importa si son 5 o 15 grados? total el sprite seria el mismo...
//pero si importa si es inclinado, hacia donde up,down,left,right...
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
        this->update(0,0,60,60);
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
    this->update(0,0,60,60);
}


void Worm_View::nextFrame2_Left(){
    if(currentDir == destDir)
    {
        qDebug()<<"Llegue a destino";
        //Llegue al destino
        currentFrame=0;
        spriteImage = new QPixmap(":/images/wormwait.png");   
        this->update(0,0,60,60);
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
    this->update(0,0,60,60);
}







void Worm_View::moveTo(int angle, int posx,int posy)
{

    currentFrame = 0;
    timer->disconnect();
    setSprite(angle);

    destDir.first = posx;
    destDir.second = posy;
    qDebug()<<"pos actual:"<<currentDir.first<<" -- "<<currentDir.second;
    qDebug()<<"pos dest  :"<<posx<<" -- "<<posy;


    if(angle!=0 && angle!=-180 && angle!=-360){
        moveDiag(angle,posx,posy);
    }


    if(movingRight())
    {
        qDebug()<<"moviendo derecha";
        //spriteImage = new QPixmap(":/images/wwalk_right.png");
        connect(timer, &QTimer::timeout, this, &Worm_View::nextFrame2_Right);
        return;
    }
    if(movingLeft())
    {
        qDebug()<<"moviendo izquierda";
        //spriteImage = new QPixmap(":/images/wwalk_left.png");
        connect(timer, &QTimer::timeout, this, &Worm_View::nextFrame2_Left);
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


void Worm_View::setSprite(int angle)
{
    if(!spriteImage)
    {
        delete(spriteImage);
    }

    if(angle==0 || angle==-360){
        spriteImage = new QPixmap(":/images/wwalk_right.png");
    }else if(angle==-180){
        spriteImage = new QPixmap(":/images/wwalk_left.png");
    }else if(angle>-90){
        spriteImage = new QPixmap(":/images/wwalku_r.png");
    }else if(angle>-180 && angle<-90){
        qDebug()<<"set image ";
        spriteImage = new QPixmap(":/images/wwalku_l.png");
    }else if(angle<-180 && angle>-270){
        spriteImage = new QPixmap(":/images/wwalkd_l.png");
    }else if(angle<-270){
        spriteImage = new QPixmap(":/images/wwalkd_r.png");
    }else{
        spriteImage = nullptr;
    }
}





















































/////////////////////////////////////////////////////



void Worm_View::move()
{
    qDebug()<<"posX:"<<x()<<" posY:"<<y();
    if(currentDir == destDir)
    {
        qDebug()<<"llegue al destino";
        //desconecto el timer de la funcion.. llegue al destino...
        return;
    }
    currentFrame+=60;
    if(!spriteImage){
        qDebug()<<"no hay imagen";
    }
    if(currentFrame >= spriteImage->height())
    {
        currentFrame=0;
    }

    if(this->desp == this->cant)
    {
        this->desp=0;
        if(this->count == this->rep)
        {
            //hacer funcion swap
            this->count=0;
            int aux = this->rep;
            this->rep = this->rep2;
            this->rep2 = aux;
            aux=this->cant;
            this->cant = this->x2;
            this->x2=aux;
        }else{
            this->count++;
        }
        //check var para ver si sube o baja
        if(this->movUP){
            setPos(x(),y()+1);
        }else{
            setPos(x(),y()-1);
        }
        this->update(0,0,60,60);
        setDir(x(),y());
        return;
    }
    // check var para ver si va a der o izq
    if(this->movR){
        setPos(x()+1,y());
    }else{
        setPos(x()-1,y());
    }
    this->desp++;
    setDir(x(),y());
    this->update(0,0,60,60);
}







void Worm_View::setVarsMove(int cant,int x2, int rep, int rep2,bool movUP,bool movR)
{
    this->cant=cant;
    this->x2=x2;
    this->rep=rep;
    this->rep2=rep2;
    this->count=1;
    this->desp=0;
    this->movUP=movUP;
    this->movR=movR;
}

//previo tengo que setear cant = cant de x1 ; x2 = cant de x2 ; rep2 = cantidad de rep de x2 ; rep = cantidad de rep de x1 ; desp en 0 y count =1.

void Worm_View::moveDiag(int angle, int posX, int posY)
{
    bool right = true;
    bool up = false;

    if((angle==-5) || (angle==-175) || (angle==-185) || (angle==-355))
    {
        if((angle==-175) || (angle==-185)){right=false;}
        if((angle==-355) || (angle==-185)){up=true;}
        setVarsMove(11,12,1,1,up,right);
    }else if((angle==-10) || (angle==-170) || (angle==-190) || (angle==-350))
    {
        if((angle==-170) || (angle==-190)){right=false;}
        if((angle==-350) || (angle==-190)){up=true;}
        setVarsMove(6,5,2,1,up,right);
    }else if((angle==-15) || (angle==-165) || (angle==-195) || (angle==-345))
    {
        if((angle==-165) || (angle==-195)){right=false;}
        if((angle==-345) || (angle==-195)){up=true;}
        setVarsMove(4,4,1,1,up,right);
    }else if((angle==-20) || (angle==-160) || (angle==-200) || (angle==-340))
    {
        qDebug()<<"entre";
        if((angle==-160) || (angle==-200)){right=false;}
        if((angle==-340) || (angle==-200)){up=true;}
        setVarsMove(4,4,1,1,up,right);
    }else if((angle==-25) || (angle==-155) || (angle==-205) || (angle==-335))
    {
        if((angle==-155) || (angle==-205)){right=false;}
        if((angle==-335) || (angle==-205)){up=true;}
        setVarsMove(3,4,5,2,up,right);
    }else if((angle==-30) || (angle==-150) || (angle==-210) || (angle==-330))
    {
        if((angle==-150) || (angle==-210)){right=false;}
        if((angle==-330) || (angle==-210)){up=true;}
        setVarsMove(3,2,3,1,up,right);
    }else if((angle==-35) || (angle==-145) || (angle==-215) || (angle==-325))
    {
        // CASO PARTICULAR...
        qDebug()<<"aun no desarrollado...";
    }else if((angle==-40) || (angle==-140) || (angle==-220) || (angle==-320))
    {
        if((angle==-140) || (angle==-220)){right=false;}
        if((angle==-320) || (angle==-220)){up=true;}
        setVarsMove(2,3,4,1,up,right);
    }else if((angle==-45) || (angle==-135) || (angle==-225) || (angle==-315))
    {
        if((angle==-135) || (angle==-225)){right=false;}
        if((angle==-315) || (angle==-225)){up=true;}
        setVarsMove(1,1,1,1,up,right);
    }

    connect(timer, &QTimer::timeout, this, &Worm_View::move);
}














