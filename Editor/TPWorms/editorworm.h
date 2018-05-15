#ifndef EDITORWORM_H
#define EDITORWORM_H

#include "editorubicable.h"

class editorWorm: public EditorUbicable
{
private:
    int vida;

public:
    editorWorm(int posX, int posY, int vida);
};

#endif // EDITORWORM_H
