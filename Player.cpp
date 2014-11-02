#include "Player.h"
#include <iostream>

/** \brief Constructor for Player class.
 *
 * \param sys IDiceInvaders* the game system.
 *  Initialize health, score, starting position, game system and sprite.
 */
Player::Player(IDiceInvaders* sys)
{
    health = 3;
    position = Vec2(320, 480 - 100);
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

/** \brief Get player health
 *
 * \return int the health.
 *
 */
int Player::getHealth()
{
    return health;
}

/** \brief Set player health.
 *
 * \param hp int the input health.
 * \return void
 *
 */
void Player::setHealth(int hp)
{
    health = hp;
}

/** \brief Set player score.
 *
 * \param sc int the input score.
 * \return void
 *
 */
void Player::setScore(int sc)
{
    score += sc;
}

/** \brief Get player rocket.
 *
 * \return std::vector<Rocket*>* the vector containing the rocket.
 *
 */
std::vector<Rocket*>* Player::getRocket()
{
    return &rocket;
}

/** \brief The player update function.
 *
 * \return void
 *  Draws the sprite to the screen, handles the controller and updates the rocket.
 */
void Player::update()
{
    if(health != 0)
    {
        // Draw sprite at new position
        sprite->draw(int(position.x()), int(position.y()));

        // Controlling keys
        handleController();

        // Update spell
        if(!rocket.empty())
            rocket.back()->update();
    }
}

Vec2* Player::getPosition()
{
    return &position;
}

/** \brief Handles the controller
 *
 * \return void
 *  Calculates the movement speed, handles the move and fire keys.
 */
void Player::handleController()
{
    // Calculating the movement speed
    float newTime = system->getElapsedTime();
    float move = (newTime - lastTime) * 160.0f;
    lastTime = newTime;

    IDiceInvaders::KeyStatus keys;
    system->getKeyStatus(keys);

    // Checking if moving to the right and shooting
    if(keys.right && position.x() < 600 && keys.fire && rocket.empty())
    {
        position.moveX(move);
        rocket.push_back(new Rocket(system));
        rocket.back()->shoot(position.x(), position.y());
    }

    // Checking if moving to the left and shooting
    else if(keys.left && position.x() > 10 && keys.fire && rocket.empty())
    {
        position.moveX(-move);
        rocket.push_back(new Rocket(system));
        rocket.back()->shoot(position.x(), position.y());
    }

    // Checking if moving to the right
    else if (keys.right && position.x() < 600)
        position.moveX(move);

    // Checking if moving to the left
    else if (keys.left && position.x() > 10)
        position.moveX(-move);

    // Checking if shooting
    else if (keys.fire && rocket.empty())
    {
        rocket.push_back(new Rocket(system));
        rocket.back()->shoot(position.x(), position.y());
    }
}
