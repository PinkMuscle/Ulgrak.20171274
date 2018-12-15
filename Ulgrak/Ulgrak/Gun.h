#ifndef Gun_h
#define Gun_h
#include "GameObject.h"
#include <vector>
#include <memory>

class Gun : GameObject
{
public:
    Gun(const LoaderParams& pParams, GameObject& player, std::vector<std::unique_ptr<GameObject>>& projectiles);
    virtual void Draw();
    virtual void Update();
    void Change(std::string tag);
    void Shot();

private:
    GameObject& player;
    std::vector<std::unique_ptr<GameObject>>& projectiles;
    int magazine;
    float damage;

    unsigned int fireRate;
    Uint32 nextFire;
};

#endif