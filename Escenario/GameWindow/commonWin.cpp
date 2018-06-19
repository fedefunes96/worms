#include "commonWin.h"
#include "ui_commonWin.h"

commonWIn::commonWIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::commonWIn)
{
    ui->setupUi(this);
    this->setWindowTitle("Victory");
    QFont f("Arial",22,QFont::Bold);
    ui->label->setFont(f);
    this->b = new backgrounMusic("/resources/sounds/BackgroundMusic/FFI - Victory.wav");
    QPixmap img = QPixmap(ROOT_PATH"/resources/images/Win.jpeg");
    ui->label->setPixmap(img);
}

commonWIn::~commonWIn()
{
    delete ui;
    delete b;
}
