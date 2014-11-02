#ifndef ROCKET_H
#define ROCKET_H

#include "DiceInvaders.h"


class Rocket
{
    public:
        Rocket(IDiceInvaders* sys);
        ~Rocket();

        void shoot(float hPosition, float vPosition);
        void update();

        float* getPosition();
    protected:
    private:
        ISprite* sprite;
        float horizontalPosition, verticalPosition;
        float position[2];
        IDiceInvaders* system;
};

#endif // ROCKET_H
