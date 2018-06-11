#include "gamewindow.h"
#include "ui_gamewindow.h"


GameWindow::GameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->playerActive=nullptr;
    this->timer = new QTimer();
    this->timer->start(500);// no hace falta chequear tan seguido...
    connect(this->timer,&QTimer::timeout,this,&GameWindow::refreshBox);
    this->setWindowTitle("Worms Armageddon");
}



void GameWindow::refreshBox()
{
    ui->textBrowser->clear();
    std::vector<Worm_View*> lista = this->playerActive->getWormsAlive();
    for (unsigned int var = 0; var < lista.size(); ++var) {
        QString aux;
        aux = "Worm:";
        aux += QString::number(lista[var]->getId());
        aux += "   vida:";
        aux += QString::number(lista[var]->getHealth());
        ui->textBrowser->append(aux);
    }
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
