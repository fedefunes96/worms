#ifndef EDITOR_WORM_VIEW_H
#define EDITOR_WORM_VIEW_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

class Worm_View: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Worm_View(int id,QObject* parent = nullptr);

    ~Worm_View();

    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

    QRectF boundingRect() const;

signals:
    void wormSelect(int id);

    void wormSetPos();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPixmap *spriteImage;   // In this QPixmap object will be placed sprite
    int currentFrame;   // Coordinates X, which starts the next frame of the sprite
    int id;
};


#endif
