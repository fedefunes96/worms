#ifndef MAPSELECTION_H
#define MAPSELECTION_H

#include <QWidget>
#include <QDialog>
#include "protocol.h"
#include <vector>
#include <QThread>
#include "controler.h"
#include "waitRoom.h"

namespace Ui {
class MapSelection;
}

class MapSelection : public QDialog
{
    Q_OBJECT

public:
    MapSelection(Protocol* protocol, QWidget *parent = nullptr);
    ~MapSelection();

    void connectControler(Controler *controler);
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
    Ui::MapSelection *ui;
    Protocol* protocol;
    WaitRoom* wait;
    void adjustView();
    bool closeX;
    bool isExec;
    bool back;
};

#endif // MAPSELECTION_H
