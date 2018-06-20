#ifndef TARGET_H
#define TARGET_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>
#include <QLabel>
#include <QTimer>
#include <QObject>
#include <QPainter>




class Target :public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Target();
    //virtual ~Target();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void setTarget(int posx, int posy, int angle);
private:
    int currentFrame;
    QPixmap *spriteImage;
};

#endif // TARGET_H
