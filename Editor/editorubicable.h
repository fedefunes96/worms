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

    int getX();

    int getY();

    void setPos(int x, int y);

    void addPos(int x, int y);
};

#endif // EDITORUBICABLE_H
