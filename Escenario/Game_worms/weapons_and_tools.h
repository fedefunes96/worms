#ifndef WEAPONS_AND_TOOLS_H
#define WEAPONS_AND_TOOLS_H

#include <QDialog>
#include <QDebug>
#include "worm_view.h"


namespace Ui {
class Weapons_and_Tools;
}

class Weapons_and_Tools : public QDialog
{
    Q_OBJECT

public:
    Weapons_and_Tools(QWidget *parent = 0,Worm_View* worm = nullptr);
    ~Weapons_and_Tools();
private slots:
    void on_misil_clicked();

    void on_bat_clicked();

    void on_banana_clicked();

    void on_dinamite_clicked();

    void on_fragGranade_clicked();

    void on_granade_clicked();

    void on_holyGranade_clicked();

    void on_morter_clicked();

    void on_teleport_clicked();

    void on_bazooka_clicked();

    void on_punch_clicked();

private:
    Ui::Weapons_and_Tools *ui;
    Worm_View* worm;
};

#endif // WEAPONS_AND_TOOLS_H
