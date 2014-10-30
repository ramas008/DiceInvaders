#ifndef PLAYER_H
#define PLAYER_H

#include "DiceInvaders.h"

class Player
{
    public:
        Player(IDiceInvaders* system, ISprite* sprite);
        virtual ~Player();

        int getHealth();
        void setHealth(int health);

        void updatePlayer();

    protected:
    private:
        int hp;
        float horizontalPosition;
        float lastTime;
        IDiceInvaders* playerSystem;
        ISprite* playerSprite;
};

#endif // PLAYER_H
