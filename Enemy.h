#ifndef ENEMY_H
#define ENEMY_H

#include "DiceInvaders.h"
#include "Vec2.h"

class Enemy
{
    public:
        Enemy(IDiceInvaders* sys, int hPosition, int vPosition);
        ~Enemy();

        void update(int direction);
        bool outOfBounds();
        void setHealth(int hp);

        Vec2* getPosition();

        int health;
    protected:
    private:
        bool timeToMove();

        int prevDirection;
        Vec2 steps;
        Vec2 position;

        IDiceInvaders* system;
        ISprite* sprite;
};

#endif // ENEMY_H
