#include "Player.h"
#include <iostream>

Player::Player(int health)
{
    hp = health;
}

Player::~Player()
{

}

void Player::onHit()
{
    hp -= 1;
}
