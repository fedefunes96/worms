#include "worm_view.h"
#include <QKeyEvent>

#include <QDebug>
#include <QList>
#include "girder_view.h"

#include <QGraphicsScene>
#include "bazooka.h"

#include <string>
#include <QString>
#include <QImage>
#include <QMatrix>
#include <QTransform>




Worm_View::Worm_View(QObject *parent) :
    QObject(parent), MovableItem()
{


    this->weapon=99; //wormwait
    setIdObj(0);
    setFlag(QGraphicsItem::ItemIsSelectable);
    currentFrame = 0;
    //this->timer=nullptr;
    spriteImage = new QPixmap(":/images/wormwait.png"); // Load the sprite image QPixmap
    this->timer = new QTimer();   // Create a timer for sprite animation
    this->timer->start(1000);   // Run the sprite on the signal generation with a frequency of 25 ms
    currentDir.first = 0;
    currentDir.second = 0;
    this->health=0;
    destDir = currentDir;
    count=0;
    alive=true; // check this after recvDamage()

    this->labelset=false;
    this->targetVis=false;
    this->target=nullptr;


    setAngle(0);


}

void Worm_View::setAngle(int angle)
{
    this->angle=angle;
    this->targetAngle=angle;
    setSprite();
}

bool Worm_View::isAlive()
{
    return this->alive;
}





void Worm_View::movTargetAngle(int dir){
    if((this->targetAngle==-90 && dir==1) || (this->targetAngle==-270 && dir==-1) || (this->targetAngle==90 && dir==-1)){
        return;
    }
    if(this->angle<-90 && this->angle>-270){
        this->targetAngle += dir;
    }else{
        this->targetAngle-=dir;
    }
    this->setTarget();
}


void Worm_View::setDir(int x, int y)
{
    currentDir.first = x;
    currentDir.second = y;
}

int Worm_View::getAngle()
{
    return angle;
}

void Worm_View::setVida(int vida)
{
    this->health = vida;
}


void Worm_View::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

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
    aux.setNum(this->health);
    labelVida->setText(aux);
    labelVida->setGeometry(x()+15,y()-10,30,20);


    if(this->targetVis){

    }
    if(!this->target){
        this->target = new Target();
        this->scene()->addItem(this->target);
    }
    this->target->setVisible(this->targetVis);
    setTarget();

}

QRectF Worm_View::boundingRect() const
{
    return QRectF(0,0,60,60);//tamaño del worm
}




bool Worm_View::isMovable()
{
    return true;
}




std::pair<int, int> &Worm_View::getDir()
{
    return currentDir;
}





void Worm_View::delete_bullet(QGraphicsItem *item)
{
    delete(item);
}




void Worm_View::setPosition(int x, int y)
{
    int width = this->boundingRect().width();
    int height = this->boundingRect().height();

    setPos(x-width/2,y-height/2);
    setDir(x-width/2,y-height/2);
    qDebug()<<"posx:"<<x-width/2<<"posy"<<y-height/2;
}

void Worm_View::setDestDir(int x, int y)
{
    int width = this->boundingRect().width();
    int height = this->boundingRect().height();
    QGraphicsScene* sc = scene();
    this->destDir.first = x-width/2;
    this->destDir.second = sc->height()-y-height/2;
}

void Worm_View::nextFrame(){
    currentFrame += 60;
    if(currentFrame >= spriteImage->height())
    {
        currentFrame=0;
    }
    this->update(0,0,60,60);
}

void Worm_View::moveTo(int angle, int posx,int posy)
{
    this->targetVis=false;

    timer->setInterval(23);
    if((angle==-270)||(this->angle>-135 && this->angle<-45))
    {
        timer->setInterval(10);// sirve para que setear la nueva velocidad..
        timer->disconnect();
    }
    currentFrame = 0;
    setAngle(angle);
    timer->disconnect();
    if(this->spriteImage== nullptr){
        qDebug()<<"aun no hay imagen...";
        return;
    }
    setDestDir(posx,posy);
    if(currentDir==destDir){
        return;
    }
    this->checkDelta();
    connect(timer, &QTimer::timeout, this, &Worm_View::mover);
}


void Worm_View::throwProjectile()
{
    //prueba
    Bazooka* g= new Bazooka(this);
    g->setPos(x()-5,y()+30);
    g->setRotation(133);
    scene()->addItem(g);
    g->fire();
}


void Worm_View::setSprite()
{
    if(!spriteImage)
    {
        delete(spriteImage);
    }

    QString path_L=":/images/wwalk.png";
    QString path_U=":/images/wwalku.png";
    QString path_D=":/images/wwalkd.png";
    QString path_Fly=":/images/wfly.png";
    QString path_Fall=":/images/wfall.png";

    loadSprite(path_L,path_U,path_D,path_Fly,path_Fall);
}




void Worm_View::stepSprite(){
    currentFrame+=60;
    if(!spriteImage){
        qDebug()<<"no hay imagen";
        return;
    }
    if(currentFrame >= spriteImage->height())
    {
        currentFrame=0;
    }
    this->update(0,0,60,60);
}

void Worm_View::moveStep()
{
    if(this->firstX){
        if(this->desp==this->x1){
            if(this->x2>0){
                setPos(x(),y()+this->up);
                setDir(x(),y());
                stepSprite();
            }
            checkDelta();
            return;
        }else{            
            this->desp++;
            setPos(x()+this->right,y());
        }
    }else{
        if(this->desp==this->x2){
            if(this->x1>0){
                setPos(x()+this->right,y());
                setDir(x(),y());
                stepSprite();
            }
            checkDelta();
            return;
        }else{
            this->desp++;
            setPos(x(),y()+this->up);
        }

    }
    setDir(x(),y());
    stepSprite();
}

void Worm_View::setVars(int cant1,int cant2,int up, int right, bool firsX)
{
    this->desp=0;
    this->x1 = cant1;
    this->x2 = cant2;
    this->up = up;
    this->right = right;
    this->firstX = firsX;
}

void Worm_View::mover()
{

    qDebug()<<"actual--> x:"<<currentDir.first<<"y:"<<currentDir.second;
    qDebug()<<"dest  --> x:"<<destDir.first<<"y:"<<destDir.second;
    if(currentDir == destDir)
    {
        qDebug()<<x();
        qDebug()<<"llegue al destino";
        timer->disconnect();
        loadSpriteWeapon(this->weapon);
        return;
    }
    moveStep();
}


void Worm_View::checkDelta()
{
    if(currentDir==destDir){
        timer->disconnect();
        qDebug()<<"LLEGUE";
        loadSpriteWeapon(this->weapon);
        return;
    }
    int dX = abs (currentDir.first-destDir.first);
    int dY = abs (currentDir.second-destDir.second);
    int cant1=0;
    int cant2=0;
    bool firstX=true;
    int up = ((this->angle<0 && this->angle>-180) ? -1 : 1);
    int right = (((this->angle<=0 && this->angle>-90) || (this->angle>-270 && this->angle<=-360)) ? 1 : -1);
    //condition ? value_if_true : value_if_false

    if(dY<=0){
        cant1=dX;
    }else if(dX<=0){
        cant2=dY;
        firstX=false;
    }else if(dX >= dY){
        cant1= int(((float)dX / (float)dY)+0.5);
        cant2=1;
    }else{
        cant2= int(((float)dY / (float)dX)+0.5);
        cant1=1;
        firstX=false;
    }
//    qDebug()<<"angle:"<<this->angle;
//    qDebug()<<"right val:"<<right;
//    qDebug()<<"up val:"<<up;
//    qDebug()<<"dX:"<<dX<<"dY:"<<dY<<"cant1:"<<cant1<<"cant2:"<<cant2;
    this->setVars(cant1,cant2,up,right,firstX);
}


void Worm_View::runSpriteWeapon()
{
    currentFrame+=60;
    if(!spriteImage){
        qDebug()<<"no hay imagen";
        return;
    }
    if(currentFrame >= spriteImage->height())
    {
        currentFrame-=60;
        this->update(0,0,60,60);
        this->timer->disconnect();
        return;
    }
    this->update(0,0,60,60);
}






void Worm_View::loadSpriteWeapon(int val)
{
    this->weapon=val;
    timer->disconnect();
    timer->setInterval(35);
    currentFrame=0;

    QString path1;
    QString path2;
    QString path3;

    switch (val) {
    case 0:
        path1 =":/images/wairlnk.png";
        path2 =":/images/wairlnku.png";
        path3 =":/images/wairlnkd.png";
        loadSprite(path1,path2,path3);
        this->targetVis=true;
        break;
    case 1:
        path1 =":/images/wbsblnk.png";
        path2 =":/images/wbsblnku.png";
        path3 =":/images/wbsblnkd.png";
        loadSprite(path1,path2,path3);
        break;
    case 2:
        path1 =":/images/wbanlnk.png";
        path2 =":/images/wbanlnku.png";
        path3 =":/images/wbanlnkd.png";
        loadSprite(path1,path2,path3);
        break;
    case 3:
        path1 =":/images/wdynlnk.png";
        path2 =":/images/wdynlnku.png";
        path3 =":/images/wdynlnkd.png";
        loadSprite(path1,path2,path3);
        break;
    case 4:
        path1 =":/images/wclslnk.png";
        path2 =":/images/wclslnku.png";
        path3 =":/images/wclslnkd.png";
        loadSprite(path1,path2,path3);
        break;
    case 5:
        path1 =":/images/wgrnlnk.png";
        path2 =":/images/wgrnlnku.png";
        path3 =":/images/wgrnlnkd.png";
        loadSprite(path1,path2,path3);
        break;
    case 6:
        path1 =":/images/whgrlnk.png";
        path2 =":/images/whgrlnku.png";
        path3 =":/images/whgrlnkd.png";
        loadSprite(path1,path2,path3);
        break;
    case 7:
        path1 =":/images/wbazlnk.png";
        path2 =":/images/wbazlnku.png";
        path3 =":/images/wbazlnkd.png";
        loadSprite(path1,path2,path3);
        break;
    case 8:
        this->spriteImage = new QPixmap(":/images/wtellnk.png");
        path1 =":/images/wtellnk.png";
        path2 =":/images/wtellnku.png";
        path3 =":/images/wtellnkd.png";
        loadSprite(path1,path2,path3);
        break;
    case 9:
        path1 =":/images/wbazlnk.png";
        path2 =":/images/wbazlnku.png";
        path3 =":/images/wbazlnkd.png";
        loadSprite(path1,path2,path3);
        break;
    case 10:
        //aca dejo al worm ocmo estaba en su pos...
        this->spriteImage = new QPixmap(":/images/wormwait.png");
        break;

    default:
        path1 =":/images/wwait.png";
        path2 =":/images/wwaitu.png";
        path3 =":/images/wwaitd.png";
        loadSprite(path1,path2,path3);
        break;
    }
    connect(timer, &QTimer::timeout, this, &Worm_View::runSpriteWeapon);
}





void Worm_View::loadSprite(QString& path_L,QString& path_U,QString path_D,QString path_Fly,QString path_Fall)
{
    QMatrix rm;
    QPixmap* pix;
    QString path;
    path = path_L;
    if((this->angle==0) || (this->angle==-360))
    {
        rm.scale(-1,1);
    }else if(this->angle==-180){
        rm.scale(1,1);
    }else if((this->angle<0 && this->angle>=-45) || (this->angle>-180 && this->angle<=-135)){
        path = path_U;
        if(this->angle>=-135){
            rm.scale(-1,1);
        }else{
            rm.scale(1,1);
        }
    }else if((this->angle<-360 && this->angle>=-315) || (this->angle<-180 && this->angle>=-225)){
        path = path_D;
        if(this->angle>=-315){
            rm.scale(-1,1);
        }else{
            rm.scale(1,1);
        }
    }else if(this->angle<-45 && this->angle>-135){
        path = path_Fly;
        if(this->angle>=-90){
            rm.scale(1,1);
        }else{
            rm.scale(-1,1);
        }
    }else{
        path = path_Fall;
        if(this->angle>=-270){
            rm.scale(1,1);
        }else{
            rm.scale(-1,1);
        }
    }
    pix = new QPixmap(path);
    this->spriteImage = new QPixmap(pix->transformed(rm));
    delete(pix);
}









void Worm_View::setTarget()
{
    this->target->setTarget(this->x(),this->y(),this->targetAngle);
}











