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

#include <QColor>

class Worm_View: public QObject, public MovableItem
{
    Q_OBJECT
public:
    Worm_View();
    Worm_View(QObject* parent, QString color);
    bool isMoving();
    bool isAlive();
    bool isMovable();
    std::pair<int, int> &getDir();
    int getAngle();
    void moveTo(int angle, int posx, int posy);
    void setVisibility(bool vis);
    int getHealth();
    void setHealth(int health);
    void setAngle(int angle);
    virtual void setPosition(int x, int y) override;
    void loadSpriteWeapon(int val);
    void movTargetAngle(int dir);
    int getWeaponId();
    bool isSelect();
    void setSelect(bool cond);
    void setAlive(bool alive);

    std::pair<int,int> getDirWeapon();

    bool hasClickeableTarget();
    int getTargetAngle();
    int getTimeWeapon();
    void setTimeWeapon(int time);
    void setClickDir(int x, int y);
    void setColor(std::string &color);
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

    // innecesarios creo... ////////////////////////////
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
////////////////////////////////////////////

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
    bool weaponCountDwn;
    int countDown;
    std::pair<int,int> clickTarget;
    QString color;




};

#endif // WORM_VIEW_H


