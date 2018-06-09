#include "player.h"
#include <QDebug>
Player::Player()
{
    this->it=0;
    this->wormActive=nullptr;
    this->myturn=false;
}

void Player::addWorm(Worm_View *worm)
{
    this->worms_list.push_back(worm);
}

void Player::setId(int id)
{
    this->id = id;
}

int Player::getId()
{
    return this->id;
}

Worm_View *Player::getWormToPlay()
{
    //qDebug()<<"pido worm para jugar";
    if(this->worms_list.empty()){
        qDebug()<<"lista vacia";
        return nullptr;
    }

    if(this->worms_list.size() == this->it){
        this->it=0;
    }
    //chequear si no esta vivo no devolverlo...
    this->wormActive = this->worms_list[this->it];
    this->it++;
    return this->wormActive;
}


Worm_View* Player::getWormActive(){
    //qDebug()<<"id worm activo player!!!!!!!!!!!"<<this->wormActive->getId();
    return this->wormActive;
}

bool Player::isActive(){
    return this->isactive;
}

void Player::setActive(bool active){
    this->isactive = active;
}

bool Player::isMyTurn()
{
    return this->myturn;
}

void Player::setTurn(bool turn)
{
    this->myturn=turn;
}

void Player::addWeapon(int type,int ammo)
{
    Weapon* weapon = new Weapon();
    weapon->setIdObj(type);
    if(ammo<0){
        weapon->setAmmo(9999);
    }else{
       weapon->setAmmo(ammo);
    }
    this->listWeapons.append(weapon);
}

bool Player::canFire(int type)
{
    QListIterator<Weapon*> Iter(this->listWeapons);
    while(Iter.hasNext())
    {
        Weapon* w =Iter.next();
        if(type==w->getIdObj() && w->getAmmo()>0){
            return true;
        }
    }
    return false;
}

void Player::fireWeapon(int type)
{
    QListIterator<Weapon*> Iter(this->listWeapons);
    while(Iter.hasNext())
    {
        Weapon* w =Iter.next();
        if(type==w->getIdObj() && w->getAmmo()>0){
            w->fire();
            return;
        }
    }
}
