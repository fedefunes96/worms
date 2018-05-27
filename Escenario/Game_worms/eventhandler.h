#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "game_view.h"

#include <QObject>
#include <QMouseEvent>
#include <QKeyEvent>
#include "camera.h"

#include "protocol.h"


class EventHandler : public QObject
{
    Q_OBJECT
public:
    explicit EventHandler(QObject *parent = 0);

    EventHandler(QObject *parent, Game_View *game_view);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    void mouseMoveEvent(QMouseEvent *m_event);
    void keyPressEvent(QKeyEvent *k_event);
    void mouseClickEvent(QMouseEvent *m_event);
    Game_View* game_view;
    Worm_View* worm_selected;
    void keyReleaseEvent(QKeyEvent *k_event);
    bool keyPress;
    Protocol* protocol;
};

#endif // EVENTHANDLER_H

