#include <windows.h>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>
#include "DiceInvaders.h"
#include "DiceInvadersLib.h"
#include "Player.h"
#include "Enemy.h"

bool isOutOfBounds(std::vector<Enemy*> e, int index);

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

    int direction = 1;
    //While running the game
	while (system->update())
	{
        player1->update();
        for(int i = 0; i < enemyAmount; i++)
        {
            enemies[i]->update(direction);
        }

        if(isOutOfBounds(enemies, 0))
            direction = -direction;
	}

	system->destroy();

	return 0;
}

/** \brief
 *
 * \param e std::vector<Enemy*>
 * \param index int
 * \return bool
 *
 */
bool isOutOfBounds(std::vector<Enemy*> e, int index)
{
    if(e.size()>index)
        return e[index]->outOfBound()?true:isOutOfBounds(e,++index);

    return false;
}

