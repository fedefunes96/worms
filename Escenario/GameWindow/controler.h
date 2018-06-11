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
private slots:
    void prueba();

signals:
    void eventCreated(QList<int> list);
    void recvMap(QList<std::string> list);
    void recvRomms(QList<std::string> list);
    void joinR(int cant);
    void playersInRoom(int cant);
    void startGame();
    void playerId(int id);
private:
    Protocol *protocol;
    QTimer *timer;
    int mi_id;
};

#endif // CONTROLER_H
