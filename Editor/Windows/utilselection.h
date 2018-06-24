#ifndef EDITORSELECCIONARMASHERRAMIENTAS_H
#define EDITORSELECCIONARMASHERRAMIENTAS_H

#include <QDialog>
#include <map>
#include "editorusables.h"
#include "mapeditor.h"

enum class UsableIds : int8_t {
    BAZOOKA = 0,
    MORTAR,
    GREEN_GRENADE,
    RED_GRENADE,
    BANANA,
    HOLY_GRENADE,
    DYNAMITE,
    BASEBALL_BAT,
    AERIAL_ATTACK,
    TELEPORTATION
};

namespace Ui {
class editorSeleccionArmasHerramientas;
}

class UtilSelection : public QDialog
{
    Q_OBJECT

public:
    explicit UtilSelection(QWidget *parent = 0);
    ~UtilSelection();
    void pasarMap(MapEditor*editor, std::map<int, editorUsables> &usables);

private slots:


    void on_Bazookka_clicked();

    void on_Mortero_clicked();

    void on_GranadaV_clicked();

    void on_GranadaR_clicked();

    void on_Banana_clicked();

    void on_GranadaS_clicked();

    void on_Dinamita_clicked();

    void on_Bate_clicked();

    void on_Aereo_clicked();

    void on_Teletransportador_clicked();

    void on_buttonBox_accepted();

private:
    Ui::editorSeleccionArmasHerramientas *ui;
    MapEditor* editor;

    void mensaje_error();
};

#endif // EDITORSELECCIONARMASHERRAMIENTAS_H
