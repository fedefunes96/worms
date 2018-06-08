#ifndef WORM_VIEW_H
#define WORM_VIEW_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QEvent>
#include <QTime>
#include <QLabel>
#include "movable.h"
#include "target.h"


class Worm_View: public QObject, public MovableItem
{
    Q_OBJECT
public:
    explicit Worm_View(QObject* parent = 0);
    bool isMoving();
    bool isAlive();
    bool isMovable();
    std::pair<int, int> &getDir();
    int getAngle();
    void moveTo(int angle, int posx, int posy);
    void setVisibility(bool vis);

    void setHealth(int health);
    void setAngle(int angle);
    virtual void setPosition(int x, int y) override;
    void loadSpriteWeapon(int val);
    void movTargetAngle(int dir);
    int getWeaponId();

    std::pair<int,int> getDirWeapon();

    bool hasClickeableTarget();
    int getTargetAngle();
    int getTimeWeapon();
private slots:
    void runSpriteWeapon();

private:
    void nextFrame();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void checkAngle(int angle);

    QLabel* labelVida;
    int health;
    bool labelset;
    std::pair<int,int> currentDir;
    std::pair<int,int> destDir;
    int angle;
    int speed;
    QTimer *timer;
    QPixmap *spriteImage;   // In this QPixmap object will be placed sprite
    int currentFrame;   // Coordinates X, which starts the next frame of the sprite

    int count;
    int x1;
    int x2;
    int rep;
    int rep2;
    int desp;
    bool movUP;
    bool movR;
    bool firstX;
    int up;
    int right;

    void setSprite();
    void setVarsMove(int x1, int x2, int rep, int rep2, bool movUP, bool movR);
    void setDestDir(int x, int y);
    void setDir(int x, int y);
    void movObj();
    void checkDelta();
    void setVars(int cant1, int cant2, int up, int right, bool firsX);
    void moveStep();
    void stepSprite();
    int weapon;
    void loadSprite(QString& path_L,QString& path_U,QString path_D,QString path_Fly="",QString path_Fall="");
    Target* target;
    void setTarget();
    bool targetVis;
    int targetAngle;
    bool moving;
    bool loadingWeapon;
    bool targetClick;




};

#endif // WORM_VIEW_H


