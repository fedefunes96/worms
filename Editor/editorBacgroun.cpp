#include "editorBacgroun.h"
#include "ui_editorBacgroun.h"

editorBacgroun::editorBacgroun(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editorBacgroun)
{
    ui->setupUi(this);
}

editorBacgroun::~editorBacgroun()
{
    delete ui;
}
