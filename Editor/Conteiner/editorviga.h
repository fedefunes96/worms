#ifndef EDITORVIGA_H
#define EDITORVIGA_H

#include "editorubicable.h"

class editorViga: public EditorUbicable
{
private:
    float angulo;
    int tam;

public:
    editorViga();

    editorViga(int posX, int posY, int tam);

    ~editorViga(){}

    //Aumenta el angulo de la Viga
    void aumentarAngulo(int angulo);

    //Retorna el angulo actual de la Viga
    float get_angulo();

    //Retorna el tamaño de la viga
    int get_tam();
};

#endif
