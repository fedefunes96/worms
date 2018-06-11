#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>

#include "mapSelection.h"
#include "roomcreator.h"
#include "protocol.h"

namespace Ui {
class Window;
}

class Window : public QDialog
{
    Q_OBJECT

public:
    Window(MapSelection *map,RoomCreator *room,Protocol* protocol,QWidget *parent = 0);
    ~Window();

    int getId();
    void connectControler(Controler *controler);
public slots:
    void setId(int id);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Window *ui;
    MapSelection *map;
    RoomCreator *room;
    Protocol *protocol;
    int id;
};

#endif // WINDOW_H
