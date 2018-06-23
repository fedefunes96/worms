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
    this->isExec=false;
    QPixmap img = QPixmap(ROOT_PATH"/resources/images/window.png");
    ui->imageBack->setScaledContents(true);
    ui->imageBack->setPixmap(img);
    ui->label->setStyleSheet("QLabel { background-color : white}");
    ui->label_2->setStyleSheet("QLabel { background-color : white}");
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
    int cant = list.size();
    for (int i = 0; i < cant; ++i){
        std::cout<<"nombre:"<<list[i]<<std::endl;
        QString name = QString::fromStdString(list[i]);
        ui->listWidget->addItem(name);
    }
}



void RoomCreator::connectControler(Controler *controler)
{
    connect(controler,SIGNAL(joinR(int)),this,SLOT(couldCreate(int)),Qt::QueuedConnection);
    connect(controler,SIGNAL(recvMap(QList<std::string>)),this,SLOT(recvMaps(QList<std::string>)));
    connect(this,SIGNAL(closeGame()),controler,SLOT(stopController()));
}


void RoomCreator::couldCreate(int could)
{
    if(!isExec){
        return;
    }
    if(could!=0){
        //pude crear
        this->wait->setShowWindow(true);
        this->closeX=false;
        this->close();
    }else{
        QMessageBox::information(this,"Error","Another room has the same name, choose another one.");
    }
}



void RoomCreator::closeEvent(QCloseEvent *event)
{
    qDebug()<<"entre al cerar room creator";
    if(this->closeX){
        qDebug()<<"no quiero que se muestre mas nada";
        this->wait->setShowWindow(false);
        emit closeGame();
    }
}

void RoomCreator::on_pushButton_clicked()
{
    if(ui->listWidget->count()==0){
        QMessageBox::information(this,"Error","There are no maps in list.");
        return;
    }
    std::string nombre = ui->lineEdit->text().toUtf8().constData();
    std::string mapName = ui->listWidget->currentItem()->text().toUtf8().constData();
    if(nombre.size()==0){
        QMessageBox::information(this,"Invalid Input","Write a name valid for the room's name.");
    }else{
        protocol->sendCreateRoom(nombre,mapName);
        //this->couldCreate(1);
    }

}

