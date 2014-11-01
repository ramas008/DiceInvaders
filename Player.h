#ifndef PLAYER_H
#define PLAYER_H

#include "DiceInvaders.h"
#include "Rocket.h"

class Player
{
    public:
        Player(IDiceInvaders* sys);
        ~Player();

        int getHealth();
        void setHealth(int hp);
        void setScore(int sc);
        void update();
        void handleController();

        Rocket* rocket;
    protected:
    private:
        int health;
        int score;
        float horizontalPosition;
        float lastTime;
        IDiceInvaders* system;
        ISprite* sprite;
};

#endif // PLAYER_H
