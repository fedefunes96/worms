#include "gameclass.h"
#include "girder_view.h"
#include <QDebug>
#include "projectile.h"


GameClass::GameClass(QRect screen,int w,int h)
{
    this->window = new GameWindow();
    this->game = new Game_View(screen,w,h);
    this->window->addGameScene(this->game);
    this->game->addCamera(this->window->getCamera());
    std::string path("../../images/intro2.jpg");
    this->window->showMaximized();
    this->game->setBackground(path);
    this->myTurn=true;
    this->myPlayer = new Player();
    this->game->setPlayerActive(this->myPlayer);
    this->window->addPlayer(this->myPlayer);

    this->deadItemCollector = new QTimer();
    this->deadItemCollector->start(100);
    connect(this->deadItemCollector,&QTimer::timeout,this,&GameClass::checkDeadItem);
}

Camera* GameClass::getCamera()
{
    return this->game->getCamera();
}

void GameClass::connectController(Controler *controler)
{
    connect(controler,SIGNAL(eventCreated(QList<int>)),this,SLOT(checkQueueEvent(QList<int>)));
}

void GameClass::recvWormHealth(int id,int health)
{
    Items *item = this->game->getItem(static_cast<int>(TypeObj::WORM),id);
    Worm_View *worm = static_cast<Worm_View*>(item);
    worm->setHealth(health);
}

void GameClass::attachWorm(int type,int id, int health)
{
    if(!this->game->containsItem(type,id)){
        Worm_View *worm = new Worm_View();
        qDebug()<<"health"<<health<<"id"<<id<<"typ"<<type;
        worm->setHealth(health);
        worm->setId(id);
        worm->setIdObj(type);
        this->game->add_Item(worm,-100,-100); // -100 pos invalida, luego al recibir su pos lo ubico..
        this->myPlayer->addWorm(worm);
    }
}

void GameClass::updateItem(int type, int id, int posX, int posY, int angle)
{
    if(this->game->getHeight()<posY || this->game->getWidth()<posX){
        return;
    }
    if(type==static_cast<int>(TypeObj::WORM)){
        if(this->game->containsItem(type,id)){
            //contiene al worm --> lo muevo
            qDebug()<<"id:"<<id<<"move worm posX:"<<posX<<"posY" <<posY<<"angle"<<angle;
            this->game->moveObjTo(type,id,posX,posY,angle);
        }
    }else if(type==static_cast<int>(TypeObj::GIRDER)){
        //es girder
        if(!this->game->containsItem(type,id)){
            //no contiene girder...
            //qDebug()<<"no contiene girder";
            Girder_View* girder = new Girder_View(angle,140);
            girder->setId(id);
            girder->setIdObj(type);
            this->game->add_Item(girder,posX,posY);
        }
    }else if(type==static_cast<int>(TypeObj::BAZOOKA_M)){
        qDebug()<<"crear misil!!!!!!!!!!!";
        qDebug()<<"type:"<<type<<"id:"<<id<<"posx:"<<posX<<"posy:"<<posY<<"angle:"<<angle;
        if(this->game->containsItem(type,id)){
            qDebug()<<"lo contiene";
            Items* item = this->game->getItem(type,id);
            MovableItem *i = static_cast<MovableItem*>(item);
            i->moveTo(-angle,posX,posY);
        }else{
            qDebug()<<"no contiene";
            Projectile *misil = new Projectile();
            misil->setIdObj(type);
            misil->setId(id);
            std::string path("../../images/misil.png");
            misil->setSpriteBullet(path);
            this->game->add_Item(misil,posX,posY);
            misil->moveTo(-angle,posX,posY);
            this->game->addItemToFollow(misil);
        }
    }else if(type==static_cast<int>(TypeObj::GREEN_GRENADE_M)){
        qDebug()<<"crear granada!!!!!!!!!!!";
        qDebug()<<"type:"<<type<<"id:"<<id<<"posx:"<<posX<<"posy:"<<posY<<"angle:"<<-angle;
        if(this->game->containsItem(type,id)){
            qDebug()<<"lo contiene";
            Items* item = this->game->getItem(type,id);
            MovableItem *i = static_cast<MovableItem*>(item);
            i->moveTo(-angle,posX,posY);
        }else{
            qDebug()<<"no contiene";
            Projectile *misil = new Projectile();
            misil->setIdObj(type);
            misil->setId(id);
            std::string path("../../images/granade.png");
            misil->setSpriteBullet(path);
            this->game->add_Item(misil,posX,posY);
            misil->moveTo(-angle,posX,posY);
            this->game->addItemToFollow(misil);
        }
    }else if(type==static_cast<int>(TypeObj::MORTAR_M)){
        qDebug()<<"crear mortar!!!!!!!!!!!";
        qDebug()<<"type:"<<type<<"id:"<<id<<"posx:"<<posX<<"posy:"<<posY<<"angle:"<<-angle;
        if(this->game->containsItem(type,id)){
            qDebug()<<"lo contiene";
            Items* item = this->game->getItem(type,id);
            MovableItem *i = static_cast<MovableItem*>(item);
            i->moveTo(-angle,posX,posY);
        }else{
            qDebug()<<"no contiene";
            Projectile *misil = new Projectile();
            misil->setIdObj(type);
            misil->setId(id);
            std::string path("../../images/mortar.png");
            misil->setSpriteBullet(path);
            this->game->add_Item(misil,posX,posY);
            misil->moveTo(-angle,posX,posY);
            this->game->addItemToFollow(misil);
        }
    }else if(type==static_cast<int>(TypeObj::AERIAL_ATTACK_M)){
        qDebug()<<"crear aerial attack!!!!!!!!!!!";
        qDebug()<<"type:"<<type<<"id:"<<id<<"posx:"<<posX<<"posy:"<<posY<<"angle:"<<-angle;
        if(this->game->containsItem(type,id)){
            qDebug()<<"lo contiene lo muevo";
            Items* item = this->game->getItem(type,id);
            MovableItem *i = static_cast<MovableItem*>(item);
            i->moveTo(-angle,posX,posY);
        }else{
            qDebug()<<"no contiene";
            Projectile *misil = new Projectile();
            misil->setIdObj(type);
            misil->setId(id);
            std::string path("../../images/airmisil.png");
            misil->setSpriteBullet(path);
            this->game->add_Item(misil,posX,posY);
            misil->moveTo(-angle,posX,posY);
            this->game->addItemToFollow(misil);
        }
    }else if(type==static_cast<int>(TypeObj::HOLY_GRENADE_M)){
        qDebug()<<"crear holy granade!!!!!!!!!!!";
        qDebug()<<"type:"<<type<<"id:"<<id<<"posx:"<<posX<<"posy:"<<posY<<"angle:"<<-angle;
        if(this->game->containsItem(type,id)){
            qDebug()<<"lo contiene";
            Items* item = this->game->getItem(type,id);
            MovableItem *i = static_cast<MovableItem*>(item);
            i->moveTo(-angle,posX,posY);
        }else{
            qDebug()<<"no contiene";
            Projectile *misil = new Projectile();
            misil->setIdObj(type);
            misil->setId(id);
            std::string path("../../images/hgranade.png");
            misil->setSpriteBullet(path);
            this->game->add_Item(misil,posX,posY);
            misil->moveTo(-angle,posX,posY);
            this->game->addItemToFollow(misil);
        }
    }else if(type==static_cast<int>(TypeObj::FRAGMENT_M)){
        qDebug()<<"crear fragment!!!!!!!!!!!";
        qDebug()<<"type:"<<type<<"id:"<<id<<"posx:"<<posX<<"posy:"<<posY<<"angle:"<<-angle;
        if(this->game->containsItem(type,id)){
            qDebug()<<"lo contiene";
            Items* item = this->game->getItem(type,id);
            MovableItem *i = static_cast<MovableItem*>(item);
            i->moveTo(-angle,posX,posY);
        }else{
            qDebug()<<"no contiene";
            Projectile *misil = new Projectile();
            misil->setIdObj(type);
            misil->setId(id);
            std::string path("../../images/hgranade.png");
            misil->setSpriteBullet(path);
            this->game->add_Item(misil,posX,posY);
            misil->moveTo(-angle,posX,posY);
            this->game->addItemToFollow(misil);
        }
    }else if(type==static_cast<int>(TypeObj::RED_GRENADE_M)){
        qDebug()<<"crear red granade!!!!!!!!!!!";
        qDebug()<<"type:"<<type<<"id:"<<id<<"posx:"<<posX<<"posy:"<<posY<<"angle:"<<-angle;
        if(this->game->containsItem(type,id)){
            qDebug()<<"lo contiene";
            Items* item = this->game->getItem(type,id);
            MovableItem *i = static_cast<MovableItem*>(item);
            i->moveTo(-angle,posX,posY);
        }else{
            qDebug()<<"no contiene";
            Projectile *misil = new Projectile();
            misil->setIdObj(type);
            misil->setId(id);
            std::string path("../../images/cluster.png");
            misil->setSpriteBullet(path);
            this->game->add_Item(misil,posX,posY);
            misil->moveTo(-angle,posX,posY);
            this->game->addItemToFollow(misil);
        }
    }else if(type==static_cast<int>(TypeObj::BANANA_M)){
        qDebug()<<"crear banana!!!!!!!!!!!";
        qDebug()<<"type:"<<type<<"id:"<<id<<"posx:"<<posX<<"posy:"<<posY<<"angle:"<<-angle;
        if(this->game->containsItem(type,id)){
            qDebug()<<"lo contiene";
            Items* item = this->game->getItem(type,id);
            MovableItem *i = static_cast<MovableItem*>(item);
            i->moveTo(-angle,posX,posY);
        }else{
            qDebug()<<"no contiene";
            Projectile *misil = new Projectile();
            misil->setIdObj(type);
            misil->setId(id);
            std::string path("../../images/banana.png");
            misil->setSpriteBullet(path);
            this->game->add_Item(misil,posX,posY);
            misil->moveTo(-angle,posX,posY);
            this->game->addItemToFollow(misil);
        }
    }
}



void GameClass::updatePlayer(int type, int id, int ammo, Worm_View *worm)
{
    if(type==2){
        this->myPlayer->addWeapon(id,ammo);
    }else if(type==3){
        this->myPlayer->setId(id);
    }else if(type==6){ //ganador creo
    }
}


Player *GameClass::getPlayer()
{
    return this->myPlayer;
}

Game_View *GameClass::getGameView()
{
    return this->game;
}


Worm_View* GameClass::getWormActive()
{
    return this->game->getWormActive();
}


std::vector<int> GameClass::fireWeapon()
{
    std::vector<int> vect;
    if(isMyTurn()){
        int idWeapon = this->game->getWormActive()->getWeaponId(); //devuelvo id negativo si no tengo arma seleccionada
        //int angle = this->game->getWormActive()->getTargetAngle();
        if(idWeapon<0 && !this->myPlayer->canFire(idWeapon)){
            qDebug()<<"entreeeeeeee";
            return vect; // lo devuelvo vacio
        }
        //puedo disparar el arma...

        this->myPlayer->fireWeapon(idWeapon); // genero bullet y disparo ... esto me tendria que devolver un id del bullet??

        std::pair<int,int> pos = this->game->getWormActive()->getDirWeapon();
        qDebug()<<"miraX:"<<pos.first<<"miraY:"<<pos.second;
        int time = this->game->getWormActive()->getTimeWeapon();
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
    }
    return vect;
}



bool GameClass::isMyTurn(){
    return this->myTurn;
}

void GameClass::removeItem(int type,int id)
{
    MovableItem* item = static_cast<MovableItem*>(this->game->getItem(type,id));
    Projectile *p = dynamic_cast<Projectile*>(item);
    if(p){
        p->explote();
        return;
    }
    item->setAlive(false);
    item->setVisibility(false);
    item->setSelect(false);
}



void GameClass::checkDeadItem()
{

    QGraphicsScene *scene = this->game->getScene();

    QList<QGraphicsItem*> list_items = scene->items();

    QList<QGraphicsItem*>::iterator it;
    for (it=list_items.begin();it!=list_items.end();it++)
    {

        Projectile* item =dynamic_cast<Projectile*>(*it);
        if(!item){// no es movible
            continue;
        }else if(!item->isAlive()){
            qDebug()<<"a remover proyectil type:"<<item->getIdObj()<<"id:"<<item->getId();
            scene->removeItem(item);
            //delete(item);
            qDebug()<<"ELIMINE ELEMENTO MUERTO !!!!!!!!!!!!!";
        }
    }
}





void GameClass::checkQueueEvent(QList<int> list)
{
    int cmd = list[0];
    qDebug()<<"gameclass comando:"<<cmd;
    if(cmd== static_cast<int>(Commands::GAME_END)){
       //terminar juego
        qDebug()<<"game end";
        this->myPlayer->setActive(false);
        this->myTurn=false;
    }else if(cmd==static_cast<int>(Commands::ATTACH_PLAYER_ID)){
        // asignar id del jugador
        qDebug()<<"attach player id event";
        this->updatePlayer(cmd,list[1]);
    }else if(cmd==static_cast<int>(Commands::ATTACH_USABLE_ID)){
        //agregar arma al player para que el worm pueda usar
        this->updatePlayer(cmd,list[1],list[2]);
    }else if(cmd==static_cast<int>(Commands::ACTUAL_PLAYER)){
        //mensaje con el id del jugador en turno
        qDebug()<<"actual player setting";
        checkRound(list[1],list[2]);
    }else if(cmd==static_cast<int>(Commands::ATTACH_WORM_ID)){
        // id del worm y su vida ... inicialmente en pos invalida, luego se mueve al recibir update
        this->attachWorm(static_cast<int>(TypeObj::WORM),list[1],list[2]);
    }else if(cmd==static_cast<int>(Commands::REMOVE)){
        // item a remover de la vista
        qDebug()<<"remove !!";
        this->removeItem(list[1],list[2]);
    }else if(cmd==static_cast<int>(Commands::POSITION)){
        // actual item position
        this->updateItem(list[1],list[2],list[3],list[4],list[5]);
    }else if(cmd==static_cast<int>(Commands::WINNER)){
        // hay ganador y es el id pasado
        qDebug()<<"winner leido!";
        this->myPlayer->setActive(false);
        this->myTurn=false;
    }else if(cmd==static_cast<int>(Commands::WORM_HEALTH)){
        qDebug()<<"recibi daño";
        this->recvWormHealth(list[1],list[2]);
    }

}


void GameClass::checkRound(int id,int id_worm){


    if(this->myPlayer->getId() != id){
        this->myTurn=false;
        this->myPlayer->setActive(false);
        Worm_View* worm = this->myPlayer->getWormActive();
        if(worm){
            worm->setSelect(false);
        }
        this->myPlayer->setWormActive(nullptr);
        return;
    }
    Items* i = this->game->getItem(static_cast<int>(TypeObj::WORM),id_worm);
    Worm_View* worm = static_cast<Worm_View*>(i);
    this->myTurn=true;
    this->myPlayer->setActive(true);
    worm->setSelect(true);
    QColor color = "black";
    worm->setColor(color);
    qDebug()<<"asdmsaldmk";
    this->myPlayer->setWormActive(worm);
    this->game->addItemToFollow(worm);

}


















