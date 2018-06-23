#ifndef EDITOR_VIGA_VIEW_H
#define EDITOR_VIGA_VIEW_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class editor_viga_view: public QObject, public QGraphicsItem
        {
            Q_OBJECT
public:
    editor_viga_view(int id,QObject* parent = 0);

    ~editor_viga_view();

    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    QRectF boundingRect() const;

signals:
    void girderSelect(int id);

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPixmap *spriteImage;   // In this QPixmap object will be placed sprite
    int currentFrame;   // Coordinates X, which starts the next frame of the sprite
    int id;

};

#endif
