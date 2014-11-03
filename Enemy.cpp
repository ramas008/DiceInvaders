#include "Enemy.h"
#include <stdlib.h>

/** \brief Constructor for Enemy class.
 *
 * \param sys IDiceInvaders* the game system.
 * \param hPosition int the horizontal position of enemy.
 * \param vPosition int the vertical position of enemy.
 *  Initializing health, position, the previous direction,
    a random number, last time for bomb and enemy and game system.
 */
Enemy::Enemy(IDiceInvaders* sys, int hPosition, int vPosition)
{
    prevDirection = 1;
    position = Vec2(hPosition*40 + 15, vPosition*40 + 15);
    bomb = NULL;
    randomNumber = rand() % 30 + 1;

    system = sys;
    sprite = system->createSprite("data/enemy1.bmp");

    lastTime = system->getElapsedTime();
    lastBombTime = system->getElapsedTime();
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
    // Draw sprite at new position
    sprite->draw(int(position.x()), int(position.y()));

    // Calculating movement speed
    float newTime = system->getElapsedTime();
    float move = (newTime - lastTime) * 160.0f;
    lastTime = newTime;

    // Look if the enemy turned around in the previous turn
    // This is because move variable vary in different times
    if(prevDirection != direction)
    {
        direction > 0?position.moveX(5):position.moveX(-5);
        position.moveY(10.0f);
        prevDirection = direction;
    }

    // Move enemy with specified direction
    position.moveX(direction*move);

    // Shoot bomb if enemy has no bomb
    if (!hasBomb() && (newTime - lastBombTime) + randomNumber > 30 )
    {
        randomNumber = rand() % 30 + 1;
        lastBombTime = newTime;
        bomb = new Bomb(system, position.x(), position.y());
    }

    // Update bomb
    if(hasBomb())
    {
        bomb->update();
        // Check if bomb went out of screen
        if(bomb->getPosition().y() > 480)
        {
            deleteBomb();
        }
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

/** \brief
 *
 * \return Vec2
 *
 */
Vec2 Enemy::getBombPosition()
{
    return bomb->getPosition();
}

void Enemy::deleteBomb()
{
    delete bomb;
    bomb = NULL;
}

bool Enemy::hasBomb()
{
    return bomb?true:false;
}

/** \brief
 *
 * \return Vec2*
 *
 */
Vec2 Enemy::getPosition()
{
    return position;
}

