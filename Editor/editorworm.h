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
    int getVida();
    void setVida(int vida);
};

#endif
