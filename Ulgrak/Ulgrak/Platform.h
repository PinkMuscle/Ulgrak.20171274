#ifndef Platfrom_h
#define Platform_h
#include "GameObject.h"

class Platform : public GameObject
{
public:
    Platform(const LoaderParams& pParams);
    virtual void Draw();
    virtual void Update();
    virtual void Clean();
};

#endif