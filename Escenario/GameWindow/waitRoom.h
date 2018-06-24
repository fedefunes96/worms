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
    WaitRoom(Protocol *protocol,QWidget *parent = nullptr);
    ~WaitRoom();

    void connectControler(Controler *controler);
    bool closeWithX();
    bool isExitRoom();
    void cleanCond();
public slots:
    void plysInRoom(int cant);
    void startGameView(QList<std::string> list);

signals:
    void startView(QList<std::string> list);
private slots:
    void on_pushButton_clicked();

private:
    Ui::WaitRoom *ui;
    Protocol *protocol;
    bool closeX;
    bool exit;
};

#endif // WAITROOM_H
