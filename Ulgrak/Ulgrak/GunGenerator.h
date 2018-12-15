#ifndef GunGenerator_h
#define GunGenerator_h
#include "GameObject.h"
#include <vector>
#include <memory>

class GunGenerator : public GameObject
{
public:
    GunGenerator(const LoaderParams& pParams, std::vector<std::unique_ptr<GameObject>>& items_);
    virtual void Draw();
    virtual void Update();

private:
    std::vector<std::unique_ptr<GameObject>>& items;
    Uint32 destoryTime;
};

#endif