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
    this->closeX=true;
    QPixmap img = QPixmap(ROOT_PATH"/resources/images/window.png");
    ui->imageBack->setScaledContents(true);
    ui->imageBack->setPixmap(img);
    ui->label->setStyleSheet("QLabel { background-color : white}");
    ui->jugadores->setStyleSheet("QLabel { background-color : white}");
    this->exit=false;
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
    emit startView(list);
    this->exit=false;
    this->closeX=false;
    this->close();
}


void WaitRoom::connectControler(Controler *controler)
{
    connect(controler,SIGNAL(playersInRoom(int)),this,SLOT(plysInRoom(int)),Qt::QueuedConnection);
    connect(controler,SIGNAL(startGame(QList<std::string>)),this,SLOT(startGameView(QList<std::string>)),Qt::QueuedConnection);
}

void WaitRoom::on_pushButton_clicked()
{
    this->protocol->sendExitRoom();
    this->exit=true;
    this->closeX=false;
    this->close();
}

bool WaitRoom::closeWithX()
{
    return this->closeX;
}

bool WaitRoom::isExitRoom(){
    return this->exit;
}

void WaitRoom::cleanCond(){
    this->exit=false;
    this->closeX=true;
}
