#include "editorviga.h"
#include <iostream>

#define pi 3.141592

editorViga::editorViga()
{

}

editorViga::editorViga(int posX, int posY, int tam)
{
    this->posX = posX;
    this->posY = posY;
    this->angulo = 0;
    this->tam = tam;
}

void editorViga::aumentarAngulo(int angulo)
{
    float ang = angulo*pi/180;
    if (ang < 0){
        ang += 2*pi;
    }
    this->angulo += ang;
    if (this->angulo > (2*pi)){
        this->angulo -= 2*pi;
    }
}

float editorViga::get_angulo()
{
    return this->angulo;
}

int editorViga::get_tam()
{
    return tam;
}
