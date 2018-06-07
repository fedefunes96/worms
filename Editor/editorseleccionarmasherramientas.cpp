#include "editorseleccionarmasherramientas.h"
#include "ui_editorseleccionarmasherramientas.h"
#include <map>
#include <editorusables.h>
#include <string>
#include <QMessageBox>
#include <iostream>

editorSeleccionArmasHerramientas::editorSeleccionArmasHerramientas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editorSeleccionArmasHerramientas)
{
    ui->setupUi(this);
    this->setWindowTitle("Seleccion de armas y herramientas");
    QPixmap bazooka = QPixmap("../images/Bazooka.png");
    QPixmap mortero = QPixmap("../images/Mortar.png");
    QPixmap granadaV = QPixmap("../images/W4_Grenade.png");
    QPixmap granadaR = QPixmap("../images/Redgrenade.png");
    QPixmap banana = QPixmap("../images/Bananabomb.png");
    QPixmap granadaS = QPixmap("../images/Holy_Grenade.png");
    QPixmap dinamita = QPixmap("../images/W4_Dynamite.png");
    QPixmap bate = QPixmap("../images/Baseballbat.png");
    QPixmap aereo = QPixmap("../images/W4_Airstrike.png");
    QPixmap tele = QPixmap("../images/IconTeleport.png");
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
}

editorSeleccionArmasHerramientas::~editorSeleccionArmasHerramientas()
{
    delete ui;
}

void editorSeleccionArmasHerramientas::pasarMap(EditorPantalla *editor, std::map<int, editorUsables> &usables){
    this->editor = editor;
    for (auto item : usables){
        if (item.first == 0){
            ui->Bazookka->setChecked(true);
        }
        if (item.first == 1){
            ui->Mortero->setChecked(true);
        }
        if (item.first == 2){
            ui->GranadaV->setChecked(true);
        }
        if (item.first == 3){
            ui->GranadaR->setChecked(true);
        }
        if (item.first == 4){
            ui->Banana->setChecked(true);
        }
        if (item.first == 5){
            ui->GranadaS->setChecked(true);
        }
        if (item.first == 6){
            ui->Dinamita->setChecked(true);
        }
        if (item.first == 7){
            ui->Bate->setChecked(true);
        }
        if (item.first == 8){
            ui->Aereo->setChecked(true);
        }
        if (item.first == 9){
            ui->Teletransportador->setChecked(true);
        }
    }
}


void editorSeleccionArmasHerramientas::on_Bazookka_clicked()
{
    if (ui->Bazookka->checkState() == Qt::Checked){
        int municion = ui->municionBazooka->text().toInt();
        if (municion == 0){
            ui->Bazookka->setChecked(false);
            mensaje_error();
        }
    }
}

void editorSeleccionArmasHerramientas::on_Mortero_clicked()
{
    if (ui->Mortero->checkState() == Qt::Checked){
        int municion = ui->municionMortero->text().toInt();
        if (municion == 0){
            ui->Mortero->setChecked(false);
            mensaje_error();
        }
    }
}

void editorSeleccionArmasHerramientas::on_GranadaV_clicked()
{
    if (ui->GranadaV->checkState() == Qt::Checked){
        int municion = ui->municionGranadaV->text().toInt();
        if (municion == 0){
            ui->GranadaV->setChecked(false);
            mensaje_error();
        }
    }
}

void editorSeleccionArmasHerramientas::on_GranadaR_clicked()
{
    if (ui->GranadaR->checkState() == Qt::Checked){
        int municion = ui->municionGranadaR->text().toInt();
        if (municion == 0){
            ui->GranadaR->setChecked(false);
            mensaje_error();
        }
    }
}

void editorSeleccionArmasHerramientas::on_Banana_clicked()
{
    if (ui->Banana->checkState() == Qt::Checked){
        int municion = ui->municionBanana->text().toInt();
        if (municion == 0){
            ui->Banana->setChecked(false);
            mensaje_error();
        }
    }
}

void editorSeleccionArmasHerramientas::on_GranadaS_clicked()
{
    if (ui->GranadaS->checkState() == Qt::Checked){
        int municion = ui->municionGranadaS->text().toInt();
        if (municion == 0){
            ui->GranadaS->setChecked(false);
            mensaje_error();
        }
    }
}

void editorSeleccionArmasHerramientas::on_Dinamita_clicked()
{
    if (ui->Dinamita->checkState() == Qt::Checked){
        int municion = ui->municionDinamita->text().toInt();
        if (municion == 0){
            ui->Dinamita->setChecked(false);
            mensaje_error();
        }
    }
}

void editorSeleccionArmasHerramientas::on_Bate_clicked()
{
    if (ui->Dinamita->checkState() == Qt::Checked){
        int municion = ui->municionBate->text().toInt();
        if (municion == 0){
            ui->Bate->setChecked(false);
            mensaje_error();
        }
    }
}

void editorSeleccionArmasHerramientas::on_Aereo_clicked()
{
    if (ui->Aereo->checkState() == Qt::Checked){
        int municion = ui->municionAereo->text().toInt();
        if (municion == 0){
            ui->Aereo->setChecked(false);
            mensaje_error();
        }
    }
}

void editorSeleccionArmasHerramientas::on_Teletransportador_clicked()
{
    if (ui->Teletransportador->checkState() == Qt::Checked){
        int municion = ui->municionTeletransportador->text().toInt();
        if (municion == 0){
            ui->Teletransportador->setChecked(false);
            mensaje_error();
        }
    }
}

void editorSeleccionArmasHerramientas::on_buttonBox_accepted()
{
    if (ui->Bazookka->checkState() == Qt::Unchecked){
        editor->remove_weapon(0);
    } else {
        editor->agregar_arma(0,ui->municionBazooka->text().toInt());
    }
    if (ui->Mortero->checkState() == Qt::Unchecked){
        editor->remove_weapon(1);
    } else {
        editor->agregar_arma(1,ui->municionMortero->text().toInt());
    }
    if (ui->GranadaV->checkState() == Qt::Unchecked){
        editor->remove_weapon(2);
    } else {
        editor->agregar_arma(2,ui->municionGranadaV->text().toInt());
    }
    if (ui->GranadaR->checkState() == Qt::Unchecked){
        editor->remove_weapon(3);
    } else {
        editor->agregar_arma(3,ui->municionGranadaR->text().toInt());
    }
    if (ui->Banana->checkState() == Qt::Unchecked){
        editor->remove_weapon(4);
    } else {
        editor->agregar_arma(4,ui->municionBanana->text().toInt());
    }
    if (ui->GranadaS->checkState() == Qt::Unchecked){
        editor->remove_weapon(5);
    } else{
        editor->agregar_arma(5,ui->municionGranadaS->text().toInt());
    }
    if (ui->Dinamita->checkState() == Qt::Unchecked){
        editor->remove_weapon(6);
    } else {
        editor->agregar_arma(6,ui->municionDinamita->text().toInt());
    }
    if (ui->Bate->checkState() == Qt::Unchecked){
        editor->remove_weapon(7);
    } else {
        editor->agregar_arma(7,ui->municionBate->text().toInt());
    }
    if (ui->Aereo->checkState() == Qt::Unchecked){
        editor->remove_weapon(8);
    } else {
        editor->agregar_arma(8,ui->municionAereo->text().toInt());
    }
    if (ui->Teletransportador->checkState() == Qt::Unchecked){
        editor->remove_weapon(9);
    } else {
        editor->agregar_arma(9,ui->municionTeletransportador->text().toInt());
    }
    editor->loadWeapons();
}

void editorSeleccionArmasHerramientas::mensaje_error()
{
    QMessageBox::information(this,tr("Error"),tr("Munivion invalida."));
}


