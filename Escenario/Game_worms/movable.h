#ifndef MOVABLEITEM_H
#define MOVABLEITEM_H

#include <QGraphicsItem>

class MovableItem:public QGraphicsItem
{
public:
    MovableItem();
    virtual bool isAlive()=0;
    virtual bool isMovable()=0;
    virtual int getId()=0;
    virtual void moveTo(int posX,int posY, int angle)=0;
protected:
    int id;
    bool alive;
};

#endif // MOVABLEITEM_H
