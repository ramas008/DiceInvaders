#include "Rocket.h"

Rocket::Rocket(IDiceInvaders* sys)
{
    system = sys;
    sprite = system->createSprite("data/rocket.bmp");
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

    position.moveY(-0.02f);
}

Vec2* Rocket::getPosition()
{
    return &position;
}

