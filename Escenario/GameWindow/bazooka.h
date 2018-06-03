#ifndef BAZOOKA_H
#define BAZOOKA_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

#include "worm_view.h"
#include "movable.h"

class Bazooka: public QObject,public MovableItem
{
    Q_OBJECT
public:
    Bazooka(Worm_View* w);

    void fire();
private slots:
    void nextFameImpact();
    void moveTo(int angle, int posx,int posy);
    bool isMovable();
    bool isAlive();
    void move();
    virtual void mover();
    virtual void runSpriteWeapon();
    virtual void setPosition(int x, int y) override;
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
    QTimer *timer2;

    void explote();
};

#endif // BAZOOKA_H
