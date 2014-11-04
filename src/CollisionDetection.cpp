#include "CollisionDetection.h"

/** \brief Check if two vectors are colliding.
 *
 * \param position1 Vec2 first vector.
 * \param position2 Vec2 second vector.
 * \return bool true if colliding and false if not.
 *
 */
bool CollisionDetection::isColliding(Vec2 position1, Vec2 position2)
{
    if(position2.x() > position1.x() - 15 &&
       position2.x() < position1.x() + 15 &&
       position2.y() > position1.y() - 15 &&
       position2.y() < position1.y() + 15)
       {
            return true;
       }

    return false;
}
