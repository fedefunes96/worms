#include "clientmainwindow.h"
#include "ui_clientmainwindow.h"
#include "mapSelection.h"
#include "exception"
#include <QMessageBox>

clientMainWindow::clientMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::clientMainWindow)
{

    ui->setupUi(this);
    this->setWindowTitle("Worms Client");
}

clientMainWindow::~clientMainWindow()
{
    delete ui;
}

void clientMainWindow::on_mapSelection_clicked()
{
    try{
        std::string ip("127.0.0.1");
        std::string puerto("7777");
        Socket sk(ip,puerto);
        Protocol protocol(&sk);
        MapSelection maps(&protocol);
        maps.setModal(true);
        maps.exec();
    } catch (std::exception e){
        QMessageBox::information(this,tr("Error"),tr("Server disconected."));
    }
}
