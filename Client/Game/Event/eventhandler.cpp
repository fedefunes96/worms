#include "eventhandler.h"
#include <QDebug>
#include <QGraphicsView>
#include <QScrollBar>

#include "protocol.h"
#include "girder_view.h"
#include <QMessageBox>

EventHandler::EventHandler(QObject *parent) : QObject(parent)
{
    this->keyPress=false;
}

EventHandler::EventHandler(QObject *parent, Game *game, Protocol* protocol) : QObject(parent), game(game), protocol(protocol)
{
    this->worm_selected = nullptr;
    this->power=10;
    connect(game->getCamera(),SIGNAL(mouseClick()),this,SLOT(fireWithClick()));
}

bool EventHandler::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress){
        keyPressEvent(static_cast<QKeyEvent *>(event));
        return true;
    }

    if(event->type() == QEvent::KeyRelease)
    {
        keyReleaseEvent(static_cast<QKeyEvent*>(event));
        return true;
    }
    return false;
}

void EventHandler::fireWithClick()
{
    Worm_View* worm = this->game->getPlayer()->getWormActive();
    if(worm==nullptr){
        return;
    }
    int idWeapon = worm->getWeaponId();
    if(idWeapon==static_cast<int>(UsableIds::AERIAL_ATTACK)||
            idWeapon==static_cast<int>(UsableIds::TELEPORTATION)){
        std::vector<int> vect = this->game->fireWeapon();
        if(vect.empty()){
            return;
        }
        std::vector<int> vect2;
        protocol->sendAttack(vect[0],vect[1],vect[2],vect2);
    }
}



void EventHandler::keyPressEvent(QKeyEvent *k_event)
{
    switch(k_event->key()) {
        case Qt::Key_Space:
        {
            if(k_event->isAutoRepeat()){
                return;
            }
            this->power=1;
            this->game->getCamera()->setFreeMove(false);
            this->game->setRefocus(false);
            break;
        }

        case Qt::Key_Left:
        {
            if(k_event->isAutoRepeat()){
                return;
            }
            keyPress = true;
            if(!this->game->isMyTurn()){
                return;
            }
            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                return;
            }
            this->protocol->sendMove(2);
            this->game->getCamera()->setFreeMove(false);
            this->game->setRefocus(false);
            break;
        }
        case Qt::Key_Right:
        {
            if(k_event->isAutoRepeat()){
                return;
            }
            if(!this->game->isMyTurn()){
                return;
            }
            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                return;
            }
            this->protocol->sendMove(1);
            this->game->getCamera()->setFreeMove(false);
            this->game->setRefocus(false);
            break;
        }
        case Qt::Key_Up:
        {
            if(!this->game->isMyTurn()){
                return;
            }
            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                return;
            }
            worm->movTargetAngle(1);
            this->game->getCamera()->setFreeMove(false);
            this->game->setRefocus(false);
            break;
        }
        case Qt::Key_Down:
        {
            if(!this->game->isMyTurn()){
                return;
            }
            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                return;
            }
            worm->movTargetAngle(-1);
            this->game->getCamera()->setFreeMove(false);
            this->game->setRefocus(false);
            break;
        }

        case Qt::Key_Return:
        {
            if(k_event->isAutoRepeat()){
                return;
            }
            if(!this->game->isMyTurn()){
                return;
            }
            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                return;
            }
            this->protocol->sendMove(3);
            this->game->getCamera()->setFreeMove(false);
            this->game->setRefocus(false);
            break;
        }

        case Qt::Key_Backspace:
        {
            if(k_event->isAutoRepeat()){
                return;
            }
            if(!this->game->isMyTurn()){
                return;
            }
            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                return;
            }
            this->protocol->sendMove(4);
            this->game->getCamera()->setFreeMove(false);
            this->game->setRefocus(false);
            break;
        }

        default:
        {
            break;
        }
    }
}


void EventHandler::keyReleaseEvent(QKeyEvent *k_event)
{

    switch (k_event->key()) {
        case Qt::Key_Left:
        {
            if(k_event->isAutoRepeat()){
                return;
            }
            if(!this->game->isMyTurn()){
                return;
            }

            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                return;
            }
            this->protocol->sendMove(0);
            break;
        }
        case Qt::Key_Right:
        {
            if(k_event->isAutoRepeat()){
                return;
            }
            if(!this->game->isMyTurn()){
                return;
            }
            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                return;
            }
            this->protocol->sendMove(0);
            break;
        }

        case Qt::Key_Space:
        {
            if(k_event->isAutoRepeat()){
                this->game->setPotBar(this->power);
                if(this->power<100){
                    this->power+=3;
                }
                break;
            }
            if(this->game->isMyTurn()){
                if(this->game->getPlayer()->getWormActive()==nullptr){
                    return;
                }
                int idWeapon = this->game->getPlayer()->getWormActive()->getWeaponId();
                if(idWeapon==static_cast<int>(UsableIds::TELEPORTATION)||
                        idWeapon==static_cast<int>(UsableIds::AERIAL_ATTACK)){
                    return;
                }
                std::vector<int> vect = this->game->fireWeapon();
                if(vect.empty()){
                    return;
                }
                std::vector<int> vect2;
                if(vect[0]==static_cast<int>(UsableIds::BANANA)||
                        vect[0]==static_cast<int>(UsableIds::BAZOOKA)||
                        vect[0]==static_cast<int>(UsableIds::GREEN_GRENADE)||
                        vect[0]==static_cast<int>(UsableIds::HOLY_GRENADE)||
                        vect[0]==static_cast<int>(UsableIds::MORTAR)||
                        vect[0]==static_cast<int>(UsableIds::RED_GRENADE)){
                    if(this->power>100){
                        vect2.push_back(100);
                    }else{
                        vect2.push_back(this->power);
                    }
                }
                if(vect.size()==4){
                    vect2.push_back(vect[3]);
                }
                protocol->sendAttack(vect[0],vect[1],vect[2],vect2);
            }
            break;
        }

        case Qt::Key_Return:
        {
            if(k_event->isAutoRepeat()){
                return;
            }
            if(!this->game->isMyTurn()){
                return;
            }
            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                return;
            }
            this->protocol->sendMove(0);
            break;
        }

        case Qt::Key_Backspace:
        {
            if(k_event->isAutoRepeat()){
                return;
            }
            if(!this->game->isMyTurn()){
                return;
            }
            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                return;
            }
            this->protocol->sendMove(0);
            break;
        }

        default:
            break;
    }
}

