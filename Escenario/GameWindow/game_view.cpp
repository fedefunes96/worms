#include "game_view.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPen>
#include <QGraphicsView>
#include "movable.h"


Game_View::Game_View()
{
}

Game_View::Game_View(QRect screen,int w,int h)
{
    //Create a graphic scene of the game. This scene will contain
    //all objects that I want to display
    this->scene = new QGraphicsScene();


    this->scene->setSceneRect(0,0,w,h); //tam escenario

    this->camera = new Camera(this->scene,screen.width(),screen.height());
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
    //do nothing for now.
}

void Game_View::add_Item(QGraphicsItem *item, int posx, int posy)
{

    this->items_list.push_back(dynamic_cast<Items*>(item));

    this->scene->addItem(item);

    Items* i = dynamic_cast<Items*>(item);
    i->setPosition(posx,this->scene->height()-posy);
}

bool Game_View::containsItem(Items* item){
    std::vector<Items*>::iterator it;
    for ( it = this->items_list.begin(); it!=this->items_list.end();it++){
        if((static_cast<Items*>(*it))->getId()==item->getId()){
            return true;
        }
    }
    return false;
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
            qDebug()<<"type:"<<item->getIdObj()<<"id:"<<item->getId();
            return static_cast<Items*>(item);
        }
    }
    return nullptr;
}

void Game_View::del_Item(Items* item)
{
    MovableItem * aux = static_cast<MovableItem*>(item);
    //this->scene->removeItem(aux);
    aux->setVisible(false);
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



QGraphicsItem *Game_View::itemAt(int posx,int posy)
{
    if(this->camera->itemAt(posx,posy) == 0){
        qDebug()<<"cero";
    }
    return this->camera->itemAt(posx,posy);
}



Worm_View* Game_View::getWormActive2()
{
    QList<QGraphicsItem*> qlist = this->scene->selectedItems();
    QList<QGraphicsItem*>::iterator it;
    for (it=qlist.begin();it!=qlist.end();it++)
    {
        if((*it)->isSelected() && (*it)->type()==Worm_View().type()){
            return static_cast<Worm_View*>(*it);
        }
    }
    qDebug()<<"no encontre nada !!!!!!!!!!!!";
    return nullptr;
}

Worm_View* Game_View::getWormActive()
{
    QList<QGraphicsItem*> list_items = this->scene->items();

    QList<QGraphicsItem*>::iterator it;
    for (it=list_items.begin();it!=list_items.end();it++)
    {

        Worm_View* item =dynamic_cast<Worm_View*>(*it);
        if(!item){// no es worm
            continue;
        }else{
            if(item->isSelect()){
                return item;
            }
        }

    }
    return nullptr;
}

void Game_View::addPlayerActive(Player* player){
    this->camera->setPlayerActive(player);
}


void Game_View::centerScreen(QRect rect)
{
    int x = (rect.width()-this->camera->width()) / 2;
    int y = (rect.height()-this->camera->height()) / 2;
    this->camera->move(x,y);
}

void Game_View::maximizateScreen()
{
    this->camera->showMaximized();
}

void Game_View::minimizateScreen()
{
    this->camera->showMinimized();
}


void Game_View::addWidget(QWidget* widget)
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
            if(item->x()==-130 && item->y()==10070){//temporal para setear el escenario
                qDebug()<<posX<<posY;
                item->setPosition(posX,this->scene->height()-posY);
                return;
            }
            item->moveTo(angle,posX,posY);
        }

    }
}






void Game_View::addItemToFollow(MovableItem* item)
{
    qDebug()<<"id worm a seguir"<<item->getId();
    item->setSelect(true); // esto tendria que estar en la logica de cuando es mi turno...
    this->camera->addItemToFollow(item);
}







