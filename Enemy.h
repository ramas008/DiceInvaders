#ifndef ENEMY_H
#define ENEMY_H

#include "DiceInvaders.h"

class Enemy
{
    public:
        Enemy(IDiceInvaders* sys, int hPosition, int vPosition);
        ~Enemy();

        void update(int amountSteps);

    protected:
    private:
        bool timeToMove();

        int health;
        float horizontalPosition, verticalPosition;
        float lastTime;
        int walkingDirection;
        int stepsTaken;

        IDiceInvaders* system;
        ISprite* sprite;
};

#endif // ENEMY_H
