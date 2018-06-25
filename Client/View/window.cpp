#include "window.h"
#include "ui_window.h"


Window::Window(Protocol *protocol, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    this->protocol = protocol;
    this->setWindowTitle("Worms Armageddon");
    this->closeX=true;
    QPixmap img = QPixmap(ROOT_PATH"/resources/images/window.png");
    ui->imageBack->setScaledContents(true);
    ui->imageBack->setPixmap(img);
    this->selectRoom=false;
    this->createRoom=false;
}

Window::~Window()
{
    delete ui;
}

void Window::on_pushButton_clicked()
{
    this->createRoom=true;
    this->closeX=false;
    this->close();
    return;
}

void Window::cleanCond(){
    this->selectRoom=false;
    this->createRoom=false;
    this->closeX=true;
}

bool Window::isSelectRoom()
{
    return this->selectRoom;
}

bool Window::iscreateRoom()
{
    return this->createRoom;
}


void Window::on_pushButton_2_clicked()
{
    this->selectRoom=true;
    this->closeX=false;
    this->close();
    return;
}

void Window::setId(int id)
{
    this->id = id;
}

void Window::connectControler(Controller *controler)
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
        emit closeGame();
    }
}

bool Window::closeWithX()
{
    return this->closeX;
}
