#include "game_view.h"
#include <QMouseEvent>
#include <QDebug>

Game_View::Game_View()
{
    //Create a graphic scene of the game. This scene will contain
    //all objects that I want to display
    this->scene = new QGraphicsScene();

    //Create the view, where all objects will be displayed.
    this->view = new QGraphicsView();
    //set the scene to the view.
    this->scene->set
    this->view->setScene(this->scene);
    //set always off the scrolls bars.
    this->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //show the view
    this->view->show();
    //Set FixedSize
    this->view->setFixedSize(700,500);
    this->scene->setSceneRect(0,0,1024,800);
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

