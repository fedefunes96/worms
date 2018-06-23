#include "window.h"
#include "ui_window.h"


Window::Window(MapSelection *map, RoomCreator *room, Protocol *protocol, WaitRoom *wait, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    this->map = map;
    this->room = room;
    this->protocol = protocol;
    this->setWindowTitle("Worms Armageddon");
    this->wait = wait;
    this->closeX=true;
    QPixmap img = QPixmap(ROOT_PATH"/resources/images/window.png");
    ui->imageBack->setScaledContents(true);
    ui->imageBack->setPixmap(img);
    //ui->imageBack->setScaledContents(true);

}

Window::~Window()
{
    delete ui;
}

void Window::on_pushButton_clicked()
{
    this->closeX=false;
    this->protocol->sendCreateRoom();
    this->close();
    this->room->setExecute(true);
    this->room->exec();
}

void Window::on_pushButton_2_clicked()
{
    this->closeX=false;
    this->protocol->sendJoinRoom();
    this->close();
    this->map->setExecute(true);
    this->map->exec();
}

void Window::setId(int id)
{
    qDebug()<<"setear id:"<<id;
    this->id = id;
}

void Window::connectControler(Controler *controler)
{
    connect(controler,SIGNAL(playerId(int)),this,SLOT(setId(int)));
    connect(this,SIGNAL(closeGame()),controler,SLOT(stopController()));
}

int Window::getId()
{
    return this->id;
}


void Window::closeEvent(QCloseEvent *event)
{
    if(this->closeX){
        qDebug()<<"entre al cerrar window";
        emit closeGame();
    }
}

bool Window::closeWithX()
{
    return this->closeX;
}
