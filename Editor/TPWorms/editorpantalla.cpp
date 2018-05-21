#include "editorpantalla.h"
#include "ui_editorpantalla.h"
#include "editorseleccionarmasherramientas.h"
#include "editor_worm_view.h"
#include <QGraphicsScene>
#include <QMessageBox>
#include "editor_viga_view.h"
#include <QGraphicsSceneMouseEvent>
#include "editor_view.h"
#include <QFileDialog>
#include <QFile>
#include "commonparser.h"

EditorPantalla::EditorPantalla(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditorPantalla)
{
    ui->setupUi(this);
    this->scene = new QGraphicsScene(this);
    scene->setFocus();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFocus();
    this->scene->setSceneRect(0,0,2000,1000);
    this->id = 0;

}

EditorPantalla::~EditorPantalla()
{
    delete ui;
}

void EditorPantalla::load()
{
    this->usables.clear();
    this->worms.clear();
    this->vigas.clear();
    for (auto &x : items){
        delete x.second;
    }
    items.clear();
    for (int i = 0; i < 100;i++){
        for (int j = 0; j < 40; j++){
            celdas[i][j].vaciar_celda();
        }
    }
    std::string name = nombre.toUtf8().constData();
    commonParser parser;
    parser.load(this,name);
}

void EditorPantalla::fileName(QString name)
{
    this->nombre = name;
    load();
}

void EditorPantalla::on_agregarGusano_clicked()
{
    this->estado = 1;
}

void EditorPantalla::on_AgregarViga_clicked()
{
    this->estado = 2;
}

void EditorPantalla::on_agregarVigaChica_clicked()
{
    this->estado = 3;
}

void EditorPantalla::agregar_gusano(int x, int y, int vida)
{
    int celdaX = x/50;
    int celdaY = y/50;
    x = celdaX*50;
    y = celdaY*50;
    int piso = x +25;
    int altura = y +1;
    if (!celdas[celdaX][celdaY].esta_ocupado()){
        QGraphicsItem *worm = new Worm_View();
        scene->addItem(worm);
        worm->setPos(x,y);
        celdas[celdaX][celdaY].llenar_celda(id);
        this->items[id] = worm;
        this->worms.emplace(std::piecewise_construct,
                                    std::forward_as_tuple(id++),
                                    std::forward_as_tuple(piso,altura,vida));
        this->estado = 0;
    } else {
        QMessageBox::information(this, tr("Error"), tr("celda ocupada"));
    }
}

int EditorPantalla::agregar_viga_grande(int x, int y)
{
    int celdaX = x/50;
    int celdaY = y/50;
    bool ocupadas = celdas[celdaX][celdaY].esta_ocupado() ||
            celdas[celdaX+1][celdaY].esta_ocupado() || celdas[celdaX+2][celdaY].esta_ocupado()
            || celdas[celdaX+3][celdaY].esta_ocupado() || celdas[celdaX+4][celdaY].esta_ocupado()
            || celdas[celdaX+5][celdaY].esta_ocupado();
    if (!ocupadas){
        int xn = celdaX*50;
        int yn = celdaY*50;
        editor_viga_view * viga = new editor_viga_view();
        viga->esGrande(true);
        scene->addItem((QGraphicsItem *)viga);
        viga->setPos(xn,yn);
        this->items[id] = viga;
        celdas[celdaX][celdaY].llenar_celda(id);
        celdas[celdaX+1][celdaY].llenar_celda(id);
        celdas[celdaX+2][celdaY].llenar_celda(id);
        celdas[celdaX+3][celdaY].llenar_celda(id);
        celdas[celdaX+4][celdaY].llenar_celda(id);
        celdas[celdaX+5][celdaY].llenar_celda(id);
        this->vigas.emplace(std::piecewise_construct,
                        std::forward_as_tuple(id++),
                        std::forward_as_tuple(x,y,6));
        this->estado = 0;
        return (id-1);
    } else {
        QMessageBox::information(this, tr("Error"), tr("celda ocupada"));
    }
    return -1;
}

int EditorPantalla::agregar_viga_chica(int x, int y)
{
    int celdaX = x/50;
    int celdaY = y/50;
    bool ocupadas = celdas[celdaX][celdaY].esta_ocupado() ||
            celdas[celdaX+1][celdaY].esta_ocupado() || celdas[celdaX+2][celdaY].esta_ocupado();
    if (!ocupadas){
        int xn = celdaX*50;
        int yn = celdaY*50;
        editor_viga_view * viga = new editor_viga_view();
        viga->esGrande(false);
        scene->addItem((QGraphicsItem*)viga);
        viga->setPos(xn,yn);
        this->items[id] = viga;
        celdas[celdaX][celdaY].llenar_celda(id);
        celdas[celdaX+1][celdaY].llenar_celda(id);
        celdas[celdaX+2][celdaY].llenar_celda(id);
        this->vigas.emplace(std::piecewise_construct,
                        std::forward_as_tuple(id++),
                        std::forward_as_tuple(x,y,3));

        this->estado = 0;
        return (id-1);
    } else {
        QMessageBox::information(this, tr("Error"), tr("celda ocupada"));
    }
    return -1;
}

bool EditorPantalla::agregar_arma(int id, int municion)
{
    std::map<int,editorUsables>::iterator it;
    it = usables.find(id);
    if (it != usables.end()){
        usables.erase(it);
        return true;
    }
    usables.emplace(std::piecewise_construct,
            std::forward_as_tuple(id),
            std::forward_as_tuple(municion));
    return false;
}

void EditorPantalla::aumetar_angulo(int id)
{
    int x1 = items[id]->pos().x()/50;
    int y1 = items[id]->pos().y()/50;
    editor_viga_view *viga = (editor_viga_view *)items[id];
    if (viga->tam()){
        for (int i = 1; i < 6; i++){
            celdas[x1+i][y1].vaciar_celda();
        }
    } else {
        for (int i = 1; i < 3; i++){
            celdas[x1+i][y1].vaciar_celda();
        }
    }
    vigas[id].aumentarAngulo(5);
    items[id]->setRotation(items[id]->rotation() - 5);
}

void EditorPantalla::on_SelecionarHerramintas_Armas_clicked()
{
    editorSeleccionArmasHerramientas pantalla3;
    pantalla3.pasarMap(this,usables);
    pantalla3.setModal(true);
    pantalla3.exec();
}

void EditorPantalla::mousePressEvent(QMouseEvent * evento)
{
    int x = evento->pos().x();
    int y = evento->pos().y();

    if (this->estado == 0){
        int celdaX = x/50;
        int celdaY = y/50;
        if (celdas[celdaX][celdaY].esta_ocupado()){
            this->current_id = this->celdas[celdaX][celdaY].obtener_id();
        } else {
            this->current_id = -1;
        }
    }

    if (this->estado == 1){
        int vida = ui->vidaGusano->text().toInt();
        if (vida != 0){
            this->agregar_gusano(x,y, vida);
        } else {
            QMessageBox::information(this,tr("Error"), tr("Vida invalida"));
        }
    }

    if (this->estado == 2){
        this->agregar_viga_grande(x,y);
    }

    if (this->estado == 3){
        agregar_viga_chica(x,y);
    }
}


void EditorPantalla::on_quitar_clicked()
{
    std::map<int, QGraphicsItem*>::iterator iter;
    iter = items.find(current_id);
    if ( iter != items.end()){
        int x = items[this->current_id]->pos().x();
        int y = items[this->current_id]->pos().y();
        int x1 = x/50;
        int y1 = y/50;
        std::map<int, editorWorm>::iterator it;
        it = this->worms.find(current_id);
        if (it != worms.end()){
            celdas[x1][y1].vaciar_celda();
            worms.erase(it);
        }

        std::map<int, editorViga>::iterator it2;
        it2 = this->vigas.find(current_id);
        if (it2 != vigas.end()){
            editor_viga_view *viga = (editor_viga_view *)items[current_id];
            if (viga->tam()){
                for (int i = 0; i < 6; i++){
                    celdas[x1+i][y1].vaciar_celda();
                }
            } else {
                for (int i = 0; i < 3; i++){
                    celdas[x1+i][y1].vaciar_celda();
                }
            }
            vigas.erase(it2);
        }

        delete items[current_id];
        items.erase(iter);
    }
}

void EditorPantalla::on_mas_clicked()
{
    std::map<int, editorViga>::iterator it2;
    it2 = this->vigas.find(current_id);
    if (it2 != vigas.end()){
        int x = items[this->current_id]->pos().x();
        int y = items[this->current_id]->pos().y();
        int x1 = x/50;
        int y1 = y/50;
        editor_viga_view *viga = (editor_viga_view *)items[current_id];
        if (viga->tam()){
            for (int i = 1; i < 6; i++){
                celdas[x1+i][y1].vaciar_celda();
            }
        } else {
            for (int i = 1; i < 3; i++){
                celdas[x1+i][y1].vaciar_celda();
            }
        }
        vigas[current_id].aumentarAngulo(5);
        items[current_id]->setRotation(items[current_id]->rotation() - 5);

    }
}

void EditorPantalla::on_menos_clicked()
{
    std::map<int, editorViga>::iterator it2;
    it2 = this->vigas.find(current_id);
    if (it2 != vigas.end()){
        int x = items[this->current_id]->pos().x();
        int y = items[this->current_id]->pos().y();
        int x1 = x/50;
        int y1 = y/50;
        editor_viga_view *viga = (editor_viga_view *)items[current_id];
        if (viga->tam()){
            for (int i = 1; i < 6; i++){
                celdas[x1+i][y1].vaciar_celda();
            }
        } else {
            for (int i = 1; i < 3; i++){
                celdas[x1+i][y1].vaciar_celda();
            }
        }
        vigas[current_id].aumentarAngulo(-5);
        items[current_id]->setRotation(items[current_id]->rotation() + 5);

    }
}

void EditorPantalla::on_saveAs_clicked()
{
    nombre = QFileDialog::getSaveFileName(this,
                                               tr("Save "),
                                               tr(".txt"));
    if (nombre.isEmpty()){
        return;
    }
    std::string name = nombre.toUtf8().constData();
    commonParser parser;
    parser.save(name,this->usables,this->worms,this->vigas);
}

void EditorPantalla::on_pushButton_clicked()
{
    if (nombre.isEmpty()){
        nombre = QFileDialog::getSaveFileName(this,
                                                   tr("Save "),
                                                   tr(".txt"));
    }
    if (nombre.isEmpty()){
        return;
    }
    std::string name = nombre.toUtf8().constData();
    commonParser parser;
    parser.save(name,this->usables,this->worms,this->vigas);
}

void EditorPantalla::on_pushButton_2_clicked()
{
    nombre = QFileDialog::getOpenFileName(this,tr("Open"),
                                                    tr("Escenario *.cfg"));
    if (nombre.isEmpty()){
        return;
    }
    this->load();
}
