#ifndef PLAYER_H
#define PLAYER_H

#include "DiceInvaders.h"

class Player
{
    public:
        Player(IDiceInvaders* sys);
        ~Player();

        int getHealth();
        void setHealth(int hp);

        void update();
    protected:
    private:
        int health;
        float horizontalPosition;
        float lastTime;
        IDiceInvaders* system;
        ISprite* sprite;
};

#endif // PLAYER_H
