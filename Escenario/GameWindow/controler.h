#ifndef CONTROLER_H
#define CONTROLER_H

#include "protocol.h"
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QList>

class Controler: public QThread
{
    Q_OBJECT
public:
    Controler(Protocol* protocol);
    void run();
public slots:
    void stopController();
signals:
    void eventCreated(QList<int> list);
    void recvMap(QList<std::string> list);
    void recvRomms(QList<std::string> list);
    void joinR(int cant);
    void playersInRoom(int cant);
    void startGame(QList<std::string> list);
    void playerId(int id);
private:
    Protocol *protocol;
};

#endif // CONTROLER_H
