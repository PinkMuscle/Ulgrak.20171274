#ifndef GunItem_h
#define GunItem_h
#include "GameObject.h"

class GunItem : public GameObject
{
public:
    GunItem(const LoaderParams& pParams);
    virtual void Draw();
    virtual void Update();

private:
    Uint32 destoryTime;
};

#endif