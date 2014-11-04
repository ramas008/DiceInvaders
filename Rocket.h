#ifndef ROCKET_H
#define ROCKET_H

#include "DiceInvaders.h"
#include "Vec2.h"

class Rocket
{
    public:
        Rocket(IDiceInvaders* sys, ISprite* rSprite, Vec2 pos);
        ~Rocket();

        Vec2 getPosition();

        void update();
    private:
        Vec2 position;
        float lastTime;

        ISprite* rocketSprite;
        IDiceInvaders* system;
};

#endif // ROCKET_H
