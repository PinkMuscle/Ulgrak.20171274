#ifndef UIBox_h
#define UIBox_h
#include "GameObject.h"

class UIBox : public GameObject
{
public:
    UIBox(const LoaderParams& pParams);
    UIBox(const LoaderParams& pParams, int frameSpeed, int frames);
    virtual void Draw();
    virtual void Update();

private:
    int frameSpeed;
    int frames;
};

#endif