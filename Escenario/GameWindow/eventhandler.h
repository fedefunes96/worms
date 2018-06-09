#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "game_view.h"

#include <QObject>
#include <QMouseEvent>
#include <QKeyEvent>
#include "camera.h"

#include "protocol.h"
#include "gameclass.h"


class EventHandler : public QObject
{
    Q_OBJECT
public:
    explicit EventHandler(QObject *parent = 0);
    EventHandler(QObject *parent, GameClass *game, Protocol *protocol);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    void mouseMoveEvent(QMouseEvent *m_event);
    void keyPressEvent(QKeyEvent *k_event);
    void mouseClickEvent(QMouseEvent *m_event);
    GameClass* game;
    Worm_View* worm_selected;
    void keyReleaseEvent(QKeyEvent *k_event);
    bool keyPress;
    Protocol* protocol;
    int power;
};

#endif // EVENTHANDLER_H

