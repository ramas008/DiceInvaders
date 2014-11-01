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

        float getHorizontalPosition();
        float getVerticalPosition();
    protected:
    private:
        float horizontalPosition, verticalPosition;
        IDiceInvaders* system;
        ISprite* sprite;
};

#endif // ROCKET_H
