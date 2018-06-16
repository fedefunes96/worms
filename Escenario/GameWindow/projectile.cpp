#include "projectile.h"
#include <QDebug>
#include <QGraphicsScene>


Projectile::Projectile():MovableItem()
{
    currentFrame=0;
    this->spriteImage = nullptr;
    timer = new QTimer();   // Create a timer for sprite animation
    this->alive=true;
}

Projectile::~Projectile()
{

}

void Projectile::nextFameImpact()
{
    currentFrame += 60;
    if(currentFrame >= spriteImage->height())
    {
        //qDebug()<<"TERMINE DE EXPLOTAR";
        timer->disconnect();
        timer->stop();
        this->alive=false;
        this->setVisible(false);
        this->selected=false;
        return;
    }
    this->update(0,0,60,60);
}

void Projectile::moveTo(int angle, int posx, int posy)
{
    //qDebug()<<"mover misil";
    int width = this->boundingRect().width();
    int height = this->boundingRect().height();
    QGraphicsScene* sc = this->scene();
    setPos(posx-width/2,sc->height()-posy-height/2);
    setTransform(QTransform().translate(30, 30).rotate(angle).translate(-30, -30));
}


bool Projectile::isMovable()
{
    return true;
}

bool Projectile::isAlive()
{
    return this->alive;
}

void Projectile::setPosition(int x, int y)
{
    int width = this->boundingRect().width();
    int height = this->boundingRect().height();
    setPos(x-width/2,y-height/2);
}



void Projectile::explote()
{

    // hacer que el timer sea singleshoot para hacer la animacion de la explosion...
    timer->start(30);
    delete(this->spriteImage);
    spriteImage = new QPixmap("../../images/shothit.png");
    //setPos(x()-30,y());
    currentFrame=0;
    connect(timer, &QTimer::timeout, this, &Projectile::nextFameImpact);
}

void Projectile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->drawPixmap(0,0, *spriteImage, 0, currentFrame, 60,60);
    Q_UNUSED(option);
    Q_UNUSED(widget);

}

QRectF Projectile::boundingRect() const
{
   return QRectF(0,0,60,60);
}



void Projectile::fire()
{
    //timer->disconnect();
    //connect(timer, &QTimer::timeout, this, &MisilBazooka::move);
}

void Projectile::setVisibility(bool vis)
{
    //this->setVisible(vis);
    this->explote();
}

bool Projectile::isSelect()
{
    return this->selected;
}

void Projectile::setSelect(bool cond)
{
    this->selected = cond;
}

void Projectile::setAlive(bool alive)
{
    this->alive = alive;
}


void Projectile::setSpriteBullet(std::string &path){
    this->spriteImage = new QPixmap(path.c_str());
}

bool Projectile::isMoving()
{
    return this->moving;
}
