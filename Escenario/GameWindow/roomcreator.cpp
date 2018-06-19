#include "roomcreator.h"
#include "ui_roomcreator.h"
#include <QLineEdit>
#include "waitRoom.h"
#include <iostream>
#include <QMessageBox>

RoomCreator::RoomCreator(WaitRoom *wait, Protocol* protocol, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoomCreator)
{
    ui->setupUi(this);
    this->protocol = protocol;
    this->wait = wait;
    this->setWindowTitle("Worms Armageddon - Creador sala");
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
        std::cout<<"nombre:"<<list[i]<<std::endl;
        QString name = QString::fromStdString(list[i]);
        ui->listWidget->addItem(name);
        //QLineEdit *line = new QLineEdit(this);
        //line->move(i*100,40);
        //line->show();
        //lines.push_back(line);
        //button *b = new button(protocol,this,list[i],line,i*100,0);
        //buttons.push_back(b);
    }
}



void RoomCreator::connectControler(Controler *controler)
{
    connect(controler,SIGNAL(recvMap(QList<std::string>)),this,SLOT(recvMaps(QList<std::string>)));
    connect(this,SIGNAL(closeGame()),controler,SLOT(stopController()));
}



void RoomCreator::closeEvent(QCloseEvent *event)
{
    if(this->closeX){
        this->wait->setShowWindow(false);
        emit closeGame();
    }
}

void RoomCreator::on_pushButton_clicked()
{
    std::string nombre = ui->lineEdit->text().toUtf8().constData();
    std::string mapName = ui->listWidget->currentItem()->text().toUtf8().constData();
    if(nombre.size()==0){
        QMessageBox::information(this,"Invalid Input","Write a name valid for the room's name.");
    }else{
        std::cout << "nombre:"<<nombre << " mapName:" <<mapName <<std::endl;
        this->wait->setShowWindow(true);
        this->closeX=false;
        protocol->sendCreateRoom(nombre,mapName);
        this->close();
    }

}

