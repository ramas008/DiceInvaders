#include "Player.h"
#include <cstddef>
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
    score = 0;

    system = sys;
    sprite = system->createSprite("data/player.bmp");
    lastTime = system->getElapsedTime();
}

/** \brief Deconstructor for Player class.
 */
Player::~Player()
{

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

void Player::setScore(int sc)
{
    score += sc;
}

std::vector<Rocket*>* Player::getRocket()
{
    return &rocket;
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

    //Controlling keys
    handleController();

    //Update spell
    if(!rocket.empty())
        rocket.back()->update();
}

void Player::handleController()
{
    //Calculating the movmentspeed
    float newTime = system->getElapsedTime();
    float move = (newTime - lastTime) * 160.0f;
    lastTime = newTime;

    IDiceInvaders::KeyStatus keys;
    system->getKeyStatus(keys);
    //Checking if moving to the right and shooting
    if(keys.right && horizontalPosition < 600 && keys.fire && rocket.empty())
    {
        horizontalPosition += move;
        rocket.push_back(new Rocket(system));
        rocket.back()->shoot(horizontalPosition, 380);
    }
    //Cheacking if moving to the left and shooting
    else if(keys.left && horizontalPosition > 10 && keys.fire && rocket.empty())
    {
        horizontalPosition -= move;
        rocket.push_back(new Rocket(system));
        rocket.back()->shoot(horizontalPosition, 380);
    }
    //Checking if moving to the right
    else if (keys.right && horizontalPosition < 600)
        horizontalPosition += move;
    //Checking if moving to the left
    else if (keys.left && horizontalPosition > 10)
        horizontalPosition -= move;
    //Checking if shooting
    else if (keys.fire && rocket.empty())
    {
        rocket.push_back(new Rocket(system));
        rocket.back()->shoot(horizontalPosition, 380);
    }
}
