#include "CollisionDetection.h"

bool CollisionDetection::onHit(Vec2* position1, Vec2* position2)
{
        if(position2->x() > position1->x() - 15 &&
           position2->x() < position1->x() + 15 &&
           position2->y() > position1->y() - 15 &&
           position2->y() < position1->y() + 15)
        {
            return true;
        }
        return false;
}

bool CollisionDetection::isOutOfBounds(std::vector<Enemy*> e, unsigned int index)
{
    if(e.size()>index)
        return e[index]->outOfBounds()?true:isOutOfBounds(e,++index);

    return false;
}

