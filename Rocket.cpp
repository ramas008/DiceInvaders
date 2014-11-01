#include "Rocket.h"
#include <iostream>

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
    //Draw sprite at new position
    sprite->draw(int(horizontalPosition), int(verticalPosition)-20);

    verticalPosition -= 0.02f;

}


float Rocket::getHorizontalPosition()
{
    return horizontalPosition;
}

float Rocket::getVerticalPosition()
{
    return verticalPosition;
}
