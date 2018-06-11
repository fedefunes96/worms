#include "mapSelection.h"
#include "ui_mapSelection.h"
#include "protocol.h"
#include <QCollator>
#include <string>
#include "waitRoom.h"
#include <QPushButton>

MapSelection::MapSelection(WaitRoom* wait,Protocol* protocol, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapSelection)
{
    this->protocol = protocol;  
    ui->setupUi(this);
    this->setWindowTitle("Worms Map Selection");
    this->wait = wait;
}

MapSelection::~MapSelection()
{
    delete ui;
}

void MapSelection::recvRooms(QList<std::string> list)
{
    int cant = list.size();
    for (int i = 0; i< cant; ++i){
        std::string name = list[i];
        button *b = new button(protocol,this,name,i*100,0);
        buttons.push_back(b);
    }
}

void MapSelection::join(int cant)
{
    if (cant){
        this->wait->exec();
    } else {
        printf("no conecto");
    }
}



void MapSelection::connectControler(Controler *controler)
{
    connect(controler,SIGNAL(join(int)),this,SLOT(join(int)));
    connect(controler,SIGNAL(recvMap(QList<std::string>)),this,SLOT(recvRooms(QList<std::string>)));
}
