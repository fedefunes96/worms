#include "editorpantalla.h"
#include "ui_editorpantalla.h"
#include "editorseleccionarmasherramientas.h"
#include "editor_worm_view.h"
#include <QGraphicsScene>
#include <QMessageBox>
#include "editor_viga_view.h"
#include <QFileDialog>
#include "celda.h"
#include "commonparser.h"
#include <QDebug>
#include <QScrollBar>
#include <QBrush>
#include <QImage>
#include "editor_viga_grande_view.h"
#include <iostream>

EditorPantalla::EditorPantalla(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditorPantalla)
{

    xscene = 2000;
    yscene = 1000;
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    this->setWindowTitle("Nuevo mapa");
    this->scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    this->scene->setSceneRect(0,-yscene,xscene,yscene);
    scene->setBackgroundBrush(QBrush(QImage("../images/fondo.png")));
    this->id = 0;
    ui->wormOpt->hide();
    ui->girderOpt->hide();
    this->current_id = -1;
    QPixmap bazooka = QPixmap("../images/Bazooka.png");
    ui->bazooka->setPixmap(bazooka);
    QPixmap mortero = QPixmap("../images/Mortar.png");
    ui->mortero->setPixmap(mortero);
    QPixmap granadaV = QPixmap("../images/W4_Grenade.png");
    ui->granadaV->setPixmap(granadaV);
    QPixmap granadaR = QPixmap("../images/Redgrenade.png");
    ui->granadaR->setPixmap(granadaR);
    QPixmap banana = QPixmap("../images/Bananabomb.png");
    ui->banana->setPixmap(banana);
    QPixmap granadaS = QPixmap("../images/Holy_Grenade.png");
    ui->granadaS->setPixmap(granadaS);
    QPixmap dinamita = QPixmap("../images/W4_Dynamite.png");
    ui->dinamita->setPixmap(dinamita);
    QPixmap bate = QPixmap("../images/Baseballbat.png");
    ui->bate->setPixmap(bate);
    QPixmap aereo = QPixmap("../images/W4_Airstrike.png");
    ui->aereo->setPixmap(aereo);
    QPixmap tele = QPixmap("../images/IconTeleport.png");
    ui->teletransportador->setPixmap(tele);
    loadWeapons();
    ui->agregarGusano->setIcon(QIcon("../images/wormwait.png"));
    ui->agregarVigaChica->setIcon(QIcon("../images/grds4.png"));
    ui->AgregarViga->setIcon(QIcon("../images/grdl4.png"));
}

EditorPantalla::~EditorPantalla()
{
    delete ui;
}

void EditorPantalla::load()
{
    this->setWindowTitle(nombre);
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
    commonParser::load(this,name);
    loadWeapons();
}

bool EditorPantalla::checkWorms()
{
    for (auto &worm : worms){
        if (worm.second.getVida() == 0){
            return false;
        }
    }
    return true;
}

void EditorPantalla::llenarCeldas(int x, int y, int cant)
{
    for (int i = 0; i < cant; ++i){
        celdas[x+i][y].llenar_celda(id);
    }
}

void EditorPantalla::vaciarCeldas(int x, int y, int cant)
{
    for (int i = 0; i < cant; ++i){
        celdas[x+i][y].vaciar_celda();
    }
}

void EditorPantalla::removeItem()
{
    std::map<int, QGraphicsItem*>::iterator iter;
    iter = items.find(current_id);
    if ( iter != items.end()){
        int x = items[this->current_id]->pos().x();
        int y = items[this->current_id]->pos().y();
        int x1 = x/24;
        int y1 = -y/24;
        std::map<int, editorWorm>::iterator it;
        it = this->worms.find(current_id);
        if (it != worms.end()){
            x1++;
            vaciarCeldas(x1,y1,1);
            worms.erase(it);
        }

        std::map<int, editorViga>::iterator it2;
        it2 = this->vigas.find(current_id);
        if (it2 != vigas.end()){
            if (vigas[current_id].get_tam() == 6){
                vaciarCeldas(x1,y1,6);
            } else {
                vaciarCeldas(x1,y1,3);
            }
            vigas.erase(it2);
        }
        delete items[current_id];
        items.erase(iter);
        current_id = -1;
        estado = 0;
        ui->girderOpt->hide();
        ui->wormOpt->hide();
    }
}

void EditorPantalla::loadWeapons()
{
    ui->bazooka->hide();
    ui->mortero->hide();
    ui->granadaV->hide();
    ui->granadaR->hide();
    ui->banana->hide();
    ui->granadaS->hide();
    ui->dinamita->hide();
    ui->bate->hide();
    ui->aereo->hide();
    ui->teletransportador->hide();
    for (auto &x : usables){
        switch (x.first){
            case 0:
                ui->bazooka->show();
            break;
            case 1:
                ui->mortero->show();
            break;
            case 2:
                ui->granadaV->show();
            break;
            case 3:
                ui->granadaR->show();
            break;
            case 4:
                ui->banana->show();
            break;
            case 5:
                ui->granadaS->show();
            break;
            case 6:
                ui->dinamita->show();
            break;
            case 7:
                ui->bate->show();
            break;
            case 8:
                ui->aereo->show();
            break;
            case 9:
                ui->teletransportador->show();
            break;
        }
    }
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

int EditorPantalla::agregar_gusano(int x, int y)
{
    int celdaX = x/24;
    int celdaY = -y/24+1;

    if (!celdas[celdaX][celdaY].esta_ocupado()){
        int xn = celdaX*24 -20;
        int yn = -celdaY*24 -20;
        QGraphicsItem *worm = new Worm_View();
        scene->addItem(worm);
        worm->setPos(xn,yn);
        llenarCeldas(celdaX,celdaY,1);
        this->items[id] = worm;
        this->worms.emplace(std::piecewise_construct,
                                    std::forward_as_tuple(id++),
                                    std::forward_as_tuple(x,-y));

        this->estado = 0;
        return (id-1);
    } else {
        QMessageBox::information(this, tr("Error"), tr("celda ocupada"));
    }
    return -1;
}

void EditorPantalla::setVIdaWorm(int id, int vida)
{
    worms[id].setVida(vida);
}

int EditorPantalla::agregar_viga_grande(int x, int y)
{
    int celdaX = x/24;
    int celdaY = -y/24+1;
    bool ocupadas = true;
    for (int i = 0; i<6; ++i){
        ocupadas = ocupadas && celdas[celdaX+i][celdaY].esta_ocupado();
    }
    if (!ocupadas){
        int xn = celdaX*24;
        int yn = -celdaY*24;
        QGraphicsItem *viga = new editor_viga_grande_view ();
        scene->addItem(viga);
        viga->setPos(xn,yn);
        llenarCeldas(celdaX,celdaY,6);
        this->items[id] = viga;
        this->vigas.emplace(std::piecewise_construct,
                        std::forward_as_tuple(id++),
                        std::forward_as_tuple(x,-y,6));
        this->estado = 0;
        return (id-1);
    } else {
        QMessageBox::information(this, tr("Error"), tr("celda ocupada"));
    }
    return -1;
}

int EditorPantalla::agregar_viga_chica(int x, int y)
{
    int celdaX = x/24;
    int celdaY = -y/24+1;
    bool ocupadas = true;
    for (int i = 0; i<3; ++i){
        ocupadas = ocupadas && celdas[celdaX+i][celdaY].esta_ocupado();
    }
    if (!ocupadas){
        int xn = celdaX*24;
        int yn = -celdaY*24;
        QGraphicsItem *viga = new editor_viga_view();
        scene->addItem(viga);
        viga->setPos(xn,yn);
        llenarCeldas(celdaX,celdaY,3);
        this->items[id] = viga;
        this->vigas.emplace(std::piecewise_construct,
                        std::forward_as_tuple(id++),
                        std::forward_as_tuple(x,-y,3));

        this->estado = 0;
        return (id-1);
    } else {
        QMessageBox::information(this, tr("Error"), tr("celda ocupada"));
    }
    return -1;
}

void EditorPantalla::agregar_arma(int id, int municion)
{
    std::map<int,editorUsables>::iterator it;
    it = usables.find(id);
    if (it != usables.end()){
        return;
    }
    usables.emplace(std::piecewise_construct,
            std::forward_as_tuple(id),
                    std::forward_as_tuple(municion));
}

void EditorPantalla::remove_weapon(int id)
{
    std::map<int,editorUsables>::iterator it;
    it = usables.find(id);
    if (it == usables.end()){
        return;
    }
    usables.erase(it);
}

void EditorPantalla::aumetar_angulo(int id)
{
    int x1 = items[id]->pos().x()/24;
    int y1 = -items[id]->pos().y()/24;
    std::map<int,editorViga>::iterator it;
    if (vigas[id].get_tam() == 6){
        vaciarCeldas(x1,y1,6);
    } else {
        vaciarCeldas(x1,y1,3);
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

    x += ui->graphicsView->horizontalScrollBar()->value();
    y += ui->graphicsView->verticalScrollBar()->value();
    if (x >= (xscene - 100)){
        xscene += 400 ;
        this->scene->setSceneRect(0,-yscene,xscene,yscene);
    }

    if (estado == 0){
        int celdaX = x/24;
        int celdaY = -y/24 +1;
        if (current_id != -1){
            items[current_id]->setOpacity(1);
        }
        if (celdas[celdaX][celdaY].esta_ocupado()){
            this->current_id = this->celdas[celdaX][celdaY].obtener_id();
            items[current_id]->setOpacity(0.5);
            std::map<int, editorViga>::iterator it;
            it = this->vigas.find(current_id);
            if (it != vigas.end()){
                ui->girderOpt->show();
                ui->wormOpt->hide();
            } else {
                ui->wormOpt->show();
                ui->girderOpt->hide();
                ui->vidaGusano->setValue(worms[current_id].getVida());
            }
        } else {
            this->current_id = -1;
            ui->wormOpt->hide();
            ui->girderOpt->hide();
        }
    }

    if (estado == 1){
        this->agregar_gusano(x,y);
        ui->agregarGusano->setChecked(false);
    }

    if (estado == 2){
        this->agregar_viga_grande(x,y);
        ui->AgregarViga->setChecked(false);
    }

    if (estado == 3){
        agregar_viga_chica(x,y);
        ui->agregarVigaChica->setChecked(false);
    }

}

void EditorPantalla::on_quitar_clicked()
{
    removeItem();
}

void EditorPantalla::on_mas_clicked()
{
    std::map<int, editorViga>::iterator it2;
    it2 = this->vigas.find(current_id);
    if (it2 != vigas.end()){
        int x = items[this->current_id]->pos().x();
        int y = items[this->current_id]->pos().y();
        int x1 = x/24 +1;
        int y1 = -y/24;
        if (vigas[current_id].get_tam() == 6){
            vaciarCeldas(x1,y1,6);
        } else {
            vaciarCeldas(x1,y1,3);
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
        int x1 = (x/24) +1;
        int y1 = -y/24;
        if (vigas[current_id].get_tam() == 6){
            vaciarCeldas(x1,y1,6);
        } else {
            vaciarCeldas(x1,y1,3);
        }
        vigas[current_id].aumentarAngulo(-5);
        items[current_id]->setRotation(items[current_id]->rotation() + 5);

    }
}

void EditorPantalla::on_saveAs_clicked()
{
    if (ui->cant->text().toInt()!= 0){
        this->cantidad = ui->cant->text().toInt();
    }
    if (this->cantidad <= worms.size()){
        if (this->checkWorms()){
            nombre = QFileDialog::getSaveFileName(this,
                                               tr("Save "),
                                               tr(".yaml"));
            if (nombre.isEmpty()){
                return;
            }
            this->setWindowTitle(nombre);
            std::string name = nombre.toUtf8().constData();
            commonParser::save(name,this->usables,this->worms,this->vigas, cantidad);
        } else {
            QMessageBox::information(this,tr("Error"),tr("hay gusanos que tienen vida 0."));
        }
    } else {
        QMessageBox::information(this,tr("Error"),tr("No hay suficientes gusanos en el escenario."));
    }
}

void EditorPantalla::on_pushButton_clicked()
{
    if (ui->cant->text().toInt()!= 0){
        this->cantidad = ui->cant->text().toInt();
    }
    if (this->cantidad <= worms.size()){
        if (this->checkWorms()){
            if (nombre.isEmpty()){
                nombre = QFileDialog::getSaveFileName(this,
                                                   tr("Save "),
                                                   tr(".yaml"));
            }
            if (nombre.isEmpty()){
                return;
            }
            this->setWindowTitle(nombre);
            std::string name = nombre.toUtf8().constData();
            commonParser::save(name,this->usables,this->worms,this->vigas, cantidad);
        } else {
            QMessageBox::information(this,tr("Error"),tr("hay gusanos que tienen vida 0"));
        }
    } else {
        QMessageBox::information(this,tr("Error"),tr("No hay suficientes gusanos en el escenario."));
    }
}

void EditorPantalla::on_pushButton_2_clicked()
{
    nombre = QFileDialog::getOpenFileName(this,tr("Open"),
                                                    tr("Escenario *.yaml"));
    if (nombre.isEmpty()){
        return;
    }
    this->load();
}

void EditorPantalla::on_ok_clicked()
{
    int vida = ui->vidaGusano->text().toInt();
    if ( vida == 0){
        QMessageBox::information(this,tr("Error"),tr("Vida indalida"));
        return;
    }
    worms[current_id].setVida(vida);
}

void EditorPantalla::on_remove_clicked()
{
    removeItem();
}
