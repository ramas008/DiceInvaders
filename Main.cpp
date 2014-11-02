#include <windows.h>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <vector>

#include "Enemy.h"
#include "Player.h"
#include "DiceInvaders.h"
#include "DiceInvadersLib.h"
#include "CollisionDetection.h"

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
	    // Update player and enemies
        player1->update();
        for(int i = 0; i < enemyAmount; i++)
        {
            enemies[i]->update(direction);
        }

        // If rightmost enemy at border change direction
        if(CollisionDetection::isOutOfBounds(enemies, 0))
            direction = -direction;

        // OnHit loop
        for(unsigned int i = 0; i < enemies.size(); i++)
        {
            // Check if rocket hits enemy
            if(!player1->getRocket()->empty() && enemies[i]->health != 0 &&
               CollisionDetection::onHit(enemies[i]->getPosition(), player1->getRocket()->back()->getPosition()))
            {
                enemies[i]->setHealth(0);
                delete player1->getRocket()->back();
                player1->getRocket()->clear();
                player1->setScore(10);
            }

            // Check if enemy hits player
            if(player1->getHealth() != 0 && enemies[i]->health != 0 &&
               CollisionDetection::onHit(enemies[i]->getPosition(), player1->getPosition()))
            {
                enemies[i]->setHealth(0);
                player1->setHealth(player1->getHealth()-1);
            }

            // Check if enemy hits player
            if(player1->getHealth() != 0 && !enemies[i]->getBomb()->empty() &&
               CollisionDetection::onHit(enemies[i]->getBomb()->back()->getPosition(), player1->getPosition()))
            {
                player1->setHealth(player1->getHealth()-1);
                delete enemies[i]->getBomb()->back();
                enemies[i]->getBomb()->clear();
            }

            // Check if bomb went out of screen
            if(!enemies[i]->getBomb()->empty() &&
               enemies[i]->getBomb()->back()->getPosition().y() > HEIGHT)
            {
                delete enemies[i]->getBomb()->back();
                enemies[i]->getBomb()->clear();
            }
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
