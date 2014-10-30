#include "Player.h"
#include <iostream>

Player::Player(IDiceInvaders* system, ISprite* sprite)
{
    hp = 3;
    horizontalPosition = 320;
    playerSystem = system;
    playerSprite = sprite;
    lastTime = playerSystem->getElapsedTime();
}

Player::~Player()
{

}

int Player::getHealth()
{
    return hp;
}

void Player::setHealth(int health)
{
    hp = health;
}

void Player::updatePlayer()
{
    //Draw sprite at new position
    playerSprite->draw(int(horizontalPosition), 480-100);

    //Calculating the movmentspeed
    float newTime = playerSystem->getElapsedTime();
    float move = (newTime - lastTime) * 160.0f;
    lastTime = newTime;

    //Controlling keys
    IDiceInvaders::KeyStatus keys;
    playerSystem->getKeyStatus(keys);
    if (keys.right && horizontalPosition < 600)
        horizontalPosition += move;
    else if (keys.left && horizontalPosition > 10)
        horizontalPosition -= move;

}
