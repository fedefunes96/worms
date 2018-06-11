#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include "protocol.h"
#include <QPushButton>
#include <QLineEdit>

class button : QWidget
{
    Q_OBJECT
public:
    button(Protocol* protocol, QWidget* widget, std::string &name, int x, int y);

    button(Protocol* protocol, QWidget* widget, std::string &name,QLineEdit *line, int x, int y);

    ~button();

private:
    QPushButton* but;
    Protocol *protocol;
    QLineEdit* lines;
    std::string name;
    QWidget* widget;

private slots:
    void conectarse();

    void create();
};

#endif
