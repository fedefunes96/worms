#include "editorusables.h"

editorUsables::editorUsables(int municiones)
{
    this->municiones = municiones;
}

int editorUsables::getAmmo()
{
    return municiones;
}
