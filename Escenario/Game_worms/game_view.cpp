#include "game_view.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPen>
#include <QGraphicsView>
#include "movable.h"


Game_View::Game_View(QRect screen,int w,int h)
{
    //Create a graphic scene of the game. This scene will contain
    //all objects that I want to display
    this->scene = new QGraphicsScene();


    this->scene->setSceneRect(0,0,w,h); //tam escenario

    camera = new Camera(this->scene,screen.width(),screen.height());



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

Worm_View* Game_View::getItem(int8_t id_type, int32_t id)
{
    std::vector<Items*>::iterator it;
    for ( it = this->items_list.begin(); it!=this->items_list.end();it++){
        Items* item = static_cast<Items*>(*it);
        if((item->getId()==id) && (item->getIdObj()==id_type)){
            return static_cast<Worm_View*>(item);
        }
    }
    return nullptr;
}

void Game_View::del_Item(QGraphicsItem* item)
{
    //First don't delete...
    //scene()->removeItem(this);
    this->scene->removeItem(item);
    //something like this we have to do
}

void Game_View::setBackground(std::__cxx11::string &path)
{
    //set the background image.
    //this->scene->setBackgroundBrush(QBrush(QImage(path.c_str())));
    //QImage small = jpgImage->scaled(inputWidth, inputHeight,Qt::KeepAspectRatio);
    QImage* image = new QImage(path.c_str());
    this->scene->setBackgroundBrush(QBrush(image->scaled(1024,800,Qt::KeepAspectRatio)));
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



Worm_View* Game_View::getWormActive()
{
    QList<QGraphicsItem*> qlist = this->scene->selectedItems();
    QList<QGraphicsItem*>::iterator it;
    for (it=qlist.begin();it!=qlist.end();it++)
    {
        if((*it)->isSelected() && (*it)->type()==Worm_View().type()){
            return static_cast<Worm_View*>(*it);
        }
    }
    qDebug()<<"no encontre nada";
    return nullptr;
}


void Game_View::addWormActive(Worm_View* worm){
    worm->setSelected(true);
    this->camera->setWormActive(worm);
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

void Game_View::moveObjTo(int id, int posX, int posY, int angle)
{

    QList<QGraphicsItem*> list_items = this->scene->items();

    QList<QGraphicsItem*>::iterator it;
    for (it=list_items.begin();it!=list_items.end();it++)
    {

        MovableItem* item =dynamic_cast<MovableItem*>(*it);
        if(!item){// no es movible
            continue;
        }else if(item->getId()==id){
            //item->moveTo(posX,posY,angle);
            if(item->x()==-130 && item->y()==10070){//temporal para setear el escenario
                qDebug()<<posX<<posY;
                item->setPosition(posX,this->scene->height()-posY);
            }
            item->moveTo(angle,posX,posY);
        }

    }
}






void Game_View::addItemToFollow(MovableItem* item)
{
    item->setSelected(true); // esto tendria que estar en la logica de cuando es mi turno...
    this->camera->addItemToFollow(item);
}







