#include "commonLose.h"
#include "ui_commonLose.h"
#include "backgrounMusic.h"

commonLose::commonLose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::commonLose)
{
    ui->setupUi(this);
    this->setWindowTitle("You Lose");
    backgrounMusic *b = new backgrounMusic("../Sounds/sounds/BackgroundMusic/Worms World Party Soundtrack - Hell.wav");
    QPixmap img = QPixmap("../imagenes/LoseScreen.gif");
    ui->label->setPixmap(img);
}

commonLose::~commonLose()
{
    delete ui;
}
