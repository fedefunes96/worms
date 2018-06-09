#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QObject>
#include "movable.h"
#include <QTimer>
#include <QPainter>

class Projectile : public QObject,public MovableItem
{
    Q_OBJECT
public:
    Projectile();
    ~Projectile();
    void moveTo(int angle, int posx,int posy);
    bool isMovable();
    bool isAlive();
    void setPosition(int x, int y);
    void fire();
    void setVisibility(bool vis);
    bool isSelect();
    void setSelect(bool cond);
    void setAlive(bool alive);
    void explote();
    void setSpriteBullet(std::string &path);

private slots:
    void nextFameImpact();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;


    int currentFrame;
    QTimer *timer;      // Timer for turning images into QPixmap
    QPixmap *spriteImage;   // In this QPixmap object will be placed sprite


};

#endif // PROJECTILE_H
