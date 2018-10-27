#ifndef Player_h
#define Player_h
#include "Game.h"
#include "Box.h"

class Player
{
public:
    Player();
    ~Player();

    void GetBoxes(Box** boxes, int num);
    void Move();
    void Render();

private:
    const float speed = 200;
    const float gravity = 2000;
    const float jumpHeight = 700;

    float x = 200;
    float y = 100;
    float xvel = 0;
    float yvel = 0;
    int jump = 0;

    int boxNum;
    Box** boxes;

    SDL_Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect dstRect;

    bool Collision();
    bool isOnPlatform();


    bool test;
};

#endif