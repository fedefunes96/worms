#include "player.h"
#include <QDebug>


Player::Player()
{
    this->it=0;
    this->wormActive=nullptr;
}


Player::~Player()
{
    for (int var = 0; var < this->listWeapons.size(); ++var) {
        delete(this->listWeapons[var]);
    }
}


void Player::addWorm(Worm_View *worm)
{
    this->worms_list.push_back(worm);
}

void Player::setColor(QString color){
    this->color = color;
}

QString Player::getColor()
{
    return this->color;
}

void Player::setId(int id)
{
    this->id = id;
}

int Player::getId()
{
    return this->id;
}

void Player::setWormActive(Worm_View* worm)
{
    this->wormActive = worm;
}

Worm_View* Player::getWormActive(){
    if(!this->wormActive){
        return nullptr;
    }
    if(!this->wormActive->isAlive()){
        return nullptr;
    }
    return this->wormActive;
}

bool Player::isActive(){
    return this->isactive;
}

void Player::setActive(bool active){
    this->isactive = active;
}


void Player::addWeapon(int type,int ammo)
{
    Weapon* weapon = new Weapon();
    weapon->setIdObj(type);
    weapon->setAmmo(ammo);
    this->listWeapons.append(weapon);
}

bool Player::canFire(int type)
{
    QListIterator<Weapon*> Iter(this->listWeapons);
    while(Iter.hasNext())
    {
        Weapon* w =Iter.next();
        if(type==w->getIdObj()){
            if(w->getAmmo()>0){
                return true;
            }else if(w->getAmmo()==-1){
                return true;
            }
        }
    }
    return false;
}


int Player::getAmmo(int id)
{
    QListIterator<Weapon*> Iter(this->listWeapons);
    while(Iter.hasNext())
    {
        Weapon* w =Iter.next();
        if(id==w->getIdObj()){
            return w->getAmmo();
        }
    }
    return 0;
}

void Player::fireWeapon(int type)
{
    QListIterator<Weapon*> Iter(this->listWeapons);
    while(Iter.hasNext())
    {
        Weapon* w =Iter.next();
        if(type==w->getIdObj() && (w->getAmmo()>0 || w->getAmmo()==-1) ){
            w->fire();
            return;
        }
    }
}



int Player::getPoints()
{
    int result=0;
    for (unsigned int var = 0; var < this->worms_list.size(); ++var) {
        result += (this->worms_list[var]->getHealth());
    }
    return result;
}


std::vector<Worm_View*> Player::getWormsAlive()
{
    std::vector<Worm_View*> lista;
    for (unsigned int var = 0; var < this->worms_list.size(); ++var) {
        if(this->worms_list[var]->isAlive()){
            lista.push_back(this->worms_list[var]);
        }
    }
    return lista;
}


