#include "waitRoom.h"
#include "ui_waitRoom.h"

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

void WaitRoom::startGameView()
{
    // iniciar el juego  la vista
    emit startView();
    this->closeX=false;
    this->close();

}

void WaitRoom::closeEvent(QCloseEvent *event)
{
    if(this->closeX){
        emit closeGame();
    }
}

void WaitRoom::connectControler(Controler *controler)
{
    connect(controler,SIGNAL(playersInRoom(int)),this,SLOT(plysInRoom(int)));
    connect(controler,SIGNAL(startGame()),this,SLOT(startGameView()));
    connect(this,SIGNAL(closeGame()),controler,SLOT(stopController()));
}

void WaitRoom::on_pushButton_clicked()
{
    this->protocol->sendExitRoom();
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
