#include "Player.h"
#include <iostream>


/** \brief Constructor for Player class.
 *
 * \param sys IDiceInvaders* the game system.
 *  Initialzing health, starting position, game system and sprite.
 */
Player::Player(IDiceInvaders* sys)
{
    health = 3;
    horizontalPosition = 320;
    system = sys;
    sprite = system->createSprite("data/player.bmp");
    lastTime = system->getElapsedTime();
}

/** \brief Deconstructor for Player class.
 */
Player::~Player()
{
    sprite->destroy();
}


/** \brief Get health for player
 *
 * \return int the health.
 *
 */
int Player::getHealth()
{
    return health;
}

/** \brief Sets the health for player
 *
 * \param hp int the input health.
 * \return void
 *
 */
void Player::setHealth(int hp)
{
    health = hp;
}

/** \brief Update function for the player
 *
 * \return void
 *  Draws the sprite to the screen, Calculates movementspeed and handles the controlls for the player.
 */
void Player::update()
{
    //Draw sprite at new position
    sprite->draw(int(horizontalPosition), 480-100);

    //Calculating the movmentspeed
    float newTime = system->getElapsedTime();
    float move = (newTime - lastTime) * 160.0f;
    lastTime = newTime;

    //Controlling keys
    IDiceInvaders::KeyStatus keys;
    system->getKeyStatus(keys);
    if (keys.right && horizontalPosition < 600)
        horizontalPosition += move;
    else if (keys.left && horizontalPosition > 10)
        horizontalPosition -= move;

}
