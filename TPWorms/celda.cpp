#include "celda.h"

celda::celda()
{

}

bool celda::esta_ocupado()
{
    return this->ocupado;
}

int celda::obtener_id()
{
    return this->id;
}

void celda::llenar_celda(int id)
{
    this->ocupado = true;
    this->id = id;
}

void celda::vaciar_celda()
{
    ocupado = false;
}
