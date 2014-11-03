#include <windows.h>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <vector>
#include <string.h>

#include "Enemy.h"
#include "Player.h"
#include "DiceInvaders.h"
#include "DiceInvadersLib.h"
#include "CollisionDetection.h"

typedef struct EnemyList {
    Enemy* enemy;
    EnemyList* nextEnemy;
} EnemyList;

bool isEnemyOutOfBounds(EnemyList* curr);
void createEnemies(EnemyList* currentPtr, EnemyList* firstPtr, IDiceInvaders* system);
void deleteEnemy(EnemyList* current, Enemy* match);
void checkCollision(Player* player1, EnemyList* currentPtr, EnemyList* firstPtr);

const int WIDTH = 640;
const int HEIGHT = 480;
const int ENEMY_AMOUNT = 40;
const int ROW_LENGTH = 10;

int APIENTRY WinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	LPSTR commandLine,
	int commandShow)
{
    // Create system
	DiceInvadersLib lib("DiceInvaders.dll");
	IDiceInvaders* system = lib.get();

    // Initialize the window
	system->init(WIDTH, HEIGHT);

    // Create player
    Player* player1 = new Player(system);

    // Creating enemies
    EnemyList* currentPtr = nullptr;
    EnemyList* firstPtr = new EnemyList;
    createEnemies(currentPtr, firstPtr, system);
    int direction = 1;

    // While game is running
	while (system->update())
	{
        // Print the player score
        char buffer[50];
        sprintf(buffer, "%d", player1->getScore());
        system->drawText(30, 30, "Score: ");
	    system->drawText(80, 30, buffer);

	    // Create new enemies if they all are dead
	    if(firstPtr->nextEnemy == nullptr)
            createEnemies(currentPtr, firstPtr, system);

	    // Update player
        player1->update();

        // Update enemy and check all collisions
        currentPtr = firstPtr->nextEnemy;
        while(currentPtr)
        {
            currentPtr->enemy->update(direction);
            checkCollision(player1, currentPtr, firstPtr);
            currentPtr = currentPtr->nextEnemy;
        }

        // If rightmost enemy at border change direction
        if(isEnemyOutOfBounds(firstPtr))
            direction = -direction;

        // If player is dead go to Game Over
        if(player1->getHealth() < 1)
                break;
	}

    // Game Over Screen
    while (system->update())
    {
        char buffer[50];
        sprintf(buffer, "%d", player1->getScore());
        system->drawText(WIDTH/2 - 20, HEIGHT/2 - 20, "Game Over!");
        system->drawText(WIDTH/2 - 20, HEIGHT/2, "Score: ");
	    system->drawText(WIDTH/2 + 30, HEIGHT/2, buffer);
    }

    delete player1;
	system->destroy();

	return 0;
}

/** \brief Check if enemy is out of bounds.
 *
 * \param current EnemyList* points on current enemy.
 * \return bool if it is out of the screen or not.
 *
 */
bool isEnemyOutOfBounds(EnemyList* current)
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
 * \return void
 *
 */
void createEnemies(EnemyList* currentPtr, EnemyList* firstPtr, IDiceInvaders* system)
{
    for(int i = 0; i < ENEMY_AMOUNT; i++)
    {
        EnemyList* current = new EnemyList;
        current->enemy = new Enemy(system, i%ROW_LENGTH, i/ROW_LENGTH);
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
 *  Delete enemy from list and from class.
 */
void deleteEnemy(EnemyList* current, Enemy* match)
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
void checkCollision(Player* player1, EnemyList* currentPtr, EnemyList* firstPtr)
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

