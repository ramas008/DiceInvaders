#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include "DiceInvaders.h"
#include "Vec2.h"
#include "Bomb.h"

class Enemy
{
    public:
        Enemy(IDiceInvaders* sys, int hPosition, int vPosition);
        ~Enemy();

        Vec2 getPosition();
        std::vector<Bomb*>* getBomb();

        void setHealth(int hp);

        void update(int direction);
        bool outOfBounds();

        int health;
    protected:
    private:
        bool timeToMove();
        int prevDirection;
        Vec2 position;
        float lastTime, lastBombTime;
        int randomNumber;

        IDiceInvaders* system;
        ISprite* sprite;
        std::vector<Bomb*> bomb;
};

#endif // ENEMY_H
