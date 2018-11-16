#ifndef Enemy_h
#define Enemy_h
#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:
    Enemy(const LoaderParams* pParams);
    virtual void Draw();
    virtual void Update();
    virtual void Clean();

private:
	void HandleInput();
};

#endif