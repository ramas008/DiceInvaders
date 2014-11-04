#include "Rocket.h"

/** \brief Constructor for Rocket class.
 *
 * \param sys IDiceInvaders* the game system.
 * \param rSprite ISprite* the rocket sprite.
 * \param pos Vec2 the position.
 * Initializing position, game system and sprite.
 */
Rocket::Rocket(IDiceInvaders* sys, ISprite* rSprite, Vec2 pos)
{
    position = pos;

    system = sys;
    rocketSprite = rSprite;

    lastTime = system->getElapsedTime();
}

/** \brief Deconstructor for Rocket class.
 */
Rocket::~Rocket()
{

}

/** \brief Rocket update function.
 *
 * \return void
 * Calculates the movement speed, draws the sprite and moves rocket.
 */
void Rocket::update()
{
    // Draw sprite at new position
    rocketSprite->draw(int(position.x()), int(position.y())-20);

    // Calculating speed
    float newTime = system->getElapsedTime();
    float move = (newTime - lastTime) * 360.0f;
    lastTime = newTime;

    // Moves rocket in negative y
    position.moveY(-move);
}

/** \brief Get rocket position.
 *
 * \return Vec2 the rocket position.
 *
 */
Vec2 Rocket::getPosition()
{
    return position;
}

