#ifndef BAZOOKA_H
#define BAZOOKA_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

#include "worm_view.h"

class Bazooka: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Bazooka(Worm_View* w);

    void fire();
private slots:
    void nextFameImpact();

    void move();
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    bool colliding();
    void setAngle(int x, int y);

    Worm_View* w;
    int currentFrame;
    std::pair<int,int> angle;
    QTimer *timer;      // Timer for turning images into QPixmap
    QPixmap *spriteImage;   // In this QPixmap object will be placed sprite


    void explote();
};

#endif // BAZOOKA_H
