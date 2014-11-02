#ifndef PLAYER_H
#define PLAYER_H

#include "DiceInvaders.h"
#include "Rocket.h"
#include <vector>
#include "Vec2.h"

class Player
{
    public:
        Player(IDiceInvaders* sys);
        ~Player();

        Vec2* getPosition();
        int getHealth();
        void setHealth(int hp);
        void setScore(int sc);
        void update();
        void handleController();
        std::vector<Rocket*>* getRocket();
    protected:
    private:
        int health;
        int score;
        Vec2 position;
        float lastTime;

        IDiceInvaders* system;
        ISprite* sprite;
        std::vector<Rocket*> rocket;
};

#endif // PLAYER_H
