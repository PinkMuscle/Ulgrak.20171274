#ifndef Texturemanager_h
#define Texturemanager_h
#include "Game.h"

class TextureManager
{
public:
    static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* renderer);
};

#endif