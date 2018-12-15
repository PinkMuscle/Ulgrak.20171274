#ifndef Explosion_h
#define Explosion_h
#include "GameObject.h"

class Explosion : public GameObject
{
public:
    Explosion(const LoaderParams& pParams);
    virtual void Draw();
    virtual void Update();
    virtual void Clean();

private:
    Uint32 nextFrameTime;
    const unsigned int frameSpeed;
};

#endif