#ifndef ENEMY_H
#define ENEMY_H

#include "DiceInvaders.h"
#include "Vec2.h"
#include "Bomb.h"

class Enemy
{
    public:
        Enemy(IDiceInvaders* sys, int hPosition, int vPosition);
        ~Enemy();

        Vec2 getPosition();
        Vec2 getBombPosition();
        bool hasBomb();
        bool outOfBounds();

        void setHealth(int hp);
        void deleteBomb();
        void update(int direction);
    protected:
    private:
        Vec2 position;
        int prevDirection;
        int randomNumber;
        bool timeToMove();
        float lastTime, lastBombTime;

        IDiceInvaders* system;
        ISprite* sprite;
        Bomb* bomb;
};

#endif // ENEMY_H
