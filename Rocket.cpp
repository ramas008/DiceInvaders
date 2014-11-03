#include "Rocket.h"

Rocket::Rocket(IDiceInvaders* sys, float hPosition, float vPosition)
{
    position = Vec2(hPosition, vPosition);
    system = sys;
    sprite = system->createSprite("data/rocket.bmp");
    lastTime = system->getElapsedTime();
}

Rocket::~Rocket()
{

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

