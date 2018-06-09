#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "worm_view.h"
#include "weapon.h"
#include <QGraphicsScene>
#include <QList>



enum class WeaponsIds : uint8_t {
    BAZOOKA = 0,
    MORTAR,
    GREEN_GRENADE,
    RED_GRENADE,
    BANANA,
    HOLY_GRENADE,
    DYNAMITE,
    BASEBALL_BAT,
    AERIAL_ATTACK,
    TELEPORTATION
};

class Player
{
public:
    Player();
    void addWorm(Worm_View*worm);
    void setId(int id);
    int getId();
    Worm_View* getWormToPlay(); // me devuelve algun worm de la lista...
    void addWeapon(int type, int ammo);
    bool canFire(int type);
    void fireWeapon(int type);
    Worm_View *getWormActive();
    bool isActive();
    void setActive(bool active);
    bool isMyTurn();
    void setTurn(bool turn);
    std::vector<Worm_View *> getWormsAlive();
private:
    std::vector<Worm_View*> worms_list;
    int id;
    QList<Weapon*> listWeapons;
    Worm_View* wormActive;
    bool isactive;
    unsigned int it;
    bool myturn;

};

#endif // PLAYER_H
