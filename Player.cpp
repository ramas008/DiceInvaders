#include "Player.h"
#include <cstdio>

/** \brief Constructor for Player class.
 *
 * \param sys IDiceInvaders* the game system.
 *  Initialize health, score, starting position, rocket, game system and sprite.
 */
Player::Player(IDiceInvaders* sys)
{
    health = 3;
    score = 0;
    position = Vec2(320, 480 - 100);
    rocket = NULL;

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

/** \brief Get player score.
 *
 * \return int the score.
 *
 */
int Player::getScore()
{
    return score;
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


/** \brief Get rocket position.
 *
 * \return Vec2 the position.
 *
 */
Vec2 Player::getRocketPosition()
{
    return rocket->getPosition();
}

/** \brief The player update function.
 *
 * \return void
 *  Draws the sprite to the screen, handles the controller and updates the rocket.
 */
void Player::update()
{
    // Draw sprite at new position
    sprite->draw(int(position.x()), int(position.y()));

    // Controlling keys
    handleController();

    // Update rocket
    if(hasRocket())
    {
        rocket->update();
        // Check if rocket went out of screen
        if(rocket->getPosition().y() < 0)
        {
            deleteRocket();
        }
    }
}

/** \brief Delete rocket.
 *
 * \return void
 *
 */
void Player::deleteRocket()
{
    delete rocket;
    rocket = NULL;
}

/** \brief Look if player rocket is in game.
 *
 * \return bool if player has the rocket or not.
 *
 */
bool Player::hasRocket()
{
    return rocket?true:false;
}

/** \brief Get player position.
 *
 * \return Vec2 the position.
 *
 */
Vec2 Player::getPosition()
{
    return position;
}

/** \brief Handles the controller
 *
 * \return void
 *  Calculates the movement speed, handles the move and fire keys.
 */
void Player::handleController()
{
    // Calculating movement speed
    float newTime = system->getElapsedTime();
    float move = (newTime - lastTime) * 160.0f;
    lastTime = newTime;

    IDiceInvaders::KeyStatus keys;
    system->getKeyStatus(keys);

    // Check if moving to the right
    if (keys.right && position.x() < 600)
        position.moveX(move);

    // Check if moving to the left
    if (keys.left && position.x() > 10)
        position.moveX(-move);

    // Check if shooting
    if (keys.fire && !hasRocket())
        rocket = new Rocket(system, position.x(), position.y());
}
