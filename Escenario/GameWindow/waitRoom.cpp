#include "waitRoom.h"
#include "ui_waitRoom.h"
#include <iostream>

WaitRoom::WaitRoom(Protocol *protocol,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitRoom)
{
    ui->setupUi(this);
    this->protocol = protocol;
    this->setWindowTitle("Worms Armageddon - Sala de espera");
    this->showW=false;
    this->closeX=true;
}

WaitRoom::~WaitRoom()
{
    delete ui;
}

void WaitRoom::plysInRoom(int cant)
{
    ui->jugadores->setText(QString::number(cant));
}

void WaitRoom::startGameView(QList<std::string> list)
{
    // iniciar el juego  la vista
    qDebug()<<"inicie la vista";
    std::cout<<"el nombre del fondo pasado es:"<<list[0] <<std::endl;
    emit startView(list);
    this->closeX=false;
    this->close();

}

void WaitRoom::closeEvent(QCloseEvent *event)
{
    if(this->closeX){
        emit closeGame();
    }
    this->close();
}

void WaitRoom::connectControler(Controler *controler)
{
    connect(controler,SIGNAL(playersInRoom(int)),this,SLOT(plysInRoom(int)),Qt::QueuedConnection);
    connect(controler,SIGNAL(startGame(QList<std::string>)),this,SLOT(startGameView(QList<std::string>)),Qt::QueuedConnection);
    connect(this,SIGNAL(closeGame()),controler,SLOT(stopController()));
}

void WaitRoom::on_pushButton_clicked()
{
    this->protocol->sendExitRoom();
    emit closeGame();
    this->close();
}

void WaitRoom::setShowWindow(bool show){
    this->showW=show;
}

bool WaitRoom::getShowWindow()
{
    return this->showW;
}

bool WaitRoom::closeWithX()
{
    return this->closeX;
}
