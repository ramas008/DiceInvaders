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
void deleteEnemy(EnemyList* current, Enemy* match);
void createEnemies(EnemyList* currentPtr, EnemyList* firstPtr, int enemyAmount, int rowLength, IDiceInvaders* system);

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
    const int WIDTH = 640;
    const int HEIGHT = 480;
	system->init(WIDTH, HEIGHT);

    // Create player
    Player* player1 = new Player(system);

    // Creating enemies
    int enemyAmount = 40;
    int rowLength = 10;
    EnemyList* currentPtr = nullptr;
    EnemyList* firstPtr = new EnemyList;
    createEnemies(currentPtr, firstPtr, enemyAmount, rowLength, system);

    int direction = 1;
    // While running the game
	while (system->update())
	{
	    // If player dead print game over
	    if(player1->getHealth() == 0)
            system->drawText(WIDTH/2, HEIGHT/2, "Game Over!");

        // Print the player score
        char buffer[50];
        sprintf(buffer, "%d", player1->getScore());
        system->drawText(30, 30, "Score: ");
	    system->drawText(80, 30, buffer);

	    // Create new enemies if they are all dead
	    if(firstPtr->nextEnemy == nullptr)
            createEnemies(currentPtr, firstPtr, enemyAmount, rowLength, system);

	    // Update player and enemies
        player1->update();
        currentPtr = firstPtr->nextEnemy;
        while(currentPtr)
        {
            currentPtr->enemy->update(direction);
            currentPtr = currentPtr->nextEnemy;
        }

        // If rightmost enemy at border change direction
        if(isEnemyOutOfBounds(firstPtr))
            direction = -direction;

        // OnHit loop
        currentPtr = firstPtr->nextEnemy;
        while(currentPtr)
        {
            // Check if rocket hits enemy
            if(!player1->getRocket()->empty() && currentPtr->enemy->health != 0 &&
               CollisionDetection::onHit(currentPtr->enemy->getPosition(), player1->getRocket()->back()->getPosition()))
            {
                currentPtr->enemy->setHealth(0);
                deleteEnemy(firstPtr, currentPtr->enemy);
                delete player1->getRocket()->back();
                player1->getRocket()->clear();
                player1->setScore(10);
            }

            // Check if enemy hits player
            if(player1->getHealth() != 0 && currentPtr->enemy->health != 0 &&
               CollisionDetection::onHit(currentPtr->enemy->getPosition(), player1->getPosition()))
            {
                currentPtr->enemy->setHealth(0);
                deleteEnemy(firstPtr, currentPtr->enemy);
                player1->setHealth(player1->getHealth()-1);
            }

            // Check if enemy bomb hits player
            if(player1->getHealth() != 0 && !currentPtr->enemy->getBomb()->empty() &&
               CollisionDetection::onHit(currentPtr->enemy->getBomb()->back()->getPosition(), player1->getPosition()))
            {
                player1->setHealth(player1->getHealth()-1);
                delete currentPtr->enemy->getBomb()->back();
                currentPtr->enemy->getBomb()->clear();
            }

            // Check if bomb went out of screen
            if(!currentPtr->enemy->getBomb()->empty() &&
               currentPtr->enemy->getBomb()->back()->getPosition().y() > HEIGHT)
            {
                delete currentPtr->enemy->getBomb()->back();
                currentPtr->enemy->getBomb()->clear();
            }
            currentPtr = currentPtr->nextEnemy;
        }

        // Check if rocket went out of screen
        if(!player1->getRocket()->empty() &&
           player1->getRocket()->back()->getPosition().y() < 0)
        {
            delete player1->getRocket()->back();
            player1->getRocket()->clear();
        }
	}

	system->destroy();

	return 0;
}

bool isEnemyOutOfBounds(EnemyList* current)
{
    if(current)
        return current->enemy->outOfBounds()?true:isEnemyOutOfBounds(current->nextEnemy);
    else
        return false;
}

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

void createEnemies(EnemyList* currentPtr, EnemyList* firstPtr, int enemyAmount, int rowLength, IDiceInvaders* system)
{
    for(int i = 0; i < enemyAmount; i++)
    {
        EnemyList* current = new EnemyList;
        current->enemy = new Enemy(system, i%rowLength, i/rowLength);
        current->nextEnemy = currentPtr;
        currentPtr = current;
    }
    firstPtr->nextEnemy = currentPtr;
}
