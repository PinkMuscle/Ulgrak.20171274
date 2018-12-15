#ifndef Gun_h
#define Gun_h
#include "GameObject.h"

class Gun : public GameObject
{
public:
    Gun(const LoaderParams& pParams);
    virtual void Draw();
    virtual void Update();
};

#endif