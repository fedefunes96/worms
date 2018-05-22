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

class Worm_View: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Worm_View(QObject* parent = 0);

    void set_idWorm(int id);
    bool collidingGirder();
    std::pair<int, int> &getDir();
    void setDir(int x, int y);
    std::pair<int, int> &getAngle();
    void moveToPos(int posx, int posy);
    void throwProjectile();
    void delete_bullet(QGraphicsItem* item);
    void add_label();
signals:
public slots:

private slots:
    void nextFrame2_Left();
    void nextFrame2_Right();
    void nextFrame2_UpLeft();
    void nextFrame2_UpLeft30();
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    bool movingRight();
    bool movingLeft();



    QLabel* vida;
    std::pair<int,int> currentDir;
    std::pair<int,int> destDir;
    std::pair<int,int> angle;
    int id_worm;
    int speed;
    QTimer *timer;      // Timer for turning images into QPixmap
    QPixmap *spriteImage;   // In this QPixmap object will be placed sprite
    int currentFrame;   // Coordinates X, which starts the next frame of the sprite
    bool movingDUpLeft();
    void setAngle(int x, int y);
    int count;

};

#endif // WORM_VIEW_H

