#ifndef ENEMY_H
#define ENEMY_H

#include "DiceInvaders.h"

class Enemy
{
    public:
        Enemy(IDiceInvaders* sys, int hPosition, int vPosition);
        ~Enemy();

        void update(int direction);
        bool outOfBounds();
        void setHealth(int hp);

        float horizontalPosition, verticalPosition;
        int health;
    protected:
    private:
        bool timeToMove();

        int prevDirection;
        float horizontalStep, verticalStep;

        IDiceInvaders* system;
        ISprite* sprite;
};

#endif // ENEMY_H
