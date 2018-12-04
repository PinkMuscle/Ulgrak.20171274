#ifndef SDLGameObject_h
#define SDLGameObject_h
#include "GameObject.h"
#include "Vector2D.h"
#include "LoaderParams.h"
#include <SDL.h>
#include <string>

class SDLGameObject : public GameObject
{
public:
    SDLGameObject(const LoaderParams* pParams);
    virtual void Draw();
    virtual void Update();
    virtual void Clean() {}
    Vector2D GetPosition() const { return position; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

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