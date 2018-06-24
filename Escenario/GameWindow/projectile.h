#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QObject>
#include "movable.h"
#include <QTimer>
#include <QPainter>
#include "generalSounds.h"

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
    void removeMovable();
    bool isSelect();
    void setSelect(bool cond);
    void setAlive(bool alive);
    void explote();
    void setSpriteBullet(std::string &path);
    bool isMoving();
    virtual int getX() override;
    virtual int getY() override;
    virtual QRectF areaRect() override;

private slots:
    void nextFameImpact();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;


    generalSounds* explotionSound;
    int currentFrame;
    QTimer *timer;
    QPixmap *spriteImage;
};

#endif // PROJECTILE_H
