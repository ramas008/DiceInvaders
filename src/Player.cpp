#include "Player.h"
#include <cstdio>

/** \brief Constructor for Player class.
 *
 * \param sys IDiceInvaders* the game system.
 * \param pSprite ISprite* the player sprite.
 * \param rSprite ISprite* the player rocket sprite.
 * \param screenR Vec2 the screen resolution.
 *  Initialize health, score, starting position, rocket,
 *  screen resolution, game system and sprite.
 */
Player::Player(IDiceInvaders* sys, ISprite* pSprite, ISprite* rSprite, Vec2 screenR)
{
    health = 3;
    score = 0;
    position = Vec2(screenR.x()/2, screenR.y() - 100);
    rocket = NULL;
    screenRes = screenR;

    system = sys;
    playerSprite = pSprite;
    rocketSprite = rSprite;

    lastTime = system->getElapsedTime();
}

/** \brief Deconstructor for Player class.
 */
Player::~Player()
{
    if(hasRocket())
        delete rocket;
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

/** \brief The player update function.
 *
 * \return void
 *  Draws the sprite to the screen, handles the controller and updates the rocket.
 */
void Player::update()
{
    // Draw sprite at new position
    playerSprite->draw(int(position.x()), int(position.y()));

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
    if (keys.right && position.x() < screenRes.x() - 40)
        position.moveX(move);

    // Check if moving to the left
    if (keys.left && position.x() > 10)
        position.moveX(-move);

    // Check if shooting
    if (keys.fire && !hasRocket())
        rocket = new Rocket(system, rocketSprite, position);
}
