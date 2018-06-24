#include "finalscreen.h"
#include "ui_finalscreen.h"

FinalScreen::FinalScreen(QApplication *app,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FinalScreen)
{
    this->app=app;
    ui->setupUi(this);
    this->setWindowTitle("End game");
    b=nullptr;
}

FinalScreen::~FinalScreen()
{
    if(b!=nullptr){
        //delete(b);
    }
    delete ui;
}


void FinalScreen::setWinner(){
    ui->text->setAttribute(Qt::WA_TranslucentBackground);
    ui->text->setText("YOU WIN !!");
    QFont f("Arial",22,QFont::Bold);
    ui->text->setFont(f);
    QPixmap img = QPixmap(ROOT_PATH"/resources/images/Win.jpeg");
    b = new backgrounMusic(ROOT_PATH"/resources/sounds/BackgroundMusic/FFI - Victory.wav");
    ui->imageBackground->setPixmap(img);
    ui->imageBackground->setScaledContents(true);
    this->exec();
}


void FinalScreen::setLoser(){
    ui->text->setAttribute(Qt::WA_TranslucentBackground);
    ui->text->setText("YOU LOSE !!");
    QFont f("Arial",22,QFont::Bold);
    ui->text->setFont(f);
    QPixmap img = QPixmap(ROOT_PATH"/resources/images/LoseScreen.gif");
    b = new backgrounMusic(ROOT_PATH"/resources/BackgroundMusic/Total Distortion You Are Dead.wav");
    ui->imageBackground->setPixmap(img);
    ui->imageBackground->setScaledContents(true);
    this->exec();
}



void FinalScreen::setIsWinner(bool iswinner)
{
    if(iswinner){
        this->setWinner();
    }else{
        this->setLoser();
    }
}

void FinalScreen::connectGame(GameClass *game)
{
    connect(game,SIGNAL(isWinner(bool)),this,SLOT(setIsWinner(bool)));
}


void FinalScreen::closeEvent(QCloseEvent *event)
{
    app->exit();
}
