#include "eventhandler.h"
#include <QDebug>
#include <QGraphicsView>
#include <QScrollBar>
EventHandler::EventHandler(QObject *parent) : QObject(parent)
{
    this->keyPress=false;
}

EventHandler::EventHandler(QObject *parent,Game_View* game_view) : QObject(parent), game_view(game_view)
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

    if(event->type() == QEvent::MouseButtonPress){
        mouseClickEvent(static_cast<QMouseEvent*>(event));
        return true;

    }
*/
    return false;
}

void EventHandler::mouseMoveEvent(QMouseEvent *m_event)
{
    qDebug()<<"posx:"<<m_event->x()<<"   posy:"<<m_event->y();
    Camera* view = this->game_view->getCamera();
    if(m_event->x() >= 757)//move_der cam
    {
        int width = this->game_view->getCamera()->width();
        qDebug()<<"mov_der";
        int y = this->game_view->getCamera()->horizontalScrollBar()->value();
        qDebug()<<y;
        if(!(y+10>=width)){
            view->horizontalScrollBar()->setValue( view->horizontalScrollBar()->value() + 10 );
        }

    }
    if(m_event->x() <= 10)//mov_izq cam
    {
        qDebug()<<"mov_izq";
        int y = this->game_view->getCamera()->horizontalScrollBar()->value();
        qDebug()<<y;
        if(!(y-10<0)){
            view->horizontalScrollBar()->setValue( view->horizontalScrollBar()->value() - 10 );
        }
    }


}

void EventHandler::mouseClickEvent(QMouseEvent *m_event)
{
    if( m_event->button() ==  Qt::LeftButton)
    {
        int x = this->game_view->getCamera()->verticalScrollBar()->value();
        int y = this->game_view->getCamera()->horizontalScrollBar()->value();
        qDebug()<<"left click";
        qDebug()<<"vertical valx:"<<x <<"vertical valy:"<<y;
        qDebug()<<"Mvalx:"<<m_event->x() <<" Mvaly:"<<m_event->y();
        if(!(this->game_view->itemAt(m_event->x(),m_event->y())))
        {
            qDebug()<<"no hay worm";
            return;
        }
        //this->view->itemAt() aca me devuelve el QgraphicsItem si yo le paso por parametro las posiciones ..
        if((this->game_view->itemAt(m_event->x(),m_event->y()))->type()==Worm_View().type())
        {
            qDebug()<<"toque al worm";
            Worm_View* worm = static_cast<Worm_View*>(this->game_view->itemAt(m_event->x(),m_event->y()));
            worm->setSelected(true);
            worm->setZValue(1);
            if(this->worm_selected){
                this->worm_selected->setSelected(false);
                this->worm_selected->setZValue(0);
            }
            this->worm_selected = worm;
        }
    }
    if( m_event->button() ==  Qt::RightButton)
    {
        qDebug()<<"right click";
    }
}

void EventHandler::keyPressEvent(QKeyEvent *k_event)
{
    if(k_event->isAutoRepeat()){
        return;
    }
    switch(k_event->key()) {
        case Qt::Key_Space:
        {
            qDebug() << "Espacio"; //JUMP worm
            if(this->game_view->getWormActive()==nullptr){
                qDebug()<<"null pointer";
                return;
            }
            this->game_view->getWormActive()->throwProjectile();
            break;
        }
        case Qt::Key_Left:
        {
            keyPress = true;
            qDebug() << "Left"; //moveLeft worm

            if(this->game_view->getWormActive()==nullptr){
                qDebug()<<"null pointer";
                return;
            }
            //this->game_view->getWormActive()->step();
            //this->game_view->getWormActive()->move_Left();

            break;
        }
        case Qt::Key_Right:
        {
            qDebug() << "Right";//moveRight worm
            if(this->game_view->getWormActive()==nullptr){
                qDebug()<<"null pointer";
                return;
            }
            break;
        }
        case Qt::Key_Up:
        {
            qDebug() << "Up";  //lookUp aim
            if(this->game_view->getWormActive()==nullptr){
                qDebug()<<"null pointer";
                return;
            }
            break;
        }
        case Qt::Key_Down:
        {
            qDebug() << "Down";//lookDown aim
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
            if(this->game_view->getWormActive()==nullptr){
                qDebug()<<"null pointer";
                return;
            }
            Worm_View* w = this->game_view->getWormActive();
            w->moveToPos(w->x()-30,w->y());
            break;
        }
        case Qt::Key_Right:
        {
            if(k_event->isAutoRepeat()){ // para saber si es repetitiva
                return;
            }
            qDebug()<<"solte tecla der";
            if(this->game_view->getWormActive()==nullptr){
                qDebug()<<"null pointer";
                return;
            }
            Worm_View* w = this->game_view->getWormActive();
            w->moveToPos(w->x()+30,w->y());
            break;
        }
        case Qt::Key_Up:
        {
            if(k_event->isAutoRepeat()){ // para saber si es repetitiva
                return;
            }
            qDebug()<<"solte tecla up";
            if(this->game_view->getWormActive()==nullptr){
                qDebug()<<"null pointer";
                return;
            }
            Worm_View* w = this->game_view->getWormActive();
            //w->moveToPos(w->x()-21,w->y()-7);
            w->moveToPos(w->x()-30,w->y()-30);
            break;
        }
        case Qt::Key_Space:
        {
            if(k_event->isAutoRepeat()){ // para saber si es repetitiva
                return;
            }
            qDebug()<<"solte Espacio";
        }
    default:
        break;
    }
}

