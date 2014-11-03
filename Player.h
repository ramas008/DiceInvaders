#ifndef PLAYER_H
#define PLAYER_H

#include "DiceInvaders.h"
#include "Rocket.h"
#include "Vec2.h"

class Player
{
    public:
        Player(IDiceInvaders* sys);
        ~Player();

        Vec2 getPosition();
        Vec2 getRocketPosition();
        bool hasRocket();
        int getHealth();
        int getScore();

        void setHealth(int hp);
        void setScore(int sc);
        void deleteRocket();
        void update();
        void handleController();
    protected:
    private:
        Vec2 position;
        int health;
        int score;
        float lastTime;

        IDiceInvaders* system;
        ISprite* sprite;
        Rocket* rocket;
};

#endif // PLAYER_H
