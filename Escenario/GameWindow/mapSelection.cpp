#include "mapSelection.h"
#include "ui_mapSelection.h"
#include "protocol.h"
#include <QCollator>
#include <string>
#include <QPushButton>

MapSelection::MapSelection(Protocol* protocol, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapSelection)
{
    this->protocol = protocol;  
    ui->setupUi(this);
    this->setWindowTitle("Worms Map Selection");
    
}

MapSelection::~MapSelection()
{
    delete ui;
}

void MapSelection::recvRooms(QVector<std::string> list)
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
        printf("conecto");
    } else {
        printf("no conecto");
    }
}



void MapSelection::connectControler(Controler *controler)
{
    connect(controler,SIGNAL(join(int)),this,SLOT(join(int)));
    connect(controler,SIGNAL(recvMap(std::vector<std::string>)),this,SLOT(recvRooms(std::vector<std::string>)));
}
