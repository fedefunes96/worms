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
