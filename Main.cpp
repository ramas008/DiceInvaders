#include <windows.h>
#include <cassert>
#include <cstdio>

#include "Vec2.h"
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
    Vec2 screenRes = Vec2(WIDTH, HEIGHT);
    system->init(screenRes.x(), screenRes.y());

    // Create all sprites
    ISprite* playerSprite = system->createSprite("data/player.bmp");
    ISprite* enemySprite = system->createSprite("data/enemy1.bmp");
    ISprite* rocketSprite = system->createSprite("data/rocket.bmp");
    ISprite* bombSprite = system->createSprite("data/bomb.bmp");

    // Create player
    Player* player1 = new Player(system, playerSprite, rocketSprite, screenRes);

    // Creating enemies
    EnemyList* currentPtr = NULL;
    EnemyList* firstPtr = new EnemyList;
    ListOfEnemies::createEnemies(currentPtr, firstPtr, system, enemySprite, bombSprite, screenRes);
    int direction = 1;

    // While game is running
    while (system->update())
    {
        // Print the player score
        char buffer[50];
        sprintf(buffer, "%d", player1->getScore());
        system->drawText(30, 30, "Score: ");
        system->drawText(80, 30, buffer);

        // Print the player health
        buffer[50];
        sprintf(buffer, "%d", player1->getHealth());
        system->drawText(WIDTH - 140, 30, "Health: ");
        system->drawText(WIDTH - 80, 30, buffer);

        // Create new enemies if they all are dead
        if(firstPtr->nextEnemy == NULL)
        {
            direction = 1;
            ListOfEnemies::createEnemies(currentPtr, firstPtr, system, enemySprite, bombSprite, screenRes);
        }

        // Update player
        player1->update();

        // If enemy at border change direction
        // A timer that makes it possible to only check the if statement each 1.5 seconds
        // because of it getting stuck and changing direction all the time
        float end, start, diff;
        end = system->getElapsedTime();
        diff = end - start;
        if(ListOfEnemies::isEnemyOutOfBounds(firstPtr) && diff > 1.5)
        {
            start = system->getElapsedTime();
            direction = -direction;
        }

        // Update enemy and check all collisions
        currentPtr = firstPtr->nextEnemy;
        while(currentPtr)
        {
            // Check if enemy is out for border
            if(int(currentPtr->enemy->getPosition().y()) > HEIGHT-40)
                player1->setHealth(0);

            currentPtr->enemy->update(direction);
            ListOfEnemies::checkCollision(player1, currentPtr, firstPtr);
            currentPtr = currentPtr->nextEnemy;
        }

        // If player is dead go to Game Over
        if(player1->getHealth() < 1)
                break;
    }

    // Game Over Screen if player is dead
    while (player1->getHealth() < 1 && system->update())
    {
        char buffer[50];
        sprintf(buffer, "%d", player1->getScore());
        system->drawText(WIDTH/2 - 20, HEIGHT/2 - 20, "Game Over!");
        system->drawText(WIDTH/2 - 20, HEIGHT/2, "Score: ");
        system->drawText(WIDTH/2 + 30, HEIGHT/2, buffer);
    }

    // Delete player at end of game
    delete player1;

    // Delete all remaining enemies
    currentPtr = firstPtr->nextEnemy;
    while(currentPtr)
    {
        ListOfEnemies::deleteEnemy(firstPtr, currentPtr->enemy);
        currentPtr = currentPtr->nextEnemy;
    }

    // Delete the enemy list pointers
    delete firstPtr;
    delete currentPtr;

    // Destroy all sprites
    playerSprite->destroy();
    enemySprite->destroy();
    rocketSprite->destroy();
    bombSprite->destroy();

    // Destroy game system
    system->destroy();

    return 0;
}
