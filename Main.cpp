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
    //Create system
	DiceInvadersLib lib("DiceInvaders.dll");
	IDiceInvaders* system = lib.get();

    //Initialize the window
    const int WIDTH = 640;
    const int HEIGHT = 480;
	system->init(WIDTH, HEIGHT);

    //Create sprite
	ISprite* sprite = system->createSprite("data/player.bmp");

    //Create player
    Player* ramin = new Player(system, sprite);

    //While running the game
	while (system->update())
	{
        ramin->updatePlayer();
	}

	sprite->destroy();
	system->destroy();

	return 0;
}
