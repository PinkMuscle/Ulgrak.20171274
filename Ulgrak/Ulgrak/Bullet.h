#ifndef Bullet_h
#define Bullet_h
#include "GameObject.h"

class Bullet : public GameObject
{
public:
    Bullet(const LoaderParams& pParams, SDL_RendererFlip flip, float damage);
    virtual void Draw();
    virtual void Update();
    float GetDamage() const { return damage; }

private:
    float damage;
    Uint32 destoryTime;
};

#endif