#include "game_view.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPen>
#include <QGraphicsView>
#include "movable.h"


Game_View::Game_View()
{
    //Create a graphic scene of the game. This scene will contain
    //all objects that I want to display
    this->scene = new QGraphicsScene();



    this->scene->setSceneRect(0,0,10000,10000); //tam escenario

    camera = new Camera(this->scene);



}

void Game_View::update_view()
{
    //do nothing for now.
}

void Game_View::add_Item(QGraphicsItem *item, int posx, int posy)
{
    float aux = ((posx*140)/6);
    int x = int(aux + 0.5);
    aux = ((posy*140)/6);
    int y = int(aux + 0.5);
    this->scene->addItem(item);
    int width = item->boundingRect().width();
    int height = item->boundingRect().height();
    item->setPos(x-width/2,this->scene->height()-y-height/2);
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
        if((*it)->isSelected()){
            return static_cast<Worm_View*>(*it);
        }
    }
    qDebug()<<"no encontre nada";
    return nullptr;
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
        if(!item){// no es un graphicItem
            continue;
        }else if(item->getId()==id){
            //item->moveTo(posX,posY,angle);
            qDebug()<<"move item at pos x:"<<item->x()<<" y:"<<item->y();
        }

    }
}






void Game_View::addItemToFollow(MovableItem* item)
{
    this->camera->addItemToFollow(item);
}
















