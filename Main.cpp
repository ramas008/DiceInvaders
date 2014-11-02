#include <windows.h>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>
#include "DiceInvaders.h"
#include "DiceInvadersLib.h"
#include "Player.h"
#include "Enemy.h"

bool isOutOfBounds(std::vector<Enemy*> e, unsigned int index);
bool onHit(std::vector<Enemy*> e, float position[]);

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
    std::vector<Enemy*> enemies;
    for(int i = 0; i < enemyAmount; i++)
    {
        enemies.push_back(new Enemy(system, i%rowLength, i/rowLength));
    }

    int direction = 1;
    // While running the game
	while (system->update())
	{
        player1->update();
        for(int i = 0; i < enemyAmount; i++)
        {
            enemies[i]->update(direction);
        }

        if(isOutOfBounds(enemies, 0))
            direction = -direction;

        // Check if rocket hits enemy
        if(!player1->getRocket()->empty() &&
           onHit(enemies, player1->getRocket()->back()->getPosition()))
        {
            player1->getRocket()->clear();
            delete player1->getRocket()->back();
            player1->setScore(10);
        }


        // Check if rocket went out of screen
        if(!player1->getRocket()->empty() &&
           player1->getRocket()->back()->getPosition()[1] < 0)
        {
            player1->getRocket()->clear();
            delete player1->getRocket()->back();
        }
	}

	system->destroy();

	return 0;
}

/** \brief Check if enemy is out of bounds.
 *
 * \param e std::vector<Enemy*>
 * \param index int
 * \return bool
 *
 */
bool isOutOfBounds(std::vector<Enemy*> e, unsigned int index)
{
    if(e.size()>index)
        return e[index]->outOfBounds()?true:isOutOfBounds(e,++index);

    return false;
}

/** \brief
 *
 * \param e std::vector<Enemy*>
 * \param hPosition float
 * \param vPosition float
 * \return bool
 *
 */
bool onHit(std::vector<Enemy*> e, float position[])
{
    for(unsigned int i = 0; i < e.size(); i++)
    {
        if(position[0] > e[i]->horizontalPosition - 15 &&
           position[0] < e[i]->horizontalPosition + 15 &&
           position[1] > e[i]->verticalPosition - 15 &&
           position[1] < e[i]->verticalPosition + 15 &&
           e[i]->health != 0)
        {
            e[i]->setHealth(0);
            return true;
        }
    }
    return false;
}
