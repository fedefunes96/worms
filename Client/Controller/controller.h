#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "protocol_client.h"
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QList>

class Controller: public QThread
{
    Q_OBJECT
public:
    Controller(ProtocolClient* protocol);
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
    ProtocolClient *protocol;
};

#endif // CONTROLLER_H
