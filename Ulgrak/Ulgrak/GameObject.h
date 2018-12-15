#ifndef SDLGameObject_h
#define SDLGameObject_h
#include "Vector2D.h"
#include "LoaderParams.h"
#include <SDL.h>
#include <string>

class GameObject
{
public:
    GameObject(const LoaderParams& pParams);
    virtual void Draw();
    virtual void Update();
    virtual void Clean();
    virtual void Destroy() { active = false; }

    Vector2D GetPosition() const { return position; }
    Vector2D GetVelocity() const { return velocity; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    float GetScale() const { return scale; }
    bool IsActive() const { return active; }

protected:
    Vector2D position;
    Vector2D velocity;
    int width;
    int height;
    int currentFrame;
    int currentRow;
    float scale;
    std::string textureID;

private:
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    bool active = true;
};

#endif