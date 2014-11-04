#ifndef PLAYER_H
#define PLAYER_H

#include "Rocket.h"

class Player
{
    public:
        Player(IDiceInvaders* sys, ISprite* pSprite, ISprite* rSprite, Vec2 screenR);
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
    private:
        Vec2 position;
        Vec2 screenRes;
        int health;
        int score;
        float lastTime;

        IDiceInvaders* system;
        ISprite* playerSprite;
        ISprite* rocketSprite;
        Rocket* rocket;
};

#endif // PLAYER_H
