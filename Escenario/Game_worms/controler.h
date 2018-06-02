#ifndef CONTROLER_H
#define CONTROLER_H

#include "protocol.h"
#include "gameclass.h"
#include <QThread>
#include <QDebug>
#include <QTimer>

class Controler: public QThread
{
public:
    Controler(Protocol* protocol,GameClass *game);
    void run();
private slots:
    void prueba();
private:
    Protocol *protocol;
    GameClass *game;
    QTimer *timer;
};

#endif // CONTROLER_H
