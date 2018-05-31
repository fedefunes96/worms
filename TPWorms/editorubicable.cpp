#include "editorubicable.h"

float EditorUbicable::getX()
{
    return posX;
}

float EditorUbicable::getY()
{
    return posY;
}

void EditorUbicable::setPos(int x, int y)
{
    this->posX = x;
    this->posY = y;
}
