#include "clientmainwindow.h"
#include "ui_clientmainwindow.h"



clientMainWindow::clientMainWindow(MapSelection *map, RoomCreator *room, Protocol *protocol, QWidget *parent):
    QMainWindow (parent),
    ui(new Ui::clientMainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Worms Map Selection");
    this->map = map;
    this->room = room;
    this->protocol = protocol;
}

clientMainWindow::~clientMainWindow()
{

}

void clientMainWindow::on_mapSelection_clicked()
{
    this->protocol->sendJoinRoom();
    this->map->exec();
}

void clientMainWindow::on_pushButton_clicked()
{
    this->protocol->sendCreateRoom();
    this->room->exec();
}
