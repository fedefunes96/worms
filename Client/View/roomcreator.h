#ifndef ROOMCREATOR_H
#define ROOMCREATOR_H

#include <QWidget>
#include "protocol_client.h"
#include <QLineEdit>
#include <QDialog>
#include "controller.h"
#include "waitRoom.h"

namespace Ui {
class RoomCreator;
}

class RoomCreator : public QDialog
{
    Q_OBJECT

public:
    RoomCreator(ProtocolClient* protocol,QWidget *parent = nullptr);
    ~RoomCreator();
    void connectControler(Controller *controler);
    void setExecute(bool enable);
    void askMaps();
    bool closeWithX();
    bool isCallBack();
    void cleanCond();
public slots:
    void recvMaps(QList<std::string> list);

    void couldCreate(int could);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_released();

private:
    Ui::RoomCreator *ui;
    ProtocolClient* protocol;
    WaitRoom* wait;
    std::vector<QLineEdit*> lines;
    bool closeX;
    bool isExec;
    bool back;
};

#endif // ROOMCREATOR_H
