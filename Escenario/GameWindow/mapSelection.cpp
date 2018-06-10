#include "mapSelection.h"
#include "ui_mapSelection.h"
#include "protocol.h"
#include <QCollator>
#include <string>
#include <QPushButton>

MapSelection::MapSelection(Protocol* protocol, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapSelection)
{
    this->protocol = protocol;  
    ui->setupUi(this);
    this->setWindowTitle("Worms Map Selection");
    // recivo cuantas salas hay
    int cant = 5;
    for (int i = 0; i< cant; ++i){
        //recivo los nobres
        std::string name = "hola";
        button *b = new button(protocol,this,name,i*100,0);
        buttons.push_back(b);
    }
}

MapSelection::~MapSelection()
{
    delete ui;
}
