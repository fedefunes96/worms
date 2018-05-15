#include "editorpantalla.h"
#include "ui_editorpantalla.h"
#include "editorseleccionarmasherramientas.h"

EditorPantalla::EditorPantalla(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditorPantalla)
{
    ui->setupUi(this);
}

EditorPantalla::~EditorPantalla()
{
    delete ui;
}

void EditorPantalla::on_buttonBox_accepted()
{

}


void EditorPantalla::on_agregarGusano_clicked()
{

}

void EditorPantalla::on_AgregarViga_clicked()
{

}

void EditorPantalla::on_SelecionarHerramintas_Armas_clicked()
{
    editorSeleccionArmasHerramientas pantalla3;
    pantalla3.setModal(true);
    pantalla3.exec();
}
