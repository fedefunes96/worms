#include "stage.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPen>
#include <QGraphicsView>
#include "movable.h"


Stage::Stage()
{
}

Stage::~Stage()
{
    delete(this->scene);
    delete(this->timerUpdate);
}

Stage::Stage(int w,int h)
{
    this->scene = new QGraphicsScene();
    this->scene->setSceneRect(0,-h,w,h);
    this->timerUpdate = new QTimer();
    connect(this->timerUpdate,&QTimer::timeout,this,&Stage::update_view);
    this->timerUpdate->start(10);
}

void Stage::addCamera(Camera *camera)
{
    this->camera = camera;
}

void Stage::resizeScene(int w, int h)
{
    qDebug()<<"screen w:"<<w<<"h"<<h;
    this->scene->setSceneRect(0,-h,w,h);
}


QGraphicsScene* Stage::getScene()
{
    return this->scene;
}

int Stage::getHeight()
{
   return this->scene->height();
}

int Stage::getWidth()
{
   return this->scene->width();
}


void Stage::update_view()
{
    this->scene->update(this->scene->sceneRect());
}

void Stage::add_Item(QGraphicsItem *item, int posx, int posy)
{
    this->items_list.push_back(dynamic_cast<Items*>(item));
    this->scene->addItem(item);
    Items* i = dynamic_cast<Items*>(item);
    i->setPosition(posx,-posy);
}

bool Stage::containsItem(int8_t id_typ, int32_t id){
    std::vector<Items*>::iterator it;
    for ( it = this->items_list.begin(); it!=this->items_list.end();it++){
        if(((static_cast<Items*>(*it))->getId()==id) && (static_cast<Items*>(*it))->getIdObj()==id_typ){
            return true;
        }
    }
    return false;
}

Items* Stage::getItem(int8_t id_type, int32_t id)
{
    std::vector<Items*>::iterator it;
    for ( it = this->items_list.begin(); it!=this->items_list.end();it++){
        Items* item = static_cast<Items*>(*it);
        if((item->getId()==id) && (item->getIdObj()==id_type)){
            return static_cast<Items*>(item);
        }
    }
    return nullptr;
}


void Stage::setBackground(std::string &path)
{
    QImage* image = new QImage(path.c_str());
    this->scene->setBackgroundBrush(QBrush(image->scaled(this->camera->width(),this->camera->height(),Qt::KeepAspectRatio)));
}


Camera *Stage::getCamera()
{
    return this->camera;
}

QGraphicsItem *Stage::itemAt(int posx,int posy) // no se si se usa ...
{
    if(this->camera->itemAt(posx,posy) == 0){
        qDebug()<<"cero";
    }
    return this->camera->itemAt(posx,posy);
}


void Stage::setPlayerActive(Player* player){
    this->camera->setPlayerActive(player);
}


void Stage::addWidget(QWidget* widget)
{
    this->scene->addWidget(widget);
    widget->setGeometry(100,100,widget->width(),widget->height());
}

void Stage::moveObjTo(int type ,int id, int posX, int posY, int angle)
{
    QList<QGraphicsItem*> list_items = this->scene->items();
    QList<QGraphicsItem*>::iterator it;
    for (it=list_items.begin();it!=list_items.end();it++)
    {
        MovableItem* item =dynamic_cast<MovableItem*>(*it);
        if(!item){// no es movible
            continue;
        }else if(item->getId()==id && item->getIdObj()==type){
            if(item->x()==-130){
                qDebug()<<"coloque worm x:"<<posX<<"y:"<<posY;
                item->setPosition(posX,this->scene->height()-posY);
                return;
            }
            item->moveTo(angle,posX,posY);
        }

    }
}

void Stage::addItemToFollow(MovableItem* item)
{
    this->camera->addItemToFollow(item);
}







