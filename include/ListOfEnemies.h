#ifndef LISTOFENEMIES_H
#define LISTOFENEMIES_H

#include "Enemy.h"
#include "Player.h"

/** \brief Single linked list with all the enemies.
 */
typedef struct EnemyList {
    Enemy* enemy;
    EnemyList* nextEnemy;
} EnemyList;

class ListOfEnemies
{
    public:
        static void checkCollision(Player* player1, EnemyList* currentPtr, EnemyList* firstPtr);
        static bool isEnemyOutOfBounds(EnemyList* curr);
        static void createEnemies(EnemyList* currentPtr, EnemyList* firstPtr, IDiceInvaders* system,
                                  ISprite* enemySprite, ISprite* bombSprite, Vec2 screenRes);
        static void deleteEnemy(EnemyList* current, Enemy* match);
    private:
        static const int ENEMY_AMOUNT = 40;
        static const int ROW_LENGTH = 10;
};

#endif // LISTOFENEMIES_H
