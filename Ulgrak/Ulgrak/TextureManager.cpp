#include "TextureManager.h"
#include "Game.h"
#include <SDL_image.h>

TextureManager* TextureManager::pInstance = nullptr;

bool TextureManager::Load(std::string fileName, std::string id)
{
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
    if (pTempSurface == 0)
    {
        return false;
    }
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), pTempSurface);
    SDL_FreeSurface(pTempSurface);

    if (pTexture != 0)
    {
        textureMap[id] = pTexture;
        return true;
    }

    return false;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, float scale, SDL_RendererFlip flip)
{
    Draw(id, x, y, width, height, scale, 0, flip);
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, float scale, double angle, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect dstRect;

    srcRect.x = 0;
    srcRect.y = 0;
    dstRect.x = x;
    dstRect.y = y;

    srcRect.w = width;
    srcRect.h = height;
    dstRect.w = int (width * scale);
    dstRect.h = int (height * scale);

    SDL_RenderCopyEx(Game::Instance()->GetRenderer(), textureMap[id], &srcRect, &dstRect, angle, 0, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, float scale, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect dstRect;

    srcRect.x = width * currentFrame;
    srcRect.y = height * currentRow;
    dstRect.x = x;
    dstRect.y = y;

    srcRect.w = width;
    srcRect.h = height;
    dstRect.w = int (width * scale);
    dstRect.h = int (height * scale);

    SDL_RenderCopyEx(Game::Instance()->GetRenderer(), textureMap[id], &srcRect, &dstRect, 0, 0, flip);
}

void TextureManager::ClearFromTextureMap(std::string id)
{
    SDL_DestroyTexture(textureMap[id]);
    textureMap.erase(id);
}