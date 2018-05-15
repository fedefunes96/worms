#include "editorseleccionarmasherramientas.h"
#include "ui_editorseleccionarmasherramientas.h"

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
