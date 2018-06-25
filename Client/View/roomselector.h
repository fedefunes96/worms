#ifndef ROOMSELECTOR_H
#define ROOMSELECTOR_H

#include <QWidget>
#include <QDialog>
#include "protocol_client.h"
#include <vector>
#include <QThread>
#include "controller.h"
#include "waitRoom.h"

namespace Ui {
class RoomSelector;
}

class RoomSelector : public QDialog
{
    Q_OBJECT

public:
    RoomSelector(ProtocolClient* protocol, QWidget *parent = nullptr);
    ~RoomSelector();

    void connectControler(Controller *controler);
    void setExecute(bool enable);
    void askRooms();
    bool isCallBack();
    bool closeWithX();
    void cleanCond();
private slots:
    void recvRooms(QList<std::string> list);
    void goWaitRoom(int cant);
    void on_pushButton_released();
    void on_pushButton_2_released();
private:
    Ui::RoomSelector *ui;
    ProtocolClient* protocol;
    WaitRoom* wait;
    void adjustView();
    bool closeX;
    bool isExec;
    bool back;
};

#endif
