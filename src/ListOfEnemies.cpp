#include "ListOfEnemies.h"
#include "CollisionDetection.h"
#include <stdlib.h>

/** \brief Check if enemy is out of bounds.
 *
 * \param current EnemyList* points on current enemy.
 * \return bool if it is out of the screen or not.
 *
 */
bool ListOfEnemies::isEnemyOutOfBounds(EnemyList* current)
{
    if(current)
        return current->enemy->outOfBounds()?true:isEnemyOutOfBounds(current->nextEnemy);
    else
        return false;
}

/** \brief Create a single linked list with all enemies.
 *
 * \param currentPtr EnemyList* points on the current enemy.
 * \param firstPtr EnemyList* points on the first enemy.
 * \param system IDiceInvaders* the game system.
 * \param enemySprite ISprite* the enemy sprite.
 * \param bombSprite ISprite* the enemy bomb sprite.
 * \param screenRes Vec2 the screen resolution.
 * \return void
 *
 */
void ListOfEnemies::createEnemies(EnemyList* currentPtr, EnemyList* firstPtr, IDiceInvaders* system,
                                  ISprite* enemySprite, ISprite* bombSprite, Vec2 screenRes)
{
    for(int i = 0; i < ENEMY_AMOUNT; i++)
    {
        EnemyList* current = new EnemyList;
        current->enemy = new Enemy(system, enemySprite, bombSprite, i%ROW_LENGTH, i/ROW_LENGTH, screenRes);
        current->nextEnemy = currentPtr;
        currentPtr = current;
    }
    firstPtr->nextEnemy = currentPtr;
}

/** \brief Delete specified enemy.
 *
 * \param current EnemyList* the list with all the enemies.
 * \param match Enemy* the specified enemy.
 * \return void
 *  Delete enemy from list and class.
 */
void ListOfEnemies::deleteEnemy(EnemyList* current, Enemy* match)
{
    if(current->nextEnemy->enemy == match)
    {
        current->nextEnemy = current->nextEnemy->nextEnemy;
        delete match;
    }
    else
        deleteEnemy(current->nextEnemy,match);
}

/** \brief Check all the collisions.
 *
 * \param player1 Player* the player.
 * \param currentPtr EnemyList* the list with all the enemies.
 * \param firstPtr EnemyList* the first enemy in list.
 * \return void
 *  Check all possible collisions and do corresponding action.
 */
void ListOfEnemies::checkCollision(Player* player1, EnemyList* currentPtr, EnemyList* firstPtr)
{
    // Check if rocket hits enemy
    if(player1->hasRocket() &&
       CollisionDetection::isColliding(currentPtr->enemy->getPosition(), player1->getRocketPosition()))
    {
        deleteEnemy(firstPtr, currentPtr->enemy);
        player1->deleteRocket();
        player1->setScore(10);
    }

    // Check if enemy hits player
    if(CollisionDetection::isColliding(currentPtr->enemy->getPosition(), player1->getPosition()))
    {
        deleteEnemy(firstPtr, currentPtr->enemy);
        player1->setHealth(player1->getHealth()-1);
    }

    // Check if enemy bomb hits player
    if(currentPtr->enemy->hasBomb() &&
       CollisionDetection::isColliding(currentPtr->enemy->getBombPosition(), player1->getPosition()))
    {
        player1->setHealth(player1->getHealth()-1);
        currentPtr->enemy->deleteBomb();
    }
}

