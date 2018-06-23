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
    void aumentarAngulo(int angulo);
    float get_angulo();
    int get_tam();
};

#endif // EDITORVIGA_H
