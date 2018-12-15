#ifndef Gun_h
#define Gun_h
#include "GameObject.h"

class Gun : GameObject
{
public:
    Gun(const LoaderParams& pParams, GameObject& player);
    virtual void Draw();
    virtual void Update();
    void Change(std::string tag);
    void Shot();

private:
    GameObject& player;
    int magazine;
    unsigned int fireRate;
    Uint32 nextFire;
};

#endif