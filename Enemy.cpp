#include "Enemy.h"
#include <stdlib.h>

/** \brief Constructor for Enemy class.
 *
 * \param sys IDiceInvaders* the game system.
 * \param enemySprite ISprite* the enemt sprite.
 * \param hPosition int the horizontal position of enemy.
 * \param vPosition int the vertical position of enemy.
 * \param screenR Vec2 the screen resolution.
 *  Initializing health, position, the previous direction, screen resolution,
 *  a random number, last time for bomb and enemy, sprite and game system.
 */
Enemy::Enemy(IDiceInvaders* sys, ISprite* eSprite, ISprite* bSprite, int hPosition, int vPosition, Vec2 screenR)
{
    prevDirection = 1;
    position = Vec2(hPosition*40 + 15, vPosition*40 + 15);
    bomb = NULL;
    randomNumber = rand() % 30 + 1;
    screenRes = screenR;

    system = sys;
    enemySprite = eSprite;
    bombSprite = bSprite;

    lastTime = system->getElapsedTime();
    lastBombTime = system->getElapsedTime();
}

/** \brief Deconstructor for Enemy class.
 */
Enemy::~Enemy()
{
    if(hasBomb())
        delete bomb;
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
    enemySprite->draw(int(position.x()), int(position.y()));

    // Calculating movement speed
    float newTime = system->getElapsedTime();
    float move = (newTime - lastTime) * 160.0f;
    lastTime = newTime;

    // Look if the enemy turned around in the previous turn
    // This is because move variable vary in different times
    if(prevDirection != direction)
    {
        direction > 0?position.moveX(5):position.moveX(-5);
        position.moveY(15.0f);
        prevDirection = direction;
    }

    // Move enemy with specified direction
    position.moveX(direction*move);

    // Shoot bomb if enemy has no bomb
    if (!hasBomb() && (newTime - lastBombTime) + randomNumber > 30 )
    {
        randomNumber = rand() % 30 + 1;
        lastBombTime = newTime;
        bomb = new Bomb(system, bombSprite, position);
    }

    // Update bomb
    if(hasBomb())
    {
        bomb->update();
        // Check if bomb went out of screen
        if(bomb->getPosition().y() > screenRes.y())
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
    return position.x() > (screenRes.x() - 30.0f) || position.x() < 0.0f;
}

/** \brief Get bombs position.
 *
 * \return Vec2 the position.
 *
 */
Vec2 Enemy::getBombPosition()
{
    return bomb->getPosition();
}

/** \brief Delete bomb.
 *
 * \return void
 *
 */
void Enemy::deleteBomb()
{
    delete bomb;
    bomb = NULL;
}

/** \brief Look if enemy bomb is in game.
 *
 * \return bool if enemy has the bomb or not.
 *
 */
bool Enemy::hasBomb()
{
    return bomb?true:false;
}

/** \brief Get enemy position.
 *
 * \return Vec2* the position.
 *
 */
Vec2 Enemy::getPosition()
{
    return position;
}

