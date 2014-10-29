#include <windows.h>
#include <cassert>
#include <cstdio>
#include <iostream>
#include "DiceInvaders.h"
#include "Player.h"
#include "DiceInvadersLib.h"

int APIENTRY WinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	LPSTR commandLine,
	int commandShow)
{
	DiceInvadersLib lib("DiceInvaders.dll");
	IDiceInvaders* system = lib.get();

    //Initialize the window
    int windowWidth = 640;
    int windowHeight = 480;
	system->init(windowWidth, windowHeight);

    //Create sprite
	ISprite* sprite = system->createSprite("data/player.bmp");
    ISprite* sprite2 = system->createSprite("data/enemy1.bmp");

    Player* ramin = new Player(3);

	float horizontalPosition = 320;
	float horizontalPosition2 = 100;
	float lastTime = system->getElapsedTime();
	while (system->update())
	{
	    //Draw the sprites at specified position
		sprite->draw(int(horizontalPosition), 480-100);
		sprite2->draw(horizontalPosition2, 100);

        //Calculate the amout of move
		float newTime = system->getElapsedTime();
		float move = (newTime - lastTime) * 160.0f;
		lastTime = newTime;

        horizontalPosition2 += move;

        //Key options
		IDiceInvaders::KeyStatus keys;
		system->getKeyStatus(keys);
		if (keys.right)
			horizontalPosition += move;
		else if (keys.left)
			horizontalPosition -= move;
	}

	sprite->destroy();
	sprite2->destroy();
	system->destroy();


	return 0;
}


