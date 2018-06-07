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
private:
    Protocol *protocol;
    QTimer *timer;
};

#endif // CONTROLER_H
