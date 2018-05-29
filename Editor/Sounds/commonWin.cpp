#include "commonWin.h"
#include "ui_commonWin.h"
#include "backgrounMusic.h"

commonWIn::commonWIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::commonWIn)
{
    ui->setupUi(this);
    this->setWindowTitle("Victory");
    QFont f("Arial",22,QFont::Bold);
    ui->label->setFont(f);
    backgrounMusic *b = new backgrounMusic("../Sounds/sounds/BackgroundMusic/FFI - Victory.wav");
    QPixmap img = QPixmap("../imagenes/Win.jpeg");
    ui->label->setPixmap(img);
}

commonWIn::~commonWIn()
{
    delete ui;
}
