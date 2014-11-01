#include "Rocket.h"
#include <iostream>

Rocket::Rocket(IDiceInvaders* sys)
{
    system = sys;
    sprite = system->createSprite("data/rocket.bmp");
}

Rocket::~Rocket()
{
    //dtor

}

void Rocket::shoot(float hPosition, float vPosition)
{
    if(test)
    {
        horizontalPosition = hPosition;
        verticalPosition = vPosition;
        test = 0;
    }
}

void Rocket::update()
{
    //Draw sprite at new position
    sprite->draw(int(horizontalPosition), int(verticalPosition)-20);

    verticalPosition -= 0.02f;

    if(verticalPosition < 0)
        test = 1;
}

void Rocket::onHit()
{
    verticalPosition = -10;
    test = 1;
}

float Rocket::getHorizontalPosition()
{
    return horizontalPosition;
}

float Rocket::getVerticalPosition()
{
    return verticalPosition;
}
