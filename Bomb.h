#ifndef BOMB_H
#define BOMB_H

#include "DiceInvaders.h"
#include "Vec2.h"

class Bomb
{
    public:
        Bomb(IDiceInvaders* sys);
        ~Bomb();

        void shoot(float hPosition, float vPosition);
        void update();

        Vec2 getPosition();
    protected:
    private:
        Vec2 position;
        float lastTime;

        ISprite* sprite;
        IDiceInvaders* system;
};

#endif // BOMB_H
