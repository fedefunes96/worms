#include "worm_view.h"
#include <QKeyEvent>

#include <QDebug>
#include <QList>
#include "girder_view.h"

#include <QGraphicsScene>

#include <string>
#include <QString>
#include <QImage>
#include <QMatrix>
#include <QTransform>
#include <math.h>

enum class WeaponsIds : uint8_t {
    BAZOOKA = 0,
    MORTAR,
    GREEN_GRENADE,
    RED_GRENADE,
    BANANA,
    HOLY_GRENADE,
    DYNAMITE,
    BASEBALL_BAT,
    AERIAL_ATTACK,
    TELEPORTATION
};

Worm_View::Worm_View(QObject *parent) :
    QObject(parent), MovableItem()
{


    this->weapon=-1; //wormwait
    this->weaponCountDwn=false;
    setIdObj(0);
    setFlag(QGraphicsItem::ItemIsSelectable);
    currentFrame = 0;
    //this->timer=nullptr;
    spriteImage = new QPixmap("../../images/wormwait.png"); // Load the sprite image QPixmap
    this->timer = new QTimer();   // Create a timer for sprite animation
    this->timer->start(1);   // Run the sprite on the signal generation with a frequency of 25 ms
    currentDir.first = 0;
    currentDir.second = 0;
    this->health=0;
    destDir = currentDir;
    count=0;
    alive=true; // check this after recvDamage()

    this->labelset=false;
    this->targetVis=false;
    this->target=nullptr;
    this->targetClick =false;
    this->moving = false;

    setAngle(0);
    this->selected=false;
    this->countDown=0;


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
    qDebug()<<"anguloooooooo: "<<this->targetAngle;
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

void Worm_View::setHealth(int vida)
{
    this->health = vida;
}


void Worm_View::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    
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
    labelVida->setGeometry(x()+22,y()-10,30,20);
    if(x()<30){
        labelVida->setVisible(false);
    }


    if(this->targetVis){

    }
    if(!this->target){
        this->target = new Target();
        this->scene()->addItem(this->target);
    }
    this->target->setVisible(this->targetVis);
    setTarget();
    painter->drawPixmap(0,0, *spriteImage, 0, currentFrame, 60,60);
    Q_UNUSED(option);
    Q_UNUSED(widget);

}

QRectF Worm_View::boundingRect() const
{
    return QRectF(0,0,60,60);//tamaño del worm
}


int Worm_View::getWeaponId()
{
    return this->weapon;
}

bool Worm_View::isSelect()
{
   return this->selected;
}

void Worm_View::setSelect(bool cond)
{
    this->selected = cond;
}

void Worm_View::setAlive(bool alive)
{
    this->alive = alive;
}

void Worm_View::setClickDir(int x, int y)
{/////////////////CHEQUEAR LO QUE DA EL CLICK DEL TELETRANSPORTAR
    this->clickTarget.first=x;
    this->clickTarget.second=y;
}

std::pair<int, int> Worm_View::getDirWeapon()
{
    std::pair<int,int> dir;
    if(!this->targetClick){
        dir.first=this->target->boundingRect().width();  //tam target x. =150
        //qDebug()<<"ancho target"<<dir.first;
        //qDebug()<<this->currentDir.first<<this->currentDir.second;
        float aux = (tan( this->targetAngle * 3.1416 / 180 ))*dir.first;
        dir.second = abs(aux);
        //qDebug()<<"nadsjksda"<<dir.second;
        if(this->targetAngle<-90 && this->targetAngle>=-270){
            dir.first = -dir.first;
            if(this->targetAngle<-180){
                dir.second = -dir.second;
            }
        }else if(this->targetAngle>0 && this->targetAngle<=90){
            dir.second = -dir.second;
        }
        int w = this->scene()->width();
        dir.first = dir.first + this->currentDir.first;
        dir.second = w - this->currentDir.second + dir.second;
        //qDebug()<<"dir x:"<<dir.first<<" dir y:"<<dir.second<<"angle"<<-this->targetAngle;
    }else{
        return this->clickTarget;
    }
    return dir;
}

int Worm_View::getTimeWeapon(){
    return this->countDown;
}

void Worm_View::setTimeWeapon(int time){
    this->countDown = time;
}

bool Worm_View::isMovable()
{
    return true;
}


int Worm_View::getTargetAngle(){
    return this->targetAngle;
}


std::pair<int, int> &Worm_View::getDir()
{
    return currentDir;
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
    this->targetClick=false;
    this->weaponCountDwn=false;
    this->weapon=-1;
    this->loadSpriteWeapon(this->weapon);
    setDestDir(posx,posy);
    if(this->currentDir==this->destDir){
        return;
    }
    this->moving=true;
    //checkAngle(angle);
    QGraphicsScene* sc = scene();
    this->setPosition(posx,sc->height()-posy);
    this->moving=false;
	return;
}

void Worm_View::setVisibility(bool vis)
{
    this->setVisible(vis);
    this->targetVis=false;
    this->labelVida->setVisible(vis);
}



void Worm_View::checkAngle(int angle)
{
    if(angle>4){
        setAngle(-angle);
    }
}



bool Worm_View::isMoving()
{
	return this->moving;
}




void Worm_View::setSprite()
{
    if(spriteImage)
    {
        delete(spriteImage);
    }

    QString path_L="../../images/wwalk.png";
    QString path_U="../../images/wwalku.png";
    QString path_D="../../images/wwalkd.png";
    QString path_Fly="../../images/wfly.png";
    QString path_Fall="../../images/wfall.png";

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







bool Worm_View::hasClickeableTarget(){
    return this->targetClick;
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
        this->loadingWeapon = false;
        return;
    }
    this->update(0,0,60,60);
}


void Worm_View::loadSpriteWeapon(int val)
{
    if(this->isMoving()){
        return;
    }
    this->weapon=val;
    qDebug()<<"weapon id"<<this->weapon;
    timer->disconnect();
    this->countDown=0;

    QString path1;
    QString path2;
    QString path3;

    switch (val) {
    case static_cast<int>(WeaponsIds::AERIAL_ATTACK):
    	currentFrame=0;
        timer->setInterval(35);
        path1 ="../../images/wairlnk.png";
        path2 ="../../images/wairlnku.png";
        path3 ="../../images/wairlnkd.png";
        loadSprite(path1,path2,path3);
        this->targetClick=true;
        break;
    case static_cast<int>(WeaponsIds::BASEBALL_BAT):
    	currentFrame=0;
        timer->setInterval(35);
        path1 ="../../images/wbsblnk.png";
        path2 ="../../images/wbsblnku.png";
        path3 ="../../images/wbsblnkd.png";
        loadSprite(path1,path2,path3);
        this->targetVis=true;
        break;
    case static_cast<int>(WeaponsIds::BANANA):
    	currentFrame=0;
        timer->setInterval(35);
        path1 ="../../images/wbanlnk.png";
        path2 ="../../images/wbanlnku.png";
        path3 ="../../images/wbanlnkd.png";
        loadSprite(path1,path2,path3);
        this->targetVis=true;
        this->weaponCountDwn=true;
        this->countDown=5;
        break;
    case static_cast<int>(WeaponsIds::DYNAMITE):
    	currentFrame=0;
        timer->setInterval(35);
        path1 ="../../images/wdynlnk.png";
        path2 ="../../images/wdynlnku.png";
        path3 ="../../images/wdynlnkd.png";
        loadSprite(path1,path2,path3);
        this->weaponCountDwn=true;
        this->countDown=5;
        break;
    case static_cast<int>(WeaponsIds::RED_GRENADE):
    	currentFrame=0;
        timer->setInterval(35);
        path1 ="../../images/wclslnk.png";
        path2 ="../../images/wclslnku.png";
        path3 ="../../images/wclslnkd.png";
        loadSprite(path1,path2,path3);
        this->targetVis=true;
        this->weaponCountDwn=true;
        this->countDown=5;
        break;
    case static_cast<int>(WeaponsIds::GREEN_GRENADE):
    	currentFrame=0;
        timer->setInterval(35);
        path1 ="../../images/wgrnlnk.png";
        path2 ="../../images/wgrnlnku.png";
        path3 ="../../images/wgrnlnkd.png";
        loadSprite(path1,path2,path3);
        this->targetVis=true;
        this->weaponCountDwn=true;
        this->countDown=5;
        break;
    case static_cast<int>(WeaponsIds::HOLY_GRENADE):
    	currentFrame=0;
        timer->setInterval(35);
        path1 ="../../images/whgrlnk.png";
        path2 ="../../images/whgrlnku.png";
        path3 ="../../images/whgrlnkd.png";
        loadSprite(path1,path2,path3);
        this->targetVis=true;
        this->weaponCountDwn=true;
        this->countDown=5;
        break;
    case static_cast<int>(WeaponsIds::MORTAR):
    	currentFrame=0;
        timer->setInterval(35);
        path1 ="../../images/wbazlnk.png";
        path2 ="../../images/wbazlnku.png";
        path3 ="../../images/wbazlnkd.png";
        loadSprite(path1,path2,path3);
        this->targetVis=true;
        break;
    case static_cast<int>(WeaponsIds::TELEPORTATION):
    	currentFrame=0;
        timer->setInterval(35);
        path1 ="../../images/wtellnk.png";
        path2 ="../../images/wtellnku.png";
        path3 ="../../images/wtellnkd.png";
        loadSprite(path1,path2,path3);
        this->targetClick=true;
        break;
    case static_cast<int>(WeaponsIds::BAZOOKA):
    	currentFrame=0;
        timer->setInterval(35);
        path1 ="../../images/wbazlnk.png";
        path2 ="../../images/wbazlnku.png";
        path3 ="../../images/wbazlnkd.png";
        loadSprite(path1,path2,path3);
        this->targetVis=true;
        break;

    default:
        path1 ="../../images/wwalk.png";
        path2 ="../../images/wwalku.png";
        path3 ="../../images/wwalkd.png";
        loadSprite(path1,path2,path3);
    	return;
        //break;
    }
    this->loadingWeapon = true;
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











