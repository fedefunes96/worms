#include "roomcreator.h"
#include "ui_roomcreator.h"
#include <QLineEdit>
#include "waitRoom.h"

RoomCreator::RoomCreator(WaitRoom *wait, Protocol* protocol, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoomCreator)
{
    ui->setupUi(this);
    this->protocol = protocol;
    this->wait = wait;
    this->setWindowTitle("Create Room");
}

RoomCreator::~RoomCreator()
{
    for (auto line : lines){
        delete line;
    }
    delete ui;
}

void RoomCreator::recvMaps(QList<std::string> list)
{
    int cant = list.size();
    for (int i = 0; i < cant; ++i){
        QLineEdit *line = new QLineEdit(this);
        line->move(i*100,40);
        line->show();
        lines.push_back(line);
        button *b = new button(protocol,this,list[i],line,i*100,0);
        buttons.push_back(b);
    }
}

void RoomCreator::createRoom()
{
    this->close();
    this->wait->exec();    
}


void RoomCreator::connectControler(Controler *controler)
{
    connect(controler,SIGNAL(recvMap(QList<std::string>)),this,SLOT(recvMaps(QList<std::string>)));
}
