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
    horizontalPosition = hPosition;
    verticalPosition = vPosition;
}

void Rocket::update()
{
    // Draw sprite at new position
    sprite->draw(int(horizontalPosition), int(verticalPosition)-20);
    position[0] = horizontalPosition;
    position[1] = verticalPosition;
    verticalPosition -= 0.02f;
}

float* Rocket::getPosition()
{
    return position;
}

