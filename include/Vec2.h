#ifndef VEC2_H
#define VEC2_H

class Vec2
{
    public:
        Vec2() : xPosition(0.0f), yPosition(0.0f) {}
        Vec2(float x, float y) : xPosition(x), yPosition(y) {}

        Vec2 operator = (Vec2 pos)
        {
            xPosition = pos.x();
            yPosition = pos.y();
            return *this;
        }

        Vec2 moveX(float xPos)
        {
            xPosition += xPos;
            return *this;
        }

        Vec2 moveY(float yPos)
        {
            yPosition += yPos;
            return *this;
        }

        float x()
        {
            return xPosition;
        }

        float y()
        {
            return yPosition;
        }
    protected:
    private:
        float xPosition;
        float yPosition;
};

#endif // VEC2_H

