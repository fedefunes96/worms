#include <QApplication>
#include "game_view.h"
#include "worm_view.h"

#include <QGraphicsRectItem>

#include "eventhandler.h"
#include "girder_view.h"

#include <QDebug>
#include <QDesktopWidget>

#include <QLabel>

#include "mybutton.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Game_View my_game;


    // center de application
    QRect rect = a.desktop()->screenGeometry();
    my_game.centerScreen(rect);



    std::string path(":/images/intro2.jpg");
    my_game.setBackground(path);


    Worm_View* worm = new Worm_View();

    worm->setFlag(QGraphicsItem::ItemIsSelectable); // i have to do it selectable then turn it on
    //worm->setFlag(QGraphicsItem::ItemIsFocusable);
    //worm->setFocus();
    worm->setSelected(true);



    //QGraphicsItem* worm2 = new Worm_View();
    //worm2->setFlag(QGraphicsItem::ItemIsSelectable); // i have to do it selectable then turn it on



    //ojo que infiere el orden en que los inserto...
    my_game.add_Item(worm,600,400);
    worm->add_label(); // solucionar esto, que se agregue o se llame al agregar el worm al scene
    worm->setDir(worm->x(),worm->y());
    //my_game.add_Item(worm2,300,250);


    //Zvalue: entre mas grande, va al frente..sino por detras

    //worm->setZValue(1);

    Girder_View* girder = new Girder_View(0,140);
    girder->setZValue(-3);
    my_game.add_Item(girder,10,200);


    Girder_View* girder2 = new Girder_View(-90,140);
    girder->setZValue(-3);
    my_game.add_Item(girder2,10,200);

    my_game.getCamera()->addItemToFollow(worm);



    EventHandler *filter = new EventHandler(&a,&my_game);
    a.installEventFilter(filter);

//convertir float a int con redondeo
    float x = 4.44444;
    int32_t asd;
    asd = (int32_t)(x+0.5);
    qDebug()<<"valor de a:"<<asd;



    return a.exec();
}
