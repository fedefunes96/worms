#ifndef EDITOR_WORM_VIEW_H
#define EDITOR_WORM_VIEW_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

class Worm_View: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Worm_View(int id,QObject* parent = nullptr);

    ~Worm_View();

    //Captura el evento de mousse Precionado para luego mandar un signal
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    //Retorna el rectangulo qu limita la imagen
    QRectF boundingRect() const;

signals:
    //Señal de que se ha selecionado el gusano
    void wormSelect(int id);

private:
    void paint(QPainter *painter, 
        const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPixmap *spriteImage;   
    int currentFrame;   
    int id;
};


#endif
