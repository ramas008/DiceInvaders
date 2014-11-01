#include "Enemy.h"

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
    horizontalStep = 0.005f;
    verticalStep = 10.0f;

    horizontalPosition = hPosition*40;
    verticalPosition = vPosition*40;

    system = sys;
    sprite = system->createSprite("data/enemy1.bmp");
}

/** \brief Deconstructor for Enemy class.
 */
Enemy::~Enemy()
{
    sprite->destroy();
}

/** \brief Update function for the Enemy.
 *
 * \param direction int the direction of movement.
 * \return void
 *  Calculating the walk path of the Enemy.
 */
void Enemy::update(int direction)
{
    sprite->draw(int(horizontalPosition), int(verticalPosition));

    //Look if the enemy turned around in the previous turn
    if(prevDirection != direction)
    {
        verticalPosition += verticalStep;
        prevDirection = direction;
    }

    horizontalPosition += direction*horizontalStep;
}

/** \brief Look if Enemy is out of the game screen.
 *
 * \return bool if Enemy is out or not.
 *
 */
bool Enemy::outOfBound()
{
    return (horizontalPosition > 600) || (horizontalPosition < 0);
}
