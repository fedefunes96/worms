#include "editorworm.h"

editorWorm::editorWorm()
{

}

editorWorm::editorWorm(int posX, int posY, int vida)
{
    this->posX = posX;
    this->posY = posY;
    this->vida = vida;
}

int editorWorm::getVida()
{
    return vida;
}
