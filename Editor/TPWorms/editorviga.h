#ifndef EDITORVIGA_H
#define EDITORVIGA_H

#include "editorubicable.h"

class editorViga: public EditorUbicable
{
private:
    int angulo;

public:
    editorViga(int posX, int posY, int angulo);
};

#endif // EDITORVIGA_H
