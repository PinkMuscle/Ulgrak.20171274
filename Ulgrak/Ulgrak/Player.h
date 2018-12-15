#ifndef Player_h
#define Player_h
#include "GameObject.h"
#include <vector>
#include <memory>

class Player : public GameObject
{
public:
    Player(const LoaderParams& pParams, std::vector<std::unique_ptr<GameObject>>& platforms_,int id);
    virtual void Draw();
    virtual void Update();
    virtual void Clean();

private:
	void HandleInput();
    bool IsOverlapped();

    int playerID;
    std::vector<std::unique_ptr<GameObject>>& platforms;

    const float speed = 0.3f;
    bool onPlatform = false;
    bool prevButtonState = true;
    int jump;
};

#endif