#ifndef GIRDER_H
#define GIRDER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

class Girder_View:public QGraphicsPixmapItem
{
public:
    Girder_View();
    Girder_View(int angle, int large);
};

#endif // GIRDER_H
