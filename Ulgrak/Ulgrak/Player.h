#ifndef Player_h
#define Player_h
#include "GameObject.h"
#include "Gun.h"
#include <vector>
#include <memory>

class Player : public GameObject
{
public:
    Player(const LoaderParams& pParams, std::vector<std::unique_ptr<GameObject>>& platforms, std::vector<std::unique_ptr<GameObject>>& projectiles);
    virtual void Draw();
    virtual void Update();
    void ChangeGun(std::string tag);
    void Damaged(float vel);
    int GetLife() const { return life; }

private:
	void HandleInput();

    std::vector<std::unique_ptr<GameObject>>& platforms;
    Gun gun;
    bool onPlatform = false;
    bool onHalfPlatform = false;
    bool prevButtonState = true;
    int life = 3;
    int jump;
    float oldY;

    Uint32 nextWake = 0;
};

#endif