#include <windows.h>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>
#include "DiceInvaders.h"
#include "DiceInvadersLib.h"
#include "Player.h"
#include "Enemy.h"

/** \brief Calculates the amount of steps the enemy needs to take.
 *
 * \param enemyAmount int the amount of enemies.
 * \param rowLength int the specified rowlength.
 * \return int the amount of steps.
 *
 */
int amountSteps(int enemyAmount, int rowLength)
{
    int amountSteps = 0;

    if(enemyAmount >= rowLength)
        amountSteps = rowLength;
    else
        amountSteps = enemyAmount;

    return amountSteps;
}

int APIENTRY WinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	LPSTR commandLine,
	int commandShow)
{
    //Create system
	DiceInvadersLib lib("DiceInvaders.dll");
	IDiceInvaders* system = lib.get();

    //Initialize the window
    const int WIDTH = 640;
    const int HEIGHT = 480;
	system->init(WIDTH, HEIGHT);

    //Create player
    Player* player1 = new Player(system);

    //Creating enemies
    int enemyAmount = 40;
    int rowLength = 10;
    std::vector<Enemy*> enemies;
    for(int i = 0; i < enemyAmount; i++)
    {
        enemies.push_back(new Enemy(system, i%rowLength, i/rowLength));
    }

    //Get how many steps the enemy needs to take
    int steps = amountSteps(enemyAmount, rowLength);

    //While running the game
	while (system->update())
	{
        player1->update();
        for(int i = 0; i < enemyAmount; i++)
        {
            enemies[i]->update(steps);
        }
	}

	system->destroy();

	return 0;
}



