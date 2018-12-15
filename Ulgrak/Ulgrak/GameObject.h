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
    virtual void Destroy() { active = false; }

    Vector2D GetPosition() const { return position; }
    Vector2D GetVelocity() const { return velocity; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    float GetScale() const { return scale; }
    std::string GetTag() const { return tag; }
    SDL_RendererFlip GetFlip() const { return flip; }
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
    std::string tag;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

private:
    bool active = true;
};

#endif