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
    this->time=0;
    this->timeToReach=0;
    this->timerRound = new QTimer();
    this->timerRound->start(1000);
    connect(this->timerRound,&QTimer::timeout,this,&GameWindow::stepTimer);

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

void GameWindow::setButtonEnable(bool enable)
{
    this->ui->pushButton->setEnabled(enable);
}


void GameWindow::setBar(int pot)
{
    ui->powerBar->setValue(pot);
}

void GameWindow::startTimerRound(int time)
{
    this->time=0;
    this->timeToReach=time;
    qDebug()<<"XXXXXXXXXXXXXXXXXXXXXX time:"<<this->time<<"timeToreach:"<<this->timeToReach;
}

void GameWindow::stepTimer()
{
    qDebug()<<"time:"<<this->time<<"timeToreach:"<<this->timeToReach;
    if(this->time>this->timeToReach){
        return;
    }
    qDebug()<<"entre tiempo";
    this->time++;
    ui->lcdNumber->display(this->time);
}

void GameWindow::setWind(int speed)
{
    ui->windBar->setValue(speed);
}

void GameWindow::setWindParm(int min, int max)
{
    ui->windBar->setMaximum(max);
    ui->windBar->setMinimum(min);
}
