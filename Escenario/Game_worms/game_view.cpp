#include "game_view.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPen>
#include <QGraphicsView>


Game_View::Game_View()
{
    //Create a graphic scene of the game. This scene will contain
    //all objects that I want to display
    this->scene = new QGraphicsScene();

    //Create the view, where all objects will be displayed.

    camera = new Camera(this->scene);

    this->scene->setSceneRect(0,0,10000,10000); //tam escenario



}

void Game_View::update_view()
{
    //do nothing for now.
}

void Game_View::add_Item(QGraphicsItem *item, int posx, int posy)
{
    this->scene->addItem(item);
    item->setPos(posx,posy);
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





