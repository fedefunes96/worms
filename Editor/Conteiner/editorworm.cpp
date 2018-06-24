#include "editorworm.h"
#include <iostream>

editorWorm::editorWorm()
{

}

editorWorm::editorWorm(int posX, int posY)
{
    this->posX = posX;
    this->posY = posY;
}

int editorWorm::getVida()
{
    return vida;
}

void editorWorm::setVida(int vida)
{
    this->vida = vida;
}
