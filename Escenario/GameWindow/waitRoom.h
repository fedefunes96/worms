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
    void setShowWindow(bool show);
    bool getShowWindow();
    void closeEvent(QCloseEvent *event);
    bool closeWithX();
public slots:
    void plysInRoom(int cant);
    void startGameView();

signals:
    void startView();
    void closeGame();
private slots:
    void on_pushButton_clicked();

private:
    Ui::WaitRoom *ui;
    Protocol *protocol;
    bool showW;
    bool closeX;
};

#endif // WAITROOM_H
