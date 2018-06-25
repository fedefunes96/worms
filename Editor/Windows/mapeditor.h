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

class MapEditor : public QDialog
{
    Q_OBJECT

public:
    explicit MapEditor(QWidget *parent = 0);

    ~MapEditor();

    void fileName(QString name);

    //Cambia la vida del gusano selecionado
    void setVIdaWorm(int id, int vida);

    //Agrega un gusano en la posicion X Y
    int add_worm(int x, int y);

    //Agrega una viga chica en la posicion X Y
    int add_small_girder(int x, int y);

    //Agrega una viga Grande en la posicion X Y
    int add_big_girder(int x, int y);

    //Agrega un arma con una id y su municion
    void agregar_arma(int id, int municion);

    //Remueve el arma que posea esa id
    void remove_weapon(int id);

    //Aumenta el angula de la viga
    void aumetar_angulo(int id, int angle);

    //Caraga las imagenes de las Armas y muetra las que se selecionaron
    void loadWeapons();

    //Cambia el fondo de pantalla
    void setBacGround(std::string &name);

public slots:
    //Accion a realizar cuando se captura la señal wormSelect
    void wormSelect(int id);

    //Accion a realizar cuando se captura la señal girderSelect
    void girderSelect(int id);

private slots:

    //Cambia el estado a ADD_WORM
    void on_agregarGusano_clicked();

    //Cambia el estado a ADD_BIG_GIRDER
    void on_AgregarViga_clicked();

    //Levanta la ventana para selecion de Armas y Herramientas
    void on_SelecionarHerramintas_Armas_clicked();

    //Cambia el estado a ADD_SMALL_GIRDER
    void on_agregarVigaChica_clicked();

    //Dependiendo de estado se hace diferentes cosas
    void mousePressEvent(QMouseEvent *evento);

    //Remueve el objeto selecionado
    void on_quitar_clicked();

    //Aumenta el angula de la viga selecionada
    void on_mas_clicked();

    //Reduce el angulo de la viga selecionada
    void on_menos_clicked();

    //Guarda un archivo en una carpeta
    void on_saveAs_clicked();

    //Guarda el archivo
    void on_pushButton_clicked();

    //Carga un mapa que se selecione a traves del QFileDialog
    void on_pushButton_2_clicked();

    //Cuando se preciona el boton cambia la vida del gusano selecionado
    void on_ok_clicked();

    //Remueve el objeto selecionado
    void on_remove_clicked();

    //Mueve el objeto hacia arriva
    void on_up_clicked();

    //Mueve el objeto hacia la izquierda
    void on_left_clicked();

    //Mueve el objeto hacia la derecha
    void on_right_clicked();

    //Mueve el objeto hacia abajo
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

    //Carga un mapa ya Existente
    void load();

    //Verifica que los gusanos sea validos
    bool checkWorms();

    //remueve el item que esta selecionado
    void removeItem();

    //chquea que los gusanos no colicionen al momento de guardar
    bool checkColicion();
};

#endif
