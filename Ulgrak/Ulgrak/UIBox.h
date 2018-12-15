#ifndef UIBox_h
#define UIBox_h
#include "GameObject.h"

class UIBox : public GameObject
{
public:
    UIBox(const LoaderParams& pParams);
    virtual void Draw();
    virtual void Update();
    virtual void Clean();
};

#endif