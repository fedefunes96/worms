#ifndef WAITROOM_H
#define WAITROOM_H

#include <QWidget>
#include <QDialog>
#include "controler.h"
#include "gamewindow.h"
#include "protocol.h"

namespace Ui {
class WaitRoom;
}

class WaitRoom : public QDialog
{
    Q_OBJECT

public:
    explicit WaitRoom(Protocol *protocol,QWidget *parent = nullptr);
    ~WaitRoom();

    void connectControler(Controler *controler);
public slots:
    void plysInRoom(int cant);
    void startGameView();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WaitRoom *ui;
    Protocol *protocol;
};

#endif // WAITROOM_H
