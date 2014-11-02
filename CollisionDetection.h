#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include <vector>
#include "Enemy.h"
#include "Vec2.h"

class CollisionDetection
{
    public:
        static bool onHit(Vec2 position1, Vec2 position2);
        static bool isOutOfBounds(std::vector<Enemy*> e, unsigned int index);
    protected:
    private:
};

#endif // COLLISIONDETECTION_H
