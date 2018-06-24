#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QMessageBox>


GameWindow::GameWindow(QApplication *app, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{
    this->app = app;
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
    ui->upCamera->setIcon(QIcon(ROOT_PATH"/resources/images/up.png"));
    ui->downCamera->setIcon(QIcon(ROOT_PATH"/resources/images/down.png"));
    ui->leftCamera->setIcon(QIcon(ROOT_PATH"/resources/images/left.png"));
    ui->rightCamera->setIcon(QIcon(ROOT_PATH"/resources/images/right.png"));
    this->setButtonTime(ui->time1,false);
    this->setButtonTime(ui->time2,false);
    this->setButtonTime(ui->time3,false);
    this->setButtonTime(ui->time4,false);
    this->setButtonTime(ui->time5,false);
    this->setButtomsCountDownHidden(true);
    ui->powerBar->setHidden(true);
    this->hasWinner=false;
}


void GameWindow::setPowerBarHidden(bool enable)
{
    ui->powerBar->setHidden(enable);
    ui->PowerLabel->setHidden(enable);
}

void GameWindow::setButtomsCountDownHidden(bool enable)
{
    ui->time1->setHidden(enable);
    ui->time2->setHidden(enable);
    ui->time3->setHidden(enable);
    ui->time4->setHidden(enable);
    ui->time5->setHidden(enable);
    ui->weaponCountDownLabel->setHidden(enable);
}

void GameWindow::setWinner(bool haswinner){
    this->hasWinner=haswinner;
}

void GameWindow::closeEvent(QCloseEvent *event)
{
    if(!this->hasWinner){
        this->app->exit();
    }
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
    QString id;
    id.setNum(player->getId());
    QString name= "Player ";
    ui->nameThisPlayer->setText(name+id);
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
    Worm_View *worm = this->playerActive->getWormActive();
    if(worm==nullptr){
        return;
    }
    int idw = worm->getWeaponId();
    if(idw==static_cast<int>(WeaponsIds::AERIAL_ATTACK) ||
       idw==static_cast<int>(WeaponsIds::BASEBALL_BAT) ||
       idw==static_cast<int>(WeaponsIds::DYNAMITE) ||
       idw==static_cast<int>(WeaponsIds::TELEPORTATION)){
        this->setPowerBarHidden(true);
    }else{
        this->setPowerBarHidden(false);
    }
    if(!worm->isWeaponCtD()){
        this->setButtomsCountDownHidden(true);
        return;
    }
    this->setButtomsCountDownHidden(false);
    this->setButtomsTime(worm->getTimeWeapon());
}

void GameWindow::setButtonEnable(bool enable)
{
    this->ui->pushButton->setEnabled(enable);
}


void GameWindow::showActualPlayer(int id)
{
    QString name= "Player ";
    QString idP;
    idP.setNum(id);
    name = name + idP;
    QMessageBox::information(this,"Actual player","Actual player is:" + name);
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




void GameWindow::showPlayerList(QList<Player*> playerList)
{
    ui->playerListPoints->clear();
    for (int var = 0; var < playerList.size(); ++var) {
        QString num;
        num.setNum(playerList[var]->getPoints());
        num = "   --> points:"+num;
        QString name= "Player ";
        QString id;
        id.setNum(playerList[var]->getId());
        name = name + id;
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(name + num);
        item->setBackgroundColor(QColor(playerList[var]->getColor()));
        ui->playerListPoints->addItem(item);
    }
}












void GameWindow::on_downCamera_clicked()
{
    ui->graphicsView->moveDownCam();
    ui->refocus->setEnabled(true);
}

void GameWindow::on_leftCamera_clicked()
{
    ui->graphicsView->moveLeftCam();
    ui->refocus->setEnabled(true);
}

void GameWindow::on_upCamera_clicked()
{
    ui->graphicsView->moveUpCam();
    ui->refocus->setEnabled(true);
}

void GameWindow::on_rightCamera_clicked()
{
    ui->graphicsView->moveRightCam();
    ui->refocus->setEnabled(true);
}

void GameWindow::on_time1_clicked()
{
    this->setButtomsTime(1);
}

void GameWindow::on_time2_clicked()
{
    this->setButtomsTime(2);
}

void GameWindow::on_time3_clicked()
{
    this->setButtomsTime(3);
}

void GameWindow::on_time4_clicked()
{
    this->setButtomsTime(4);
}

void GameWindow::on_time5_clicked()
{
    this->setButtomsTime(5);
}




void GameWindow::setButtomsTime(int time)
{
    Worm_View *worm = this->playerActive->getWormActive();
    if(worm==nullptr || !worm->isWeaponCtD()){
        this->setButtomsCountDownHidden(true);
        return;
    }
    this->setButtomsCountDownHidden(false);
    this->setButtonTime(ui->time1,false);
    this->setButtonTime(ui->time2,false);
    this->setButtonTime(ui->time3,false);
    this->setButtonTime(ui->time4,false);
    this->setButtonTime(ui->time5,false);
    if(time==1){
        this->setButtonTime(ui->time1,true);
    }else if(time==2){
        this->setButtonTime(ui->time2,true);
    }else if(time==3){
        this->setButtonTime(ui->time3,true);
    }else if(time==4){
        this->setButtonTime(ui->time4,true);
    }else{
        this->setButtonTime(ui->time5,true);
    }
    worm->setTimeWeapon(time);
}








void GameWindow::setButtonTime(QPushButton *button,bool enable)
{
    if(enable){
        QPalette pal = button->palette();
        pal.setColor(QPalette::Button, QColor(Qt::red));
        button->setAutoFillBackground(true);
        button->setPalette(pal);
        button->update();
    }else{
        QPalette pal = button->palette();
        pal.setColor(QPalette::Button, QColor(Qt::white));
        button->setAutoFillBackground(true);
        button->setPalette(pal);
        button->update();
    }
}









