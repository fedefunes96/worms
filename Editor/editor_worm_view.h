#ifndef EDITOR_WORM_VIEW_H
#define EDITOR_WORM_VIEW_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
class Worm_View: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Worm_View(QObject* parent = 0);

    ~Worm_View();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPixmap *spriteImage;   // In this QPixmap object will be placed sprite
    int currentFrame;   // Coordinates X, which starts the next frame of the sprite


};


#endif
