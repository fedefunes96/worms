#ifndef MOVABLEITEM_H
#define MOVABLEITEM_H

#include <QGraphicsItem>
#include <items.h>

class MovableItem:public QGraphicsItem,public Items
{
public:
    MovableItem();
    virtual bool isAlive()=0;
    virtual void setAlive(bool alive)=0;
    virtual bool isMovable()=0;
    virtual void moveTo(int angle, int posx,int posy)=0;
    virtual void setVisibility(bool vis)=0;
    virtual bool isSelect()=0;
    virtual void setSelect(bool cond)=0;
    virtual bool isMoving()=0;
protected:
    bool alive;
    bool selected;
    bool moving;
};

#endif // MOVABLEITEM_H
