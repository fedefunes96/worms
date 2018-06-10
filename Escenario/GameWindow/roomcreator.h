#ifndef ROOMCREATOR_H
#define ROOMCREATOR_H

#include <QWidget>
#include "protocol.h"
#include "button.h"
#include <QLineEdit>
#include <QDialog>

namespace Ui {
class RoomCreator;
}

class RoomCreator : public QDialog
{
    Q_OBJECT

public:
    explicit RoomCreator(Protocol* protocol,QWidget *parent = nullptr);
    ~RoomCreator();

private:
    Ui::RoomCreator *ui;
    Protocol* protocol;
    std::vector<button*> buttons;
    std::vector<QLineEdit*> lines;
};

#endif // ROOMCREATOR_H
