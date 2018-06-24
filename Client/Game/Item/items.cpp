#include "items.h"

Items::Items()
{
}

int Items::getId()
{
    return this->id;
}

void Items::setId(int id)
{
    this->id=id;
}

void Items::setIdObj(int id)
{
    this->idObj = id;
}

int Items::getIdObj()
{
    return this->idObj;
}

