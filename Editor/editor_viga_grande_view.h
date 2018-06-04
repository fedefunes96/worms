#ifndef EDITOR_VIGA_GRANDE_VIEW_H
#define EDITOR_VIGA_GRANDE_VIEW_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>


class editor_viga_grande_view: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    editor_viga_grande_view(QObject* parent = 0);

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPixmap *spriteImage;   // In this QPixmap object will be placed sprite
    int currentFrame;   // Coordinates X, which starts the next frame of the sprite
};
#endif