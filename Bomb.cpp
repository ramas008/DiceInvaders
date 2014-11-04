#include "Bomb.h"

/** \brief Constructor for Bomb class.
 *
 * \param sys IDiceInvaders* the game system.
 * \param bSprite ISprite* the bomb sprite.
 * \param pos Vec2 the position.
 * Initializing position, game system and sprite.
 */
Bomb::Bomb(IDiceInvaders* sys, ISprite* bSprite, Vec2 pos)
{
    position = pos;

    system = sys;
    bombSprite = bSprite;

    lastTime = system->getElapsedTime();
}

/** \brief Deconstructor for Bomb class.
 */
Bomb::~Bomb()
{

}

/** \brief Bomb update function.
 *
 * \return void
 * Calculates the movement speed, draws the sprite and moves bomb.
 */
void Bomb::update()
{
    // Draw sprite at new position
    bombSprite->draw(int(position.x()), int(position.y())+20);

    // Calculating speed
    float newTime = system->getElapsedTime();
    float move = (newTime - lastTime) * 160.0f;
    lastTime = newTime;

    // Moves bomb in positive y
    position.moveY(move);
}

/** \brief Get bomb position.
 *
 * \return Vec2 the position.
 *
 */
Vec2 Bomb::getPosition()
{
    return position;
}
