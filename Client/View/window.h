#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>

#include "roomselector.h"
#include "roomcreator.h"
#include "protocol.h"
#include "waitRoom.h"

namespace Ui {
class Window;
}

class Window : public QDialog
{
    Q_OBJECT

public:
    Window(Protocol* protocol,QWidget *parent = 0);
    ~Window();

    int getId();
    void connectControler(Controller *controler);
    void closeEvent(QCloseEvent *event);
    bool closeWithX();
    bool isSelectRoom();
    bool iscreateRoom();
    void cleanCond();
signals:
    void closeGame();
public slots:
    void setId(int id);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Window *ui;
    RoomSelector *map;
    RoomCreator *room;
    Protocol *protocol;
    WaitRoom *wait;
    int id;
    bool closeX;
    bool createRoom;
    bool selectRoom;

};

#endif // WINDOW_H
