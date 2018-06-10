#ifndef MAPSELECTION_H
#define MAPSELECTION_H

#include <QWidget>
#include <QDialog>
#include "protocol.h"
#include "button.h"
#include <vector>
#include <QThread>
#include "controler.h"

namespace Ui {
class MapSelection;
}

class MapSelection : public QDialog
{
    Q_OBJECT

public:
    explicit MapSelection(Protocol* protocol, QWidget *parent = nullptr);
    ~MapSelection();

    void connectControler(Controler *controler);
private slots:
    void recvRooms(QVector<std::string> list);
    void join(int cant);

private:
    Ui::MapSelection *ui;
    Protocol* protocol;
    std::vector<button*> buttons;
    void adjustView();
};

#endif // MAPSELECTION_H
