#ifndef TrasformComponent_h
#define TrasformComponent_h
#include "ECS.h"
#include "Vector2D.h"

class TransformComponent : Component
{
public:
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;

    void Init() override
    {
        velocity.Zero();
    }

    void Update() override
    {
        velocity += acceleration;
        position += velocity;
    }
};

#endif