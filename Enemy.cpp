#include "Enemy.h"
#include <iostream>

/** \brief Constructor for Enemy class.
 *
 * \param sys IDiceInvaders* the game system.
 * \param hPosition int the horizontal position of enemy.
 * \param vPosition int the vertical position of enemy.
 *  Initializing health, walking direction, steps taken, game system and sprite.
 */
Enemy::Enemy(IDiceInvaders* sys, int hPosition, int vPosition)
{
    health = 1;
    walkingDirection = 1;
    stepsTaken = 0;

    horizontalPosition = hPosition;
    verticalPosition = vPosition;

    system = sys;
    sprite = system->createSprite("data/enemy1.bmp");
    lastTime = system->getElapsedTime();
}

/** \brief Deconstructor for Enemy class.
 */
Enemy::~Enemy()
{
    sprite->destroy();
}

/** \brief Calculating the walking path of the enemy.
 *
 * \param amountSteps int the amount of steps for each row.
 * \return void
 * Draws sprite on screen depending on the walking path.
 */
void Enemy::update(int amountSteps)
{
    sprite->draw(10 + int(horizontalPosition)*40, 60 + int(verticalPosition)*40);

    if(timeToMove())
    {
        stepsTaken += 1;
        if(stepsTaken%(16 - amountSteps) == 0)
        {
            verticalPosition += 1;
            walkingDirection *= -1;
        }
        else
            horizontalPosition += walkingDirection;
    }
}

/** \brief Calculating if enemy is allowed to move.
 *
 * \return bool if allowed or not.
 *
 */
bool Enemy::timeToMove()
{
    float movementSpeed = 1.0;
    float newTime = system->getElapsedTime();
    float move = (newTime - lastTime);
    if(move > movementSpeed)
    {
        lastTime = newTime;
        return true;
    }
    return false;
}
