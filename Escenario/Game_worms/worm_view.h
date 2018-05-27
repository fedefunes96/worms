#ifndef WORM_VIEW_H
#define WORM_VIEW_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QEvent>
#include <QTime>
#include <QLabel>
#include "movable.h"

class Worm_View: public QObject, public MovableItem
{
    Q_OBJECT
public:
    explicit Worm_View(QObject* parent = 0);
    bool isAlive();
    void set_idWorm(int id);
    int getId();
    bool isMovable();
    std::pair<int, int> &getDir();
    void setDir(int x, int y);
    std::pair<int, int> &getAngle();
    void moveTo(int angle, int posx, int posy);
    void throwProjectile();
    void delete_bullet(QGraphicsItem* item);
    void setVida(int vida);
    void moveDiag(int angle, int posX, int posY);    
signals:
public slots:

private slots:
    void nextFrame2_Left();
    void nextFrame2_Right();
    void move();
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    bool movingRight();
    bool movingLeft();



    QLabel* labelVida;
    int vida;
    bool labelset;
    std::pair<int,int> currentDir;
    std::pair<int,int> destDir;
    std::pair<int,int> angle;
    int speed;
    QTimer *timer;      // Timer for turning images into QPixmap
    QPixmap *spriteImage;   // In this QPixmap object will be placed sprite
    int currentFrame;   // Coordinates X, which starts the next frame of the sprite
    void setAngle(int x, int y);

    int count;
    int cant;
    int x2;
    int rep;
    int rep2;
    int desp;
    bool movUP;
    bool movR;

    void setSprite(int angle);
    void setVarsMove(int cant, int x2, int rep, int rep2, bool movUP, bool movR);
};

#endif // WORM_VIEW_H


