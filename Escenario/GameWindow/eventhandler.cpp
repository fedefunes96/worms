#include "eventhandler.h"
#include <QDebug>
#include <QGraphicsView>
#include <QScrollBar>

#include "protocol.h"
#include "girder_view.h"

EventHandler::EventHandler(QObject *parent) : QObject(parent)
{
    this->keyPress=false;
}

EventHandler::EventHandler(QObject *parent, GameClass *game, Protocol* protocol) : QObject(parent), game(game), protocol(protocol)
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
    Worm_View* worm = this->game->getWormActive();
    if(worm==nullptr){
        return;
    }
    int idWeapon = worm->getWeaponId();
    if(idWeapon==static_cast<int>(UsableIds::AERIAL_ATTACK)||
            idWeapon==static_cast<int>(UsableIds::TELEPORTATION)){
        std::vector<int> vect = this->game->fireWeapon();
        if(vect.empty()){
            qDebug()<<"vector vacio --> no arma seleccionada o disponible";
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
            qDebug()<<"aprete espacio!!!!!!!!!!!!!!!";
            this->power=10;
            break;
        }

        case Qt::Key_Left:
        {
            if(k_event->isAutoRepeat()){
                return;
            }
            keyPress = true;
            qDebug() << "Left"; //moveLeft worm
            this->protocol->sendMove(2);
            /*
            if(!this->game->isMyTurn()){
                qDebug()<<"no es mi turno";
                return;
            }
*/
            Worm_View* worm = this->game->getWormActive();
            if(worm==nullptr){
                qDebug()<<"worm nulo";
                return;
            }
            worm->setAngle(-180);
            this->protocol->sendMove(2);
            qDebug()<< "id worm a mover:"<<worm->getId();
            break;
        }
        case Qt::Key_Right:
        {
            if(k_event->isAutoRepeat()){
                return;
            }

            //qDebug() << "Right";//moveRight worm
            if(!this->game->isMyTurn()){
                return;
            }

            Worm_View* worm = this->game->getWormActive();
            if(worm==nullptr){
                return;
            }
            worm->setAngle(0);
            this->protocol->sendMove(1);
            break;
        }
        case Qt::Key_Up:
        {
            qDebug() << "Up";  //lookUp aim
            if(!this->game->isMyTurn()){
                return;
            }

            Worm_View* worm = this->game->getWormActive();
            if(worm==nullptr){
                return;
            }
            worm->movTargetAngle(1);
            break;
        }
        case Qt::Key_Down:
        {
            qDebug() << "Down";//lookDown aim
            if(!this->game->isMyTurn()){
                return;
            }

            Worm_View* worm = this->game->getWormActive();
            if(worm==nullptr){
                return;
            }
            worm->movTargetAngle(-1);
            break;
        }

        case Qt::Key_Return:
        {
            if(k_event->isAutoRepeat()){
                return;
            }

            qDebug() << "Enter!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";//moveRight worm
            if(!this->game->isMyTurn()){
                return;
            }

            Worm_View* worm = this->game->getWormActive();
            if(worm==nullptr){
                return;
            }
            worm->setAngle(worm->getAngle());
            this->protocol->sendMove(3);
            break;
        }

        case Qt::Key_Backspace:
        {
            if(k_event->isAutoRepeat()){
                return;
            }

            qDebug() << "backSpace";//moveRight worm
            if(!this->game->isMyTurn()){
                return;
            }

            Worm_View* worm = this->game->getWormActive();
            if(worm==nullptr){
                return;
            }
            worm->setAngle(worm->getAngle());
            this->protocol->sendMove(4);
            break;
        }

        case Qt::Key_1:
        {
            if(k_event->isAutoRepeat()){
                return;
            }
            if(!this->game->isMyTurn()){
                return;
            }
            Worm_View* worm = this->game->getWormActive();
            if(worm==nullptr){
                return;
            }
            worm->setTimeWeapon(1);
            break;
        }
        case Qt::Key_2:
        {
            if(k_event->isAutoRepeat()){
                return;
            }
            if(!this->game->isMyTurn()){
                return;
            }

            Worm_View* worm = this->game->getWormActive();
            if(worm==nullptr){
                return;
            }
            worm->setTimeWeapon(2);
            break;

        }
        case Qt::Key_3:
        {
            if(k_event->isAutoRepeat()){
                return;
            }
            if(!this->game->isMyTurn()){
                return;
            }

            Worm_View* worm = this->game->getWormActive();
            if(worm==nullptr){
                return;
            }
            worm->setTimeWeapon(3);
            break;

        }
        case Qt::Key_4:
        {
            if(k_event->isAutoRepeat()){
                return;
            }
            if(!this->game->isMyTurn()){
                return;
            }

            Worm_View* worm = this->game->getWormActive();
            if(worm==nullptr){
                return;
            }
            worm->setTimeWeapon(4);
            break;

        }
        case Qt::Key_5:
        {
            if(k_event->isAutoRepeat()){
                return;
            }
            if(!this->game->isMyTurn()){
                return;
            }

            Worm_View* worm = this->game->getWormActive();
            if(worm==nullptr){
                return;
            }
            worm->setTimeWeapon(5);
            break;
        }
        default:
        {
            qDebug() << "Unhandled"; //sin definir aun
            break;
        }
    }
}


void EventHandler::keyReleaseEvent(QKeyEvent *k_event)
{

    switch (k_event->key()) {
        case Qt::Key_Left:
        {
            if(k_event->isAutoRepeat()){ // para saber si es repetitiva
                return;
            }
            qDebug()<<"solte tecla izq";
            if(!this->game->isMyTurn()){
                return;
            }

            Worm_View* worm = this->game->getWormActive();
            if(worm==nullptr){
                return;
            }
            this->protocol->sendMove(0);
            break;
        }
        case Qt::Key_Right:
        {
            if(k_event->isAutoRepeat()){ // para saber si es repetitiva
                return;
            }
            qDebug()<<"solte tecla der";
            if(!this->game->isMyTurn()){
                return;
            }

            Worm_View* worm = this->game->getWormActive();
            if(worm==nullptr){
                return;
            }
            this->protocol->sendMove(0);
            break;
        }

        case Qt::Key_Space:
        {
            if(k_event->isAutoRepeat()){ // para saber si es repetitiva
                if(this->power<100){
                    qDebug()<< "power:"<<this->power;
                    this->power+=10;
                }
                break;
            }
            if(this->game->isMyTurn()){
                std::vector<int> vect = this->game->fireWeapon();

                if(vect.empty()){
                    qDebug()<<"vector vacio --> no arma seleccionada o disponible";
                    return;
                }
                std::vector<int> vect2;
                if(vect[0]==static_cast<int>(UsableIds::BANANA)||
                        vect[0]==static_cast<int>(UsableIds::BAZOOKA)||
                        vect[0]==static_cast<int>(UsableIds::GREEN_GRENADE)||
                        vect[0]==static_cast<int>(UsableIds::HOLY_GRENADE)||
                        vect[0]==static_cast<int>(UsableIds::MORTAR)||
                        vect[0]==static_cast<int>(UsableIds::RED_GRENADE)){
                    vect2.push_back(this->power);
                }
                if(vect.size()==4){
                    vect2.push_back(vect[3]);
                }
                protocol->sendAttack(vect[0],vect[1],vect[2],vect2);
                qDebug()<<"dispare! event";
            }
            qDebug()<<"solte Espacio";
            break;
        }

        case Qt::Key_Return:
        {
            if(k_event->isAutoRepeat()){
                return;
            }

            qDebug() << "solte Enter";//moveRight worm
            if(!this->game->isMyTurn()){
                return;
            }

            Worm_View* worm = this->game->getWormActive();
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

            qDebug() << "solte backSpace";//moveRight worm
            if(!this->game->isMyTurn()){
                return;
            }

            Worm_View* worm = this->game->getWormActive();
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

