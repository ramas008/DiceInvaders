#ifndef ROCKET_H
#define ROCKET_H

#include "DiceInvaders.h"
#include "Vec2.h"

class Rocket
{
    public:
        Rocket(IDiceInvaders* sys);
        ~Rocket();

        void shoot(float hPosition, float vPosition);
        void update();

        Vec2* getPosition();
    protected:
    private:
        ISprite* sprite;
        Vec2 position;
        float horizontalPosition, verticalPosition;
        IDiceInvaders* system;
};

#endif // ROCKET_H
