#include "editorseleccionarmasherramientas.h"
#include "ui_editorseleccionarmasherramientas.h"
#include <map>
#include <editorusables.h>
#include <string>
#include <QMessageBox>

editorSeleccionArmasHerramientas::editorSeleccionArmasHerramientas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editorSeleccionArmasHerramientas)
{
    ui->setupUi(this);
}

editorSeleccionArmasHerramientas::~editorSeleccionArmasHerramientas()
{
    delete ui;
}

void editorSeleccionArmasHerramientas::pasarMap(EditorPantalla *editor, std::map<int, editorUsables> &usables){
    this->editor = editor;
    for (auto item : usables){
        if (item.first == 1){
            this->ui->bazooka->setText("Sacar");
        }
        if (item.first == 2){
            this->ui->Mortero->setText("Sacar");
        }
        if (item.first == 3){
            this->ui->GranadaV->setText("Sacar");
        }
        if (item.first == 4){
             this->ui->GranadaR->setText("Sacar");
        }
        if (item.first == 5){
            this->ui->Banana->setText("Sacar");
        }
        if (item.first == 6){
            this->ui->GranadaS->setText("Sacar");
        }
        if (item.first == 7){
            this->ui->Dinamita->setText("Sacar");
        }
        if (item.first == 8){
            this->ui->Bate->setText("Sacar");
        }
        if (item.first == 9){
            this->ui->Aereo->setText("Sacar");
        }
        if (item.first == 10){
            this->ui->Teletransportador->setText("Sacar");
        }
    }
}

void editorSeleccionArmasHerramientas::on_bazooka_clicked()
{
    int municion = ui->municionBazooka->text().toInt();
    if (municion == 0){
        QMessageBox::information(this, tr("Error"), tr("municion invalida"));
    } else{
        if (editor->agregar_arma(1,municion)){
            ui->bazooka->setText("Selecionar");
        } else {
            ui->bazooka->setText("Sacar");
        }
    }
}

void editorSeleccionArmasHerramientas::on_Mortero_clicked()
{
    int municion = ui->municionMortero->text().toInt();
    if (municion == 0){
        QMessageBox::information(this, tr("Error"), tr("municion invalida"));
    } else{
        if (editor->agregar_arma(2,municion)){
            ui->Mortero->setText("Selecionar");
        } else {
            ui->Mortero->setText("Sacar");
        }
    }
}

void editorSeleccionArmasHerramientas::on_GranadaV_clicked()
{
    int municion = ui->municionGranadaV->text().toInt();
    if (municion == 0){
        QMessageBox::information(this, tr("Error"), tr("municion invalida"));
    } else{
        if (editor->agregar_arma(3,municion)){
            ui->GranadaV->setText("Selecionar");
        } else {
            ui->GranadaV->setText("Sacar");
        }
    }
}

void editorSeleccionArmasHerramientas::on_GranadaR_clicked()
{
    int municion = ui->municionGranadaR->text().toInt();
    if (municion == 0){
        QMessageBox::information(this, tr("Error"), tr("municion invalida"));
    } else{
        if (editor->agregar_arma(4,municion)){
            ui->GranadaR->setText("Selecionar");
        } else {
            ui->GranadaR->setText("Sacar");
        }
    }
}

void editorSeleccionArmasHerramientas::on_Banana_clicked()
{
    int municion = ui->municionBanana->text().toInt();
    if (municion == 0){
        QMessageBox::information(this, tr("Error"), tr("municion invalida"));
    } else{
        if (editor->agregar_arma(5,municion)){
            ui->Banana->setText("Selecionar");
        } else {
            ui->Banana->setText("Sacar");
        }
    }
}

void editorSeleccionArmasHerramientas::on_GranadaS_clicked()
{
    int municion = ui->municionGranadaS->text().toInt();
    if (municion == 0){
        QMessageBox::information(this, tr("Error"), tr("municion invalida"));
    } else{
        if (editor->agregar_arma(6,municion)){
        ui->GranadaS->setText("Selecionar");
        } else {
        ui->GranadaS->setText("Sacar");
        }
    }
}

void editorSeleccionArmasHerramientas::on_Dinamita_clicked()
{
    int municion = ui->municionDinamita->text().toInt();
    if (municion == 0){
        QMessageBox::information(this, tr("Error"), tr("municion invalida"));
    } else{
        if (editor->agregar_arma(7,municion)){
            ui->Dinamita->setText("Selecionar");
        } else {
            ui->Dinamita->setText("Sacar");
        }
    }
}

void editorSeleccionArmasHerramientas::on_Bate_clicked()
{
    int municion = ui->municionBate->text().toInt();
    if (municion == 0){
        QMessageBox::information(this, tr("Error"), tr("municion invalida"));
    } else{
        if (editor->agregar_arma(8,municion)){
            ui->Bate->setText("Selecionar");
        } else {
            ui->Bate->setText("Sacar");
        }
    }
}

void editorSeleccionArmasHerramientas::on_Aereo_clicked()
{
    int municion = ui->municiobnaereo->text().toInt();
    if (municion == 0){
        QMessageBox::information(this, tr("Error"), tr("municion invalida"));
    } else{
        if (editor->agregar_arma(9,municion)){
            ui->Aereo->setText("Selecionar");
        } else {
            ui->Aereo->setText("Sacar");
        }
    }
}

void editorSeleccionArmasHerramientas::on_Teletransportador_clicked()
{
    int municion = ui->municionTeletransportador->text().toInt();
    if (municion == 0){
        QMessageBox::information(this, tr("Error"), tr("municion invalida"));
    } else{
        if (editor->agregar_arma(10,municion)){
            ui->Teletransportador->setText("Selecionar");
        } else {
            ui->Teletransportador->setText("Sacar");
        }
    }
}
