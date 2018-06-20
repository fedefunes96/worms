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
    ui->refocus->setEnabled(false);
    this->setWindowState(this->windowState() | Qt::WindowMaximized);
    //ui->powerBar->setMaximum(1000);
    //ui->powerBar->setMinimum(0);

}


void GameWindow::closeEvent(QCloseEvent *event)
{
    emit closeGame();
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
    //delete(this->timer);
    //delete(this->timerRound);
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
    this->time=time;
    this->timeToReach=0;
    ui->lcdNumber->setPalette(Qt::gray);
}

void GameWindow::stepTimer()
{
    if(this->time==this->timeToReach){
        return;
    }
    this->time--;
    ui->lcdNumber->display(this->time);
    if(this->time <= 10){
        ui->lcdNumber->setPalette(Qt::red);
    }
}

void GameWindow::setWind(int speed)
{
    if(speed<0){
        ui->windLeft->setEnabled(true);
        ui->windRight->setValue(0);
        ui->windRight->setEnabled(false);
        ui->windLeft->setValue(abs(speed));
        return;
    }
    ui->windRight->setEnabled(true);
    ui->windLeft->setValue(0);
    ui->windLeft->setEnabled(false);
    ui->windRight->setValue(abs(speed));
}

void GameWindow::setWindParm(int min, int max)
{
    ui->windRight->setMaximum(max);
    ui->windRight->setMinimum(0);
    ui->windLeft->setMaximum(max);
    ui->windLeft->setMinimum(0);
}

void GameWindow::setRefocusEnable(bool enable)
{
    ui->refocus->setEnabled(enable);
}

void GameWindow::on_refocus_clicked()
{
    ui->graphicsView->setFreeMove(false);
    ui->refocus->setEnabled(false);
}
