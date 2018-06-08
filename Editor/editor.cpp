#include "editor.h"
#include "ui_editor.h"

editor::editor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editor)
{
    ui->setupUi(this);
    xscene = 2000;
    yscene = 1000;
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    this->setWindowTitle("Nuevo mapa");
}

editor::~editor()
{
    delete ui;
}
