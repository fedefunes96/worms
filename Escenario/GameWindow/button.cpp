#include "button.h"
#include <QString>
#include "roomcreator.h"
#include "mapSelection.h"

button::button(Protocol *protocol, QWidget *widget, std::string &name, int x,int y)
{
    this->protocol = protocol;
    but = new QPushButton(widget);
    but->move(x,y);
    this->widget = widget;
    but->setText(QString::fromStdString(name));
    but->show();
    connect(but,SIGNAL(released()),this,SLOT(conectarse()));
}

button::button(Protocol *protocol, QWidget *widget, std::string &name, QLineEdit *line, int x, int y)
{
    this->protocol = protocol;
    but = new QPushButton(widget);
    this->widget = widget;
    but->move(x,y);
    this->lines = line;
    but->setText(QString::fromStdString(name));
    but->show();
    connect(but,SIGNAL(released()),this,SLOT(create()));
    connect(but,SIGNAL(released()),widget,SLOT(createRoom()));
}

button::~button()
{
    delete but;
}

void button::conectarse()
{
    std::string name = but->text().toUtf8().constData();
    protocol->sendSelectRoom(name);
    //widget->close();
}

void button::create()
{
    std::string nombre = lines->text().toUtf8().constData();
    if (nombre.size() == 0){

    } else {
        std::string name = but->text().toUtf8().constData();
        protocol->sendCreateRoom(nombre,name);
        //widget->close();
    }
}
