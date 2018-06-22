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
#include <QGraphicsSceneMouseEvent>
#include <QString>
#include "editorworm.h"
#include "editorviga.h"
#include <QDropEvent>
#include <vector>

enum class State : int8_t {
   NOTHING = 0,
   ADD_WORM,
   ADD_BIG_GIRDER,
   ADD_SMALL_GIRDER
};

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

    void setVIdaWorm(int id, int vida);

    int add_worm(int x, int y);

    int add_small_girder(int x, int y);

    int add_big_girder(int x, int y);

    void agregar_arma(int id, int municion);

    void remove_weapon(int id);

    void aumetar_angulo(int id);

    void loadWeapons();

    void setBacGround(std::string &name);

public slots:
    void wormSelect(int id);

    void girderSelect(int id);

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

    void on_ok_clicked();

    void on_remove_clicked();

    void on_up_clicked();

    void on_left_clicked();

    void on_right_clicked();

    void on_down_clicked();

private:
    std::map<int, QGraphicsItem*> items;
    unsigned int cantidad = 2;
    std::map<std::pair<int,int>,int> celdas;
    Ui::EditorPantalla *ui;
    std::map<int,editorUsables>usables;
    std::map<int, editorWorm> worms;
    std::map<int, editorViga> vigas;
    int id;
    State estado;
    QGraphicsScene * scene;
    int current_id;
    QString nombre;
    int xscene;
    int yscene;
    std::vector<QPixmap*> armas;
    QString bakcground;

    void load();

    bool checkWorms();

    void removeItem();
};


#endif
