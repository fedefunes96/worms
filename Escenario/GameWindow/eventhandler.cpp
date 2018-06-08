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
    if(event->type() == QEvent::MouseMove){
        mouseMoveEvent(static_cast<QMouseEvent*>(event));
        return true;
    }
*/


    // SOLUCIONAR!!!!!!!!! , capaz captar signal click del mouse y conectar...
/*    if(event->type() == QEvent::MouseButtonPress){
        mouseClickEvent(static_cast<QMouseEvent*>(event));
        return true;
        if(this->game->isMyTurn()){
            this->game->getWormActive()->hasClickeableTarget();
            mouseClickEvent(static_cast<QMouseEvent*>(event));
            return true;
        }
    }
*/

    return false;
}

void EventHandler::mouseMoveEvent(QMouseEvent *m_event)
{
    qDebug()<<"posx:"<<m_event->x()<<"   posy:"<<m_event->y();
    /*
    Camera* view = this->game->getCamera();
    if(m_event->x() >= 757)//move_der cam
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
*/

}

void EventHandler::mouseClickEvent(QMouseEvent *m_event)
{
/*
    if( m_event->button() ==  Qt::LeftButton)
    {
        int x = this->game->getCamera()->verticalScrollBar()->value();
        int y = this->game->getCamera()->horizontalScrollBar()->value();
        qDebug()<<"left click";
        qDebug()<<"vertical valx:"<<x <<"vertical valy:"<<y;
        qDebug()<<"Mvalx:"<<m_event->x() <<" Mvaly:"<<m_event->y();
//        if(!(this->game->itemAt(m_event->x(),m_event->y())))
//        {
//            qDebug()<<"no hay worm";
//            return;
//        }
        //this->view->itemAt() aca me devuelve el QgraphicsItem si yo le paso por parametro las posiciones ..

        std::pair<int,int>pos= this->game->getCamera()->getPosButton();
        if(m_event->x()>=pos.first && m_event->x()<pos.first+30 && m_event->y()>=pos.second && m_event->y()<pos.second+30){
            this->game->getCamera()->handleButton();
        }


    }
    */
}







void EventHandler::keyPressEvent(QKeyEvent *k_event)
{
    switch(k_event->key()) {
        case Qt::Key_Space:
        {
            if(k_event->isAutoRepeat()){
                return;
            }
            qDebug() << "Espacio"; //JUMP worm
            if(this->game->isMyTurn()){
                std::vector<int> vect = this->game->fireWeapon();
                
                if(vect.empty()){
                    qDebug()<<"vector vacio --> no arma seleccionada o disponible";
                    return;
                }
                //std::vector<int> vect2;
                protocol->sendAttack(vect[0],vect[1],vect[2],vect[3]);
                qDebug()<<"dispare! event";
            }
            break;
        }
        case Qt::Key_M:
        {
            if(!this->game->isMyTurn()){
                return;
            }
            this->game->getCamera()->handleButton();
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
                return;
            }

            Worm_View* worm = this->game->getWormActive();
            //qDebug()<<"id worm a mover:"<<worm->getId();
            worm->setAngle(-180);
            this->protocol->sendMove((int8_t)worm->getId(),2);
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
            worm->setAngle(0);
            this->protocol->sendMove(worm->getId(),1);
            break;
        }
        case Qt::Key_Up:
        {
            qDebug() << "Up";  //lookUp aim
            if(!this->game->isMyTurn()){
                return;
            }

            Worm_View* worm = this->game->getWormActive();
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
            this->protocol->sendMove(worm->getId(),3);
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
            this->protocol->sendMove(worm->getId(),4);
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
            this->protocol->sendMove(worm->getId(),0);
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
            this->protocol->sendMove(worm->getId(),0);
            break;
        }

        case Qt::Key_Space:
        {
            if(k_event->isAutoRepeat()){ // para saber si es repetitiva
                return;
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
            this->protocol->sendMove(worm->getId(),0);
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
            this->protocol->sendMove(worm->getId(),0);
            break;
        }




    default:
        break;
    }
}

