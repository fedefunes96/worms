#ifndef EDITORWORM_H
#define EDITORWORM_H

#include "editorubicable.h"

class editorWorm: public EditorUbicable
{
private:
    int vida = 100;

public:
    editorWorm();

    editorWorm(int posX, int posY);

    ~editorWorm(){}

    //Retorna la Vida del Gusano
    int getVida();

    //Cambia la vida del Gusano
    void setVida(int vida);
};

#endif
