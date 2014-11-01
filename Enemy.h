#ifndef ENEMY_H
#define ENEMY_H

#include "DiceInvaders.h"

class Enemy
{
    public:
        Enemy(IDiceInvaders* sys, int hPosition, int vPosition);
        ~Enemy();

        void update(int direction);
        bool outOfBound();
    protected:
    private:
        bool timeToMove();

        int prevDirection;
        int health;
        float horizontalPosition, verticalPosition;
        float horizontalStep, verticalStep;

        IDiceInvaders* system;
        ISprite* sprite;
};

#endif // ENEMY_H
