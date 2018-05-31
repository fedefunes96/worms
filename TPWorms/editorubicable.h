#ifndef EDITORUBICABLE_H
#define EDITORUBICABLE_H


class EditorUbicable
{
protected:
    float posX;
    float posY;

public:
    EditorUbicable(){}

    float getX();

    float getY();

    void setPos(int x, int y);
};

#endif // EDITORUBICABLE_H
