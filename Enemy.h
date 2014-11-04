#ifndef ENEMY_H
#define ENEMY_H

#include "Bomb.h"

class Enemy
{
    public:
        Enemy(IDiceInvaders* sys, ISprite* eSprite, ISprite* bSprite, int hPosition, int vPosition, Vec2 screenR);
        ~Enemy();

        Vec2 getPosition();
        Vec2 getBombPosition();
        bool hasBomb();
        bool outOfBounds();

        void deleteBomb();
        void update(int direction);
    private:
        Vec2 position;
        Vec2 screenRes;
        int prevDirection;
        int randomNumber;
        float lastTime, lastBombTime;

        IDiceInvaders* system;
        ISprite* enemySprite;
        ISprite* bombSprite;
        Bomb* bomb;
};

#endif // ENEMY_H
