#ifndef Collision_h
#define Collision_h
#include "GameObject.h"
#include "Vector2D.h"

class Collision
{
public:
    static bool AABB(const GameObject& obj1, const GameObject& obj2)
    {
        if (obj1.GetPosition().GetX() <= obj2.GetPosition().GetX() + obj2.GetWidth() &&
            obj2.GetPosition().GetX() <= obj1.GetPosition().GetX() + obj1.GetWidth() &&
            obj1.GetPosition().GetY() <= obj2.GetPosition().GetY() + obj2.GetHeight() &&
            obj2.GetPosition().GetY() <= obj1.GetPosition().GetY() + obj1.GetHeight())
        {
            return true;
        }

        return false;
    }
};

#endif