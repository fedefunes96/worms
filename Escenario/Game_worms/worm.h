#ifndef WORM_H
#define WORM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>


class Worm: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    /*Constructor*/
    explicit Worm(QObject* parent = 0);

    /*Return true if it's colliding with a Girder*/
    bool isCollidingToGirder();

    /*Set the id of the worm*/
    void setWormId(int id);

    /*Set the worm speed*/
    void setWormSpeed(int speed);


private:
    /*Function for drawing the sprite at the currentFrame*/
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /*Returns the bounding Rect area of the worm view*/
    QRectF boundingRect() const;

    /*QPixmap object in will be placed the sprite*/
    QPixmap *spriteImage;

    /*Coordinates X, which starts the next frame of the sprite*/
    int currentFrame;

    /*Id of the worm. It's zero by default*/
    int id;

    /*Speed of the worm. By default it's 1*/
    int speed;




};

#endif // WORM_H
