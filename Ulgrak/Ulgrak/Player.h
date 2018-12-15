#ifndef Player_h
#define Player_h
#include "GameObject.h"
#include <vector>
#include <memory>

class Player : public GameObject
{
public:
    Player(const LoaderParams& pParams, std::vector<std::unique_ptr<GameObject>>& platforms_);
    virtual void Draw();
    virtual void Update();
    virtual void Clean();

private:
	void HandleInput();

    std::vector<std::unique_ptr<GameObject>>& platforms;
    bool onPlatform = false;
    bool onHalfPlatform = false;
    bool prevButtonState = true;
    int jump;
    float oldY;
};

#endif