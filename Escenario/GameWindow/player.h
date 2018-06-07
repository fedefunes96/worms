#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "worm_view.h"
#include "weapon.h"
#include <QGraphicsScene>
#include "bazooka.h"
#include <QList>



enum class WeaponType : uint8_t {
    BAZOOKA_ID = 0,
    AIRMISIL_ID,
    BANANA_ID,
    MORTER_ID,
    BAT_ID,
    DINAMITE_ID,
    GRANADE_ID,
    FRAG_GRANADE_ID,
    HOLY_GRANADE_ID,
    TELEPORT_ID,
    PUNCH_ID
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
    void fireWeapon(int type, QGraphicsScene *scene, int angle, int posX, int posY);
    Worm_View *getWormActive();
    bool isActive();
    void setActive(bool active);
private:
    std::vector<Worm_View*> worms_list;
    int id;
    QList<Weapon*> listWeapons;
    Worm_View* wormActive;
    bool isactive;
    unsigned int it;

};

#endif // PLAYER_H
