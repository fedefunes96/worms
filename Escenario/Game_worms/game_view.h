#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QBrush>
#include <QImage>
#include <string>
#include <QObject>

class Game_View
{
private:
    QGraphicsScene* scene;
    QGraphicsView* view;

public:
    Game_View();
    void update_view();
    void add_Item(QGraphicsItem* item,int posx, int posy);
    void del_Item(QGraphicsItem* item);
    void setBackground(std::string& path);
};

#endif // GAME_VIEW_H
