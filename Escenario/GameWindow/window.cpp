#include "window.h"
#include "ui_window.h"

Window::Window(MapSelection *map, RoomCreator *room, Protocol *protocol, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    this->map = map;
    this->room = room;
    this->protocol = protocol;
    this->setWindowTitle("Worms Armageddon");
}

Window::~Window()
{
    delete ui;
}

void Window::on_pushButton_clicked()
{
    this->protocol->sendCreateRoom();
    this->close();
    this->room->exec();
}

void Window::on_pushButton_2_clicked()
{
    this->protocol->sendJoinRoom();
    this->close();
    this->map->exec();
}

void Window::setId(int id)
{
    qDebug()<<"setear id:"<<id;
    this->id = id;
}

void Window::connectControler(Controler *controler)
{
    connect(controler,SIGNAL(playerId(int)),this,SLOT(setId(int)));
}

int Window::getId()
{
    return this->id;
}
