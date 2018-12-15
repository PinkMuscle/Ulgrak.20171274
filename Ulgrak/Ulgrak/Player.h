#ifndef Player_h
#define Player_h
#include "GameObject.h"
#include "Gun.h"
#include <vector>
#include <memory>

class Player : public GameObject
{
public:
    Player(const LoaderParams& pParams, std::vector<std::unique_ptr<GameObject>>& platforms_);
    virtual void Draw();
    virtual void Update();
    void ChangeGun(std::string tag);

private:
	void HandleInput();

    std::vector<std::unique_ptr<GameObject>>& platforms;
    Gun gun;
    bool onPlatform = false;
    bool onHalfPlatform = false;
    bool prevButtonState = true;
    int jump;
    float oldY;
};

#endif