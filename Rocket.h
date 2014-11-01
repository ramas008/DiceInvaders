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
        void onHit();
        float getHorizontalPosition();
        float getVerticalPosition();
    protected:
    private:
        bool test = 1;
        float horizontalPosition, verticalPosition;
        IDiceInvaders* system;
        ISprite* sprite;
};

#endif // ROCKET_H
