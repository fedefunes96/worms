#ifndef EDITORPANTALLA_H
#define EDITORPANTALLA_H

#include <QDialog>
#include <map>
#include <QtCore>
#include <QtGui>
#include "editorusables.h"
#include <QEvent>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QString>
#include "editorworm.h"
#include "editorviga.h"
#include "celda.h"

namespace Ui {
class EditorPantalla;
}

class EditorPantalla : public QDialog
{
    Q_OBJECT

public:
    explicit EditorPantalla(QWidget *parent = 0);

    ~EditorPantalla();

    void fileName(QString name);

    void agregar_gusano(int x, int y, int vida);

    int agregar_viga_grande(int x, int y);

    int agregar_viga_chica(int x, int y);

    bool agregar_arma(int id, int municion);

    void aumetar_angulo(int id);

private slots:

    void on_agregarGusano_clicked();

    void on_AgregarViga_clicked();

    void on_SelecionarHerramintas_Armas_clicked();

    void on_agregarVigaChica_clicked();

    void mousePressEvent(QMouseEvent *evento);

    void on_quitar_clicked();

    void on_mas_clicked();

    void on_menos_clicked();

    void on_saveAs_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    std::map<int, QGraphicsItem*> items;
    celda celdas[100][40];
    Ui::EditorPantalla *ui;
    std::map<int,editorUsables>usables;
    std::map<int, editorWorm> worms;
    std::map<int, editorViga> vigas;
    int id;
    int estado;
    QGraphicsScene * scene;
    int current_id;
    QString nombre;

    void load();
};


#endif
