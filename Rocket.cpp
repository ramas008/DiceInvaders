#include "Rocket.h"

Rocket::Rocket(IDiceInvaders* sys)
{
    system = sys;
    sprite = system->createSprite("data/rocket.bmp");
    lastTime = system->getElapsedTime();
}

Rocket::~Rocket()
{

}

void Rocket::shoot(float hPosition, float vPosition)
{
    position = Vec2(hPosition, vPosition);
}

void Rocket::update()
{
    // Draw sprite at new position
    sprite->draw(int(position.x()), int(position.y())-20);

    // Calculating speed
    float newTime = system->getElapsedTime();
    float move = (newTime - lastTime) * 360.0f;
    lastTime = newTime;

    position.moveY(-move);
}

Vec2 Rocket::getPosition()
{
    return position;
}

