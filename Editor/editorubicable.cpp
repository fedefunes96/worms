#include "editorubicable.h"

int EditorUbicable::getX()
{
    return posX;
}

int EditorUbicable::getY()
{
    return posY;
}

void EditorUbicable::setPos(int x, int y)
{
    this->posX = x;
    this->posY = y;
}

void EditorUbicable::addPos(int x, int y)
{
    this->posX += x;
    this->posY += y;
}
