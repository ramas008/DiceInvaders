#include <windows.h>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <vector>
#include <string.h>

#include "Enemy.h"
#include "Player.h"
#include "DiceInvaders.h"
#include "ListOfEnemies.h"
#include "DiceInvadersLib.h"

const int WIDTH = 640;
const int HEIGHT = 480;

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
    ListOfEnemies::createEnemies(currentPtr, firstPtr, system);
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
            ListOfEnemies::createEnemies(currentPtr, firstPtr, system);

	    // Update player
        player1->update();

        // Update enemy and check all collisions
        currentPtr = firstPtr->nextEnemy;
        while(currentPtr)
        {
            currentPtr->enemy->update(direction);
            ListOfEnemies::checkCollision(player1, currentPtr, firstPtr);
            currentPtr = currentPtr->nextEnemy;
        }

        // If enemy at border change direction
        if(ListOfEnemies::isEnemyOutOfBounds(firstPtr))
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
