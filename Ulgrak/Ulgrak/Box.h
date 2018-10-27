#ifndef Box_h
#define Box_h
#include "Game.h"

class Box
{
public:
    Box() {}
    Box(int x, int y, int w, int h);
    ~Box() {}

    void Render();
    SDL_Rect GetRect();

private:
    int x = 0, y = 0;
    int w = 64, h = 64;

    SDL_Rect rect;
};

#endif