#ifndef EDITORUBICABLE_H
#define EDITORUBICABLE_H


class EditorUbicable
{
protected:
    int posX;
    int posY;

public:
    EditorUbicable(){}

    ~EditorUbicable(){}

    //Obtener la posiscion X del Ubicable
    int getX();

    //Obtener la posiscion Y del Ubicable
    int getY();

    //Cambia la posiscion del ubicable
    void setPos(int x, int y);

    //Suma los valores a la posicion actual del Ubicable
    void addPos(int x, int y);
};

#endif 
