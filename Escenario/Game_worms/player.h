#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "worm_view.h"

class Player
{
public:
    Player();
    void addWorm(Worm_View*worm);
    void setId(int id);
    int getId();
    Worm_View* getWormToPlay(); // me devuelve algun worm de la lista...
private:
    std::vector<Worm_View*> worms_list;
    int id;
    std::vector<Worm_View*>::iterator it;

};

#endif // PLAYER_H
