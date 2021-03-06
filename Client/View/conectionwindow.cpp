#include "conectionwindow.h"
#include "ui_conectionwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <iostream>

ConectionWindow::ConectionWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConectionWindow)
{
    ui->setupUi(this);
    this->closeX=true;
    this->setWindowTitle("Start Connection");
    QPixmap img = QPixmap(ROOT_PATH"/resources/images/window.png");
    ui->label->setStyleSheet("QLabel { background-color : white}");
    ui->label_2->setStyleSheet("QLabel { background-color : white}");
    ui->imageBack->setScaledContents(true);
    ui->imageBack->setPixmap(img);
}

ConectionWindow::~ConectionWindow()
{
    delete ui;
}


void ConectionWindow::on_pushButton_clicked()
{
    std::string ip = ui->ipLine->text().toUtf8().constData();
    std::string port = ui->portLine->text().toUtf8().constData();
    if(ip.size()==0 || port.size()==0){
        QMessageBox::information(this,"Invalid Input","Complete correctly ip box and port box.");
        return;
    }
    try{
        Socket client(ip,port);
        this->list.push_back(std::move(client));
    }catch (SocketException& e){
         QMessageBox::information(this,"Server Error","Could not connect to the server specified. Try again.");
         return;
    }
    this->closeX=false;
    this->close();
}


Socket ConectionWindow::getSocket()
{
    return std::move(this->list[0]);
}


bool ConectionWindow::closeWithX()
{
    return this->closeX;
}
