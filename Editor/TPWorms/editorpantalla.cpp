#include "editorpantalla.h"
#include "ui_editorpantalla.h"
#include "editorseleccionarmasherramientas.h"
#include "editor_worm_view.h"
#include <QGraphicsScene>
#include <QMessageBox>
#include "editor_viga_view.h"
#include "editor_view.h"
#include <QFileDialog>
#include "commonparser.h"
#include <QDebug>
#include <QScrollBar>
#include <QBrush>
#include <QImage>
#include <iostream>
#include <QGraphicsSceneMouseEvent>

EditorPantalla::EditorPantalla(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditorPantalla)
{
    xscene = 2000;
    yscene = 1000;
    ui->setupUi(this);
    this->setWindowTitle("Nuevo mapa");
    this->scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setFocus();
    this->scene->setSceneRect(0,-yscene,xscene,yscene);
    scene->setBackgroundBrush(QBrush(QImage("../imagenes/fondo.png")));
    this->id = 0;
    ui->vidaGusano->hide();
    ui->ok->hide();
    ui->mas->hide();
    ui->menos->hide();
    this->current_id = -1;
    QPixmap bazooka = QPixmap("../imagenes/Bazooka.png");
    ui->bazooka->setPixmap(bazooka);
    QPixmap mortero = QPixmap("../imagenes/Mortar.png");
    ui->mortero->setPixmap(mortero);
    QPixmap granadaV = QPixmap("../imagenes/W4_Grenade.png");
    ui->granadaV->setPixmap(granadaV);
    QPixmap granadaR = QPixmap("../imagenes/Redgrenade.png");
    ui->granadaR->setPixmap(granadaR);
    QPixmap banana = QPixmap("../imagenes/Bananabomb.png");
    ui->banana->setPixmap(banana);
    QPixmap granadaS = QPixmap("../imagenes/Holy_Grenade.png");
    ui->granadaS->setPixmap(granadaS);
    QPixmap dinamita = QPixmap("../imagenes/W4_Dynamite.png");
    ui->dinamita->setPixmap(dinamita);
    QPixmap bate = QPixmap("../imagenes/Baseballbat.png");
    ui->bate->setPixmap(bate);
    QPixmap aereo = QPixmap("../imagenes/W4_Airstrike.png");
    ui->aereo->setPixmap(aereo);
    QPixmap tele = QPixmap("../imagenes/IconTeleport.png");
    ui->teletransportador->setPixmap(tele);
    loadWeapons();
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
            case 1:
                ui->bazooka->show();
            break;
            case 2:
                ui->mortero->show();
            break;
            case 3:
                ui->granadaV->show();
            break;
            case 4:
                ui->granadaR->show();
            break;
            case 5:
                ui->banana->show();
            break;
            case 6:
                ui->granadaS->show();
            break;
            case 7:
                ui->dinamita->show();
            break;
            case 8:
                ui->bate->show();
            break;
            case 9:
                ui->aereo->show();
            break;
            case 10:
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
    int celdaX = x/50;
    int celdaY = -y/50+1;

    if (!celdas[celdaX][celdaY].esta_ocupado()){
        int xn = celdaX*50;
        int yn = -celdaY*50;
        int piso = x +25;
        int altura = y +1;
        QGraphicsItem *worm = new Worm_View();
        scene->addItem(worm);
        worm->setPos(xn,yn);
        celdas[celdaX][celdaY].llenar_celda(id);
        this->items[id] = worm;
        this->worms.emplace(std::piecewise_construct,
                                    std::forward_as_tuple(id++),
                                    std::forward_as_tuple(piso,-altura));

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
    int celdaX = x/50;
    int celdaY = -y/50+1;
    bool ocupadas = celdas[celdaX][celdaY].esta_ocupado() ||
            celdas[celdaX+1][celdaY].esta_ocupado() || celdas[celdaX+2][celdaY].esta_ocupado()
            || celdas[celdaX+3][celdaY].esta_ocupado() || celdas[celdaX+4][celdaY].esta_ocupado()
            || celdas[celdaX+5][celdaY].esta_ocupado();
    if (!ocupadas){
        int xn = celdaX*50;
        int yn = -celdaY*50;
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
    int celdaX = x/50;
    int celdaY = -y/50+1;
    bool ocupadas = celdas[celdaX][celdaY].esta_ocupado() ||
            celdas[celdaX+1][celdaY].esta_ocupado() || celdas[celdaX+2][celdaY].esta_ocupado();
    if (!ocupadas){
        int xn = celdaX*50;
        int yn = -celdaY*50;
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

    x += ui->graphicsView->horizontalScrollBar()->value();
    y += ui->graphicsView->verticalScrollBar()->value();
    if (x >= (xscene - 100)){
        xscene += 400 ;
        this->scene->setSceneRect(0,-yscene,xscene,yscene);
    }
    if (y >= (yscene - 100)){
        yscene += 400;
        this->scene->setSceneRect(0,-yscene,xscene,yscene);
    }
    if (this->estado == 0){
        int celdaX = x/50;
        int celdaY = -y/50 +1;
        if (celdas[celdaX][celdaY].esta_ocupado()){
            if (current_id != -1){
                items[current_id]->setOpacity(1);
            }
            this->current_id = this->celdas[celdaX][celdaY].obtener_id();
            items[current_id]->setOpacity(0.5);
            std::map<int, editorViga>::iterator it;
            it = this->vigas.find(current_id);
            if (it != vigas.end()){
                ui->mas->show();
                ui->menos->show();
                ui->vidaGusano->hide();
                ui->ok->hide();
            } else {
                ui->vidaGusano->show();
                int vida = worms[current_id].getVida();
                if (vida != 0){
                    ui->vidaGusano->setText(QString::number(vida));
                } else {
                    ui->vidaGusano->setText("vida");
                }
                ui->ok->show();
                ui->mas->hide();
                ui->menos->hide();
            }
        } else {
            if (current_id != -1){
                items[current_id]->setOpacity(1);
            }
            this->current_id = -1;
            ui->vidaGusano->hide();
            ui->ok->hide();
            ui->mas->hide();
            ui->menos->hide();
        }
    }

    if (this->estado == 1){
        this->agregar_gusano(x,y);
        ui->agregarGusano->setChecked(false);
    }

    if (this->estado == 2){
        this->agregar_viga_grande(x,y);
        ui->AgregarViga->setChecked(false);
    }

    if (this->estado == 3){
        agregar_viga_chica(x,y);
        ui->agregarVigaChica->setChecked(false);
    }

}

void EditorPantalla::mouseReleaseEvent(QMouseEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();
    std::cout<<x<<' '<<y<<std::endl;
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
        current_id = -1;
        ui->vidaGusano->hide();
        ui->ok->hide();
        ui->mas->hide();
        ui->menos->hide();
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
    if (this->checkWorms()){
        nombre = QFileDialog::getSaveFileName(this,
                                               tr("Save "),
                                               tr(".txt"));
        if (nombre.isEmpty()){
            return;
        }
        this->setWindowTitle(nombre);
        std::string name = nombre.toUtf8().constData();
        commonParser::save(name,this->usables,this->worms,this->vigas);
    } else {
        QMessageBox::information(this,tr("Error"),tr("hay gusanos que tienen vida 0"));
    }
}

void EditorPantalla::on_pushButton_clicked()
{
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
        commonParser::save(name,this->usables,this->worms,this->vigas);
    } else {
        QMessageBox::information(this,tr("Error"),tr("hay gusanos que tienen vida 0"));
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


void EditorPantalla::on_pushButton_3_clicked()
{

}
