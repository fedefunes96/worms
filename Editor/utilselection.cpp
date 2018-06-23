#include "utilselection.h"
#include "ui_editorseleccionarmasherramientas.h"
#include <map>
#include <editorusables.h>
#include <string>
#include <QMessageBox>
#include <iostream>

#define INFINITE_AMMO -1

UtilSelection::UtilSelection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editorSeleccionArmasHerramientas)
{
    ui->setupUi(this);
    this->setWindowTitle("Seleccion de armas y herramientas");
    QPixmap bazooka = QPixmap(ROOT_PATH"/resources/images/Bazooka.png");
    QPixmap mortero = QPixmap(ROOT_PATH"/resources/images/Mortar.png");
    QPixmap granadaV = QPixmap(ROOT_PATH"/resources/images/W4_Grenade.png");
    QPixmap granadaR = QPixmap(ROOT_PATH"/resources/images/Redgrenade.png");
    QPixmap banana = QPixmap(ROOT_PATH"/resources/images/Bananabomb.png");
    QPixmap granadaS = QPixmap(ROOT_PATH"/resources/images/Holy_Grenade.png");
    QPixmap dinamita = QPixmap(ROOT_PATH"/resources/images/W4_Dynamite.png");
    QPixmap bate = QPixmap(ROOT_PATH"/resources/images/Baseballbat.png");
    QPixmap aereo = QPixmap(ROOT_PATH"/resources/images/W4_Airstrike.png");
    QPixmap tele = QPixmap(ROOT_PATH"/resources/images/IconTeleport.png");
    ui->bazooka_2->setPixmap(bazooka);
    ui->mortero->setPixmap(mortero);
    ui->granadaV->setPixmap(granadaV);
    ui->granadaR->setPixmap(granadaR);
    ui->banana->setPixmap(banana);
    ui->granadaS->setPixmap(granadaS);
    ui->dinamita->setPixmap(dinamita);
    ui->bate->setPixmap(bate);
    ui->aereo->setPixmap(aereo);
    ui->tele->setPixmap(tele);
    ui->BazookaIA->setCheckState(Qt::CheckState::Checked);
    ui->municionMortero->setValue(10);
    ui->GreenGrenadeIA->setCheckState(Qt::CheckState::Checked);
    ui->municionGranadaR->setValue(10);
    ui->municionBanana->setValue(5);
    ui->municionGranadaS->setValue(2);
    ui->municionDinamita->setValue(5);
    ui->BatIA->setCheckState(Qt::CheckState::Checked);
    ui->municionAereo->setValue(2);
    ui->TeleIA->setCheckState(Qt::CheckState::Checked);
}

UtilSelection::~UtilSelection()
{
    delete ui;
}

void UtilSelection::pasarMap(MapEditor *editor, std::map<int, editorUsables> &usables){
    this->editor = editor;
    for (auto item : usables){
        int ammo = item.second.getAmmo();
        if (item.first == (int)UsableIds::BAZOOKA){
            ui->Bazookka->setChecked(true);
            if (ammo > 0){
                ui->municionBazooka->setValue(ammo);
                ui->BazookaIA->setCheckState(Qt::CheckState::Unchecked);
            }
        }
        if (item.first == (int)UsableIds::MORTAR){
            ui->Mortero->setChecked(true);
            if (ammo > 0){
                ui->municionMortero->setValue(ammo);
                ui->MortaIA->setCheckState(Qt::CheckState::Unchecked);
            }
        }
        if (item.first == (int)UsableIds::GREEN_GRENADE){
            ui->GranadaV->setChecked(true);
            if (ammo > 0){
                ui->municionGranadaV->setValue(ammo);
                ui->GreenGrenadeIA->setCheckState(Qt::CheckState::Unchecked);
            }
        }
        if (item.first == (int)UsableIds::RED_GRENADE){
            ui->GranadaR->setChecked(true);
            if (ammo > 0){
                ui->municionGranadaR->setValue(ammo);
                ui->RedGrenadeIA->setCheckState(Qt::CheckState::Unchecked);
            }
        }
        if (item.first == (int)UsableIds::BANANA){
            ui->Banana->setChecked(true);
            if (ammo > 0){
                ui->municionBanana->setValue(ammo);
                ui->BananaIA->setCheckState(Qt::CheckState::Unchecked);
            }
        }
        if (item.first == (int)UsableIds::HOLY_GRENADE){
            ui->GranadaS->setChecked(true);
            if (ammo > 0){
                ui->municionGranadaS->setValue(ammo);
                ui->HGrenadeIA->setCheckState(Qt::CheckState::Unchecked);
            }
        }
        if (item.first == (int)UsableIds::DYNAMITE){
            ui->Dinamita->setChecked(true);
            if (ammo > 0){
                ui->municionDinamita->setValue(ammo);
                ui->DynamiteIA->setCheckState(Qt::CheckState::Unchecked);
            }
        }
        if (item.first == (int)UsableIds::BASEBALL_BAT){
            ui->Bate->setChecked(true);
            if (ammo > 0){
                ui->municionBate->setValue(ammo);
                ui->BatIA->setCheckState(Qt::CheckState::Unchecked);
            }
        }
        if (item.first == (int)UsableIds::AERIAL_ATTACK){
            ui->Aereo->setChecked(true);
            if (ammo > 0){
                ui->municionAereo->setValue(ammo);
                ui->AIrIA->setCheckState(Qt::CheckState::Unchecked);
            }
        }
        if (item.first == (int)UsableIds::TELEPORTATION){
            ui->Teletransportador->setChecked(true);
            if (ammo > 0){
                ui->municionTeletransportador->setValue(ammo);
                ui->TeleIA->setCheckState(Qt::CheckState::Unchecked);
            }
        }
    }
}


void UtilSelection::on_Bazookka_clicked()
{
    if (ui->Bazookka->checkState() == Qt::Checked){
        int municion = ui->municionBazooka->text().toInt();
        if (municion == 0 && (ui->BazookaIA->checkState() == Qt::Unchecked)){
            ui->Bazookka->setChecked(false);
            mensaje_error();
        }
    }
}

void UtilSelection::on_Mortero_clicked()
{
    if (ui->Mortero->checkState() == Qt::Checked){
        int municion = ui->municionMortero->text().toInt();
        if (municion == 0 && (ui->MortaIA->checkState() == Qt::Unchecked)){
            ui->Mortero->setChecked(false);
            mensaje_error();
        }
    }
}

void UtilSelection::on_GranadaV_clicked()
{
    if (ui->GranadaV->checkState() == Qt::Checked){
        int municion = ui->municionGranadaV->text().toInt();
        if (municion == 0 && (ui->GreenGrenadeIA->checkState() == Qt::Unchecked)){
            ui->GranadaV->setChecked(false);
            mensaje_error();
        }
    }
}

void UtilSelection::on_GranadaR_clicked()
{
    if (ui->GranadaR->checkState() == Qt::Checked){
        int municion = ui->municionGranadaR->text().toInt();
        if (municion == 0 && (ui->RedGrenadeIA->checkState() == Qt::Unchecked)){
            ui->GranadaR->setChecked(false);
            mensaje_error();
        }
    }
}

void UtilSelection::on_Banana_clicked()
{
    if (ui->Banana->checkState() == Qt::Checked){
        int municion = ui->municionBanana->text().toInt();
        if (municion == 0 && (ui->BananaIA->checkState() == Qt::Unchecked)){
            ui->Banana->setChecked(false);
            mensaje_error();
        }
    }
}

void UtilSelection::on_GranadaS_clicked()
{
    if (ui->GranadaS->checkState() == Qt::Checked){
        int municion = ui->municionGranadaS->text().toInt();
        if (municion == 0 && (ui->HGrenadeIA->checkState() == Qt::Unchecked)){
            ui->GranadaS->setChecked(false);
            mensaje_error();
        }
    }
}

void UtilSelection::on_Dinamita_clicked()
{
    if (ui->Dinamita->checkState() == Qt::Checked){
        int municion = ui->municionDinamita->text().toInt();
        if (municion == 0 && (ui->DynamiteIA->checkState() == Qt::Unchecked)){
            ui->Dinamita->setChecked(false);
            mensaje_error();
        }
    }
}

void UtilSelection::on_Bate_clicked()
{
    if (ui->Dinamita->checkState() == Qt::Checked){
        int municion = ui->municionBate->text().toInt();
        if (municion == 0 && (ui->BatIA->checkState() == Qt::Unchecked)){
            ui->Bate->setChecked(false);
            mensaje_error();
        }
    }
}

void UtilSelection::on_Aereo_clicked()
{
    if (ui->Aereo->checkState() == Qt::Checked){
        int municion = ui->municionAereo->text().toInt();
        if (municion == 0 && (ui->AIrIA->checkState() == Qt::Unchecked)){
            ui->Aereo->setChecked(false);
            mensaje_error();
        }
    }
}

void UtilSelection::on_Teletransportador_clicked()
{
    if (ui->Teletransportador->checkState() == Qt::Checked){
        int municion = ui->municionTeletransportador->text().toInt();
        if (municion == 0 && (ui->TeleIA->checkState() == Qt::Unchecked)){
            ui->Teletransportador->setChecked(false);
            mensaje_error();
        }
    }
}

void UtilSelection::on_buttonBox_accepted()
{
    if (ui->Bazookka->checkState() == Qt::Unchecked){
        editor->remove_weapon((int)UsableIds::BAZOOKA);
    } else {
        if (ui->BazookaIA->checkState() == Qt::Unchecked){
            editor->agregar_arma((int)UsableIds::BAZOOKA,ui->municionBazooka->text().toInt());
        } else {
            editor->agregar_arma((int)UsableIds::BAZOOKA,INFINITE_AMMO);
        }
    }
    if (ui->Mortero->checkState() == Qt::Unchecked){
        editor->remove_weapon((int)UsableIds::MORTAR);
    } else {
        if (ui->MortaIA->checkState() == Qt::Unchecked){
            editor->agregar_arma((int)UsableIds::MORTAR,ui->municionMortero->text().toInt());
        } else {
            editor->agregar_arma((int)UsableIds::MORTAR,INFINITE_AMMO);
        }
    }
    if (ui->GranadaV->checkState() == Qt::Unchecked){
        editor->remove_weapon((int)UsableIds::GREEN_GRENADE);
    } else {
        if (ui->GreenGrenadeIA->checkState() == Qt::Unchecked){
            editor->agregar_arma((int)UsableIds::GREEN_GRENADE,ui->municionGranadaV->text().toInt());
        } else {
            editor->agregar_arma((int)UsableIds::GREEN_GRENADE,INFINITE_AMMO);
        }
    }
    if (ui->GranadaR->checkState() == Qt::Unchecked){
        editor->remove_weapon((int)UsableIds::RED_GRENADE);
    } else {
        if (ui->RedGrenadeIA->checkState() == Qt::Unchecked){
            editor->agregar_arma((int)UsableIds::RED_GRENADE,ui->municionGranadaR->text().toInt());
        } else {
            editor->agregar_arma((int)UsableIds::RED_GRENADE,INFINITE_AMMO);
        }
    }
    if (ui->Banana->checkState() == Qt::Unchecked){
        editor->remove_weapon((int)UsableIds::BANANA);
    } else {
        if (ui->BananaIA->checkState() == Qt::Unchecked){
            editor->agregar_arma((int)UsableIds::BANANA,ui->municionBanana->text().toInt());
        } else {
            editor->agregar_arma((int)UsableIds::BANANA,INFINITE_AMMO);
        }
    }
    if (ui->GranadaS->checkState() == Qt::Unchecked){
        editor->remove_weapon((int)UsableIds::HOLY_GRENADE);
    } else{
        if (ui->HGrenadeIA->checkState() == Qt::Unchecked){
            editor->agregar_arma((int)UsableIds::HOLY_GRENADE,ui->municionGranadaS->text().toInt());
        } else {
            editor->agregar_arma((int)UsableIds::HOLY_GRENADE,INFINITE_AMMO);
        }
    }
    if (ui->Dinamita->checkState() == Qt::Unchecked){
        editor->remove_weapon((int)UsableIds::DYNAMITE);
    } else {
        if (ui->DynamiteIA->checkState() == Qt::Unchecked){
            editor->agregar_arma((int)UsableIds::DYNAMITE,ui->municionDinamita->text().toInt());
        } else {
            editor->agregar_arma((int)UsableIds::DYNAMITE,INFINITE_AMMO);
        }
    }
    if (ui->Bate->checkState() == Qt::Unchecked){
        editor->remove_weapon((int)UsableIds::BASEBALL_BAT);
    } else {
        if (ui->BatIA->checkState() == Qt::Unchecked){
            editor->agregar_arma((int)UsableIds::BASEBALL_BAT,ui->municionBate->text().toInt());
        } else {
            editor->agregar_arma((int)UsableIds::BASEBALL_BAT,INFINITE_AMMO);
        }
    }
    if (ui->Aereo->checkState() == Qt::Unchecked){
        editor->remove_weapon((int)UsableIds::AERIAL_ATTACK);
    } else {
        if (ui->AIrIA->checkState() == Qt::Unchecked){
            editor->agregar_arma((int)UsableIds::AERIAL_ATTACK,ui->municionAereo->text().toInt());
        } else {
            editor->agregar_arma((int)UsableIds::AERIAL_ATTACK,INFINITE_AMMO);
        }
    }
    if (ui->Teletransportador->checkState() == Qt::Unchecked){
        editor->remove_weapon((int)UsableIds::TELEPORTATION);
    } else {
        if (ui->TeleIA->checkState() == Qt::Unchecked){
            editor->agregar_arma((int)UsableIds::TELEPORTATION,ui->municionTeletransportador->text().toInt());
        } else {
            editor->agregar_arma((int)UsableIds::TELEPORTATION,INFINITE_AMMO);
        }
    }
    editor->loadWeapons();
}

void UtilSelection::mensaje_error()
{
    QMessageBox::information(this,tr("Error"),tr("Invalid ammunition."));
}


