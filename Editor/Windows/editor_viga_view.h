#ifndef EDITOR_VIGA_VIEW_H
#define EDITOR_VIGA_VIEW_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class editor_viga_view: public QObject, public QGraphicsItem
        {
            Q_OBJECT
public:
    editor_viga_view(int id,QObject* parent = 0);

    ~editor_viga_view();

    //Captura el evento de mousse Precionado para luego mandar un signal
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    //Retorna el rectangulo qu limita la imagen
    QRectF boundingRect() const;

signals:
    //Señal de que se ha selecionado la viga
    void girderSelect(int id);

private:
    void paint(QPainter *painter, 
        const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPixmap *spriteImage;   
    int currentFrame;   
    int id;

};

#endif
