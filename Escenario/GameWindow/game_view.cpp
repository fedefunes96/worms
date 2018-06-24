#include "game_view.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPen>
#include <QGraphicsView>
#include "movable.h"


Game_View::Game_View()
{
}

Game_View::Game_View(int w,int h)
{
    this->scene = new QGraphicsScene();
    this->scene->setSceneRect(0,-h,w,h); //tam escenario
    this->timerUpdate = new QTimer();
    connect(this->timerUpdate,&QTimer::timeout,this,&Game_View::update_view);
    this->timerUpdate->start(10);

}


void Game_View::addCamera(Camera *camera)
{
    this->camera = camera;
}

void Game_View::resizeScene(int w, int h)
{
    qDebug()<<"screen w:"<<w<<"h"<<h;
    this->scene->setSceneRect(0,-h,w,h);
}


QGraphicsScene* Game_View::getScene()
{
    return this->scene;
}

int Game_View::getHeight()
{
   return this->scene->height();
}

int Game_View::getWidth()
{
   return this->scene->width();
}


void Game_View::update_view()
{
    this->scene->update(this->scene->sceneRect());
}

void Game_View::add_Item(QGraphicsItem *item, int posx, int posy)
{
    this->items_list.push_back(dynamic_cast<Items*>(item));
    this->scene->addItem(item);
    Items* i = dynamic_cast<Items*>(item);
    i->setPosition(posx,-posy);
}

bool Game_View::containsItem(int8_t id_typ, int32_t id){
    std::vector<Items*>::iterator it;
    for ( it = this->items_list.begin(); it!=this->items_list.end();it++){
        if(((static_cast<Items*>(*it))->getId()==id) && (static_cast<Items*>(*it))->getIdObj()==id_typ){
            return true;
        }
    }
    return false;
}

Items* Game_View::getItem(int8_t id_type, int32_t id)
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


void Game_View::setBackground(std::string &path)
{
    //set the background image.
    //this->scene->setBackgroundBrush(QBrush(QImage(path.c_str())));
    //QImage small = jpgImage->scaled(inputWidth, inputHeight,Qt::KeepAspectRatio);
    QImage* image = new QImage(path.c_str());
    this->scene->setBackgroundBrush(QBrush(image->scaled(this->camera->width(),this->camera->height(),Qt::KeepAspectRatio)));
}


Camera *Game_View::getCamera()
{
    return this->camera;
}



QGraphicsItem *Game_View::itemAt(int posx,int posy) // no se si se usa ...
{
    if(this->camera->itemAt(posx,posy) == 0){
        qDebug()<<"cero";
    }
    return this->camera->itemAt(posx,posy);
}



void Game_View::setPlayerActive(Player* player){
    this->camera->setPlayerActive(player);
}


void Game_View::addWidget(QWidget* widget)  // creo que no se usa mas ...
{
    this->scene->addWidget(widget);
    widget->setGeometry(100,100,widget->width(),widget->height());
}

void Game_View::moveObjTo(int type ,int id, int posX, int posY, int angle)
{

    QList<QGraphicsItem*> list_items = this->scene->items();

    QList<QGraphicsItem*>::iterator it;
    for (it=list_items.begin();it!=list_items.end();it++)
    {

        MovableItem* item =dynamic_cast<MovableItem*>(*it);
        if(!item){// no es movible
            continue;
        }else if(item->getId()==id && item->getIdObj()==type){
            //item->moveTo(posX,posY,angle);
            if(item->x()==-130){//temporal para setear el escenario
                qDebug()<<"coloque worm x:"<<posX<<"y:"<<posY;
                item->setPosition(posX,this->scene->height()-posY); ///////// aca tambien deberia cambiarlo...
                return;
            }
            item->moveTo(angle,posX,posY);
        }

    }
}

void Game_View::addItemToFollow(MovableItem* item)
{
    this->camera->addItemToFollow(item);
}







