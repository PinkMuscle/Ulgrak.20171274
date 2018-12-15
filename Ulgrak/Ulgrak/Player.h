#ifndef Player_h
#define Player_h
#include "GameObject.h"

class Player : public GameObject
{
public:
    Player(const LoaderParams& pParams);
    virtual void Draw();
    virtual void Update();
    virtual void Clean();

private:
	void HandleInput();

    const float speed = 0.3f;
};

#endif