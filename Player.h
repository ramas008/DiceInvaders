#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "DiceInvaders.h"
#include "Rocket.h"
#include "Vec2.h"

class Player
{
    public:
        Player(IDiceInvaders* sys);
        ~Player();

        Vec2 getPosition();
        int getHealth();
        std::vector<Rocket*>* getRocket();

        void setHealth(int hp);
        void setScore(int sc);

        void update();
        void handleController();
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
