#ifndef BOMB_H
#define BOMB_H

#include "DiceInvaders.h"
#include "Vec2.h"

class Bomb
{
    public:
        Bomb(IDiceInvaders* sys, ISprite* bSprite, Vec2 pos);
        ~Bomb();

        Vec2 getPosition();

        void update();
    private:
        Vec2 position;
        float lastTime;

        ISprite* bombSprite;
        IDiceInvaders* system;
};

#endif // BOMB_H
