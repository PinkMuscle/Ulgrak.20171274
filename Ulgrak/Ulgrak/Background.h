#ifndef Background_h
#define Background_h
#include "GameObject.h"

class Background : public GameObject
{
public:
    Background(const LoaderParams& pParams);
    virtual void Draw();
    virtual void Update();
};

#endif