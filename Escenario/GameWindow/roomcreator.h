#ifndef ROOMCREATOR_H
#define ROOMCREATOR_H

#include <QWidget>
#include "protocol.h"
#include "button.h"
#include <QLineEdit>
#include <QDialog>
#include "controler.h"
#include "waitRoom.h"

namespace Ui {
class RoomCreator;
}

class RoomCreator : public QDialog
{
    Q_OBJECT

public:
    RoomCreator(Protocol* protocol,QWidget *parent = nullptr);
    ~RoomCreator();
    void connectControler(Controler *controler);
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
    Protocol* protocol;
    WaitRoom* wait;
    std::vector<button*> buttons;
    std::vector<QLineEdit*> lines;
    bool closeX;
    bool isExec;
    bool back;
};

#endif // ROOMCREATOR_H
