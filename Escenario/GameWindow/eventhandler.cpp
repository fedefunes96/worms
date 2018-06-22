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
/*
    if(this->game->isMyTurn()){
        if(event->type() == QEvent::MouseMove){
               mouseMoveEvent(static_cast<QMouseEvent*>(event));
               return true;
           }
    }
    */
    return false;
}

/*
oid EventHandler::mouseMoveEvent(QMouseEvent *m_event)
{
    qDebug()<<"posx:"<<m_event->x()<<"   posy:"<<m_event->y();

    Camera* view = this->game->getCamera();
    if(m_event->x() >= (view->width()-100))//move_der cam
    {
        int width = this->game->getCamera()->width();
        qDebug()<<"mov_der";
        int y = this->game->getCamera()->horizontalScrollBar()->value();
        qDebug()<<y;
        if(!(y+10>=width)){
            view->horizontalScrollBar()->setValue( view->horizontalScrollBar()->value() + 10 );
        }

    }
    if(m_event->x() <= 10)//mov_izq cam
    {
        qDebug()<<"mov_izq";
        int y = this->game->getCamera()->horizontalScrollBar()->value();
        qDebug()<<y;
        if(!(y-10<0)){
            view->horizontalScrollBar()->setValue( view->horizontalScrollBar()->value() - 10 );
        }
    }

}

*/




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
            //qDebug()<<"aprete espacio!!!!!!!!!!!!!!!";
            this->power=1;
            this->game->getCamera()->setFreeMove(false);
            break;
        }

        case Qt::Key_Left:
        {
            if(k_event->isAutoRepeat()){
                return;
            }
            keyPress = true;
            qDebug() << "Left"; //moveLeft worm

            if(!this->game->isMyTurn()){
                //qDebug()<<"no es mi turno";
                return;
            }
            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                //qDebug()<<"worm nulo";
                return;
            }
            this->protocol->sendMove(2);
            this->game->getCamera()->setFreeMove(false);
            //qDebug()<< "id worm a mover:"<<worm->getId();
            break;
        }
        case Qt::Key_Right:
        {
            if(k_event->isAutoRepeat()){
                return;
            }

            qDebug() << "Right";//moveRight worm
            if(!this->game->isMyTurn()){
                return;
            }

            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                return;
            }
            this->protocol->sendMove(1);
            this->game->getCamera()->setFreeMove(false);
            break;
        }
        case Qt::Key_Up:
        {
            qDebug() << "Up";  //lookUp aim
            if(!this->game->isMyTurn()){
                return;
            }

            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                return;
            }
            worm->movTargetAngle(1);
            this->game->getCamera()->setFreeMove(false);
            break;
        }
        case Qt::Key_Down:
        {
            qDebug() << "Down";//lookDown aim
            if(!this->game->isMyTurn()){
                return;
            }

            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                return;
            }
            worm->movTargetAngle(-1);
            this->game->getCamera()->setFreeMove(false);
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

            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                return;
            }
            //worm->setAngle(worm->getAngle());
            this->protocol->sendMove(3);
            this->game->getCamera()->setFreeMove(false);
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

            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                return;
            }
            //worm->setAngle(worm->getAngle());
            this->protocol->sendMove(4);
            this->game->getCamera()->setFreeMove(false);
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
            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                return;
            }
            if(!worm->isWeaponCtD()){
                return;
            }
            worm->setTimeWeapon(1);
            //QMessageBox::information("Set weapon countdown","Countdown = 1.");
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

            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                return;
            }
            if(!worm->isWeaponCtD()){
                return;
            }
            worm->setTimeWeapon(2);
            //QMessageBox::information(this,"Set weapon countdown","Countdown = 2.");
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

            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                return;
            }
            if(!worm->isWeaponCtD()){
                return;
            }
            worm->setTimeWeapon(3);
            //QMessageBox::information(this,"Set weapon countdown","Countdown = 3.");
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

            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                return;
            }
            if(!worm->isWeaponCtD()){
                return;
            }
            worm->setTimeWeapon(4);
            //QMessageBox::information(this,"Set weapon countdown","Countdown = 4.");
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

            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                return;
            }
            if(!worm->isWeaponCtD()){
                return;
            }
            worm->setTimeWeapon(5);
            //QMessageBox::information(this,"Set weapon countdown","Countdown = 5.");
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

            Worm_View* worm = this->game->getPlayer()->getWormActive();
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

            Worm_View* worm = this->game->getPlayer()->getWormActive();
            if(worm==nullptr){
                return;
            }
            this->protocol->sendMove(0);
            break;
        }

        case Qt::Key_Space:
        {
            if(k_event->isAutoRepeat()){ // para saber si es repetitiva
                this->game->setPotBar(this->power);
                if(this->power<100){
                    //qDebug()<< "power:"<<this->power;
                    this->power+=3;
                }
                break;
            }
            if(this->game->isMyTurn()){
                int idWeapon = this->game->getPlayer()->getWormActive()->getWeaponId();
                if(idWeapon==static_cast<int>(UsableIds::TELEPORTATION)||
                        idWeapon==static_cast<int>(UsableIds::AERIAL_ATTACK)){
                    return;
                }
                std::vector<int> vect = this->game->fireWeapon();

                if(vect.empty()){
                    //qDebug()<<"vector vacio --> no arma seleccionada o disponible";
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
                //qDebug()<<"dispare! event";
            }
            //qDebug()<<"solte Espacio";
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

            qDebug() << "solte backSpace";//moveRight worm
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

