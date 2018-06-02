#include "gameclass.h"
#include "girder_view.h"

GameClass::GameClass(QRect screen,int w,int h)
{
    this->game = new Game_View(screen,w,h);
    std::string path(":/images/intro2.jpg");
    this->game->setBackground(path);
    this->myPlayer = new Player();
    this->queue = new QQueue<EventGame>();
    this->timer = new QTimer();
    this->timer->start(1);
    connect(this->timer,&QTimer::timeout,this,&GameClass::checkQueueEvent);
}



void GameClass::updateItem(int type, int id, int health, int posX, int posY, int angle)
{
    if(health!=-10 && type==0){
        //add vida
        qDebug()<<"type:"<<type<<"id"<<id;
        if(this->game->containsItem(type,id)){
            //contiene al worm
            qDebug()<<"contiene worm";
            Worm_View *worm = this->game->getItem(type,id);
            worm->setVida(health);
        }else{
            //no contiene al worm --> lo creo..
            qDebug()<<"no tengo worm, seteo vida y pos arbitraria";
            Worm_View *worm = new Worm_View();
            worm->setVida(health);
            worm->setId(id);
            worm->setIdObj(type);
            this->game->add_Item(worm,-100,-100); // -100 pos invalida, luego al recibir su pos lo ubico..
        }
    }else if(health==-10 && type==0){
        // add worm
        qDebug()<<"add worm";
        if(this->game->containsItem(type,id)){
            //contiene al worm --> lo muevo
            qDebug()<<"move worm";
            this->game->moveObjTo(id,posX,posY,angle);
        }else{
            qDebug()<<"pos worm sin vida";
            // no lo contiene lo tengo que agregar
            Worm_View* worm = new Worm_View();
            worm->setVida(100);//default...
            worm->setId(id);
            worm->setIdObj(type);
            worm->setAngle(angle);
            qDebug()<<"posX:"<<posX<<"posY:"<<posY;
            this->game->add_Item(worm,posX,posY);
            this->myPlayer->addWorm(worm);
//            if(id==0){
//                this->game->addWormActive(worm);
//            }
        }
    }else if(type==1 && health==-10){
        //es girder
        qDebug()<<"girder";
        if(!this->game->containsItem(type,id)){
            //no contiene girder...
            qDebug()<<"no contiene girder";
            Girder_View* girder = new Girder_View(angle,140);
            girder->setId(id);
            girder->setIdObj(type);
            this->game->add_Item(girder,posX,posY);
        }
    }
    //falta chequear si es un misil/proyectil...

}



void GameClass::updatePlayer(int type, int id, int ammo, Worm_View *worm)
{
    if(type==2){
        //set weapon to player to be usable
    }else if(type==3){
        qDebug()<<"entre";
        this->myPlayer->setId(id);
    }else if(type==6){
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


void GameClass::moveWorm(){
    this->game->moveObjTo(0,300,300,-45);
}



void GameClass::addEvent(EventGame event){
    this->queue->enqueue(event);
}


void GameClass::checkQueueEvent(){
    if(!this->queue->isEmpty()){
        EventGame e = this->queue->dequeue();

        if(e.typeEvent== static_cast<int>(TypeEvent::GAME_END)){
            qDebug()<<"game end";
            this->timer->stop();
        }else if(e.typeEvent==static_cast<int>(TypeEvent::ATTACH_PLAYER_ID)){
            qDebug()<<"attach player id event";
            this->updatePlayer(e.typeEvent,e.id);

        }else if(e.typeEvent==static_cast<int>(TypeEvent::ATTACH_USABLE_ID)){
            //add to player id , the weapon id and ammo
        }else if(e.typeEvent==static_cast<int>(TypeEvent::ACTUAL_PLAYER)){
            //enable player id to play
        }else if((e.typeEvent==static_cast<int>(TypeEvent::ATTACH_WORM_ID)) || (e.typeEvent==static_cast<int>(TypeEvent::POSITION))){
            qDebug()<<"update item";
            this->updateItem(e.typeObj,e.id,e.health,e.posX,e.posY,e.angle);
        }else if(e.typeEvent==static_cast<int>(TypeEvent::REMOVE)){
            //remove item
        }else if(e.typeEvent==static_cast<int>(TypeEvent::WINNER)){
            qDebug()<<"winner asoidaoisd";
            this->timer->stop();
        }


    }
}


