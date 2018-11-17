#ifndef SDLGameObject_h
#define SDLGameObject_h
#include "GameObject.h"
#include "Vector2D.h"
#include <string>

class LoaderParams;

class SDLGameObject : public GameObject
{
public:
    SDLGameObject(const LoaderParams* pParams);
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