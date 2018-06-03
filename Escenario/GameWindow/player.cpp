#include "player.h"

Player::Player()
{
    it=this->worms_list.begin();
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
    if(it==this->worms_list.end()){
        it=this->worms_list.begin();
    }
    Worm_View* worm = (*it);
    it++;
    return worm;
}


