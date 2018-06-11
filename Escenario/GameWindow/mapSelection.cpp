#include "mapSelection.h"
#include "ui_mapSelection.h"
#include "protocol.h"
#include <QCollator>
#include <string>
#include "waitRoom.h"
#include <QPushButton>
#include <iostream>

MapSelection::MapSelection(WaitRoom* wait,Protocol* protocol, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapSelection)
{
    this->protocol = protocol;  
    ui->setupUi(this);
    this->setWindowTitle("Worms Armageddon - Seleccion de sala");
    this->wait = wait;
}

MapSelection::~MapSelection()
{
    delete ui;
}

void MapSelection::recvRooms(QList<std::string> list)
{
    qDebug()<<"recibi salas existentes";
    int cant = list.size();
    for (int i = 0; i< cant; ++i){
        std::string name = list[i];
        std::cout << name << std::endl;
        button *b = new button(protocol,this,name,i*100,0);
        buttons.push_back(b);
    }
}

void MapSelection::goWaitRoom(int cant)
{
    if (cant>0){
        this->close();
        this->wait->exec();
    } else {
        qDebug()<<"no se conecto";
    }
}



void MapSelection::connectControler(Controler *controler)
{
    connect(controler,SIGNAL(joinR(int)),this,SLOT(goWaitRoom(int)));
    connect(controler,SIGNAL(recvMap(QList<std::string>)),this,SLOT(recvRooms(QList<std::string>)));
}
