#ifndef CELDA_H
#define CELDA_H


class celda
{
private:
    int id;
    bool ocupado = false;

public:
    celda();

    bool esta_ocupado();

    int obtener_id();

    void llenar_celda(int id);

    void vaciar_celda();
};

#endif // CELDA_H
