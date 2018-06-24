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

enum class MoveDirection : char {
    NONE = 0,
    RIGHT,
    LEFT,
    JUMP_FORW,
    JUMP_BACK
};

Worm_View::Worm_View()
{
}

Worm_View::~Worm_View()
{
    if(this->spriteImage){
        delete(this->spriteImage);
    }
    if(this->timer){
        delete(this->timer);
    }
    if(this->target){
        delete(this->target);
    }
    if(this->labelVida){
        delete(this->labelVida);
    }
    if(this->showSelected!=nullptr){
        delete(this->showSelected);
    }
    delete(this->fall);
    delete(this->jump);
    delete(this->wormDeath);
}


Worm_View::Worm_View(QObject *parent, QString color) :
    QObject(parent), MovableItem()
{
    this->last_on_ground=true;
    this->weapon=-1;
    this->weaponCountDwn=false;
    setIdObj(0);
    setFlag(QGraphicsItem::ItemIsSelectable);
    currentFrame = 0;
    spriteImage = new QPixmap(ROOT_PATH"/resources/images/wormwait.png");
    this->timer = new QTimer();
    this->timer->start(1);
    currentDir.first = 0;
    currentDir.second = 0;
    this->health=0;
    destDir = currentDir;
    alive=true;
    this->labelVida=nullptr;
    this->labelset=false;
    this->targetVis=false;
    this->target=nullptr;
    this->targetClick =false;
    this->moving = false;
    this->showSelected=nullptr;
    setAngle(0);
    this->selected=false;
    this->countDown=0;
    this->color = color;
    this->countFrame=0;
    this->last_on_ground=1;
    this->last_dir=0;
    this->jumping=false;
    this->fall = new generalSounds(ROOT_PATH"/resources/sounds/English/fall/NOOO.WAV");
    this->jump =  new generalSounds(ROOT_PATH"/resources/sounds/English/jump/JUMP1.WAV");
    this->wormDeath = new generalSounds(ROOT_PATH"/resources/sounds/English/BYEBYE.WAV");
    this->showlabelSelect=false;

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

void Worm_View::setHealth(int vida)
{
    this->health = vida;
}


void Worm_View::setStatus(int on_ground, int dir)
{
    QMatrix rm;
    QPixmap *aux;

    if(on_ground==1){
        if(dir==static_cast<int>(MoveDirection::LEFT)){
            this->jumping=false;
            this->targetVis=false;
            this->targetClick=false;
            this->weaponCountDwn=false;
            this->weapon=-1;
            this->loadSpriteWeapon(this->weapon);
            //mover izq
            qDebug()<<"set izq";
            if(this->last_dir!=static_cast<int>(MoveDirection::LEFT)){
                qDebug()<<"set izq2";
                if(this->last_dir==static_cast<int>(MoveDirection::JUMP_BACK) ||
                   this->last_dir==static_cast<int>(MoveDirection::JUMP_FORW) ||
                   this->last_on_ground==0){
                    this->moving=false;
                    setAngle(-180);
                }else if(this->angle!=-180){
                    this->moving=false;
                    setAngle(-180);
                }
            }else if(this->last_on_ground==0){
                setAngle(-180);
            }else if(this->weapon!=-1){
                qDebug()<<"Dejo de Cargar el arma...";
                setAngle(-180);
            }
            this->last_on_ground=on_ground;
            this->moving=true;
        }else if(dir==static_cast<int>(MoveDirection::RIGHT)){
            this->jumping=false;
            this->targetVis=false;
            this->targetClick=false;
            this->weaponCountDwn=false;
            this->weapon=-1;
            this->loadSpriteWeapon(this->weapon);
            //mover der
            qDebug()<<"set der";
            if(this->last_dir!=static_cast<int>(MoveDirection::RIGHT)){
                qDebug()<<"set der2";
                if(this->last_dir==static_cast<int>(MoveDirection::JUMP_BACK) ||
                   this->last_dir==static_cast<int>(MoveDirection::JUMP_FORW) ||
                        this->last_on_ground==0){
                    this->moving=false;
                    setAngle(0);
                }else if(this->angle!=0){
                    this->moving=false;
                    setAngle(0);
                }
                this->last_dir=dir;
            }else if(this->last_on_ground==0){
                setAngle(0);
            }else if(this->weapon!=-1){
                qDebug()<<"Dejo de Cargar el arma...";
                setAngle(0);
            }
            this->last_on_ground=on_ground;
            this->moving=true;
        }else if(dir==static_cast<int>(MoveDirection::JUMP_BACK)){
            //saltar
            this->targetVis=false;
            this->targetClick=false;
            this->weaponCountDwn=false;
            this->weapon=-1;
            this->loadSpriteWeapon(this->weapon);
            this->jumping=true;
            qDebug()<<"salte hacia atras";
            delete(this->spriteImage);
            this->currentFrame=0;
            aux = new QPixmap(ROOT_PATH"/resources/images/wbackflp.png");
            if(this->angle==0){
                rm.scale(-1,1);
            }else{
                rm.scale(1,1);
            }
            this->spriteImage = new QPixmap(aux->transformed(rm));
            delete(aux);
            aux = nullptr;
            this->last_dir=dir;
            this->last_on_ground=on_ground;
            this->moving=true;
            this->jump->play();
        }else if(dir==static_cast<int>(MoveDirection::JUMP_FORW) && this->last_dir!=dir){
            //saltar
            this->targetVis=false;
            this->targetClick=false;
            this->weaponCountDwn=false;
            this->weapon=-1;
            this->loadSpriteWeapon(this->weapon);
            this->jumping=true;
            qDebug()<<"salte hacia adelante";
            delete(this->spriteImage);
            this->currentFrame=0;
            aux = new QPixmap(ROOT_PATH"/resources/images/wfly.png");
            if(this->angle==0){
                rm.scale(-1,1);
            }else{
                rm.scale(1,1);
            }
            this->spriteImage = new QPixmap(aux->transformed(rm));
            delete(aux);
            aux = nullptr;
            this->last_dir=dir;
            this->last_on_ground=on_ground;
            this->moving=true;
            this->jump->play();
        }else if(dir==static_cast<int>(MoveDirection::NONE)){
            // dejar de moverme
            if(this->jumping){
                return;
            }
            qDebug()<<"deje de moverme";
            this->moving=false;
            this->targetVis=false;
            this->targetClick=false;
            this->weaponCountDwn=false;
            this->weapon=-1;
            this->loadSpriteWeapon(this->weapon);
            this->last_dir=dir;
            this->last_on_ground=on_ground;
        }
    }else{
        // esta en aire
        qDebug()<<"last dir:"<<this->last_dir;
        if(dir==static_cast<int>(MoveDirection::LEFT) || dir==static_cast<int>(MoveDirection::RIGHT)){
            if(this->jumping){
                //rotar imagen
                qDebug()<<"estoy saltando y quiero rotar";
                if(dir==static_cast<int>(MoveDirection::LEFT)){
                    //rotar a izq
                    this->angle=-180;
                    this->targetAngle=this->angle;
                }else{
                    this->angle=0;
                    this->targetAngle=this->angle;
                }
            }else if(this->last_dir==static_cast<int>(MoveDirection::LEFT) || this->last_dir==static_cast<int>(MoveDirection::RIGHT)){
                //me estoy cayendo ...
                qDebug()<<"me estoy cayendo.....";
                delete(this->spriteImage);
                this->currentFrame=0;
                aux = new QPixmap(ROOT_PATH"/resources/images/wfall.png");
                if(this->angle==0){
                    rm.scale(-1,1);
                }else{
                    rm.scale(1,1);
                }
                this->spriteImage = new QPixmap(aux->transformed(rm));
                delete(aux);
                aux = nullptr;
            }else if(this->last_dir==static_cast<int>(MoveDirection::JUMP_BACK) || this->last_dir==static_cast<int>(MoveDirection::JUMP_FORW)){
                qDebug()<<"Estaba saltando..roto";
                if(dir==static_cast<int>(MoveDirection::LEFT)){
                    //rotar a izq
                    this->angle=-180;
                    this->targetAngle=this->angle;
                }else{
                    this->angle=0;
                    this->targetAngle=this->angle;
                }
            }
        }else if(this->last_dir==static_cast<int>(MoveDirection::LEFT) || this->last_dir==static_cast<int>(MoveDirection::RIGHT)){
            //me estoy cayendo ...
            this->fall->play();
            qDebug()<<"me estoy cayendo.....";
            delete(this->spriteImage);
            this->currentFrame=0;
            aux = new QPixmap(ROOT_PATH"/resources/images/wfall.png");
            if(this->angle==0){
                rm.scale(-1,1);
            }else{
                rm.scale(1,1);
            }
            this->spriteImage = new QPixmap(aux->transformed(rm));
            delete(aux);
            aux = nullptr;
        }else if(dir==static_cast<int>(MoveDirection::NONE) && this->jumping==false){
            if(this->last_dir==static_cast<int>(MoveDirection::JUMP_BACK) ||
                    this->last_dir==static_cast<int>(MoveDirection::JUMP_FORW)){
                // estaba saltando no hacer nada...
            }else if(isFalling()){
                //me caigo solo o por golpe
                delete(this->spriteImage);
                this->currentFrame=0;
                aux = new QPixmap(ROOT_PATH"/resources/images/wfall.png");
                if(this->angle==0){
                    rm.scale(-1,1);
                }else{
                    rm.scale(1,1);
                }
                this->spriteImage = new QPixmap(aux->transformed(rm));
                delete(aux);
                aux = nullptr;
            }else{
                //sali volando
                delete(this->spriteImage);
                this->currentFrame=0;
                aux = new QPixmap(ROOT_PATH"/resources/images/wfly.png");
                if(this->angle==0){
                    rm.scale(-1,1);
                }else{
                    rm.scale(1,1);
                }
                this->spriteImage = new QPixmap(aux->transformed(rm));
                delete(aux);
                aux = nullptr;
            }
        }
        this->jumping=false;
        this->last_on_ground=on_ground;
    }

}

bool Worm_View::isFalling()
{
    return (this->lastDir.second < this->currentDir.second);
}

bool Worm_View::isFlying()
{
    return (this->lastDir.second > this->currentDir.second);
}

void Worm_View::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->showSelected==nullptr){
        this->showSelected = new QLabel();
        this->showSelected->setAttribute(Qt::WA_TranslucentBackground);
        this->showSelected->setPixmap(QPixmap(ROOT_PATH"/resources/images/selected.png"));
        scene()->addWidget(showSelected);
    }
    this->showSelected->setGeometry(x()+5,y()-40,56,41);
    this->showSelected->setVisible(this->showlabelSelect);
    if(!labelset){
        labelVida = new QLabel();
        labelVida->setAttribute(Qt::WA_TranslucentBackground);
        QColor clr(this->color);
        this->labelVida->setStyleSheet("color: #" + QString::number(clr.rgb(), 16));
        labelset=true;
        scene()->addWidget(labelVida);
        this->labelVida->setVisible(true);
    }
    QString aux;
    aux.setNum(this->health);
    labelVida->setText(aux);
    labelVida->setGeometry(x()+22,y()-10,30,20);
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
    return QRectF(0,0,60,60);
}


int Worm_View::getWeaponId()
{
    return this->weapon;
}

bool Worm_View::isWeaponCtD()
{
    return this->weaponCountDwn;
}

bool Worm_View::isSelect()
{
   return this->selected;
}

void Worm_View::setSelect(bool cond)
{
    this->selected = cond;
    if(cond==false){
        this->moving=false;
        this->targetVis=false;
    }
    this->showlabelSelect = cond;
}

void Worm_View::setAlive(bool alive)
{
    this->alive = alive;
}

int Worm_View::getX()
{
    return this->x();
}

int Worm_View::getY()
{
    return this->y();
}

QRectF Worm_View::areaRect()
{
    return this->boundingRect();
}

void Worm_View::setClickDir(int x, int y)
{
    this->clickTarget.first=x;
    this->clickTarget.second=y;
}

std::pair<int, int> Worm_View::getDirWeapon()
{
    std::pair<int,int> dir;
    if(!this->targetClick){
        dir.first=this->target->boundingRect().width();
        float aux = (tan( this->targetAngle * 3.1416 / 180 ))*dir.first;
        dir.second = abs(aux);
        if(this->targetAngle<-90 && this->targetAngle>=-270){
            dir.first = -dir.first;
            if(this->targetAngle<-180){
                dir.second = -dir.second;
            }
        }else if(this->targetAngle>0 && this->targetAngle<=90){
            dir.second = -dir.second;
        }
        dir.first = dir.first + this->currentDir.first;
        dir.second =  -this->currentDir.second + dir.second;
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
    this->lastDir.first=this->currentDir.first;
    this->lastDir.second=this->currentDir.second;
}

void Worm_View::setDestDir(int x, int y)
{
    int width = this->boundingRect().width();
    int height = this->boundingRect().height();
    this->destDir.first = x-width/2;
    this->destDir.second = -y-height/2;
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
    setDestDir(posx,posy);
    if(this->currentDir==this->destDir){
        return;
    }
    this->lastDir.first=this->currentDir.first;
    this->lastDir.second=this->currentDir.second;
    this->setPosition(posx,-posy);
    nextFrame();
	return;
}

void Worm_View::removeMovable()
{
    if(this->spriteImage){
        delete(this->spriteImage);
    }
    this->currentFrame=0;
    this->spriteImage = new QPixmap(ROOT_PATH"/resources/images/grave.png");
    this->alive=false;
    this->moving=false;
    this->selected=false;
    this->targetVis=false;
    if(this->labelVida!=nullptr){
        this->labelVida->setVisible(false);
    }
    this->showlabelSelect=false;
    if(this->showSelected!=nullptr){
        this->showSelected->setVisible(false);
    }
    this->wormDeath->play();
}

int Worm_View::getHealth()
{
    return this->health;
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
    this->countFrame=0;
    this->currentFrame=0;
    if(spriteImage)
    {
        delete(spriteImage);
    }
    QString path_L=ROOT_PATH"/resources/images/wwalk.png";
    loadSprite(path_L);
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
    this->targetVis = false;
    this->weaponCountDwn=false;
    if(this->isMoving()){
        qDebug()<<"se esta moviendo al cargar el arma";
        return;
    }
    this->weapon=val;
    qDebug()<<"weapon id"<<this->weapon;
    timer->disconnect();
    this->countDown=0;

    QString path1;

    switch (val) {
    case static_cast<int>(WeaponsIds::AERIAL_ATTACK):
    	currentFrame=0;
        timer->setInterval(35);
        path1 =ROOT_PATH"/resources/images/wairlnk.png";
        loadSprite(path1);
        this->targetClick=true;
        break;
    case static_cast<int>(WeaponsIds::BASEBALL_BAT):
    	currentFrame=0;
        timer->setInterval(35);
        path1 =ROOT_PATH"/resources/images/wbsblnk.png";
        loadSprite(path1);
        break;
    case static_cast<int>(WeaponsIds::BANANA):
    	currentFrame=0;
        timer->setInterval(35);
        path1 =ROOT_PATH"/resources/images/wbanlnk.png";
        loadSprite(path1);
        this->targetVis=true;
        this->weaponCountDwn=true;
        this->countDown=5;
        break;
    case static_cast<int>(WeaponsIds::DYNAMITE):
    	currentFrame=0;
        timer->setInterval(35);
        path1 =ROOT_PATH"/resources/images/wdynlnk.png";
        loadSprite(path1);
        this->weaponCountDwn=true;
        this->countDown=5;
        break;
    case static_cast<int>(WeaponsIds::RED_GRENADE):
    	currentFrame=0;
        timer->setInterval(35);
        path1 =ROOT_PATH"/resources/images/wclslnk.png";
        loadSprite(path1);
        this->targetVis=true;
        this->weaponCountDwn=true;
        this->countDown=5;
        break;
    case static_cast<int>(WeaponsIds::GREEN_GRENADE):
    	currentFrame=0;
        timer->setInterval(35);
        path1 =ROOT_PATH"/resources/images/wgrnlnk.png";
        loadSprite(path1);
        this->targetVis=true;
        this->weaponCountDwn=true;
        this->countDown=5;
        break;
    case static_cast<int>(WeaponsIds::HOLY_GRENADE):
    	currentFrame=0;
        timer->setInterval(35);
        path1 =ROOT_PATH"/resources/images/whgrlnk.png";
        loadSprite(path1);
        this->targetVis=true;
        this->weaponCountDwn=true;
        this->countDown=5;
        break;
    case static_cast<int>(WeaponsIds::MORTAR):
    	currentFrame=0;
        timer->setInterval(35);
        path1 =ROOT_PATH"/resources/images/wbazlnk.png";
        loadSprite(path1);
        this->targetVis=true;
        break;
    case static_cast<int>(WeaponsIds::TELEPORTATION):
    	currentFrame=0;
        timer->setInterval(35);
        path1 =ROOT_PATH"/resources/images/wtellnk.png";
        loadSprite(path1);
        this->targetClick=true;
        break;
    case static_cast<int>(WeaponsIds::BAZOOKA):
    	currentFrame=0;
        timer->setInterval(35);
        path1 =ROOT_PATH"/resources/images/wbz2lnk.png";
        loadSprite(path1);
        this->targetVis=true;
        break;

    default:
        path1 =ROOT_PATH"/resources/images/wwalk.png";
        loadSprite(path1);
    	return;
    }
    this->loadingWeapon = true;
    connect(timer, &QTimer::timeout, this, &Worm_View::runSpriteWeapon);
}

void Worm_View::loadSprite(QString& path_L)
{
    QMatrix rm;
    QPixmap* pix;
    QString path;
    path = path_L;
    if((this->angle==0))
    {
        rm.scale(-1,1);
    }else if(this->angle==-180){
        rm.scale(1,1);
    }
    pix = new QPixmap(path);
    this->spriteImage = new QPixmap(pix->transformed(rm));
    delete(pix);
}

void Worm_View::setTarget()
{
    this->target->setTarget(this->x(),this->y(),this->targetAngle);
}
