#include "game.h"
#include "girder_view.h"
#include <QDebug>
#include "projectile.h"
#include <QColor>
#include <QCoreApplication>

Game::Game(QApplication *app)
{
    this->app = app;
}

Game::~Game()
{
    delete(this->deadItemCollector);
    for (int var = 0; var < this->players_list.size(); ++var) {
        delete(this->players_list[var]);
    }
    delete(this->window);
    delete(this->game);

}

void Game::setIdPlayer(int id)
{
    if(!this->players_list.empty()){
        return;
    }
    this->window = new GameWindow(this->app);
    this->game = new Stage(10,10);
    this->window->addGameScene(this->game);
    this->game->addCamera(this->window->getCamera());
    this->myTurn=false;
    createColorList();
    this->myPlayer = new Player();
    this->myPlayer->setId(id);
    this->myPlayer->setColor(getColor(id));
    this->players_list.append(this->myPlayer);
    this->game->setPlayerActive(this->myPlayer);
    this->window->addPlayer(this->myPlayer);
    this->deadItemCollector = new QTimer();
    this->deadItemCollector->start(10);
    connect(this->deadItemCollector,&QTimer::timeout,this,&Game::checkDeadItem);
    this->window->setRefocusEnable(false);
    this->lastP=nullptr;
}

Camera* Game::getCamera()
{
    return this->game->getCamera();
}

void Game::connectWaitRoom(WaitRoom *wait){
    connect(wait,SIGNAL(startView(QList<std::string>)),this,SLOT(showWindow(QList<std::string>)));
}

void Game::showWindow(QList<std::string> list)
{
    std::string path(ROOT_PATH"/resources/images/"+list[0]);
    this->window->showMaximized();
    b = new backgrounMusic(ROOT_PATH"/resources/sounds/BackgroundMusic/Soundtrack.wav");
    this->game->setBackground(path);
}

void Game::setRefocus(bool enable)
{
    this->window->setRefocusEnable(enable);
}

void Game::connectController(Controller *controler)
{
    connect(controler,SIGNAL(eventCreated(QList<int>)),this,SLOT(checkQueueEvent(QList<int>)));
}


void Game::setPotBar(int pot)
{
    this->window->setBar(pot);
}


QString Game::getColor(int id_player)
{
    while(id_player>= this->color_list.size()){
        id_player -= this->color_list.size();
    }
    return this->color_list[id_player];
}

void Game::createColorList()
{
    this->color_list.append("blue");
    this->color_list.append("yellow");
    this->color_list.append("red");
    this->color_list.append("purple");
    this->color_list.append("cyan");
    this->color_list.append("green");
    this->color_list.append("orange");
    this->color_list.append("darkRed");
    this->color_list.append("darkGray");
    this->color_list.append("white");
    this->color_list.append("darkBlue");
    this->color_list.append("magenta");
    this->color_list.append("gray");
    this->color_list.append("darkCyan");
    this->color_list.append("darkMagenta");
    this->color_list.append("lightGray");
}


Player* Game::getPlayerInList(int id_player)
{
    for (int var = 0; var < this->players_list.size(); ++var) {
        if(id_player==(this->players_list[var]->getId())){
            return this->players_list[var];
        }
    }
    return nullptr;
}

void Game::recvWormHealth(int id,int health)
{
    Items *item = this->game->getItem(static_cast<int>(TypeObj::WORM),id);
    Worm_View *worm = static_cast<Worm_View*>(item);
    worm->setHealth(health);
}

void Game::attachWorm(int type,int id_player,int id, int health)
{
    if(!this->game->containsItem(type,id)){
        Worm_View *worm = new Worm_View(this,getColor(id_player));
        worm->setHealth(health);
        worm->setId(id);
        worm->setIdObj(type);
        this->game->add_Item(worm,-100,-100); // -100 pos invalida, luego al recibir su pos lo ubico..

        Player *player = getPlayerInList(id_player);
        if(player==nullptr){
            //no tengo player..
            player= new Player();
            player->setId(id_player);
            player->setColor(getColor(id_player));
            this->players_list.append(player);
        }
        player->addWorm(worm);
    }
}

void Game::updateItem(int type, int id, int posX, int posY, int angle)
{
    if((this->game->getHeight()<posY || this->game->getWidth() < posX) ){
        if(this->game->getHeight()<posY){
            this->game->resizeScene(this->game->getWidth(),posY*10);
        }
        if(this->game->getWidth()<posX){
            this->game->resizeScene(posX*10,this->game->getHeight());
        }
    }

    if(type==static_cast<int>(TypeObj::WORM)){
        if(this->game->containsItem(type,id)){
            this->game->moveObjTo(type,id,posX,posY,angle);
        }
    }else if(type==static_cast<int>(TypeObj::SMALL_GIRDER)){
        if(!this->game->containsItem(type,id)){
            Girder_View* girder = new Girder_View(angle,70);
            girder->setId(id);
            girder->setIdObj(type);
            this->game->add_Item(girder,posX,posY);
        }
    }else if(type==static_cast<int>(TypeObj::LARGE_GIRDER)){
        if(!this->game->containsItem(type,id)){
            Girder_View* girder = new Girder_View(angle,140);
            girder->setId(id);
            girder->setIdObj(type);
            this->game->add_Item(girder,posX,posY);
        }
    }else if(type==static_cast<int>(TypeObj::BAZOOKA_M)){
        std::string path(ROOT_PATH"/resources/images/misil.png");
        this->throwProjectile(type,id,posX,posY,angle,path);
    }else if(type==static_cast<int>(TypeObj::GREEN_GRENADE_M)){
        std::string path(ROOT_PATH"/resources/images/granade.png");
        this->throwProjectile(type,id,posX,posY,angle,path);
    }else if(type==static_cast<int>(TypeObj::MORTAR_M)){
        std::string path(ROOT_PATH"/resources/images/mortar.png");
        this->throwProjectile(type,id,posX,posY,angle,path);
    }else if(type==static_cast<int>(TypeObj::AERIAL_ATTACK_M)){
        std::string path(ROOT_PATH"/resources/images/airmisil.png");
        this->throwProjectile(type,id,posX,posY,angle,path);
    }else if(type==static_cast<int>(TypeObj::HOLY_GRENADE_M)){
        std::string path(ROOT_PATH"/resources/images/hgranade.png");
        this->throwProjectile(type,id,posX,posY,angle,path);
    }else if(type==static_cast<int>(TypeObj::FRAGMENT_M)){
        std::string path(ROOT_PATH"/resources/images/fragm.png");
        this->throwProjectile(type,id,posX,posY,angle,path);
    }else if(type==static_cast<int>(TypeObj::RED_GRENADE_M)){
        std::string path(ROOT_PATH"/resources/images/cluster.png");
        this->throwProjectile(type,id,posX,posY,angle,path);
    }else if(type==static_cast<int>(TypeObj::BANANA_M)){
        std::string path(ROOT_PATH"/resources/images/banana.png");
        this->throwProjectile(type,id,posX,posY,angle,path);
    }else if(type==static_cast<int>(TypeObj::DYNAMITE_M)){
        std::string path(ROOT_PATH"/resources/images/dynamite.png");
        this->throwProjectile(type,id,posX,posY,angle,path);
    }
}



void Game::throwProjectile(int type,int id,int posX,int posY,int angle,std::string &path)
{
    if(this->game->containsItem(type,id)){
        Items* item = this->game->getItem(type,id);
        MovableItem *i = static_cast<MovableItem*>(item);
        i->moveTo(-angle,posX,posY);
    }else{
        Projectile *misil = new Projectile();
        misil->setIdObj(type);
        misil->setId(id);
        misil->setSpriteBullet(path);
        this->game->add_Item(misil,posX,posY);
        misil->moveTo(-angle,posX,posY);
        misil->setSelect(true);
        this->game->getCamera()->addProjectileToFollow(misil);
    }
}


void Game::updatePlayer(int type, int id, int ammo, Worm_View *worm)
{
    if(type==2){
        this->myPlayer->addWeapon(id,ammo);
    }
}


Player *Game::getPlayer()
{
    return this->myPlayer;
}

Stage *Game::getGameView()
{
    return this->game;
}


std::vector<int> Game::fireWeapon()
{
    std::vector<int> vect;
    if(isMyTurn()){
        int idWeapon = this->myPlayer->getWormActive()->getWeaponId(); //devuelvo id negativo si no tengo arma seleccionada
        if(idWeapon<0 && !this->myPlayer->canFire(idWeapon)){
            return vect; // lo devuelvo vacio
        }
        //puedo disparar el arma...
        this->myPlayer->fireWeapon(idWeapon);
        std::pair<int,int> pos = this->myPlayer->getWormActive()->getDirWeapon();
        int time = this->myPlayer->getWormActive()->getTimeWeapon();
        vect.push_back(idWeapon);
        vect.push_back(pos.first);
        vect.push_back(pos.second);
        if(idWeapon==static_cast<int>(WeaponsIds::BANANA) ||
                idWeapon==static_cast<int>(WeaponsIds::DYNAMITE) ||
                idWeapon==static_cast<int>(WeaponsIds::GREEN_GRENADE) ||
                idWeapon==static_cast<int>(WeaponsIds::HOLY_GRENADE) ||
                idWeapon==static_cast<int>(WeaponsIds::RED_GRENADE)){
            vect.push_back(time);
        }
        this->window->setButtonEnable(false);
        this->myPlayer->getWormActive()->loadSpriteWeapon(-1);
        this->window->startTimerRound(3);
    }
    return vect;
}


bool Game::isMyTurn(){
    return this->myTurn;
}

void Game::removeItem(int type,int id)
{
    MovableItem* item = static_cast<MovableItem*>(this->game->getItem(type,id));
    item->removeMovable();
}



void Game::checkDeadItem()
{
    QGraphicsScene *scene = this->game->getScene();
    QList<QGraphicsItem*> list_items = scene->items();
    QList<QGraphicsItem*>::iterator it;
    for (it=list_items.begin();it!=list_items.end();it++)
    {
        MovableItem *itemMov = dynamic_cast<MovableItem*>(*it);
        if(!itemMov){
            continue;
        }
        if(itemMov->isAlive() && !itemMov->isSelect()){
            if(itemMov->isMoving()){
                if(!this->game->getCamera()->containsitemToFollow(itemMov)){
                    this->game->getCamera()->addItemToFollow(itemMov);
                }
            }else{
                if(this->game->getCamera()->containsitemToFollow(itemMov)){
                    this->game->getCamera()->delItemToFollow(itemMov);
                }
            }

        }
        Projectile* item =dynamic_cast<Projectile*>(*it);
        if(!item){// no es movible
            continue;
        }else if(!item->isAlive()){
            scene->removeItem(item);
            //delete(item);
        }
    }
}





void Game::checkQueueEvent(QList<int> list)
{
    this->window->showPlayerList(this->players_list);
    this->window->cleanWeaponInfoView();
    this->game->getCamera()->followObject();
    int cmd = list[0];
    if(cmd== static_cast<int>(Commands::GAME_END)){
        this->myPlayer->setActive(false);
        this->myTurn=false;
    }else if(cmd==static_cast<int>(Commands::ATTACH_PLAYER_ID)){
        this->updatePlayer(cmd,list[1]);
    }else if(cmd==static_cast<int>(Commands::ATTACH_USABLE_ID)){
        this->updatePlayer(cmd,list[1],list[2]);
    }else if(cmd==static_cast<int>(Commands::ACTUAL_PLAYER)){
        checkRound(list);
    }else if(cmd==static_cast<int>(Commands::ATTACH_WORM_ID)){
        this->attachWorm(static_cast<int>(TypeObj::WORM),list[1],list[2],list[3]);
    }else if(cmd==static_cast<int>(Commands::REMOVE)){
        this->removeItem(list[1],list[2]);
    }else if(cmd==static_cast<int>(Commands::POSITION)){
        this->updateItem(list[1],list[2],list[3],list[4],list[5]);
    }else if(cmd==static_cast<int>(Commands::WINNER)){
        this->myPlayer->setActive(false);
        this->myTurn=false;
        this->window->setWinner(true);
        this->window->close();
        b->stop();
        if(list[1]==this->myPlayer->getId()){
            emit isWinner(true);
        }else{
            emit isWinner(false);
        }
    }else if(cmd==static_cast<int>(Commands::WORM_HEALTH)){
        this->recvWormHealth(list[1],list[2]);
    }else if(cmd==static_cast<int>(Commands::WORM_STATUS)){
        setStatusWorm(list);
    }else if(cmd==static_cast<int>(Commands::WIND_PARAMS)){
        this->window->setWindParm(list[1],list[2]);
    }else if(cmd==static_cast<int>(Commands::WIND_SPEED)){
        this->window->setWind(list[1]);
    }

}


void Game::setStatusWorm(QList<int> list)
{
    Items *item = this->game->getItem(static_cast<int>(TypeObj::WORM),list[1]);
    if(!item){
        return;
    }
    Worm_View *worm = static_cast<Worm_View*>(item);
    worm->setStatus(list[2],list[3]);
}

void Game::checkRound(QList<int> list){
    this->window->startTimerRound(40);
    if(this->lastP!=nullptr){
        Worm_View *w = this->lastP->getWormActive();
        if(w!=nullptr){
            w->setSelect(false);
        }
    }

    this->lastP=this->getPlayerInList(list[1]);
    Items* i = this->game->getItem(static_cast<int>(TypeObj::WORM),list[2]);
    Worm_View* worm = static_cast<Worm_View*>(i);
    worm->setSelect(true);
    this->lastP->setWormActive(worm);
    this->game->addItemToFollow(worm);
    if(this->myPlayer->getId() != list[1]){
        this->setPotBar(0);
        this->myTurn=false;
        this->window->setButtonEnable(false);
        this->myPlayer->setActive(false);
        Worm_View* worm2 = this->myPlayer->getWormActive();
        if(worm2!=nullptr){
            worm2->setSelect(false);
            worm2->loadSpriteWeapon(-1);
        }
        this->myPlayer->setWormActive(nullptr);
        return;
    }
    this->myTurn=true;
    this->setPotBar(0);
    this->window->setButtonEnable(true);
    this->myPlayer->setActive(true);
}



