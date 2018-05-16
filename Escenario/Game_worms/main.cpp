#include <QApplication>
#include "game_view.h"
#include "worm_view.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game_View my_game;

    std::string path(":/image/intro.jpg");
    my_game.setBackground(path);


    QGraphicsItem* worm = new Worm_View();

    worm->setFlag(QGraphicsItem::ItemIsFocusable);
    worm->setFocus();

    my_game.add_Item(worm,600,250);




    return a.exec();
}
