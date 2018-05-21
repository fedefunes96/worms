#ifndef EDITORSELECCIONARMASHERRAMIENTAS_H
#define EDITORSELECCIONARMASHERRAMIENTAS_H

#include <QDialog>
#include <map>
#include "editorusables.h"
#include "editorpantalla.h"

namespace Ui {
class editorSeleccionArmasHerramientas;
}

class editorSeleccionArmasHerramientas : public QDialog
{
    Q_OBJECT

public:
    explicit editorSeleccionArmasHerramientas(QWidget *parent = 0);
    ~editorSeleccionArmasHerramientas();
    void pasarMap(EditorPantalla*editor, std::map<int, editorUsables> &usables);

private slots:
    void on_bazooka_clicked();

    void on_Mortero_clicked();

    void on_GranadaV_clicked();

    void on_GranadaR_clicked();

    void on_Banana_clicked();

    void on_GranadaS_clicked();

    void on_Dinamita_clicked();

    void on_Bate_clicked();

    void on_Aereo_clicked();

    void on_Teletransportador_clicked();

private:
    Ui::editorSeleccionArmasHerramientas *ui;
    EditorPantalla* editor;
};

#endif // EDITORSELECCIONARMASHERRAMIENTAS_H
