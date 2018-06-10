#include "roomcreator.h"
#include "ui_roomcreator.h"
#include <QLineEdit>

RoomCreator::RoomCreator(Protocol* protocol,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoomCreator)
{
    ui->setupUi(this);
    this->protocol = protocol;
    this->setWindowTitle("Create Room");
}

RoomCreator::~RoomCreator()
{
    for (auto line : lines){
        delete line;
    }
    delete ui;
}

void RoomCreator::recvMaps(QVector<std::string> list)
{
    int cant = list.size();
    for (int i = 0; i < cant; ++i){
        QLineEdit *line = new QLineEdit(this);
        line->move(i*100,40);
        line->show();
        lines.push_back(line);
        std::string name = list[i];
        button *b = new button(protocol,this,name,line,i*100,0);
        buttons.push_back(b);
    }
}


void RoomCreator::connectControler(Controler *controler)
{
    connect(controler,SIGNAL(recvMap(std::vector<std::string>)),this,SLOT(recvMaps(std::vector<std::string>)));
}
