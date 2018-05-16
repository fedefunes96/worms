#ifndef WORM_VIEW_H
#define WORM_VIEW_H

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

    bool is_moving();
    void keyPressEvent(QKeyEvent *event);
signals:
public slots:

private slots:
    void nextFrame_L();   // Slot for turning images into QPixmap
    void nextFrame_R();
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void move_Left();
    void move_Right();
    void pause();
    void resume();


    bool moving;
    QTimer *timer;      // Timer for turning images into QPixmap
    QPixmap *spriteImage;   // In this QPixmap object will be placed sprite
    int currentFrame;   // Coordinates X, which starts the next frame of the sprite


};

#endif // WORM_VIEW_H

