#ifndef ITEMS_H
#define ITEMS_H

#include <QRectF>

class Items
{
public:
    Items();
    int getId();
    void setId(int id);
    void setIdObj(int id);
    int getIdObj();
    virtual void setPosition(int x, int y)=0;
    virtual int getX()=0;
    virtual int getY()=0;
    virtual QRectF areaRect()=0;
protected:
    int id;
    int idObj;
};

#endif // ITEMS_H
