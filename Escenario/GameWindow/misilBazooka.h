#ifndef MISIL_BAZOOKA_H
#define MISIL_BAZOOKA_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

#include "movable.h"

class MisilBazooka: public QObject,public MovableItem
{
    Q_OBJECT
public:
    MisilBazooka();
    void moveTo(int angle, int posx,int posy);
    bool isMovable();
    bool isAlive();
    void setPosition(int x, int y);
    void fire();


private slots:
    void nextFameImpact();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    bool colliding();
    void explote();
    
    int currentFrame;
    QTimer *timer;      // Timer for turning images into QPixmap
    QPixmap *spriteImage;   // In this QPixmap object will be placed sprite


};

#endif
