#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "stage.h"

#include <QObject>
#include <QMouseEvent>
#include <QKeyEvent>
#include "camera.h"

#include "protocol.h"
#include "game.h"


class EventHandler : public QObject
{
    Q_OBJECT
public:
    explicit EventHandler(QObject *parent = 0);
    EventHandler(QObject *parent, Game *game, Protocol *protocol);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
private slots:
    void fireWithClick();
private:
    void mouseMoveEvent(QMouseEvent *m_event);
    void keyPressEvent(QKeyEvent *k_event);
    void mouseClickEvent(QMouseEvent *m_event);
    Game* game;
    Worm_View* worm_selected;
    void keyReleaseEvent(QKeyEvent *k_event);
    bool keyPress;
    Protocol* protocol;
    int power;
};

#endif // EVENTHANDLER_H

