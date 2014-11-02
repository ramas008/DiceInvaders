#include "Enemy.h"
#include <iostream>

/** \brief Constructor for Enemy class.
 *
 * \param sys IDiceInvaders* the game system.
 * \param hPosition int the horizontal position of enemy.
 * \param vPosition int the vertical position of enemy.
 *  Initializing health, the previous direction, horizontal and
 *  vertical step lenght, game system and starting position of sprite.
 */
Enemy::Enemy(IDiceInvaders* sys, int hPosition, int vPosition)
{
    health = 1;
    prevDirection = 1;

    steps = Vec2(0.005f, 10.0f);
    position = Vec2(hPosition*40 + 15, vPosition*40 + 15);

    system = sys;
    sprite = system->createSprite("data/enemy1.bmp");
    lastTime = system->getElapsedTime();
}

/** \brief Deconstructor for Enemy class.
 */
Enemy::~Enemy()
{

}

/** \brief Update function for the Enemy.
 *
 * \param direction int the direction of movement.
 * \return void
 *  Calculating the walk path of the Enemy.
 */
void Enemy::update(int direction)
{
    if(health != 0)
    {
        sprite->draw(int(position.x()), int(position.y()));

        float newTime = system->getElapsedTime();
        float move = (newTime - lastTime) * 160.0f;
        lastTime = newTime;

        // Look if the enemy turned around in the previous turn
        if(prevDirection != direction)
        {
            position.moveY(0.1f);
            prevDirection = direction;
        }

        position.moveX(direction*move);
    }
}

/** \brief Look if Enemy is out of the game screen.
 *
 * \return bool if Enemy is out or not.
 *
 */
bool Enemy::outOfBounds()
{
    return (position.x() > 600) || (position.x() < 0);
}

Vec2* Enemy::getPosition()
{
    return &position;
}

void Enemy::setHealth(int hp)
{
    health = hp;
}

