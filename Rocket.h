#ifndef ROCKET_H
#define ROCKET_H

#include "DiceInvaders.h"
#include "Vec2.h"

class Rocket
{
    public:
        Rocket(IDiceInvaders* sys, float hPosition, float vPosition);
        ~Rocket();

        void update();

        Vec2 getPosition();
    protected:
    private:
        Vec2 position;
        float lastTime;
        ISprite* sprite;
        IDiceInvaders* system;
};

#endif // ROCKET_H
