#include "gameclass.h"
#include "girder_view.h"
#include <QDebug>
#include "misilBazooka.h"
GameClass::GameClass(QRect screen,int w,int h)
{
    this->game = new Game_View(screen,w,h);
    std::string path("../../images/intro2.jpg");
    this->game->setBackground(path);
    this->myTurn=true;
    this->myPlayer = new Player();
    this->game->addPlayerActive(this->myPlayer);
}

Camera* GameClass::getCamera()
{
    return this->game->getCamera();
}

void GameClass::connectController(Controler *controler)
{
    connect(controler,SIGNAL(eventCreated(QList<int>)),this,SLOT(checkQueueEvent(QList<int>)));
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
        qDebug()<<"type:"<<type<<"id:"<<id<<"posx:"<<posX<<"posy:"<<posY;
        if(this->game->containsItem(type,id)){
            qDebug()<<"lo contiene";
            Items* item = this->game->getItem(type,id);
            MovableItem *i = static_cast<MovableItem*>(item);
            i->moveTo(angle,posX,posY);
        }else{
            qDebug()<<"no contiene";
            MisilBazooka *misil = new MisilBazooka();
            misil->setIdObj(type);
            misil->setId(id);
            this->game->add_Item(misil,posX,posY);
            misil->moveTo(angle,posX,posY);
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

        //std::pair<int,int> posW = this->game->getWormActive()->getDir();
        this->myPlayer->fireWeapon(idWeapon); // genero bullet y disparo ... esto me tendria que devolver un id del bullet??

        int id = this->game->getWormActive()->getId();
        std::pair<int,int> pos = this->game->getWormActive()->getDirWeapon();
        qDebug()<<"miraX:"<<pos.first<<"miraY:"<<pos.second;
        //int timeW = this->game->getWormActive()->getTimeWeapon();
        vect.push_back(idWeapon);
        vect.push_back(id);
        vect.push_back(pos.first);
        vect.push_back(pos.second);
        //vect.push_back(timeW);
        //falta el power que esta en el release
    }
    return vect;
}



bool GameClass::isMyTurn(){
    return this->myTurn;
}

void GameClass::removeItem(int type,int id)
{
    MovableItem* item = static_cast<MovableItem*>(this->game->getItem(type,id));
    item->setVisibility(false);
}

void GameClass::checkQueueEvent(QList<int> list)
{
    int cmd = list[0];
    qDebug()<<cmd;
    if(cmd== static_cast<int>(Commands::GAME_END)){
       //terminar juego
        qDebug()<<"game end";
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
        checkRound(list[1]);
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
    }

}


void GameClass::checkRound(int id){
    if(this->myPlayer->getId() != id){
        this->myTurn=false;
        this->myPlayer->getWormActive()->setSelect(false);
        this->myPlayer->setActive(false);
        return;
    }
    this->myTurn=true;
    Worm_View* worm = this->myPlayer->getWormToPlay();    
    this->myPlayer->setActive(true);
    this->game->addItemToFollow(worm);
}


















