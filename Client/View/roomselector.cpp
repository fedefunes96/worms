#include "roomselector.h"
#include "ui_roomselector.h"
#include <QCollator>
#include <string>
#include "waitRoom.h"
#include <QPushButton>
#include <iostream>
#include <QMessageBox>

RoomSelector::RoomSelector(ProtocolClient* protocol, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoomSelector)
{
    this->protocol = protocol;  
    ui->setupUi(this);
    this->setWindowTitle("Worms Armageddon - Room selector");
    this->closeX=true;
    isExec=false;
    QPixmap img = QPixmap(ROOT_PATH"/resources/images/window.png");
    ui->imageBack->setScaledContents(true);
    ui->imageBack->setPixmap(img);
    ui->label->setStyleSheet("QLabel { background-color : white}");
    this->back=false;
}

void RoomSelector::setExecute(bool enable)
{
    this->isExec=enable;
}

RoomSelector::~RoomSelector()
{
    delete ui;
}


void RoomSelector::askRooms(){
    this->protocol->sendJoinRoom();
}

void RoomSelector::recvRooms(QList<std::string> list)
{
    qDebug()<<"recibi salas existentes";
    ui->listWidget->clear();
    int cant = list.size();
    for (int i = 0; i < cant; ++i){
        std::cout<<"nombre:"<<list[i]<<std::endl;
        QString name = QString::fromStdString(list[i]);
        ui->listWidget->addItem(name);
    }
}

void RoomSelector::goWaitRoom(int cant)
{
    if(!isExec){
        return;
    }
    qDebug()<<"en Map Selection pude conectarme con"<<cant;
    if (cant>0){
        this->back=false;
        this->closeX=false;
        this->close();
    } else {
        QMessageBox::information(this,"Error","That room is not available anymore.");
        QListWidgetItem *item = ui->listWidget->takeItem(ui->listWidget->currentIndex().row());
        delete(item);
    }
}

void RoomSelector::connectControler(Controller *controler)
{
    connect(controler,SIGNAL(joinR(int)),this,SLOT(goWaitRoom(int)),Qt::QueuedConnection);
    connect(controler,SIGNAL(recvMap(QList<std::string>)),this,SLOT(recvRooms(QList<std::string>)),Qt::QueuedConnection);
}

void RoomSelector::on_pushButton_released()
{
    if(ui->listWidget->count()==0){
        QMessageBox::information(this,"Error","There are no rooms in list.");
        return;
    }
    QListWidgetItem *item = ui->listWidget->currentItem();
    if(!item){
        QMessageBox::information(this,"Error","There is no selected room.");
        return;
    }
    std::string name = ui->listWidget->currentItem()->text().toUtf8().constData();
    protocol->sendSelectRoom(name);
}

void RoomSelector::cleanCond(){
    this->back=false;
    this->isExec=false;
    this->closeX=true;
}

bool RoomSelector::closeWithX(){
    return this->closeX;
}

bool RoomSelector::isCallBack(){
    return this->back;
}

void RoomSelector::on_pushButton_2_released()
{
    this->back=true;
    this->closeX=false;
    this->close();
}
