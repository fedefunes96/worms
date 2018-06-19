#include "commonLose.h"
#include "ui_commonLose.h"

commonLose::commonLose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::commonLose)
{
    ui->setupUi(this);
    this->setWindowTitle("You Lose");
    b = new backgrounMusic("/resources/sounds/BackgroundMusic/Total Distortion You Are Dead.wav");
    QPixmap img = QPixmap(ROOT_PATH"/resources/images/LoseScreen.gif");
    ui->label->setPixmap(img);
}

commonLose::~commonLose()
{
    delete ui;
    delete b;
}
