#include "button.h"
#include <QString>

button::button(Protocol *protocol, QWidget *widget, std::string &name, int x,int y)
{
    this->protocol = protocol;
    but = new QPushButton(widget);
    but->move(x,y);
    but->setText(QString::fromStdString(name));
    but->show();
    connect(but,SIGNAL(released()),this,SLOT(conectarse()));
}

button::button(Protocol *protocol, QWidget *widget, std::string &name, QLineEdit *line, int x, int y)
{
    this->protocol = protocol;
    but = new QPushButton(widget);
    but->move(x,y);
    this->lines = line;
    but->setText(QString::fromStdString(name));
    but->show();
    connect(but,SIGNAL(released()),this,SLOT(create()));
}

button::~button()
{
    delete but;
}

void button::conectarse()
{
    protocol->sendSelectRoom(name);
}

void button::create()
{
    std::string nombre = lines->text().toUtf8().constData();
    if (nombre.size() == 0){

    } else {
        protocol->sendCreateRoom(nombre,name);
    }
}
