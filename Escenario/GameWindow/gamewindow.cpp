#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->playerActive=nullptr;
}



void GameWindow::addGameScene(Game_View *gameScene)
{
    this->gameScene = gameScene;
    ui->graphicsView->addScene(this->gameScene->getScene());
}

Camera* GameWindow::getCamera()
{
    return this->ui->graphicsView;
}


GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::addPlayer(Player *player)
{
    this->playerActive = player;
}

void GameWindow::on_pushButton_clicked()
{
    if(this->playerActive==nullptr){
        return;
    }
    this->menuWeapons = new Weapons_and_Tools(this,this->playerActive);
    this->menuWeapons->setModal(true);
    this->menuWeapons->setAttribute(Qt::WA_DeleteOnClose);
    this->menuWeapons->exec();
    this->menuWeapons=nullptr;
}
