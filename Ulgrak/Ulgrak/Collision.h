#ifndef Collision_h
#define Collision_h
#include "GameObject.h"
#include "Vector2D.h"

class Collision
{
public:
    static bool AABB(GameObject* p1, GameObject* p2)
    {
        float leftA = p1->GetPosition().x;
        float rightA = p1->GetPosition().x + p1->GetWidth() * p1->GetScale();
        float topA = p1->GetPosition().y;
        float bottomA = p1->GetPosition().y + p1->GetHeight() * p1->GetScale();

        float leftB = p2->GetPosition().x;
        float rightB = p2->GetPosition().x + p2->GetWidth() * p2->GetScale();
        float topB = p2->GetPosition().y;
        float bottomB = p2->GetPosition().y + p2->GetHeight() * p2->GetScale();

        
        if (bottomA <= topB) { return false; }
        if (topA >= bottomB) { return false; }
        if (rightA <= leftB) { return false; }
        if (leftA >= rightB) { return false; }

        return true;
    }
};

#endif