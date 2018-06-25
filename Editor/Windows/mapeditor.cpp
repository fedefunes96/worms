#include "mapeditor.h"
#include "ui_editorpantalla.h"
#include "utilselection.h"
#include "editor_worm_view.h"
#include <QGraphicsScene>
#include <QMessageBox>
#include "editor_viga_view.h"
#include <QFileDialog>
#include "parser.h"
#include <QDebug>
#include <QScrollBar>
#include <QBrush>
#include <QImage>
#include "editor_viga_grande_view.h"
#include <iostream>

MapEditor::MapEditor(QWidget *parent) :
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
    bazooka = bazooka.scaled(60,60,Qt::KeepAspectRatio,
        Qt::SmoothTransformation);
    ui->bazooka->setPixmap(bazooka);
    QPixmap mortero = QPixmap(ROOT_PATH"/resources/images/Mortar.png");
    mortero = mortero.scaled(60,60,Qt::KeepAspectRatio,
        Qt::SmoothTransformation);
    ui->mortero->setPixmap(mortero);
    QPixmap granadaV = QPixmap(ROOT_PATH"/resources/images/W4_Grenade.png");
    granadaV = granadaV.scaled(60,60,Qt::KeepAspectRatio,
        Qt::SmoothTransformation);
    ui->granadaV->setPixmap(granadaV);
    QPixmap granadaR = QPixmap(ROOT_PATH"/resources/images/Redgrenade.png");
    granadaR = granadaR.scaled(60,60,Qt::KeepAspectRatio,
        Qt::SmoothTransformation);
    ui->granadaR->setPixmap(granadaR);
    QPixmap banana = QPixmap(ROOT_PATH"/resources/images/Bananabomb.png");
    banana = banana.scaled(60,60,Qt::KeepAspectRatio,
        Qt::SmoothTransformation);
    ui->banana->setPixmap(banana);
    QPixmap granadaS = QPixmap(ROOT_PATH"/resources/images/Holy_Grenade.png");
    granadaS = granadaS.scaled(60,60,Qt::KeepAspectRatio,
        Qt::SmoothTransformation);
    ui->granadaS->setPixmap(granadaS);
    QPixmap dinamita = QPixmap(ROOT_PATH"/resources/images/W4_Dynamite.png");
    dinamita = dinamita.scaled(60,60,Qt::KeepAspectRatio,
        Qt::SmoothTransformation);
    ui->dinamita->setPixmap(dinamita);
    QPixmap bate = QPixmap(ROOT_PATH"/resources/images/Baseballbat.png");
    bate = bate.scaled(60,60,Qt::KeepAspectRatio,
        Qt::SmoothTransformation);
    ui->bate->setPixmap(bate);
    QPixmap aereo = QPixmap(ROOT_PATH"/resources/images/W4_Airstrike.png");
    aereo = aereo.scaled(60,60,Qt::KeepAspectRatio,
        Qt::SmoothTransformation);
    ui->aereo->setPixmap(aereo);
    QPixmap tele = QPixmap(ROOT_PATH"/resources/images/IconTeleport.png");
    tele = tele.scaled(60,60,Qt::KeepAspectRatio,
        Qt::SmoothTransformation);
    ui->teletransportador->setPixmap(tele);
    loadWeapons();
    ui->agregarGusano->setIcon(QIcon(
        ROOT_PATH"/resources/images/wormwait.png"));
    ui->agregarVigaChica->setIcon(QIcon(
        ROOT_PATH"/resources/images/grds4.png"));
    ui->AgregarViga->setIcon(QIcon(
        ROOT_PATH"/resources/images/grdl4.png"));
    ui->moveOpt->hide();
    ui->cant->setValue(2);
    estado = State::NOTHING;
}

MapEditor::~MapEditor()
{
    for (auto& x : items){
        delete x.second;
    }
    delete scene;
    delete ui;
}

void MapEditor::load()
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
    Parser::load(this,name);
    loadWeapons();
}

bool MapEditor::checkWorms()
{
    for (auto &worm : worms){
        if (worm.second.getVida() == 0){
            return false;
        }
    }
    return true;
}

void MapEditor::removeItem()
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
        estado = State::NOTHING;
        ui->girderOpt->hide();
        ui->wormOpt->hide();
        ui->moveOpt->hide();
    }
}

void MapEditor::loadWeapons()
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

void MapEditor::setBacGround(std::string &name)
{
    std::string backgroun = ROOT_PATH;
    backgroun += "/resources/images/";
    backgroun += name;
    this->bakcground = QString::fromStdString(backgroun);
    scene->setBackgroundBrush(QBrush(QImage(bakcground)));
}

void MapEditor::wormSelect(int id)
{
    std::map<int, QGraphicsItem*>::iterator iter;
    iter = items.find(current_id);
    if ( iter != items.end()){
        items[current_id]->setOpacity(1);
    }
    this->current_id = id;
    items[id]->setOpacity(0.5);
    ui->wormOpt->show();
    ui->girderOpt->hide();
    ui->moveOpt->show();
    ui->vidaGusano->setValue(worms[id].getVida());
}

void MapEditor::girderSelect(int id)
{
    std::map<int, QGraphicsItem*>::iterator iter;
    iter = items.find(current_id);
    if ( iter != items.end()){
        items[current_id]->setOpacity(1);
    }
    this->current_id = id;
    items[id]->setOpacity(0.5);
    ui->wormOpt->hide();
    ui->moveOpt->show();
    ui->girderOpt->show();
}

void MapEditor::fileName(QString name)
{
    this->nombre = name;
    load();
}

void MapEditor::on_agregarGusano_clicked()
{
    this->estado = State::ADD_WORM;
}

void MapEditor::on_AgregarViga_clicked()
{
    this->estado = State::ADD_BIG_GIRDER;
}

void MapEditor::on_agregarVigaChica_clicked()
{
    this->estado = State::ADD_SMALL_GIRDER;
}

void MapEditor::setVIdaWorm(int id, int vida)
{
    worms[id].setVida(vida);
}

int MapEditor::add_worm(int x, int y)
{
    Worm_View *worm = new Worm_View(id);
    int xn = x - worm->boundingRect().center().toPoint().x();
    int yn = y - worm->boundingRect().center().toPoint().y();
    connect(worm,SIGNAL(wormSelect(int)),this,SLOT(wormSelect(int)));
    scene->addItem(worm);
    worm->setPos(xn,yn);
    worm->setFlag(QGraphicsItem::ItemIsSelectable,true);
    this->items[id] = worm;
    this->worms.emplace(std::piecewise_construct,
                                std::forward_as_tuple(id++),
                                std::forward_as_tuple(x,-y));
    estado = State::NOTHING;
    return (id-1);
}

int MapEditor::add_small_girder(int x, int y)
{
    editor_viga_view *viga = new editor_viga_view(id);
    int xn = x - viga->boundingRect().center().toPoint().x();
    int yn = y - viga->boundingRect().center().toPoint().y();
    scene->addItem(viga);
    viga->setPos(xn,yn);
    this->items[id] = viga;
    connect(viga,SIGNAL(girderSelect(int)),this,SLOT(girderSelect(int)));
    viga->setFlag(QGraphicsItem::ItemIsSelectable,true);
    this->vigas.emplace(std::piecewise_construct,
                    std::forward_as_tuple(id++),
                    std::forward_as_tuple(x,-y,3));
    estado = State::NOTHING;
    return (id-1);
}

int MapEditor::add_big_girder(int x, int y)
{
    editor_viga_grande_view *viga = new editor_viga_grande_view (id);
    int xn = x - viga->boundingRect().center().toPoint().x();
    int yn = y - viga->boundingRect().center().toPoint().y();
    scene->addItem(viga);
    viga->setPos(xn,yn);
    this->items[id] = viga;
    connect(viga,SIGNAL(girderSelect(int)),this,SLOT(girderSelect(int)));
    viga->setFlag(QGraphicsItem::ItemIsSelectable,true);
    this->vigas.emplace(std::piecewise_construct,
                    std::forward_as_tuple(id++),
                    std::forward_as_tuple(x,-y,6));
    estado = State::NOTHING;
    return (id-1);
}


void MapEditor::agregar_arma(int id, int municion)
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

void MapEditor::remove_weapon(int id)
{
    std::map<int,editorUsables>::iterator it;
    it = usables.find(id);
    if (it == usables.end()){
        return;
    }
    usables.erase(it);
}

void MapEditor::aumetar_angulo(int id, int angle)
{
    vigas[id].aumentarAngulo(angle);
    items[id]->setTransformOriginPoint(items[id]->boundingRect().center());
    items[id]->setRotation(items[id]->rotation() - angle);
}

void MapEditor::on_SelecionarHerramintas_Armas_clicked()
{
    UtilSelection pantalla3;
    pantalla3.pasarMap(this,usables);
    pantalla3.setModal(true);
    pantalla3.exec();
}

void MapEditor::mousePressEvent(QMouseEvent *evento)
{
    int x = evento->pos().x();
    int y = evento->pos().y();
    x += ui->graphicsView->horizontalScrollBar()->value();
    y += ui->graphicsView->verticalScrollBar()->value();
    if (x >= (xscene - 100)){
        xscene += 400 ;
        this->scene->setSceneRect(0,-yscene,xscene,yscene);
    }
    if (estado == State::NOTHING){
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

    if (estado == State::ADD_WORM){
        this->add_worm(x,y);
        ui->agregarGusano->setChecked(false);
    }

    if (estado == State::ADD_BIG_GIRDER){
        this->add_big_girder(x,y);
        ui->AgregarViga->setChecked(false);
    }

    if (estado == State::ADD_SMALL_GIRDER){
        add_small_girder(x,y);
        ui->agregarVigaChica->setChecked(false);
    }

}

void MapEditor::on_quitar_clicked()
{
    removeItem();
}

void MapEditor::on_mas_clicked()
{
    std::map<int, editorViga>::iterator it2;
    it2 = this->vigas.find(current_id);
    if (it2 != vigas.end()){
        vigas[current_id].aumentarAngulo(5);
        items[current_id]->setTransformOriginPoint(
            items[current_id]->boundingRect().center());
        items[current_id]->setRotation(items[current_id]->rotation() - 5);
    }
}

void MapEditor::on_menos_clicked()
{
    std::map<int, editorViga>::iterator it2;
    it2 = this->vigas.find(current_id);
    if (it2 != vigas.end()){
        vigas[current_id].aumentarAngulo(-5);
        items[current_id]->setTransformOriginPoint(
            items[current_id]->boundingRect().center());
        items[current_id]->setRotation(items[current_id]->rotation() + 5);

    }
}

void MapEditor::on_saveAs_clicked()
{
    if (ui->cant->text().toInt()!= 0){
        this->cantidad = ui->cant->text().toInt();
    }

    bool colicion = this->checkColicion();
    if (colicion){
    	QMessageBox::information(this,tr("Error"),
                tr("There are worms colliding."));
    	return;
    }

    if (this->cantidad <= worms.size()){
        if (this->checkWorms()){
            nombre = QFileDialog::getSaveFileName(this,
                                               tr("Save "),
                                               ROOT_PATH"/resources/maps",
                                               tr("*.yaml"));
            if (nombre.isEmpty()){
                return;
            }
            this->setWindowTitle(nombre);
            std::string name = nombre.toUtf8().constData();
            std::string background = "fondo.png";
            Parser::save(name,this->usables,this->worms,
                this->vigas, cantidad,background);
        } else {
            QMessageBox::information(this,tr("Error"),
                tr("There are worms with 0 health."));
        }
    } else {
        QMessageBox::information(this,tr("Error"),
            tr("Not enough worms on scene."));
    }
}

void MapEditor::on_pushButton_clicked()
{
    if (ui->cant->text().toInt()!= 0){
        this->cantidad = ui->cant->text().toInt();
    }

    bool colicion = this->checkColicion();
    if (colicion){
    	QMessageBox::information(this,tr("Error"),
                tr("There are worms colliding."));
    	return;
    }

    if (this->cantidad <= worms.size()){
        if (this->checkWorms()){
            if (nombre.isEmpty()){
                nombre = QFileDialog::getSaveFileName(this,
                                                   tr("Save"),
                                                   ROOT_PATH"/resources/maps",
                                                   tr("*.yaml"));
            }
            if (nombre.isEmpty()){
                return;
            }
            this->setWindowTitle(nombre);
            std::string name = nombre.toUtf8().constData();
            std::string background = "fondo.png";
            Parser::save(name,this->usables,this->worms,
                this->vigas, cantidad,background);
        } else {
            QMessageBox::information(this,tr("Error"),
                tr("There are worms with 0 health."));
        }
    } else {
        QMessageBox::information(this,tr("Error"),
            tr("Not enough worms on scene."));
    }
}

void MapEditor::on_pushButton_2_clicked()
{
    nombre = QFileDialog::getOpenFileName(this,tr("Open"),
        ROOT_PATH"/resources/maps",
         tr("*.yaml"));
    if (nombre.isEmpty()){
        return;
    }
    this->load();
}

void MapEditor::on_ok_clicked()
{
    int vida = ui->vidaGusano->text().toInt();
    if ( vida == 0){
        QMessageBox::information(this,tr("Error"),tr("Invalid health."));
        return;
    }
    worms[current_id].setVida(vida);
}

void MapEditor::on_remove_clicked()
{
    removeItem();
}

void MapEditor::on_up_clicked()
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

void MapEditor::on_left_clicked()
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

void MapEditor::on_right_clicked()
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

void MapEditor::on_down_clicked()
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


bool MapEditor::checkColicion(){
	for (auto &worm : worms){
		QList<QGraphicsItem*> colicion;
		colicion = items[worm.first]->collidingItems(Qt::IntersectsItemBoundingRect);
		if (!colicion.isEmpty()){
			return true;
		}
	}
	return false;
}