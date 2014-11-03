#include "Bomb.h"

Bomb::Bomb(IDiceInvaders* sys, float hPosition, float vPosition)
{
    position = Vec2(hPosition, vPosition);
    system = sys;
    sprite = system->createSprite("data/bomb.bmp");
    lastTime = system->getElapsedTime();
}

Bomb::~Bomb()
{

}

void Bomb::update()
{
    // Draw sprite at new position
    sprite->draw(int(position.x()), int(position.y())+20);

    // Calculating speed
    float newTime = system->getElapsedTime();
    float move = (newTime - lastTime) * 160.0f;
    lastTime = newTime;

    position.moveY(move);
}

Vec2 Bomb::getPosition()
{
    return position;
}
