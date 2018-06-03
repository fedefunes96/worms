#include "mapSelection.h"
#include "ui_mapSelection.h"
#include "protocol.h"
#include <QCollator>
#include <string>

MapSelection::MapSelection(Protocol* protocol, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapSelection)
{
    this->protocol = protocol;
    interaction = new InteractionInSelection(protocol,this);
    ui->setupUi(this);
    labels = this->findChildren<QLabel*>();
    buttons = this->findChildren<QPushButton*>();
    QCollator c;
    c.setNumericMode(true);
    qSort(labels.begin(),labels.end(),[&c](const QLabel* label1, const QLabel* label2){
        if(c.compare(label1->objectName(),label2->objectName()) < 0){
            return true
        }
        return false;
    });

    qSort(buttons.begin(),buttons.end(),[&c](const QPushButton* button1, const QPushButton* button2){
        if(c.compare(button1->objectName(),button2->objectName()) < 0){
            return true
        }
        return false;
    });
    this->setWindowTitle("Worms Map Selection");
    this->setWindowState(Qt::WindowMaximized);
    adjustView();
    interaction->start();
}

MapSelection::~MapSelection()
{
    interaction->join();
    delete ui;
}

void MapSelection::adjustView(int8_t id, std::string &buf)
{
    buttons[id].setText(buf);
}

void MapSelection::adjustView()
{
    for(int i = 0; i < labels.size(); ++i){
        labels[i]->hide();
    }
    for (int i = 0; i < buttons.size(); ++i){
        buttons[i].hide();
    }
    int8_t cant = protocol->recvRooms();
    for (int8_t i = 0; i< cant; ++i){
        labels[i]->show();
        buttons[i].show();
    }
    for (int8_t i = 0; i< cant; ++i){
        int8_t id;
        int8_t cantMax;
        int8_t cantActual;
        protocol->recvRoomCaratc(&id,&cantMax,&cantActual);
        std::string s;
        s<<cantActual;
        s<< '/';
        s<<cantMax;
        buttons[i].setText(s);
    }
}

void MapSelection::on_map1Select_clicked()
{
    int8_t id = 1;
    protocol->sendRoomSel(id);
}

void MapSelection::on_map2select_clicked()
{
    int8_t id = 2;
    protocol->sendRoomSel(id);
}

void MapSelection::on_map3Select_clicked()
{
    int8_t id = 3;
    protocol->sendRoomSel(id);
}

void MapSelection::on_map4Select_clicked()
{
    int8_t id = 4;
    protocol->sendRoomSel(id);
}

void MapSelection::on_map5Select_clicked()
{
    int8_t id = 5;
    protocol->sendRoomSel(id);
}

void MapSelection::on_map6Select_clicked()
{
    int8_t id = 6;
    protocol->sendRoomSel(id);
}
