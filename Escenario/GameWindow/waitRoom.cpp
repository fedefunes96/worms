#include "waitRoom.h"
#include "ui_waitRoom.h"

WaitRoom::WaitRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WaitRoom)
{
    ui->setupUi(this);
}

WaitRoom::~WaitRoom()
{
    delete ui;
}

void WaitRoom::plysInRoom(int cant)
{
    // hacer algo con la cantidad de jugadoress....
}

void WaitRoom::startGameView()
{
    // iniciar el juego  la vista
}



void WaitRoom::connectControler(Controler *controler)
{
    connect(controler,SIGNAL(playersInRoom(int)),this,SLOT(plysInRoom(int)));
    connect(controler,SIGNAL(startGame()),this,SLOT(startGameView()));
}
