#ifndef EDITOR_VIEW_H
#define EDITOR_VIEW_H

#include <QGraphicsView>
#include "celda.h"
#include <QGraphicsScene>

class editor_view:  public QGraphicsView
{
    Q_OBJECT
public:
    editor_view();

    celda celdas[100][40];

    void mousePressEvent(QMouseEvent *event);

    void agregar_gusano(int x, int y);

    void agregar_viga_grande(int x, int y);

    void agregar_viga_chica(int x, int y);

    int estado;

    int id = 0;

    QGraphicsScene* scene;

    void pasar_esena(QGraphicsScene* escena);
};

#endif
