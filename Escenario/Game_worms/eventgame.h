#ifndef EVENTGAME_H
#define EVENTGAME_H

enum class TypeEvent : int{
    POSITION = 0,
    ATTACH_WORM_ID,
    ATTACH_USABLE_ID,
    ATTACH_PLAYER_ID,
    REMOVE,
    GAME_END,
    ACTUAL_PLAYER,
    WINNER,
    MOVE,
    ATTACK
};

class EventGame
{
public:
    EventGame();
    int typeEvent;
    int typeObj;
    int id;
    int health;
    int posX;
    int posY;
    int ammo;
    int angle;

};

#endif // EVENTGAME_H
