#include "waitRoom.h"
#include "ui_waitRoom.h"

WaitRoom::WaitRoom(Protocol *protocol,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitRoom)
{
    ui->setupUi(this);
    this->protocol = protocol;
}

WaitRoom::~WaitRoom()
{
    delete ui;
}

void WaitRoom::plysInRoom(int cant)
{
    ui->jugadores->setText(QString::number(cant));
}

void WaitRoom::startGameView()
{
    // iniciar el juego  la vista
}



void WaitRoom::connectControler(Controler *controler)
{
    connect(controler,SIGNAL(playersInRoom(int)),this,SLOT(plysInRoom(int)));
    connect(controler,SIGNAL(startGame()),this,SLOT(startGameView()));
}

void WaitRoom::on_pushButton_clicked()
{
    this->protocol->sendExitRoom();
}
