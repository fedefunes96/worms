#ifndef WAITROOM_H
#define WAITROOM_H

#include <QWidget>
#include <QDialog>
#include "controller.h"
#include "gamewindow.h"
#include "protocol_client.h"

namespace Ui {
class WaitRoom;
}

class WaitRoom : public QDialog
{
    Q_OBJECT

public:
    WaitRoom(ProtocolClient *protocol,QWidget *parent = nullptr);
    ~WaitRoom();

    void connectControler(Controller *controler);
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
    ProtocolClient *protocol;
    bool closeX;
    bool exit;
};

#endif // WAITROOM_H
