#ifndef MOVABLEITEM_H
#define MOVABLEITEM_H

#include <QGraphicsItem>
#include <items.h>

class MovableItem:public QGraphicsItem,public Items
{
public:
    MovableItem();
    virtual bool isAlive()=0;
    virtual bool isMovable()=0;
    virtual void moveTo(int angle, int posx,int posy)=0;
    virtual void setVisibility(bool vis)=0;
protected:
    bool alive;
};

#endif // MOVABLEITEM_H
