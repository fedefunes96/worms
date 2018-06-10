#ifndef MAPSELECTION_H
#define MAPSELECTION_H

#include <QWidget>
#include <QDialog>
#include "protocol.h"
#include "button.h"
#include <vector>
#include <QThread>

namespace Ui {
class MapSelection;
}

class MapSelection : public QDialog
{
    Q_OBJECT

public:
    explicit MapSelection(Protocol* protocol, QWidget *parent = nullptr);
    ~MapSelection();

private slots:

private:
    Ui::MapSelection *ui;
    Protocol* protocol;
    std::vector<button*> buttons;
    void adjustView();
};

#endif // MAPSELECTION_H
