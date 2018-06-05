#ifndef MAPSELECTION_H
#define MAPSELECTION_H

#include <QWidget>
#include <QDialog>
#include "protocol.h"
#include "interactionInSelection.h"
#include <QLabel>
#include <QPushButton>

namespace Ui {
class MapSelection;
}

class MapSelection : public QDialog
{
    Q_OBJECT

public:
    explicit MapSelection(Protocol* protocol, QWidget *parent = 0);
    ~MapSelection();
    void adjustView(int8_t id, std::string &buf);

private slots:
    void on_map1Select_clicked();

    void on_map2select_clicked();

    void on_map3Select_clicked();

    void on_map4Select_clicked();

    void on_map5Select_clicked();

    void on_map6Select_clicked();

private:
    Ui::MapSelection *ui;
    Protocol* protocol;
    InteractionInSelection* interaction;
    QList<QLabel*> labels;
    QList<QPushButton> buttons;

    void adjustView();
};

#endif // MAPSELECTION_H
