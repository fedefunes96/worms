#include "mapSelection.h"
#include "ui_mapSelection.h"
#include "protocol.h"
#include <QCollator>
#include <string>
#include "waitRoom.h"
#include <QPushButton>
#include <iostream>
#include <QMessageBox>

MapSelection::MapSelection(WaitRoom* wait,Protocol* protocol, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapSelection)
{
    this->protocol = protocol;  
    ui->setupUi(this);
    this->setWindowTitle("Worms Armageddon - Room selector");
    this->wait = wait;
    this->closeX=true;
    isExec=false;
    QPixmap img = QPixmap(ROOT_PATH"/resources/images/window.png");
    ui->imageBack->setScaledContents(true);
    ui->imageBack->setPixmap(img);
    ui->label->setStyleSheet("QLabel { background-color : white}");
}

void MapSelection::setExecute(bool enable)
{
    this->isExec=enable;
}

MapSelection::~MapSelection()
{
    delete ui;
}

void MapSelection::recvRooms(QList<std::string> list)
{
    qDebug()<<"recibi salas existentes";

    int cant = list.size();
    for (int i = 0; i < cant; ++i){
        std::cout<<"nombre:"<<list[i]<<std::endl;
        QString name = QString::fromStdString(list[i]);
        ui->listWidget->addItem(name);
    }
}

void MapSelection::goWaitRoom(int cant)
{
    if(!isExec){
        return;
    }
    qDebug()<<"en Map Selection pude conectarme con"<<cant;
    if (cant>0){
        this->wait->setShowWindow(true);
        this->closeX=false;
        this->close();
    } else {
        qDebug()<<"no se conecto";
    }
}

void MapSelection::closeEvent(QCloseEvent *event)
{
    if(this->closeX){
        this->wait->setShowWindow(false);
        emit closeGame();
    }
}


void MapSelection::connectControler(Controler *controler)
{
    connect(controler,SIGNAL(joinR(int)),this,SLOT(goWaitRoom(int)),Qt::QueuedConnection);
    connect(controler,SIGNAL(recvMap(QList<std::string>)),this,SLOT(recvRooms(QList<std::string>)),Qt::QueuedConnection);
    connect(this,SIGNAL(closeGame()),controler,SLOT(stopController()));
}

void MapSelection::on_pushButton_clicked()
{

}

void MapSelection::on_pushButton_released()
{
    if(ui->listWidget->count()==0){
        QMessageBox::information(this,"Error","There are no rooms in list.");
        return;
    }
    std::string name = ui->listWidget->currentItem()->text().toUtf8().constData();
    protocol->sendSelectRoom(name);
}
