#ifndef GIRDER_H
#define GIRDER_H

#include <QGraphicsPixmapItem>
#include "items.h"

class Girder_View:public QGraphicsPixmapItem,public Items
{
public:
    Girder_View();
    Girder_View(int angle, int large);
    virtual void setPosition(int x,int y) override;
    virtual int getX() override;
    virtual int getY() override;
    virtual QRectF areaRect() override;
};

#endif // GIRDER_H
