#include "commonLose.h"
#include "ui_commonLose.h"

commonLose::commonLose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::commonLose)
{
    ui->setupUi(this);
    this->setWindowTitle("You Lose");
    //b = new backgrounMusic("../../sounds/BackgroundMusic/Worms World Party Soundtrack - Hell.wav");
    QPixmap img = QPixmap("../../images/LoseScreen.gif");
    ui->label->setPixmap(img);
}

commonLose::~commonLose()
{
    delete ui;
    //delete b;
}
