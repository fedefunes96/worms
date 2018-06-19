#ifndef MAPSELECTION_H
#define MAPSELECTION_H

#include <QWidget>
#include <QDialog>
#include "protocol.h"
#include "button.h"
#include <vector>
#include <QThread>
#include "controler.h"
#include "waitRoom.h"

namespace Ui {
class MapSelection;
}

class MapSelection : public QDialog
{
    Q_OBJECT

public:
    explicit MapSelection(WaitRoom* wait,Protocol* protocol, QWidget *parent = nullptr);
    ~MapSelection();

    void connectControler(Controler *controler);
    void closeEvent(QCloseEvent *event);
private slots:
    void recvRooms(QList<std::string> list);
    void goWaitRoom(int cant);
    void on_pushButton_clicked();

signals:
    void closeGame();

private:
    Ui::MapSelection *ui;
    Protocol* protocol;
    std::vector<button*> buttons;
    WaitRoom* wait;
    void adjustView();
    bool closeX;
};

#endif // MAPSELECTION_H
