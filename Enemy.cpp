#include "Enemy.h"
#include <iostream>
#include <stdlib.h>

/** \brief Constructor for Enemy class.
 *
 * \param sys IDiceInvaders* the game system.
 * \param hPosition int the horizontal position of enemy.
 * \param vPosition int the vertical position of enemy.
 *  Initializing health, the previous direction,
    position of enemy, game system.
 */
Enemy::Enemy(IDiceInvaders* sys, int hPosition, int vPosition)
{
    health = 1;
    prevDirection = 1;
    position = Vec2(hPosition*40 + 15, vPosition*40 + 15);

    system = sys;
    sprite = system->createSprite("data/enemy1.bmp");
    lastTime = system->getElapsedTime();
    lastBombTime = system->getElapsedTime();
    randomNumber = rand() % 30 + 1;
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

        // Calculating speed
        float newTime = system->getElapsedTime();
        float move = (newTime - lastTime) * 160.0f;
        lastTime = newTime;

        // Look if the enemy turned around in the previous turn
        if(prevDirection != direction)
        {
            direction > 0?position.moveX(5):position.moveX(-5);
            position.moveY(10.0f);
            prevDirection = direction;
        }

        position.moveX(direction*move);

        // Shoot bomb if vector is not empty
        if (bomb.empty() && (newTime - lastBombTime) + randomNumber > 30 )
        {
            randomNumber = rand() % 30 + 1;
            lastBombTime = newTime;
            bomb.push_back(new Bomb(system));
            bomb.back()->shoot(position.x(), position.y());
        }
    }

    // Update bomb
    if(!bomb.empty())
        bomb.back()->update();
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

std::vector<Bomb*>* Enemy::getBomb()
{
    return &bomb;
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

void Enemy::setHealth(int hp)
{
    health = hp;
}
