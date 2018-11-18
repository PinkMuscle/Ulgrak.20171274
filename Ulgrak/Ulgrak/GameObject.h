#ifndef GameObject_h
#define GameObject_h
#include "Vector2D.h"
#include <string>

class LoaderParams;

class GameObject
{
public:
    GameObject(const LoaderParams* pParams);
    virtual void Draw();
    virtual void Update();
    virtual void Clean() {}

protected:
	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;
    int width;
    int height;
    int currentFrame;
    int currentRow;
    std::string textureID;
};

#endif