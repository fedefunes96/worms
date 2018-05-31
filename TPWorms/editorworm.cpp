#include "editorworm.h"

editorWorm::editorWorm()
{

}

editorWorm::editorWorm(int posX, int posY)
{
    this->posX = posX*6/140;
    this->posY = posY*6/140;
}

int editorWorm::getVida()
{
    return vida;
}

void editorWorm::setVida(int vida)
{
    this->vida = vida;
}
