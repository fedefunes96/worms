#include "commonWin.h"
#include "ui_commonWin.h"
#include "backgrounMusic.h"

commonWIn::commonWIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::commonWIn)
{
    ui->setupUi(this);
    this->setWindowTitle("Victory");
    QFont f("Arial",22,QFont::Bold);
    ui->label->setFont(f);
    b = new backgrounMusic("../../sounds/BackgroundMusic/FFI - Victory.wav");
    QPixmap img = QPixmap("../../images/Win.jpeg");
    ui->label->setPixmap(img);
}

commonWIn::~commonWIn()
{
    delete ui;
    delete b;
}
