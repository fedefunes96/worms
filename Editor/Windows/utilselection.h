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

    //Carga en la pantalla los datos las armas ya existentes
    void pasarMap(MapEditor*editor, std::map<int, editorUsables> &usables);

private slots:

    //Verifica que los datos de la Bazooka sean validos 
    //cuando se preciona el checkbox
    void on_Bazookka_clicked();

    //Verifica que los datos del Mortero sean validos 
    //cuando se preciona el checkbox
    void on_Mortero_clicked();

    //Verifica que los datos de la Granada Verde sean validos 
    //cuando se preciona el checkbox
    void on_GranadaV_clicked();

    //Verifica que los datos de la Granada Roja sean validos 
    //cuando se preciona el checkbox
    void on_GranadaR_clicked();

    //Verifica que los datos de la Banana sean validos 
    //cuando se preciona el checkbox
    void on_Banana_clicked();

    //Verifica que los datos de la Granada Santa sean validos 
    //cuando se preciona el checkbox
    void on_GranadaS_clicked();

    //Verifica que los datos de la Dinamita sean validos 
    //cuando se preciona el checkbox
    void on_Dinamita_clicked();

    //Verifica que los datos del Bate de Baseball sean validos 
    //cuando se preciona el checkbox
    void on_Bate_clicked();

    //Verifica que los datos del Ataque Aereo sean validos 
    //cuando se preciona el checkbox
    void on_Aereo_clicked();

    //Verifica que los datos del Teletransportador sean validos 
    //cuando se preciona el checkbox
    void on_Teletransportador_clicked();

    //Agrega todas las armas selecionadas y remueve las que no
    void on_buttonBox_accepted();

private:
    Ui::editorSeleccionArmasHerramientas *ui;
    MapEditor* editor;

    //Mensaje de error cuando los datos no son validos
    void mensaje_error();
};

#endif
