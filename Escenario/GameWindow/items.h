#ifndef ITEMS_H
#define ITEMS_H


class Items
{
public:
    Items();
    int getId();
    void setId(int id);
    void setIdObj(int id);
    int getIdObj();
    virtual void setPosition(int x, int y)=0;
protected:
    int id;
    int idObj;
};

#endif // ITEMS_H
