#include "Box.h"

Box::Box(int x, int y, int w, int h)
{
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void Box::Render()
{
    SDL_RenderFillRect(Game::renderer, &rect);
}

SDL_Rect Box::GetRect()
{
    return rect;
}