#include "projectile.h"
#include <QDebug>
#include <QGraphicsScene>


Projectile::Projectile():MovableItem()
{
    currentFrame=0;
    this->spriteImage = nullptr;
    timer = new QTimer();
    this->alive=true;
    this->explotionSound = new generalSounds(ROOT_PATH"/resources/sounds/English/Explosion.wav");
}


Projectile::~Projectile()
{
    if(this->timer){
        delete(this->timer);
    }
    if(this->spriteImage){
        delete(this->spriteImage);
    }
    delete(this->explotionSound);
}


void Projectile::nextFameImpact()
{
    currentFrame += 60;
    if(currentFrame >= spriteImage->height())
    {
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
    int width = this->boundingRect().width();
    int height = this->boundingRect().height();
    setPos(posx-width/2,-posy-height/2);
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
    timer->start(30);
    delete(this->spriteImage);
    spriteImage = new QPixmap(ROOT_PATH"/resources/images/shothit.png");
    currentFrame=0;
    connect(timer, &QTimer::timeout, this, &Projectile::nextFameImpact);
    this->explotionSound->play();
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

void Projectile::removeMovable()
{
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

int Projectile::getX()
{
    return this->x();
}

int Projectile::getY()
{
    return this->y();
}

QRectF Projectile::areaRect()
{
    return this->boundingRect();
}
