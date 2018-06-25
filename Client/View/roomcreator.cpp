#include "roomcreator.h"
#include "ui_roomcreator.h"
#include <QLineEdit>
#include "waitRoom.h"
#include <iostream>
#include <QMessageBox>

RoomCreator::RoomCreator(ProtocolClient* protocol, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoomCreator)
{
    ui->setupUi(this);
    this->protocol = protocol;
    this->setWindowTitle("Worms Armageddon - Room creator");
    this->isExec=false;
    QPixmap img = QPixmap(ROOT_PATH"/resources/images/window.png");
    ui->imageBack->setScaledContents(true);
    ui->imageBack->setPixmap(img);
    ui->label->setStyleSheet("QLabel { background-color : white}");
    ui->label_2->setStyleSheet("QLabel { background-color : white}");
    this->back=false;
    this->closeX=true;
}

RoomCreator::~RoomCreator()
{
    delete ui;
}

void RoomCreator::setExecute(bool enable)
{
    this->isExec=enable;
}

void RoomCreator::recvMaps(QList<std::string> list)
{
    ui->listWidget->clear();
    int cant = list.size();
    for (int i = 0; i < cant; ++i){
        QString name = QString::fromStdString(list[i]);
        ui->listWidget->addItem(name);
    }
}

bool RoomCreator::closeWithX(){
    return this->closeX;
}

void RoomCreator::askMaps(){
    this->protocol->sendCreateRoom();
}

void RoomCreator::connectControler(Controller *controler)
{
    connect(controler,SIGNAL(joinR(int)),this,SLOT(couldCreate(int)),Qt::QueuedConnection);
    connect(controler,SIGNAL(recvMap(QList<std::string>)),this,SLOT(recvMaps(QList<std::string>)));
}


void RoomCreator::couldCreate(int could)
{
    if(!isExec){
        return;
    }
    if(could!=0){
        this->back=false;
        this->closeX=false;
        this->close();
    }else{
        QMessageBox::information(this,"Error","Another room has the same name, choose another one.");
    }
}


void RoomCreator::on_pushButton_clicked()
{
    if(ui->listWidget->count()==0){
        QMessageBox::information(this,"Error","There are no maps in list.");
        return;
    }
    std::string nombre = ui->lineEdit->text().toUtf8().constData();
    QListWidgetItem *item = ui->listWidget->currentItem();
    if(!item){
        QMessageBox::information(this,"Error","There is no selected map.");
        return;
    }
    std::string mapName = ui->listWidget->currentItem()->text().toUtf8().constData();
    if(nombre.size()==0){
        QMessageBox::information(this,"Invalid Input","Write a name valid for the room's name.");
    }else{
        protocol->sendCreateRoom(nombre,mapName);
    }
}

bool RoomCreator::isCallBack(){
    return this->back;
}

void RoomCreator::cleanCond(){
    this->back=false;
    this->closeX=true;
    this->isExec=false;
}

void RoomCreator::on_pushButton_2_released()
{
    this->back=true;
    this->closeX=false;
    this->close();
}
