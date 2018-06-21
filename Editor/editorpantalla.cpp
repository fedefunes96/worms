#include "editorpantalla.h"
#include "ui_editorpantalla.h"
#include "editorseleccionarmasherramientas.h"
#include "editor_worm_view.h"
#include <QGraphicsScene>
#include <QMessageBox>
#include "editor_viga_view.h"
#include <QFileDialog>
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
    xscene = 3000;
    yscene = 10000;
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    this->setWindowTitle("Nuevo mapa");
    this->scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    this->scene->setSceneRect(0,-yscene,xscene,yscene);
    std::string name = "fondo.png";
    this->setBacGround(name);
    this->id = 0;
    ui->wormOpt->hide();
    ui->girderOpt->hide();
    this->current_id = -1;
    QPixmap bazooka = QPixmap(ROOT_PATH"/resources/images/Bazooka.png");
    bazooka = bazooka.scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->bazooka->setPixmap(bazooka);
    QPixmap mortero = QPixmap(ROOT_PATH"/resources/images/Mortar.png");
    mortero = mortero.scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->mortero->setPixmap(mortero);
    QPixmap granadaV = QPixmap(ROOT_PATH"/resources/images/W4_Grenade.png");
    granadaV = granadaV.scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->granadaV->setPixmap(granadaV);
    QPixmap granadaR = QPixmap(ROOT_PATH"/resources/images/Redgrenade.png");
    granadaR = granadaR.scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->granadaR->setPixmap(granadaR);
    QPixmap banana = QPixmap(ROOT_PATH"/resources/images/Bananabomb.png");
    banana = banana.scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->banana->setPixmap(banana);
    QPixmap granadaS = QPixmap(ROOT_PATH"/resources/images/Holy_Grenade.png");
    granadaS = granadaS.scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->granadaS->setPixmap(granadaS);
    QPixmap dinamita = QPixmap(ROOT_PATH"/resources/images/W4_Dynamite.png");
    dinamita = dinamita.scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->dinamita->setPixmap(dinamita);
    QPixmap bate = QPixmap(ROOT_PATH"/resources/images/Baseballbat.png");
    bate = bate.scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->bate->setPixmap(bate);
    QPixmap aereo = QPixmap(ROOT_PATH"/resources/images/W4_Airstrike.png");
    aereo = aereo.scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->aereo->setPixmap(aereo);
    QPixmap tele = QPixmap(ROOT_PATH"/resources/images/IconTeleport.png");
    tele = tele.scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->teletransportador->setPixmap(tele);
    loadWeapons();
    ui->agregarGusano->setIcon(QIcon(ROOT_PATH"/resources/images/wormwait.png"));
    ui->agregarVigaChica->setIcon(QIcon(ROOT_PATH"/resources/images/grds4.png"));
    ui->AgregarViga->setIcon(QIcon(ROOT_PATH"/resources/images/grdl4.png"));
    ui->moveOpt->hide();
    ui->cant->setValue(2);
}

EditorPantalla::~EditorPantalla()
{
    for (auto& x : items){
        delete x.second;
    }
    delete scene;
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
    celdas.clear();
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
            worms.erase(it);
        }

        std::map<int, editorViga>::iterator it2;
        it2 = this->vigas.find(current_id);
        if (it2 != vigas.end()){
            vigas.erase(it2);
        }
        delete items[current_id];
        items.erase(iter);
        current_id = -1;
        estado = 0;
        ui->girderOpt->hide();
        ui->wormOpt->hide();
        ui->moveOpt->hide();
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

void EditorPantalla::setBacGround(std::string &name)
{
    std::string backgroun = ROOT_PATH;
    backgroun += "/resources/images/";
    backgroun += name;
    this->bakcground = QString::fromStdString(backgroun);
    scene->setBackgroundBrush(QBrush(QImage(bakcground)));
}

void EditorPantalla::wormSelect(int id)
{
    this->current_id = id;
    items[id]->setOpacity(0.5);
    ui->wormOpt->show();
    ui->girderOpt->hide();
    ui->moveOpt->show();
    ui->vidaGusano->setValue(worms[id].getVida());
}

void EditorPantalla::wormSetPos()
{
    int x = items[current_id]->scenePos().toPoint().x();
    int y = items[current_id]->scenePos().toPoint().y();
    this->worms[current_id].setPos(x,-y);
}

void EditorPantalla::girderSelect(int id)
{
    this->current_id = id;
    items[id]->setOpacity(0.5);
    ui->wormOpt->hide();
    ui->moveOpt->show();
    ui->girderOpt->show();
}

void EditorPantalla::girderSetPos()
{
    int x = items[current_id]->scenePos().toPoint().x();
    int y = items[current_id]->scenePos().toPoint().y();
    this->vigas[current_id].setPos(x,-y);
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
    if (true){
        Worm_View *worm = new Worm_View(id);
        int xn = x - worm->boundingRect().center().toPoint().x();
        int yn = y - worm->boundingRect().center().toPoint().y();
        connect(worm,SIGNAL(wormSelect(int)),this,SLOT(wormSelect(int)));
        connect(worm,SIGNAL(wormSetPos()),this,SLOT(wormSetPos()));
        scene->addItem(worm);
        worm->setPos(xn,yn);
        worm->setFlag(QGraphicsItem::ItemIsSelectable,true);
        this->items[id] = worm;
        this->worms.emplace(std::piecewise_construct,
                                    std::forward_as_tuple(id++),
                                    std::forward_as_tuple(x,-y));

        this->estado = 0;
        return (id-1);
    } else {
        QMessageBox::information(this, tr("Error"), tr("celda ocupada."));
    }
    return -1;
}

void EditorPantalla::setVIdaWorm(int id, int vida)
{
    worms[id].setVida(vida);
}

int EditorPantalla::add_worm(int x, int y)
{
    Worm_View *worm = new Worm_View(id);
    int xn = x - worm->boundingRect().center().toPoint().x();
    int yn = y - worm->boundingRect().center().toPoint().y();
    connect(worm,SIGNAL(wormSelect(int)),this,SLOT(wormSelect(int)));
    connect(worm,SIGNAL(wormSetPos()),this,SLOT(wormSetPos()));
    scene->addItem(worm);
    worm->setPos(xn,yn);
    worm->setFlag(QGraphicsItem::ItemIsSelectable,true);
    this->items[id] = worm;
    this->worms.emplace(std::piecewise_construct,
                                std::forward_as_tuple(id++),
                                std::forward_as_tuple(x,-y));
    return (id-1);
}

int EditorPantalla::add_small_girder(int x, int y)
{
    editor_viga_view *viga = new editor_viga_view(id);
    int xn = x - viga->boundingRect().center().toPoint().x();
    int yn = y - viga->boundingRect().center().toPoint().y();
    scene->addItem(viga);
    viga->setPos(xn,yn);
    this->items[id] = viga;
    connect(viga,SIGNAL(girderSelect(int)),this,SLOT(girderSelect(int)));
    connect(viga,SIGNAL(girderSetPos()),this,SLOT(girderSetPos()));
    viga->setFlag(QGraphicsItem::ItemIsSelectable,true);
    this->vigas.emplace(std::piecewise_construct,
                    std::forward_as_tuple(id++),
                    std::forward_as_tuple(x,-y,3));
    return (id-1);
}

int EditorPantalla::add_big_girder(int x, int y)
{
    editor_viga_grande_view *viga = new editor_viga_grande_view (id);
    int xn = x - viga->boundingRect().center().toPoint().x();
    int yn = y - viga->boundingRect().center().toPoint().y();
    scene->addItem(viga);
    viga->setPos(xn,yn);
    this->items[id] = viga;
    connect(viga,SIGNAL(girderSelect(int)),this,SLOT(girderSelect(int)));
    connect(viga,SIGNAL(girderSetPos()),this,SLOT(girderSetPos()));
    viga->setFlag(QGraphicsItem::ItemIsSelectable,true);
    this->vigas.emplace(std::piecewise_construct,
                    std::forward_as_tuple(id++),
                    std::forward_as_tuple(x,-y,6));
    return (id-1);
}

int EditorPantalla::agregar_viga_grande(int x, int y)
{
    if (true){
        editor_viga_grande_view *viga = new editor_viga_grande_view (id);
        int xn = x - viga->boundingRect().center().toPoint().x();
        int yn = y - viga->boundingRect().center().toPoint().y();
        scene->addItem(viga);
        viga->setPos(xn,yn);
        this->items[id] = viga;
        connect(viga,SIGNAL(girderSelect(int)),this,SLOT(girderSelect(int)));
        connect(viga,SIGNAL(girderSetPos()),this,SLOT(girderSetPos()));
        viga->setFlag(QGraphicsItem::ItemIsSelectable,true);
        this->vigas.emplace(std::piecewise_construct,
                        std::forward_as_tuple(id++),
                        std::forward_as_tuple(x,-y,6));
        this->estado = 0;
        return (id-1);
    } else {
        QMessageBox::information(this, tr("Error"), tr("celda ocupada."));
    }
    return -1;
}

int EditorPantalla::agregar_viga_chica(int x, int y)
{
    if (true){
        editor_viga_view *viga = new editor_viga_view(id);
        int xn = x - viga->boundingRect().center().toPoint().x();
        int yn = y - viga->boundingRect().center().toPoint().y();
        scene->addItem(viga);
        viga->setPos(xn,yn);
        this->items[id] = viga;
        connect(viga,SIGNAL(girderSelect(int)),this,SLOT(girderSelect(int)));
        connect(viga,SIGNAL(girderSetPos()),this,SLOT(girderSetPos()));
        viga->setFlag(QGraphicsItem::ItemIsSelectable,true);
        this->vigas.emplace(std::piecewise_construct,
                        std::forward_as_tuple(id++),
                        std::forward_as_tuple(x,-y,3));

        this->estado = 0;
        return (id-1);
    } else {
        QMessageBox::information(this, tr("Error"), tr("celda ocupada."));
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
    vigas[id].aumentarAngulo(5);
    items[id]->setTransformOriginPoint(items[id]->boundingRect().center());
    items[id]->setRotation(items[id]->rotation() - 5);
}

void EditorPantalla::on_SelecionarHerramintas_Armas_clicked()
{
    editorSeleccionArmasHerramientas pantalla3;
    pantalla3.pasarMap(this,usables);
    pantalla3.setModal(true);
    pantalla3.exec();
}

void EditorPantalla::mousePressEvent(QMouseEvent *evento)
{
    int x = evento->pos().x();
    int y = evento->pos().y();
    x += ui->graphicsView->horizontalScrollBar()->value();
    y += ui->graphicsView->verticalScrollBar()->value();
    std::cout<<"x: "<<x<<" y: "<<y<<std::endl;
    if (x >= (xscene - 100)){
        xscene += 400 ;
        this->scene->setSceneRect(0,-yscene,xscene,yscene);
    }
    if (estado == 0){
        ui->wormOpt->hide();
        ui->girderOpt->hide();
        ui->moveOpt->hide();
        std::map<int, QGraphicsItem*>::iterator iter;
        iter = items.find(current_id);
        if ( iter != items.end()){
            items[current_id]->setOpacity(1);
        }
        current_id = -1;
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
        vigas[current_id].aumentarAngulo(5);
        items[current_id]->setTransformOriginPoint(items[current_id]->boundingRect().center());
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
        vigas[current_id].aumentarAngulo(-5);
        items[current_id]->setTransformOriginPoint(items[current_id]->boundingRect().center());
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
            std::string background = "fondo.png";
            commonParser::save(name,this->usables,this->worms,this->vigas, cantidad,background);
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
            std::string background = "fondo.png";
            commonParser::save(name,this->usables,this->worms,this->vigas, cantidad,background);
        } else {
            QMessageBox::information(this,tr("Error"),tr("hay gusanos que tienen vida 0."));
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
        QMessageBox::information(this,tr("Error"),tr("Vida indalida."));
        return;
    }
    worms[current_id].setVida(vida);
}

void EditorPantalla::on_remove_clicked()
{
    removeItem();
}

void EditorPantalla::on_up_clicked()
{
    items[current_id]->moveBy(0,-5);
    std::map<int, editorWorm>::iterator it;
    it = this->worms.find(current_id);
    if (it != worms.end()){
        worms[current_id].addPos(0,5);
    } else {
        vigas[current_id].addPos(0,5);
    }

}

void EditorPantalla::on_left_clicked()
{
    items[current_id]->moveBy(-5,0);
    std::map<int, editorWorm>::iterator it;
    it = this->worms.find(current_id);
    if (it != worms.end()){
        worms[current_id].addPos(-5,0);
    } else {
        vigas[current_id].addPos(-5,0);
    }
}

void EditorPantalla::on_right_clicked()
{
    items[current_id]->moveBy(5,0);
    std::map<int, editorWorm>::iterator it;
    it = this->worms.find(current_id);
    if (it != worms.end()){
        worms[current_id].addPos(5,0);
    } else {
        vigas[current_id].addPos(5,0);
    }
}

void EditorPantalla::on_down_clicked()
{
    items[current_id]->moveBy(0,5);
    std::map<int, editorWorm>::iterator it;
    it = this->worms.find(current_id);
    if (it != worms.end()){
        worms[current_id].addPos(0,-5);
    } else {
        vigas[current_id].addPos(0,-5);
    }
}
