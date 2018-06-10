#ifndef CLIENTMAINWINDOW_H
#define CLIENTMAINWINDOW_H

#include <QMainWindow>
#include "protocol.h"
#include "controler.h"
#include "mapSelection.h"
#include "roomcreator.h"

namespace Ui {
class clientMainWindow;
}

class clientMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit clientMainWindow(MapSelection *map,RoomCreator *room,Protocol* protocol,QWidget *parent = nullptr);
    ~clientMainWindow();

private slots:
    void on_mapSelection_clicked();

    void on_pushButton_clicked();

private:
    Ui::clientMainWindow *ui;
    MapSelection *map;
    RoomCreator *room;
    Protocol* protocol;
};

#endif
